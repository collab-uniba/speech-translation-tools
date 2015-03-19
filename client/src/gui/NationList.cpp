#include "NationList.h"
#include <fstream>
#include <iostream>


NationList::NationList()
{
	this->nations = new vector<NationInfo>();
}

NationList::~NationList()
{
	free(this->nations);
}

bool NationList::ReadFromFile(const char* path)
{
	bool flagn = true;
	string line;
	ifstream myfile(path);
	int c = myfile.tellg();
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string buf;
			stringstream ss(line);
			vector<string> tokens;

			while (ss >> buf)
				tokens.push_back(buf);

			NationInfo info(tokens.at(0).c_str(), tokens.at(1).c_str(), tokens.at(2).c_str(), tokens.at(3).c_str());
			this->nations->push_back(info);
		}
		myfile.close();
		flagn = true;
	}
	else
	{
		cout << "Impossibile aprire il file";
		flagn = false;
	}
	return flagn;
}

int NationList::GetSize()
{
	return this->nations->size();
}

vector<NationInfo>* NationList::GetList()
{
	return this->nations;
}

char* NationList::Search(const wxString *language, const SEARCHPARAMETER parameter)
{
	char* flag = "false";
	for (int i = 0; i < this->nations->size(); i++)
	{
		if (strcmp(this->nations->at(i).GetLanguage(),language->mb_str())==0)
		{
			flag = "true";
			switch (parameter)
			{
			case COUNTRY:
				return this->nations->at(i).GetNation();
			case LOCALES:
				return this->nations->at(i).GetLocalCode();
			case APICODE:
				return this->nations->at(i).GetLangCode();
			case LANGUAGE:
				return this->nations->at(i).GetLanguage();
				break;
			};
		}
	}
	return flag;
}

char* NationList::SearchForLocale(const wxString* language, const wxString* nation)
{
	char temp[20];
	for (int i = 0; i < this->nations->size(); i++)
	{
		if ((strcmp(this->nations->at(i).GetLanguage(),language->mb_str()) == 0) && (strcmp(this->nations->at(i).GetNation(),nation->mb_str())==0)){
			strcpy(temp, this->nations->at(i).GetLocalCode());
		}
	}
	return temp;
}

NationInfo NationList::Get(int index){
	return this->nations->at(index);
}

