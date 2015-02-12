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

void Session::setCurrentLang(char* lang){
	CURRENT_LANG = strdup(lang);
}

const char* Session::getCurrentLang(){
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




