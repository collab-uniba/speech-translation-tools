#pragma once
#include <iostream>

using namespace std;

/*
* Class used for storing nation name, language, local code and apicode used during URL REST request
*/

class NationInfo
{
public:
	NationInfo(){};
	NationInfo(const char *,const char *,const char *,const char *);
	NationInfo(const NationInfo&);
	~NationInfo();

	char * GetNation() { return Nation; }
	char * GetLanguage() { return Language; }
	char * GetLocalCode() { return LocalCode; }
	char * GetLangCode() { return LangCode; }

private:
	char Nation[20];
	char Language[20];
	char LocalCode[5];
	char LangCode[5];
};

