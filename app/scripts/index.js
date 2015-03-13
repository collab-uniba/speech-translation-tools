setTimeout(function(){
  document.webL10n.setLanguage('en-US');
  document.documentElement.lang = document.webL10n.getLanguage();
},1000);

var language = document.getElementById('language');

language.onchange = function() {
  document.webL10n.setLanguage(language.value);
  document.documentElement.lang = document.webL10n.getLanguage();
};

//store username, language and room name
var loginButton = document.getElementById('login');
localStorage.clear();

loginButton.onclick = function(){
  var roomName = document.getElementById('room');
  var userName = document.getElementById('username');
  var language = document.getElementById('language');

  localStorage.setItem('room-name', roomName.value);
  localStorage.setItem('user-name', userName.value);
  localStorage.setItem('language', language.value);

  window.location.replace('./app.html');
  return false;
};
