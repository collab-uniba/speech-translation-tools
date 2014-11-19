TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Bing Translator, speech conversion by Nuance Dragon. The tool is intended to support multilanguage group communcation and collaboration. 

TeamTranslate is written in C/C++ and is available under MPL license.

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with version 2013.

To build the client, open Visual Studio 2013 and load the TeamTranslate client solution (`PATH\to\client\TeamTranslate.sln`) and build it in _Release_ configuration (not ~~Debug~~, look for _*Configuration Manager*_ command under the _*Build*_ menu).

To test the client, you will need a TeamSpeak server. Tocompile it, open the server solution (`PATH\to\server\ts3_server_sample.sln`) and build it in either _Debug_ or _Release_ configuration.
