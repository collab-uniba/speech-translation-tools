var rtcMultiConnection = new RTCMultiConnection();

rtcMultiConnection.session = { data: true };

rtcMultiConnection.sdpConstraints.mandatory = {
    OfferToReceiveAudio: true,
    OfferToReceiveVideo: true
};

// using websockets for signaling!
rtcMultiConnection.openSignalingChannel = function(config) {
    config.channel = config.channel || this.channel;
    var websocket = new WebSocket(SIGNALING_SERVER);
    websocket.channel = config.channel;
    websocket.onopen = function() {
        websocket.push(JSON.stringify({
            open: true,
            channel: config.channel
        }));
        if (config.callback)
            config.callback(websocket);
    };
    websocket.onmessage = function(event) {
        config.onmessage(JSON.parse(event.data));
    };
    websocket.push = websocket.send;
    websocket.send = function(data) {
        if (websocket.readyState != 1) {
                    return setTimeout(function() {
                        websocket.send(data);
                    }, 1000);
        }

        websocket.push(JSON.stringify({
            data: data,
            channel: config.channel
        }));
    };
};

rtcMultiConnection.customStreams = { };

/*
// http://www.rtcmulticonnection.org/docs/fakeDataChannels/
rtcMultiConnection.fakeDataChannels = true;
if(rtcMultiConnection.UA.Firefox) {
rtcMultiConnection.session.data = true;
}
*/

rtcMultiConnection.autoTranslateText = false;

//this is fired when another user join the room
rtcMultiConnection.onopen = function(e) {
    getElement('#allow-webcam').disabled = false;
    getElement('#allow-mic').disabled = false;

    addSysMessage({
        header: e.extra.username,
        message: _('connectionOpen') + ' ' + e.extra.username + '.',
        userinfo: getUserinfo(rtcMultiConnection.blobURLs[rtcMultiConnection.userid], 'images/info.png'),
        color: e.extra.color
    });

    addPartecipant({
      username: e.extra.username,
      userid: e.userid,
      color: e.extra.color,
      language: e.extra.language
    });

    numbersOfUsers.innerHTML = parseInt(numbersOfUsers.innerHTML) + 1;
};

function whoIsSpeaking(event){
  var userSpeaking = document.getElementById(event.userid + 'speaking');
  if (event.data.speaking) {
    userSpeaking.className = 'who-is-speaking';
    return;
  }

  if (event.data.stoppedSpeaking) {
    userSpeaking.className = 'hide';
    return;
  }

  userSpeaking.className = 'hide';
}

rtcMultiConnection.onmessage = function(e) {
  if(e.data.typing || e.data.stoppedTyping) {
    var whoIsTyping = document.getElementById(e.userid + 'typing');
    if (e.data.typing) {
      whoIsTyping.className = 'who-is-typing';
      return;
    }

    if (e.data.stoppedTyping) {
      whoIsTyping.className = 'hide';
      return;
    }

    whoIsTyping.className = 'hide';
  }
  else if(e.data.speaking || e.data.stoppedSpeaking){
    whoIsSpeaking(e);
    return;
  }

  //check if the sender and the receiver speak the same language. In this case, if
  //the sent message is transcribed (and not sent using the text chat) it is discarded
  if(e.extra.language===rtcMultiConnection.extra.language && e.data.transcribed){
    //nothing to do
  }else{
    //translate the incoming message if the message language is different from the user language
    //or if the user choises to translate also text messages (default choice)
    var autoTextTranslation = getElement('#autoTextTranslation').checked;
    if(e.extra.language===rtcMultiConnection.extra.language || (!autoTextTranslation && !e.data.transcribed)) {
      addNewMessage({
        header: e.extra.username,
        message: e.data.message,
        userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
        color: e.extra.color
      });

      document.title = e.data.message;
    }
    else {

      var engine = getElement('#MTengine').value;

      if (engine === '0') {

        //Google translator
        var translator = new Translator();
        translator.translateLanguage(e.data.message, {
          from: e.extra.language.substring(0, 2),
          to: rtcMultiConnection.extra.language.substring(0, 2),
          api_key: 'AIzaSyBADiOrgX7ov4A5r6q23o6DE782QNnbrN4', // use your own key
          callback: function (translatedText) {
            addNewMessage({
              header: e.extra.username,
              message: e.data.message,
              userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
              color: e.extra.color,
              translated: translatedText,
              lastMessageUUID: Math.round(Math.random() * 9999) + Date.now()
            });

            document.title = translatedText;
          }
        });
      }
      else {
        //Microsoft Translator
        var bingAPIpath = SERVER_PATH + '/api/bing?callback=?';
        $.ajax({
          url: bingAPIpath,
          dataType: 'jsonp',
          data: 'q=' + e.data.message + '&tl=' + rtcMultiConnection.extra.language + '&sl=' + e.extra.language,
          jsonp: 'callback',
          success: function (data) {
            addNewMessage({
              header: e.extra.username,
              message: e.data.message,
              userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
              color: e.extra.color,
              translated: data,
              lastMessageUUID: Math.round(Math.random() * 9999) + Date.now()
            });

            document.title = data;
          },
          error: function () {
            console.log('Bing Translator error!!');
            alert('Error');
          }
        });
      }
    }
  }
};

