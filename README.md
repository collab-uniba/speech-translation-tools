speech-translation-tools
========================

A collection of several instruments to collect data in experiments about speech translation. Each branch refers to a different technology.

Guida: http://liuxingguang.blogspot.it/2014/02/using-wxwidgets-30-in-microsoft-visual.html

Per compilare correttamente la soluzione in visual studio bisogna seguire queste istruzioni:

1. Installare Microsoft Visual Studio 2013
2. Scaricare e installare le WxWidgets 3.0.0. la versione windows installer. Installare in una path senza spazi ad esempio "C:\wxWidgets-3.0.0" o "D:\wxWidgets-3.0.0"
3. Aggiungere una nuova variabile di sistema di nome WXWIN, e valore C:\wxWidgets-3.0.0 ( o la tua path)
4. Aprire il file "\build\msw\wx_vc10.sln".
5. Compilare la soluzione sia nella versione Debug che in Release
6. Ora cancellate la cartella in samples/minimal e sostituitela con il progetto su github
7. Infine copiate la cartella include e lib del progetto nella workspace delle wxwigets ovvero in $WXWIN\lib $WXWIN\include.
