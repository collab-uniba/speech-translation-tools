var yourName = localStorage.getItem('user-name');
var roomName = localStorage.getItem('room-name');
var language = localStorage.getItem('language');

//check if the user is logged in, otherwise redirect him to the login page
if(!roomName || !yourName || roomName==='' || yourName==='')
  window.location.replace('./index.html');

//set interface language
setTimeout(function(){
  document.webL10n.setLanguage(language);
  document.documentElement.lang = document.webL10n.getLanguage();
},500);

if(location.hostname==='localhost'){
  var SIGNALING_SERVER = 'wss://' + location.hostname + ':12034';
  var SERVER_PATH = location.protocol + '//' + location.hostname + ':12034';
}
else{
  //for Heroku
  var SIGNALING_SERVER = location.origin.replace(/^https/, 'wss');
  var SERVER_PATH = location.origin;
}

function getElement(selector) {
    return document.querySelector(selector);
}

var main = getElement('.main');

function getRandomColor() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.round(Math.random() * 15)];
    }
    return color;
}

function getTimeNow() {
  var d = new Date(),
    h = (d.getHours()<10?'0':'') + d.getHours(),
    m = (d.getMinutes()<10?'0':'') + d.getMinutes();
    return h + ':' + m;
}

function addSysMessage(args) {
  var newMessageDIV = document.createElement('div');
  newMessageDIV.className = 'new-message';

  var timestamp = document.createElement('p');
  timestamp.innerHTML = Date();
  timestamp.className ='hide';
  newMessageDIV.appendChild(timestamp);

  var userActivityDIV = document.createElement('div');
  userActivityDIV.className = 'system-activity img-rounded';

  var p = document.createElement('p');
  p.className = 'system-message';
  p.style = 'display: inline;width: 60%;margin: 0 auto;color: #FFFFFF;';
  p.innerHTML = args.message;
  userActivityDIV.appendChild(p);

  newMessageDIV.appendChild(userActivityDIV);

  var messageboard = document.getElementById('messageboard');
  messageboard.appendChild(newMessageDIV);
  messageboard.scrollTop = messageboard.scrollHeight;


  if (args.callback) {
    args.callback(newMessageDIV);
  }

  document.querySelector('#message-sound').play();
}


function addNewMessage(args) {
    var newMessageDIV = document.createElement('div');

    var timestamp = document.createElement('p');
    timestamp.innerHTML = Date();
    timestamp.className ='hide';
    newMessageDIV.appendChild(timestamp);

    if(args.translated) {

      var translatedMessage = document.createElement('div');

      var username = document.createElement('p');
      username.innerHTML = args.header;
      username.style.color = args.color;
      username.style.fontWeight = 'bold';
      translatedMessage.appendChild(username);

      var playTTS = document.createElement('img');
      playTTS.src = './images/play.png';
      playTTS.className = 'playIcon floatRight';
      if(getElement('#autoTTS').checked)
        textToSpeech(args.translated);

      playTTS.onclick = function() {textToSpeech(args.translated);};

      translatedMessage.appendChild(playTTS);

      var translatedText = document.createElement('p');
      translatedText.innerHTML = args.translated;
      translatedText.className = 'message';
      translatedMessage.appendChild(translatedText);

      var time = document.createElement('p');
      time.innerHTML = getTimeNow();
      time.className = 'floatRight';
      translatedMessage.appendChild(time);

      var expand = document.createElement('p');
      expand.innerHTML = '+';
      expand.onclick = function () {
        var origMessage = document.getElementById('originalMessage' + args.lastMessageUUID);
        if (origMessage.className === 'hide') {
          origMessage.className = 'show';
          expand.innerHTML = '-';
        }
        else {
          origMessage.className = 'hide';
          expand.innerHTML = '+';
        }
      };
      translatedMessage.appendChild(expand);

      newMessageDIV.appendChild(translatedMessage);

    }

    var originalMessage = document.createElement('div');

    if(args.translated) {
      originalMessage.className = 'hide';
      originalMessage.id = 'originalMessage' + args.lastMessageUUID;

      var label = document.createElement('p');
      label.innerHTML = _('originalText');
      originalMessage.appendChild(label);
    }else{
      var username = document.createElement('p');
      username.innerHTML = args.header;
      originalMessage.appendChild(username);
    }

    var originalText = document.createElement('p')
    originalText.innerHTML = args.message;
    originalText.className = 'message';
    originalMessage.appendChild(originalText);

    if(!args.translated){
      var time = document.createElement('p');
      time.innerHTML = getTimeNow();
      time.className = 'floatRightUp';
      originalMessage.appendChild(time);
    }

    var originalAudio = document.createElement('audio');
    //TODO: link to the audio file
    originalMessage.appendChild(originalAudio);

    newMessageDIV.appendChild(originalMessage);



    //if the message is from the user itself, use another class
    if(args.source == rtcMultiConnection.userid)
      newMessageDIV.className = 'user-activity-me img-rounded';
    else{
      newMessageDIV.className = 'user-activity img-rounded';
      newMessageDIV.style.borderColor = args.color;
    }


    var messageboard = document.getElementById('messageboard');
    messageboard.appendChild(newMessageDIV);
    messageboard.scrollTop = messageboard.scrollHeight;


    if (args.callback) {
        args.callback(newMessageDIV);
    }

    document.querySelector('#message-sound').play();
}