var sessions = { };
rtcMultiConnection.onNewSession = function(session) {
    if (sessions[session.sessionid]) return;
    sessions[session.sessionid] = session;

    session.join();

    addSysMessage({
        header: session.extra.username,
        message: _('makingHandshake'),
        userinfo: '<img src="images/action-needed.png">',
        color: session.extra.color
    });
};

rtcMultiConnection.onRequest = function(request) {
    rtcMultiConnection.accept(request);
    addSysMessage({
        header: _('newPartecipant'),
        message: _('partecipantFound') + ' ' + request.extra.username + ' ( ' + request.userid + ' )...',
        userinfo: '<img src="images/action-needed.png">',
        color: request.extra.color
    });
};

rtcMultiConnection.onCustomMessage = function(message) {
    if (message.hasCamera) {
        var msg = message.extra.username + ' ' + _('enabledWebcam') + ' <button id="preview"> ' + _('preview') + '</button> ---- <button id="share-your-cam">' + _('shareWebcam') + '</button>';

        addSysMessage({
            header: message.extra.username,
            message: msg,
            userinfo: '<img src="images/action-needed.png">',
            color: message.extra.color,
            callback: function(div) {
                div.querySelector('#preview').onclick = function() {
                    this.disabled = true;

                    message.session.oneway = true;
                    rtcMultiConnection.sendMessage({
                        renegotiate: true,
                        streamid: message.streamid,
                        session: message.session
                    });
                    if(getElement('.users-container').style.display === 'none')
                      getElement('#openList').click();
                };

                div.querySelector('#share-your-cam').onclick = function() {
                    this.disabled = true;
                    getElement('#allow-webcam').disabled = true;
                    getElement('#allow-webcam').className = 'hide';
                    getElement('#close-webcam').className = 'btn-default icon img-rounded';
                    getElement('#close-webcam').disabled = false;
                    getElement('#allow-mic').disabled = true;

                    if (!message.hasScreen) {
                        session = { audio: true, video: true };

                        rtcMultiConnection.captureUserMedia(function(stream) {
                            rtcMultiConnection.renegotiatedSessions[JSON.stringify(session)] = {
                                session: session,
                                stream: stream
                            };

                            rtcMultiConnection.peers[message.userid].peer.connection.addStream(stream);
                            div.querySelector('#preview').onclick();
                        }, session);
                    }
                };
            }
        });
    }

    if (message.hasMic) {
        addSysMessage({
            header: message.extra.username,
            message: message.extra.username + ' ' + _('enabledMicrophone') + ' <button id="listen">' + _('listen') + '</button> ---- <button id="share-your-mic">' + _('shareMic') + '</button>',
            userinfo: '<img src="images/action-needed.png">',
            color: message.extra.color,
            callback: function(div) {
                div.querySelector('#listen').onclick = function() {
                    this.disabled = true;
                    message.session.oneway = true;
                    rtcMultiConnection.sendMessage({
                        renegotiate: true,
                        streamid: message.streamid,
                        session: message.session
                    });
                };

                div.querySelector('#share-your-mic').onclick = function() {
                    this.disabled = true;
                    getElement('#allow-mic').disabled = true;
                    getElement('#allow-mic').className = 'hide';
                    getElement('#close-mic').className = 'btn-default icon img-rounded';
                    getElement('#close-mic').disabled = false;

                    var session = { audio: true };

                    rtcMultiConnection.captureUserMedia(function(stream) {
                        rtcMultiConnection.renegotiatedSessions[JSON.stringify(session)] = {
                            session: session,
                            stream: stream
                        };

                        rtcMultiConnection.peers[message.userid].peer.connection.addStream(stream);
                        div.querySelector('#listen').onclick();
                    }, session);
                };
            }
        });
    }

    if (message.renegotiate) {
        var customStream = rtcMultiConnection.customStreams[message.streamid];
        if (customStream) {
            rtcMultiConnection.peers[message.userid].renegotiate(customStream, message.session);
        }
    }
};


