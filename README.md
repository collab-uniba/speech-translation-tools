TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Bing Translator, speech conversion by Nuance Dragon.
The tool is intended to support multilanguage group communcation and collaboration. TeamTranslate is available under MPL license.

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with version 2013.

1. Download and install Microsoft Visual Studio 2013.
2. Download and install [WxWidgets 3.0] (https://www.wxwidgets.org/downloads) (pick the Windows installer). Install it into a location without whitespaces, such as `C:\WxWidgets-3.0.2`.
3. Add a new system variable, named `WXWIN` with path value `C:\WxWidgets-3.0.2` (or whatever path was chosed before).
4. Open solution file located in `C:\WxWidgets-3.0.2\build\msw\wx_vc12.sln`.
5. Buil the solution in _*Release*_ configuration, not _Debug_ (look for _*Configuration Manager*_ command under the _*Build*_ menu).

For more info on building WxWidgets, please refer to [this page] (http://liuxingguang.blogspot.it/2014/02/using-wxwidgets-30-in-microsoft-visual.html).

Now, open Visual Studio 2013 and load the TeamTranslate client solution (`PATH\to\client\teamtranslate.sln`) and build it in _Release_ configuration (not _Debug_).
Finally, to test the client, you will need a TeamSpeak server compiled in debug mode. To do so, open the server solution (`PATH\to\server\ts3_server_sample.sln`) and build it in_Debug_ configuration.
