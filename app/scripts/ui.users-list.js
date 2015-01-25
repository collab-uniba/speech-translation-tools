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

  var typing = document.createElement('p');
  typing.className = 'who-is-typing';
  typing.style = "display: inline;"
  newPartecipantDIV.appendChild(typing);

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
