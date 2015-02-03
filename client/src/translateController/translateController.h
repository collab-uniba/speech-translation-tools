#ifndef _TRANSLATECONTROLLER_H
#define _TRANSLATECONTROLLER_H

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include "translateVariable.h"
#include "../connectionController/connectionController.h"
#include "../GlobalVariables.h"

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "../tinyxml2.h"
#include <curl/curl.h>
#include "..\gui\NationList.h"
#include "..\gui\NationInfo.h"

using namespace tinyxml2;
using namespace std;

class TranslateController
{
	public:
		static void InitLanguageVariable(char* lang);
		static wxString translateLabels(char* language);
		static void readXmlLangDoc(char* filename);
		static void parseBing(char *word);
		static void parseGoogle(char *str);
		static char *richiestaBing(wxString StringSource, char * lang);
		static char *richiestaGoogle(wxString StringSource, char * lang);
};

#endif