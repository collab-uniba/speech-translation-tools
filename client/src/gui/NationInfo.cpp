#include "NationInfo.h"


NationInfo::NationInfo(const char * _Nation,const char * _Language,const char * _LocalCode,const char * _LangCode)
{
	strcpy(this->Nation,  _Nation);
	strcpy(this->Language, _Language);
	strcpy(this->LocalCode, _LocalCode);
	strcpy(this->LangCode, _LangCode);
}

NationInfo::NationInfo(const NationInfo &copy)
{
	strcpy(this->Nation, copy.Nation);
	strcpy(this->Language, copy.Language);
	strcpy(this->LocalCode, copy.LocalCode);
	strcpy(this->LangCode, copy.LangCode);
}

NationInfo::~NationInfo()
{
}
