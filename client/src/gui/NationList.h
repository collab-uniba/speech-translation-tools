#pragma once

#include "NationInfo.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
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
	bool ReadFromFile(string);
	int GetSize();
	vector<NationInfo>* GetList();
	char* Search(string, SEARCHPARAMETER);
	char* SearchForLocale(string language, string nation);
	NationInfo Get(int index);

private:
	vector<NationInfo> *nations;
};

