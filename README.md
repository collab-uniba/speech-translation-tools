TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Bing Translator, speech conversion by Nuance Dragon.
The tool is intended to support multilanguage group communcation and collaboration. TeamTranslate is available under MPL license.

Guida: http://liuxingguang.blogspot.it/2014/02/using-wxwidgets-30-in-microsoft-visual.html

Per compilare correttamente la soluzione in visual studio bisogna seguire queste istruzioni:

1. Installare Microsoft Visual Studio 2013
2. Scaricare e installare le WxWidgets 2.9.3. la versione windows installer. Installare in una path senza spazi ad esempio "C:\WxWidgets 2.9.3" o "D:\WxWidgets 2.9.3"
3. Aggiungere una nuova variabile di sistema di nome WXWIN, e valore C:\WxWidgets 2.9.3 ( o la tua path)
4. Aprire il file "\build\msw\wx_vc10.sln".
5. Compilare la soluzione nella versione Release