rtcMultiConnection.blobURLs = { };
rtcMultiConnection.onstream = function(e) {
    if (e.stream.getVideoTracks().length) {
        rtcMultiConnection.blobURLs[e.userid] = e.blobURL;
        /*
        if( document.getElementById(e.userid) ) {
            document.getElementById(e.userid).muted = true;
        }
        */
        addSysMessage({
            header: e.extra.username,
            message: e.extra.username + ' ' + _('enabledWebcam'),
            userinfo: '<video id="' + e.userid + '" src="' + URL.createObjectURL(e.stream) + '" autoplay muted=true volume=0></video>',
            color: e.extra.color
        });
    } else {
        addSysMessage({
            header: e.extra.username,
            message: e.extra.username + ' ' + _('enabledMicrophone'),
            userinfo: '<audio src="' + URL.createObjectURL(e.stream) + '" controls muted=true volume=0></audio>',
            color: e.extra.color
        });
    }

    var container = document.createElement('div');
    container.style.height = '100%';
    container.style.padding = '5px';
    usersContainer.appendChild(container);
    var media = document.createElement('div');
    media.style.height = 'calc(100% - 30px)';
    if(!e.stream.getVideoTracks().length){
      media.style.border = '1px solid';
      var audioText = document.createElement('p');
      audioText.innerHTML = _('audioText');
      audioText.className = 'audioText';
      media.appendChild(audioText);
    }

    media.appendChild(e.mediaElement);
    container.appendChild(media);
    var name = document.createElement('p');
    name.innerHTML = e.extra.username;
    if(e.userid == rtcMultiConnection.userid){
      container.id = 'media' + rtcMultiConnection.userid;
      name.style.color = 'forestgreen';
    }
    else{
      container.id = 'media' + e.userid;
      name.style.color = e.extra.color;
    }

    name.style.textAlign = 'center';
    container.appendChild(name);
};

rtcMultiConnection.sendMessage = function(message) {
    message.userid = rtcMultiConnection.userid;
    message.extra = rtcMultiConnection.extra;
    rtcMultiConnection.sendCustomMessage(message);
};

rtcMultiConnection.onstreamended = function(e) {
  var element = getElement('#media'+ e.userid);
  if(element)
    element.parentNode.removeChild(element);

  if(e.isVideo)
    addSysMessage({
        message: e.extra.username + ' ' + _('disabledWebcam'),
    });
  else
    addSysMessage({
        message: e.extra.username + ' ' + _('disabledMicrophone'),
    });

};

rtcMultiConnection.onclose = rtcMultiConnection.onleave = function(event) {
    addSysMessage({
        header: event.extra.username,
        message: event.extra.username + ' left the room.',
        userinfo: getUserinfo(rtcMultiConnection.blobURLs[event.userid], 'images/info.png'),
        color: event.extra.color
    });

    removePartecipant({userid: event.userid});
    numbersOfUsers.innerHTML = parseInt(numbersOfUsers.innerHTML) - 1;

};
