TeamTranslate
========================
A real-time speech to speech translation tool. Real-time translation is provided by Google Translate or Bing Translator, speech conversion by Nuance Dragon.
The tool is intended to support multilanguage group communcation and collaboration. TeamTranslate is available under MPL license.

How to build
------------------------
To compile the solution, you will need Visual Studio. We have tested these steps with versions 2010 and 2013.

1. Download and install Microsoft Visual Studio 201x.
2. Download and install [WxWidgets 3.0] (https://www.wxwidgets.org/downloads) (pick the Windows installer). Install it into a location without whitespaces, such as `C:\WxWidgets3` or `D:\WxWidgets3`
3. Add a new system variable, named `WXWIN` with value `C:\WxWidgets3` (or whatever path was chosed before)
4. Open solution file located in `\build\msw\wx_vc10.sln`.
5. Buil the solution in _Release_ configuration (not _Debug_)

For more info on building WxWidgets, please refer to [this page] (http://liuxingguang.blogspot.it/2014/02/using-wxwidgets-30-in-microsoft-visual.html).
