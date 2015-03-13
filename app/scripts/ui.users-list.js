var usersList = getElement('#openList');
var numbersOfUsers = getElement('.numbers-of-users');

numbersOfUsers.innerHTML = 1;

var usersContainer = getElement('.users-container');

function addPartecipant(args){
  var newPartecipantDIV = document.createElement('div');
  newPartecipantDIV.id = args.userid;
  newPartecipantDIV.className = 'new-message';
  newPartecipantDIV.innerHTML = args.username;
  newPartecipantDIV.style.color = args.color;

  var flag = document.createElement('img');
  flag.className = 'flags';
  flag.src = "./images/flags/" + args.language.substring(3).toLowerCase() + ".png";
  flag.style = "display: inline;"
  newPartecipantDIV.appendChild(flag);

  var typing = document.createElement('img');
  typing.id = args.userid + 'typing';
  typing.className = 'hide';
  typing.src = "./images/glyphicons-269-keyboard-wireless.png";
  newPartecipantDIV.appendChild(typing);

  var speaking = document.createElement('img');
  speaking.id = args.userid + 'speaking';
  speaking.className = 'hide';
  speaking.src = "./images/glyphicons-185-volume-up.png";
  newPartecipantDIV.appendChild(speaking);

  document.getElementById('partecipants').appendChild(newPartecipantDIV);
}

function removePartecipant(args){
  var partecipantDIV = document.getElementById(args.userid).remove();
}


usersList.onclick = function() {
    if (usersList.className.indexOf('selected') != -1) {
        usersList.className = usersList.className.replace( / selected/g , '');
        usersContainer.style.display = 'none';
        document.getElementById('openList').innerHTML = "Show Video";
    } else {
        usersList.className += ' selected';
        usersContainer.style.display = 'block';
        document.getElementById('openList').innerHTML = "Hide Video";
    }
};
