$( document ).ready(function() {

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
  };

});
