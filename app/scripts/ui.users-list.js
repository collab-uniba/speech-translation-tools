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
  flag.src = './images/flags/' + args.language.substring(3).toLowerCase() + '.png';
  flag.style = 'display: inline;';
  newPartecipantDIV.appendChild(flag);

  var typing = document.createElement('img');
  typing.id = args.userid + 'typing';
  typing.className = 'hide';
  typing.src = './images/glyphicons-269-keyboard-wireless.png';
  newPartecipantDIV.appendChild(typing);

  var speaking = document.createElement('img');
  speaking.id = args.userid + 'speaking';
  speaking.className = 'hide';
  speaking.src = './images/glyphicons-185-volume-up.png';
  newPartecipantDIV.appendChild(speaking);

  document.getElementById('partecipantsList').appendChild(newPartecipantDIV);
}

function removePartecipant(args){
  document.getElementById(args.userid).remove();
}


usersList.onclick = function() {
    var messageBoard = getElement('#messageboard');
    var partecipantsDIV = getElement('#partecipants');
    var partecipantsList = getElement('#partecipantsList');
    if (usersContainer.style.display === 'flex') {
        usersList.className = usersList.className.replace( / selected/g , '');
        usersContainer.style.display = 'none';
        document.getElementById('openList').innerHTML = _('openList');
        messageBoard.style.height = 'calc(100vh - 232px)';
        partecipantsDIV.style.height = 'calc(100vh - 232px)';
        partecipantsList.style.height = 'calc(100vh - 273px)';
    } else {
        usersList.className += ' selected';
        usersContainer.style.display = 'flex';
        document.getElementById('openList').innerHTML = _('closeList');
        messageBoard.style.height = '28vh';
        partecipantsDIV.style.height = '28vh';
        partecipantsList.style.height = 'calc(28vh - 41px)';
    }
    messageBoard.scrollTop = messageBoard.scrollHeight;
    partecipantsList.scrollTop = 0;
};