function textToSpeech(textToPlay){
  var translator = new Translator();
  var engine = getElement('#TTSengine').value;

  if(engine==='0')
    translator.speakTextUsingGoogleSpeaker({
      textToSpeak: textToPlay,
      targetLanguage: rtcMultiConnection.extra.language,
      callback: function (WAV_File) {
        var audio = document.createElement('audio');
        audio.src = WAV_File;
        audio.play();
      }
    });
  else if(engine==='1')
    translator.speakTextUsingMicrosoftSpeaker({
      textToSpeak: textToPlay,
      targetLanguage: rtcMultiConnection.extra.language,
      callback: function (WAV_File) {
        var audio = document.createElement('audio');
        audio.src = WAV_File;
        audio.play();
      }
    });
  else
    translator.speakTextUsingRobot(textToPlay, {
      workerPath: location.href.substring(0, location.href.lastIndexOf('/')) + '/scripts/Robot-Speaker.js',
      callback: function (WAV_File) {
        var audio = document.createElement('audio');
        audio.src = WAV_File;
        audio.play();
      },
      amplitude: 100,
      wordgap: 0,
      pitch: 50,
      speed: 175,
      onSpeakingEnd: function() {},
      onWorkerFileDownloadStart: function() {},
      onWorkerFileDownloadEnd: function() {}
    });
}


window.onload = function() {

  setTimeout(function() {
    var userNameLabel = document.getElementById('username');
    userNameLabel.innerHTML = _('usernameLabel') + ' ' + yourName;
  }, 500);

  var username = yourName || 'Anonymous';

  rtcMultiConnection.extra = {
    username: username,
    color: getRandomColor(),
    language: language
  };

  setTimeout(function() {
    addSysMessage({
      header: username,
      message: _('searchingRoom'),
      userinfo: '<img src="images/action-needed.png">'
    });
  },500);

  addPartecipant({
    username: username,
    userid: rtcMultiConnection.userid,
    color: '#000000',
    language: language
  });

  var roomid = roomName;
  rtcMultiConnection.channel = roomid;

  var websocket = new WebSocket(SIGNALING_SERVER);
  websocket.onmessage = function(event) {
    var data = JSON.parse(event.data);
    if (data.isChannelPresent == false) {
      addSysMessage({
        header: username,
        message: _('newRoom'),
        userinfo: '<img src="images/action-needed.png">'
      });

      rtcMultiConnection.open();
    } else {
      addSysMessage({
        header: username,
        message: _('roomFound'),
        userinfo: '<img src="images/action-needed.png">'
      });
      rtcMultiConnection.join(roomid);
    }
  };
  websocket.onopen = function() {
    websocket.send(JSON.stringify({
      checkPresence: true,
      channel: roomid
    }));
  };
};

