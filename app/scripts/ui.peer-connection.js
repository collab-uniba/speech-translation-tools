var rtcMultiConnection = new RTCMultiConnection();

rtcMultiConnection.session = { data: true };

rtcMultiConnection.sdpConstraints.mandatory = {
    OfferToReceiveAudio: true,
    OfferToReceiveVideo: true
};

// using websockets for signaling!
//var SIGNALING_SERVER = location.origin.replace(/^http/, 'ws');  //enable this for Heroku
var SIGNALING_SERVER = 'ws://' + document.domain + ':12034';
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

/*var onMessageCallbacks = {};

var SIGNALING_SERVER = '/';
rtcMultiConnection.openSignalingChannel = function (config) {
  var channel = config.channel || this.channel;
  var sender = Math.round(Math.random() * 9999999999) + 9999999999;

  io.connect(SIGNALING_SERVER).emit('new-channel', {
    channel: channel,
    sender : sender
  });

  var socket = io.connect(SIGNALING_SERVER + channel);
  socket.channel = channel;

  socket.on('connect', function () {
    if (config.callback) config.callback(socket);
  });

  socket.send = function (message) {
    socket.emit('message', {
      sender: sender,
      data  : message
    });
  };

  socket.on('message', config.onmessage);
};

rtcMultiConnection.connect();*/


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
        message: 'Data connection is opened between you and ' + e.extra.username + '.',
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


rtcMultiConnection.onmessage = function(e) {
    var whoIsTyping = document.getElementById(e.userid).lastChild;
    if (e.data.typing) {
        whoIsTyping.innerHTML = ' is typing ...';
        return;
    }

    if (e.data.stoppedTyping) {
        whoIsTyping.innerHTML = '';
        return;
    }

    whoIsTyping.innerHTML = '';

    //translate the incoming message only if the message language is different from the user language
    //and it's not transcribed with the speech recognition
    if(e.extra.language===rtcMultiConnection.extra.language || !e.data.transcribed) {
      addNewMessage({
        header: e.extra.username,
        message: e.data,
        userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
        color: e.extra.color
      });

      document.title = e.data;
    }
    else{




/*      var websocket1 = new WebSocket(SIGNALING_SERVER);
      websocket1.channel = '1';
      websocket1.onopen = function() {
        websocket1.push(JSON.stringify({
          open: true,
          channel: '1'
        }));
*//*        if (config.callback)
          config.callback(websocket1);*//*
      };
      websocket1.push = websocket1.send;


  websocket1.send = function(data) {
    console.log('send');
    if (websocket1.readyState != 1) {
      return setTimeout(function() {
        websocket1.send(JSON.stringify({
            translate: true,
            channel: '1',
            from: e.extra.language,
            to: rtcMultiConnection.extra.language,
            text: e.data.message
          })
        );
      }, 1000);
    }

    websocket1.push(JSON.stringify({
      data: e.data.message,
      channel: '1'
    }));

      };

      websocket1.onmessage = function(event){
        alert('onmessage');
        addNewMessage({
          header: e.extra.username,
          message: e.data.message,
          userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
          color: e.extra.color,
          translated: JSON.parse(event.data)
        });
      };*/






      //Google translator
      var translator = new Translator();
      translator.translateLanguage(e.data.message, {
        from: e.extra.language.substring(0,2),
        to: rtcMultiConnection.extra.language.substring(0,2),
        api_key: 'AIzaSyAs8hCMuWBOOfOo3kbnUWqzuu10r1j1-io', // use your own key
        callback: function (translatedText) {
          addNewMessage({
            header: e.extra.username,
            message: e.data.message,
            userinfo: getUserinfo(rtcMultiConnection.blobURLs[e.userid], 'images/chat-message.png'),
            color: e.extra.color,
            translated: translatedText,
            lastMessageUUID:  Math.round(Math.random() * 999999999) + 9995000
          });

          document.title = translatedText;
        }
      });
    }

};

var sessions = { };
rtcMultiConnection.onNewSession = function(session) {
    if (sessions[session.sessionid]) return;
    sessions[session.sessionid] = session;

    session.join();

    addSysMessage({
        header: session.extra.username,
        message: 'Making handshake with room owner....!',
        userinfo: '<img src="images/action-needed.png">',
        color: session.extra.color
    });
};

rtcMultiConnection.onRequest = function(request) {
    rtcMultiConnection.accept(request);
    addSysMessage({
        header: 'New Participant',
        message: 'A participant found. Accepting request of ' + request.extra.username + ' ( ' + request.userid + ' )...',
        userinfo: '<img src="images/action-needed.png">',
        color: request.extra.color
    });
};

rtcMultiConnection.onCustomMessage = function(message) {
    if (message.hasCamera) {
        var msg = message.extra.username + ' enabled webcam. <button id="preview">Preview</button> ---- <button id="share-your-cam">Share Your Webcam</button>';

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
                };

                div.querySelector('#share-your-cam').onclick = function() {
                    this.disabled = true;

                    if (!message.hasScreen) {
                        session = { audio: true, video: true };

                        rtcMultiConnection.captureUserMedia(function(stream) {
                            rtcMultiConnection.renegotiatedSessions[JSON.stringify(session)] = {
                                session: session,
                                stream: stream
                            }

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
            message: message.extra.username + ' enabled microphone. <button id="listen">Listen</button> ---- <button id="share-your-mic">Share Your Mic</button>',
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

                    var session = { audio: true };

                    rtcMultiConnection.captureUserMedia(function(stream) {
                        rtcMultiConnection.renegotiatedSessions[JSON.stringify(session)] = {
                            session: session,
                            stream: stream
                        }

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
            message: e.extra.username + ' enabled webcam.',
            userinfo: '<video id="' + e.userid + '" src="' + URL.createObjectURL(e.stream) + '" autoplay muted=true volume=0></vide>',
            color: e.extra.color
        });
    } else {
        addSysMessage({
            header: e.extra.username,
            message: e.extra.username + ' enabled microphone.',
            userinfo: '<audio src="' + URL.createObjectURL(e.stream) + '" controls muted=true volume=0></vide>',
            color: e.extra.color
        });
    }
    usersContainer.appendChild(e.mediaElement);
};

rtcMultiConnection.sendMessage = function(message) {
    message.userid = rtcMultiConnection.userid;
    message.extra = rtcMultiConnection.extra;
    rtcMultiConnection.sendCustomMessage(message);
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
