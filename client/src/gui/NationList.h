#pragma once

#include "NationInfo.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <wx/string.h>
#include <sstream>


enum SEARCHPARAMETER
{
	COUNTRY,
	LOCALES,
	APICODE,
	LANGUAGE
};

/*
* Class containing the list of all nation's info readed from file locales_code.txt
*/

class NationList
{
public:
	NationList();
	~NationList();
	bool ReadFromFile(const char* file);
	int GetSize();
	vector<NationInfo>* GetList();
	char* Search(const wxString* language, const SEARCHPARAMETER parameter);
	char* SearchForLocale(const wxString* language, const wxString* nation);
	NationInfo Get(int index);

private:
	vector<NationInfo> *nations;
};