function getUserinfo(blobURL, imageURL) {
    return blobURL ? '<video src="' + blobURL + '" autoplay controls></video>' : '<img src="' + imageURL + '">';
}

var isShiftKeyPressed = false;

getElement('.main-input-box textarea').onkeydown = function(e) {
    if (e.keyCode == 16) {
        isShiftKeyPressed = true;
    }
};

var timer;
var send = document.getElementById('sendText');
send.disabled = 'disabled';

getElement('#sendText').onclick = function(){
  var e = $.Event( "keyup", { keyCode: 13 } );
  $('#textArea').trigger(e);
};

getElement('.main-input-box textarea').onkeyup = function(e) {

  if(this.value.trim().length===0){
    send.disabled = 'disabled';
    this.value = '';
    return;
  }else{
    send.removeAttribute('disabled');
  }

  clearTimeout(timer);

  timer = setTimeout(function() { rtcMultiConnection.send({
    stoppedTyping: true
  }); }, 5000);

  if (this.value.length ===0) {
    rtcMultiConnection.send({stoppedTyping: true});
    return;
  }


  rtcMultiConnection.send({
    typing: true
  });


  if (isShiftKeyPressed) {
    //shift key
    if (e.keyCode == 16) {
      isShiftKeyPressed = false;
    }
    return;
  }

  //enter key
  if (e.keyCode != 13) return;

  var message = this.value.slice(0,-1); //remove enter key char from the string

  addNewMessage({
    header: rtcMultiConnection.extra.username,
    message: message,
    userinfo: getUserinfo(rtcMultiConnection.blobURLs[rtcMultiConnection.userid], 'images/chat-message.png'),
    color: rtcMultiConnection.extra.color,
    source: rtcMultiConnection.userid
  });

  rtcMultiConnection.send({message: message, transcribed: false});
  rtcMultiConnection.send({stoppedTyping: true});

  send.disabled = 'disabled';
  this.value = '';
};

getElement('#allow-webcam').onclick = function() {
    this.disabled = true;

    var session = { audio: true, video: true };

    rtcMultiConnection.captureUserMedia(function(stream) {
        var streamid = rtcMultiConnection.token();
        rtcMultiConnection.customStreams[streamid] = stream;

        speakingNotification(stream);

        rtcMultiConnection.sendMessage({
            hasCamera: true,
            streamid: streamid,
            session: session
        });
    }, session);
};

getElement('#allow-mic').onclick = function() {
    this.disabled = true;
    var session = { audio: true };

    rtcMultiConnection.captureUserMedia(function(stream) {
        var streamid = rtcMultiConnection.token();
        rtcMultiConnection.customStreams[streamid] = stream;

        speakingNotification(stream);

        rtcMultiConnection.sendMessage({
            hasMic: true,
            streamid: streamid,
            session: session
        });
    }, session);

  var translator = new Translator();
  translator.voiceToText(function (text) {


    addNewMessage({
      header: rtcMultiConnection.extra.username,
      message: text,
      source : rtcMultiConnection.userid
    });

    rtcMultiConnection.send({message: text, transcribed: true});

  }, rtcMultiConnection.extra.language);

};

function speakingNotification(audioStream){
  var options = {};
  var speechEvents = hark(audioStream, options);

  speechEvents.on('speaking', function() {
    rtcMultiConnection.send({
      speaking: true
    });
  });

  speechEvents.on('stopped_speaking', function() {
    rtcMultiConnection.send({
      stoppedSpeaking: true
    });
  });
}

getElement('#logout').onclick = function() {
  rtcMultiConnection.leave();
  localStorage.clear();
  window.location.replace('./index.html');
};
