// window.onbeforeunload = function(e){
// 	if(confirm('Are you nuts? Do you really want to leave me?')){
// 		return 'OK, Good Bye then';
// 	}
// 	else {
// 		e = e || event;
// 		if(e.preventDefault){e.preventDefault();}
// 		e.returnValue = false;
// 		return 'I said, "Are you nuts? Do you really want to leave me?"';
// 	}
// }

window.addEventListener("beforeunload", function (e) {
  var confirmationMessage = "\o/";

  (e || window.event).returnValue = confirmationMessage;     // Gecko and Trident
  return confirmationMessage;                                // Gecko and WebKit
});

function saveLog(){
  // var content = [['1st title', '2nd title', '3rd title', '4th title'], ['a a a', 'bb\nb', 'cc,c', 'dd"d'], ['www', 'xxx', 'yyy', 'zzz']];
  var content = getMessages();
  var result = generateCSV(content);
  exportCSV(result);
}

//retrieve messages from the messageboard
//and transform them into an array
function getMessages(){
  var content=[];

  var messageboard = getElement('#messageboard');
  var nodes= messageboard.children;
  for(i=0;i<nodes.length;i++){
    var message=[];
    var currentNode = messageboard.children[i];
    message.push(currentNode.firstChild.innerHTML); //timestamp
    if(currentNode.className==='user-activity'){
      //user message
      var message = currentNode.children[0];
      message.push(message.firstChild.innerHTML); //sender

      if(currentNode.children.length>1) //a translated message has 2 children
        message.push(message.children[2].innerHTML); //translated message

      var originalMessage = currentNode.children[1];
      message.push(originalMessage.children[1].innerHTML); //original message
    }else{
      //system message
      message.push('system'); //the sender is the system
      message.push(currentNode.firstChild.firstChild.innerHTML); //system message
    }

    content.push(message)
  }
  return content;
}

function generateCSV(content){
  var finalVal = 'TIMESTAMP,SENDER,ORIGINAL TEXT,TRANSLATED TEXT\n'; //header

  for (var i = 0; i < content.length; i++) {
    var value = content[i];

    for (var j = 0; j < value.length; j++) {
      var innerValue = value[j];
      var result = innerValue.replace(/"/g, '""');
      if (result.search(/("|,|\n)/g) >= 0)
        result = '"' + result + '"';
      if (j > 0)
        finalVal += ',';
        finalVal += result;
    }

    finalVal += '\n';
  }
  return finalVal;
}

function exportCSV(finalVal){
  var link = document.createElement('a');
  link.setAttribute('download', 'test.csv');
  link.setAttribute('href', 'data:text/csv;charset=utf-8,' + encodeURIComponent(finalVal));
  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);
}
