var express = require("express");
var app = express();
var port = process.env.PORT || 12034;
var oneDay = 86400000;
var server;
var env = env = process.env.NODE_ENV || 'development';

var forceSsl = function (req, res, next) {
  if (req.headers['x-forwarded-proto'] === 'http') {
    return res.redirect(['https://', req.get('Host'), req.url].join(''));
  }
  return next();
};

if(env === 'production'){
  //force SSL on Heroku
  app.use(forceSsl);

  var http = require("http");
  process.env.PWD = process.cwd();

  app.use(express.static(process.env.PWD, { maxAge: oneDay }));
  server = http.createServer(app);
}else{
  var fs = require('fs');
  var https = require("https");

  var options = {
    cert: fs.readFileSync('keys/server.crt'),
    key: fs.readFileSync('keys/server.key')
  };

  app.use(express.static("./app", { maxAge: oneDay }));
  server = https.createServer(options, app);
}

server.listen(port, function() {
  console.log((new Date()) + ' Server is listening on port ' + port);
});

var WebSocketServer = require('websocket').server;
new WebSocketServer({
  httpServer: server,
  autoAcceptConnections: false
}).on('request', onRequest);
// shared stuff
var CHANNELS = { };
function onRequest(socket) {
  var origin = socket.origin + socket.resource;
  var websocket = socket.accept(null, origin);
  websocket.on('message', function(message) {
    if (message.type === 'utf8') {
      onMessage(JSON.parse(message.utf8Data), websocket);
    }
  });
  websocket.on('close', function() {
    truncateChannels(websocket);
  });
}
function onMessage(message, websocket) {
  if (message.checkPresence)
    checkPresence(message, websocket);
  else if (message.open)
    onOpen(message, websocket);
  else
    sendMessage(message, websocket);
}
function onOpen(message, websocket) {
  var channel = CHANNELS[message.channel];
  if (channel)
    CHANNELS[message.channel][channel.length] = websocket;
  else
    CHANNELS[message.channel] = [websocket];
}
function sendMessage(message, websocket) {
  message.data = JSON.stringify(message.data);
  var channel = CHANNELS[message.channel];
  if (!channel) {
    console.error('no such channel exists');
    return;
  }
  for (var i = 0; i < channel.length; i++) {
    if (channel[i] && channel[i] != websocket) {
      try {
        channel[i].sendUTF(message.data);
      } catch(e) {
      }
    }
  }
}
function checkPresence(message, websocket) {
  websocket.sendUTF(JSON.stringify({
    isChannelPresent: !!CHANNELS[message.channel]
  }));
}
function swapArray(arr) {
  var swapped = [],
    length = arr.length;
  for (var i = 0; i < length; i++) {
    if (arr[i])
      swapped[swapped.length] = arr[i];
  }
  return swapped;
}
function truncateChannels(websocket) {
  for (var channel in CHANNELS) {
    var _channel = CHANNELS[channel];
    for (var i = 0; i < _channel.length; i++) {
      if (_channel[i] == websocket)
        delete _channel[i];
    }
    CHANNELS[channel] = swapArray(_channel);
    if (CHANNELS && CHANNELS[channel] && !CHANNELS[channel].length)
      delete CHANNELS[channel];
  }
}

app.route("/api/tts").get(function(req,res){
  res.type('audio/mpeg');

  var text = req.query.q;
  var targetLanguage = req.query.tl;
  var request = require('request');
  var url = 'https://translate.google.pl/translate_tts?ie=UTF-8&q=' + text + '&tl=' + targetLanguage + '&total=1&idx=0&client=t&prev=input';
  request.get(url).pipe(res);
});

app.route("/api/bing").get(function(req,res){
  res.type('application/javascript'); //this is required for JSONP


  var MsTranslator = require('mstranslator');
  // Second parameter to constructor (true) indicates that
  // the token should be auto-generated.
  var client = new MsTranslator({
    client_id: 'tesi-tedone',
    client_secret: 'KslnC9dBCTulJSLLcxAVuwOl5L/UTAHd9mQ3DszUTAk='
  }, true);

  var params = {
    text: req.query.q,
    from: req.query.sl,
    to: req.query.tl
  };

  client.translate(params, function (err, data) {
    res.header('Content-type','application/json');
    res.header('Charset','utf8');
    res.send(req.query.callback + '('+ JSON.stringify(data) + ');');
  });
});
