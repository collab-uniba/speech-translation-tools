window.addEventListener("beforeunload", function (e) {
  var confirmationMessage = _('closeMessage');

  (e || window.event).returnValue = confirmationMessage;     // Gecko and Trident
  return confirmationMessage;                                // Gecko and WebKit
});

getElement('#saveLog').onclick = function(){
  saveLog();
};

function saveLog(){
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
    if(currentNode.className!=='new-message'){
      //user message
      var userMessage = currentNode.children[1];
      message.push(userMessage.firstChild.innerHTML); //sender

      if(currentNode.children.length>2){ //a translated message has 3 children
        var originalMessage = currentNode.children[2];
        message.push(originalMessage.children[1].innerHTML); //original message
        message.push(userMessage.children[2].innerHTML); //translated message
      }else{
        var originalMessage = currentNode.children[1];
        message.push(originalMessage.children[1].innerHTML); //original message
        message.push(''); //empty message
      }
    }else{
      //system message
      message.push('system'); //the sender is the system
      message.push(currentNode.children[1].firstChild.innerHTML); //system message
      message.push(''); //empty value
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
