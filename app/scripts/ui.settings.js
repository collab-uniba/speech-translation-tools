getElement('#settingsButton').onclick = function() {
  localStorage.clear();
  var autoTTS = document.getElementById('autoTTS');
  var TTSengine = document.getElementById('TTSengine');
  var MTengine = document.getElementById('MTengine');

  localStorage.setItem('autoTTS', autoTTS.checked);
  localStorage.setItem('TTSengine', TTSengine.value);
  localStorage.setItem('MTengine', MTengine.value);
};

getElement('#discard').onclick = getElement('#discardX').onclick = function() {
  document.getElementById('autoTTS').checked = JSON.parse(localStorage.getItem('autoTTS'));
  document.getElementById('TTSengine').value =localStorage.getItem('TTSengine');
  document.getElementById('MTengine').value = localStorage.getItem('MTengine');
};

getElement('#TTSengine').onchange = function() {
  var TTSengine = document.getElementById('TTSengine');
  var label = document.getElementById('char100');
  if(TTSengine.value==="0")
    label.className = "control-label";
  else
    label.className = "control-label hide";
};
