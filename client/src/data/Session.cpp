#include "Session.h"



Session* Session::Instance() {
	if (_instance == 0) {
		_instance = new Session;
	}
	return _instance;
}

void Session::setGoogleAPIKey(char* code){
	GOOGLE_API_KEY = strdup(code);
}

const char* Session::getGoogleAPIKey(){
	return GOOGLE_API_KEY;
}

void Session::setLanguage(char* lang){
	CURRENT_LANG = strdup(lang);
}

const char* Session::getLanguage(){
	return CURRENT_LANG;
}

void Session::setNick(char* nick){
	NICK = strdup(nick);
}

const char* Session::getNick(){
	return NICK;
}

void Session::setService(char* serv){
	SERVICE = strdup(serv);
}

const char* Session::getService(){
	return SERVICE;
}

const char* Session::getServerAddress(){
	return SERVER_ADDRESS;
}

void Session::setServerAddress(char *sv){
	SERVER_ADDRESS = strdup(sv);
}

void Session::setNumbLanguageSelected(int v){
	this->NumbLanguageSelected = v;
}
int Session::getNumbLanguageSelected(){
	return NumbLanguageSelected;
}

const char* Session::getTranslationEngine(){
	return translationEngine;
}

const char* Session::setTranslationEngine(char* sv){
	translationEngine = strdup(sv);
}


void Session::update(){
	FILE* config = fopen("conf\\config.txt", "w");
	fprintf(config, "%s\n", SERVER_ADDRESS);
	fprintf(config, "%s\n", NICK);
	fprintf(config, "%d\n", NumbLanguageSelected);
	fprintf(config, "%s\n", CURRENT_LANG);
	fprintf(config, "%s", translationEngine);
	fflush(config);
	fclose(config);
}

bool Session::read(){
	FILE * config;
	if (config = fopen("conf\\config.txt", "r"))
	{
		fscanf(config, "%s", SERVER_ADDRESS);
		fscanf(config, "%s", NICK);
		fscanf(config, "%d", NumbLanguageSelected);
		fscanf(config, "%s", CURRENT_LANG);
		fscanf(config, "%s", translationEngine);
		fflush();
		fclose(config);
		return true;
	} else
		return false;
}
