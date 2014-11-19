TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Bing Translator, speech conversion by Nuance Dragon. The tool is intended to support multilanguage group communcation and collaboration. 

TeamTranslate is written in C/C++ and is available under MPL license.

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with version 2013.

To build the client, open Visual Studio 2013 and load the TeamTranslate client solution (`PATH\to\client\TeamTranslate.sln`) and build it in _Release_ configuration (not ~~Debug~~, look for _*Configuration Manager*_ command under the _*Build*_ menu). Now, copy all the `PATH\to\client\dll\*.dll` files to the `PATH\to\client\bin` dir where the `TeamTranslate.exe` file is.

To test the client, you will need a TeamSpeak server. To compile it, open the server solution (`PATH\to\server\ts3_server_sample.sln`) and build it in either _Debug_ or _Release_ configuration. Now, copy the `PATH\to\server\dll\*.dll` files to to the `PATH\to\server\bin` dir where the `ts3_server_sample_release.exe` file is.

Speech to text requirements
---------------------------
For the speech to text to work properly in your language of choice, make sure that you have installed
* Java 7+ 
* The Microsoft Speech API package for your language. In Windows 8.1 the package for your current language is typically installed already. To add more or to configure earlier Windows version (< 8.1), go to _Control Panel > Language_ and pick yours to download.

