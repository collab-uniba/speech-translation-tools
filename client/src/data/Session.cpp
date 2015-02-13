#include "Session.h"



// Global static pointer used to ensure a single instance of the class.
Session* Session::m_pInstance = NULL;

/** This function is called to create an instance of the class.
Calling the constructor publicly is not allowed. The constructor
is private and is only called by this Instance function.
*/

Session* Session::Instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Session;

	return m_pInstance;
}

 
/*

Session* Session::Instance() {
	if (_instance == 0) {
		_instance = new Session();
		_instance->read();
	}
	return _instance;
}*/
 
void Session::setGoogleAPIKey(char* code){
	_googleAPI = strdup(code);
}

const char* Session::getGoogleAPIKey(){
	return _googleAPI;
}

void Session::setLanguage(char* lang){
	_language = strdup(lang);
}

const char* Session::getLanguage(){
	return _language;
}

void Session::setNick(char* nick){
	_nick = strdup(nick);
}

const char* Session::getNick(){
	return _nick;
}

void Session::setService(char* serv){
	_service = strdup(serv);
}

const char* Session::getService(){
	return _service;
}

const char* Session::getServerAddress(){
	return _serverAddress;
}

void Session::setServerAddress(char *sv){
	_serverAddress = strdup(sv);
}

void Session::setNumbLanguageSelected(int v){
	_numbLanguageSelected = v;
}
int Session::getNumbLanguageSelected(){
	return _numbLanguageSelected;
}

 const char* Session::getTranslationEngine(){
	return _translationEngine;
}

 void  Session::setTranslationEngine(char* sv){
	_translationEngine = strdup(sv);
}


void Session::update(){
	FILE* config = fopen("conf\\config.txt", "w");
	fprintf(config, "%s\n", _serverAddress);
	fprintf(config, "%s\n", _nick);
	fprintf(config, "%d\n", _numbLanguageSelected);
	fprintf(config, "%s\n", _language);
	fprintf(config, "%s", _translationEngine);
	fflush(config);
	fclose(config);
}

bool Session::read(){
	FILE * config;
	if (config = fopen("conf\\config.txt", "r"))
	{
		fscanf(config, "%s", _serverAddress);
		fscanf(config, "%s", _nick);
		fscanf(config, "%d", _numbLanguageSelected);
		fscanf(config, "%s", _language);
		fscanf(config, "%s", _translationEngine);
		fflush(config);
		fclose(config);
		return true;
	} else
		return false;
}


 char* Session::getGoogleURLTranslation(){
	return "https://www.googleapis.com/language/translate/v2?key=";
}