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

  var userActivityDIV = document.createElement('div');
  userActivityDIV.className = 'system-activity';

  var p = document.createElement('p');
  p.className = 'message';
  p.style = 'display: inline;width: 60%;margin: 0 auto;color: #FFFFFF;';
  p.innerHTML = args.message;
  userActivityDIV.appendChild(p);

  newMessageDIV.appendChild(userActivityDIV);

  var messageboard = document.getElementById("messageboard");
  messageboard.appendChild(newMessageDIV);
  messageboard.scrollTop = messageboard.scrollHeight;


  if (args.callback) {
    args.callback(newMessageDIV);
  }

  document.querySelector('#message-sound').play();
}


function addNewMessage(args) {
    var newMessageDIV = document.createElement('div');

    if(args.translated) {

      var translatedMessage = document.createElement('div');

      var username = document.createElement('p');
      username.innerHTML = args.header;
      username.style.color = args.color;
      translatedMessage.appendChild(username);

      var playTTS = document.createElement('img');
      playTTS.src = './images/play.png';
      playTTS.className = 'playIcon floatRight';
      //playTTS.onclick = textToSpeech(args.translated);
      playTTS.onclick = function() {textToSpeech(args.translated);};
      translatedMessage.appendChild(playTTS);

      var translatedText = document.createElement('p');
      translatedText.innerHTML = args.translated;
      translatedText.className = 'message';
      translatedMessage.appendChild(translatedText);

      var timestamp = document.createElement('p');
      timestamp.innerHTML = getTimeNow();
      timestamp.className = 'floatRight';
      translatedMessage.appendChild(timestamp);

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
      label.innerHTML = 'Testo originale';
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
      var timestamp = document.createElement('p');
      timestamp.innerHTML = getTimeNow();
      timestamp.className = 'floatRight';
      originalMessage.appendChild(timestamp);
    }

    var originalAudio = document.createElement('audio');
    //TODO: link al file audio
    originalMessage.appendChild(originalAudio);

    newMessageDIV.appendChild(originalMessage);



    //if the message is from the user itself, use another class
    if(args.source == rtcMultiConnection.userid)
      newMessageDIV.className = 'user-activity-me';
    else
      newMessageDIV.className = 'user-activity';


    var messageboard = document.getElementById("messageboard");
    messageboard.appendChild(newMessageDIV);
    messageboard.scrollTop = messageboard.scrollHeight;


    if (args.callback) {
        args.callback(newMessageDIV);
    }

    document.querySelector('#message-sound').play();
}

function textToSpeech(textToPlay){
  var translator = new Translator();
  translator.speakTextUsingRobot(textToPlay, {
    workerPath: location.origin + '/scripts/Robot-Speaker.js',
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
};


window.onload = function() {


  var yourName = localStorage.getItem('user-name');
  var roomName = localStorage.getItem('room-name');
  var language = localStorage.getItem('language');

  //check if the user is logged in, otherwise redirect him to the login page
  if(roomName===null || yourName===null)
    window.location.replace("./index.html");

  var userNameLabel = document.getElementById("username");
  userNameLabel.innerHTML = "Your username is: " + yourName;

  var btnLogout = document.getElementById("logout");
  btnLogout.onclick = function(){
    localStorage.clear()();
  };

    var username = yourName || 'Anonymous';

    rtcMultiConnection.extra = {
        username: username,
        color: getRandomColor(),
        language: language
    };

    addSysMessage({
        header: username,
        message: 'Searching for existing rooms...',
        userinfo: '<img src="images/action-needed.png">'
    });

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
                message: 'No room found. Creating new room...',
                userinfo: '<img src="images/action-needed.png">'
            });

          rtcMultiConnection.open();
        } else {
            addSysMessage({
                header: username,
                message: 'Room found. Joining the room...',
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

var numberOfKeys = 0;
getElement('.main-input-box textarea').onkeyup = function(e) {
    numberOfKeys++;
    if (numberOfKeys > 3) numberOfKeys = 0;

    if (!numberOfKeys) {
        if (e.keyCode == 8) {
            return rtcMultiConnection.send({
                stoppedTyping: true
            });
        }

        rtcMultiConnection.send({
            typing: true
        });
    }

    if (isShiftKeyPressed) {
        if (e.keyCode == 16) {
            isShiftKeyPressed = false;
        }
        return;
    }


    if (e.keyCode != 13) return;

    addNewMessage({
        header: rtcMultiConnection.extra.username,
        message: this.value,
        userinfo: getUserinfo(rtcMultiConnection.blobURLs[rtcMultiConnection.userid], 'images/chat-message.png'),
        color: rtcMultiConnection.extra.color,
        source: rtcMultiConnection.userid
    });

    rtcMultiConnection.send(this.value);

    this.value = '';
};

getElement('#allow-webcam').onclick = function() {
    this.disabled = true;

    var session = { audio: true, video: true };

    rtcMultiConnection.captureUserMedia(function(stream) {
        var streamid = rtcMultiConnection.token();
        rtcMultiConnection.customStreams[streamid] = stream;

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
