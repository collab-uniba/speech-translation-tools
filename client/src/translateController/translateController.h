#pragma once

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include "translateVariable.h"
#include "../GlobalVariables.h"

#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <curl/curl.h>

#include "../tinyxml2.h"
#include "../gui/NationList.h"
#include "../gui/NationInfo.h"
#include "../data/session.h"

using namespace tinyxml2;
using namespace std;


class ErrorLabels : public exception{
public:
	ErrorLabels(const char* s) {
		reason = strdup(s);
	}
	virtual const char* what() const throw()
	{
		return reason;
	}

private:
	const char*  reason;
};

class TranslateController
{
	public:
		static void InitLanguageVariable(char* lang)  throw();
		static wxString translateLabels(char* language);
		static void readXmlLangDoc(char* filename);
};

