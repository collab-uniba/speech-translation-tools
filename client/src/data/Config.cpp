#include "Config.h"

void Config::setGoogleAPIKey(const char* code){
	_googleAPI = strdup(code);
}

char* Config::getGoogleAPIKey(){
	return _googleAPI;
}

void Config::setLanguage(const char* lang){
	_language = strdup(lang);
}

char* Config::getLanguage(){
	return _language;
}

void Config::setNick(const char* nick){
	_nick = strdup(nick);
}

char* Config::getNick(){
	return _nick;
}

void Config::setService(const char* serv){
	_service = strdup(serv);
}

char* Config::getService(){
	return _service;
}

char* Config::getServerAddress(){
	return _serverAddress;
}

void Config::setServerAddress(const char *sv){
	_serverAddress = strdup(sv);
}

void Config::setNumbLanguageSelected(int v){
	_numbLanguageSelected = v;
}
int Config::getNumbLanguageSelected(){
	return _numbLanguageSelected;
}

char* Config::getTranslationEngine(){
	return _translationEngine;
}

void  Config::setTranslationEngine(const char* sv){
	_translationEngine = strdup(sv);
}


void Config::update(){
	FILE* config = fopen("conf\\config.txt", "w");
	fprintf(config, "%s\n", _serverAddress);
	fprintf(config, "%s\n", _nick);
	fprintf(config, "%d\n", _numbLanguageSelected);
	fprintf(config, "%s\n", _language);
	fprintf(config, "%s", _translationEngine);
	fflush(config);
	fclose(config);
}

bool Config::read(){
	FILE * config;
	char* str = (char*)malloc(100);
	int aux;
	if (config = fopen("conf\\config.txt", "r"))
	{
		fscanf(config, "%s", str);
		setServerAddress(str);
		fscanf(config, "%s", str);
		setNick(str);
		fscanf(config, "%d", &aux);
		setNumbLanguageSelected(aux);
		fscanf(config, "%s", str);
		setLanguage(str);
		fscanf(config, "%s", str);
		setTranslationEngine(str);
		fflush(config);
		fclose(config);
		free(str);
		return true;
	}
	else
		return false;
}

 