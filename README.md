TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Microsoft Bing Translator, speech conversion by Nuance Dragon. The tool is intended to support multilanguage group communication  and collaboration. 

TeamTranslate is written in C/C++ and uses WxWidgets for the UI. You can download the client installer from [here](https://github.com/xandros90/speech-translation-tools/blob/teamspeak/client/installer/TeamTranslate.msi?raw=true).

It is available under MPL license.

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with version 2013.

To build the client, open Visual Studio 2013 and load the TeamTranslate client solution (`PATH\to\client\TeamTranslate.sln`). You have build it in _Release_ configuration (look for _*Configuration Manager*_ command under the _*Build*_ menu). Now, copy all the `PATH\to\client\dll\*.dll` files to the `PATH\to\client\bin` dir where the `TeamTranslate.exe` file is.

To test the client, you will need a TeamSpeak server. To compile it, open the server solution (`PATH\to\server\ts3_server_sample.sln`) and build it in _Release_ configuration. Now, make sure that `PATH\to\server\dll\*.dll` files are present in the `PATH\to\server\bin` dir where the `ts3_server_sample_release.exe` file is.

Speech to text requirements
---------------------------
For the speech to text to work properly in your language of choice, make sure that you have installed:
* Java 7+ 
* The Microsoft Speech API package for your language. In Windows 8.1 the package for your current language is typically installed already. To add more or to configure earlier Windows version (< 8.1), go to _Control Panel > Language_ and pick yours to download.
* Fill out the `config.ini` file located in `PATH\to\client\bin\conf`.

Machine translation configuration
--------------------
In order to use the machine translation  services, you need to obtain the proper API keys and edit the configuration files stored in the `PATH\to\client\bin\conf` dir.

As per Google Translate, this is a ***paid*** service. A valid API key can be obtained from the [Google developer console](https://console.developers.google.com), enabling the Translate API and providing correct billing info. Then, paste the valid key in the `config.ini` file.

As per Microsoft Bing Translator, instead, this is a ***free*** service (up to 2M characters per month). A valid API key can be obtained for free upon registering your app on [Windows Azure Marketplace](https://datamarket.azure.com/dataset/bing/microsofttranslator). Then, paste the obtained _clientID_ and _clientSecret_ into the `config.ini` file.

In order to enable the speech to text tool, it is necessary to get an API key at the [Nuance website] (https://dragonmobile.nuancemobiledeveloper.com/public/index.php?task=home). Then, paste the obtained _AppID_ and _AppKey_ into the `config.ini` file.
