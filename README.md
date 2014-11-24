TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Microsoft Bing Translator, speech conversion by Nuance Dragon. The tool is intended to support multilanguage group communcation and collaboration. 

TeamTranslate is written in C/C++ and uses WxWidgets for the UI.

It is available under MPL license.

How to build WxWidgets
------------------------
Before compiling TeamTranslate, you will have to compile and install WxWidgets library in your system.
* Download and install [WxWidgets 3.0] (https://www.wxwidgets.org/downloads) (pick the Windows installer). Install it into a location without whitespaces, such as `C:\WxWidgets-3.0.2`.
* Add a new system variable, named `WXWIN` with path value `C:\WxWidgets-3.0.2` (or whatever path was chosed before).
* Open solution file located in `\build\msw\wx_vc10.sln`.
* Open solution file located in `C:\WxWidgets-3.0.2\build\msw\wx_vc10.sln`.
* Build the solution in _Release_ configuration, not _Debug_ (look for _Configuration Manager_ command under the _*Build*_ menu). 

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with version 2013.

To build the client, open Visual Studio 2013 and load the TeamTranslate client solution (`PATH\to\client\TeamTranslate.sln`). You can build it in boht  _Release_ and _Debug_ configuration (look for _*Configuration Manager*_ command under the _*Build*_ menu). Now, copy all the `PATH\to\client\dll\*.dll` files to the `PATH\to\client\bin` dir where the `TeamTranslate.exe` file is.

To test the client, you will need a TeamSpeak server. To compile it, open the server solution (`PATH\to\server\ts3_server_sample.sln`) and build it in either _Debug_ or _Release_ configuration. Now, copy the `PATH\to\server\dll\*.dll` files to to the `PATH\to\server\bin` dir where the `ts3_server_sample_release.exe` file is.

Speech to text requirements
---------------------------
For the speech to text to work properly in your language of choice, make sure that you have installed
* Java 7+ 
* The Microsoft Speech API package for your language. In Windows 8.1 the package for your current language is typically installed already. To add more or to configure earlier Windows version (< 8.1), go to _Control Panel > Language_ and pick yours to download.

Machine translation configuration
--------------------
In order to use the machine tranlsation services, you need to obtain the proper API keys and edit the configuration files stored in the `PATH\to\client\conf` dir.

As per Google Translate, this is a paid service. A valid API key can be obtained from the [Google developer console](https://console.developers.google.com), enabling the Translate API and providing correct billing info. Then, paste the valid key in the `API.txt` file.

As per Microsoft Bing Translator, this is a free service (for up to 2M characters per month). A valid API key can be obtained for free upong registering one's app on [Windows Azure Marketplace](https://datamarket.azure.com/dataset/bing/microsofttranslator). Then, paste the obtained _clientID_ and _clientSecret_ into the `BING.txt` file.
