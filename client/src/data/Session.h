#ifndef __SESSION_H__
#define __SESSION_H__

#include <cstring>
#include <stdio.h>


/* 
 * Set and get functions
 */
 
class Session{
public:
	static Session* Instance();
	bool openLogFile(char* logFile);
	void writeToLogFile();
	bool closeLogFile();

private:
	Session(){};  // Private so that it can  not be called
	Session(Session const&){};             // copy constructor is private
	Session& operator=(Session const&){};  // assignment operator is private
	static Session* m_pInstance;
 
public:
	/*static Session* Instance();*/

	void setNick(char* nick);
	const char* getNick();

	void setService(char* serv);
	const char* getService();

	void setLanguage(char* lang);
	const char* getLanguage();

	const char* getServerAddress();
	void setServerAddress(char *sv);

	void setGoogleAPIKey(char* code);
	const char* getGoogleAPIKey();

	void setNumbLanguageSelected(int v);
	int getNumbLanguageSelected();

	const char* Session::getTranslationEngine();
	void Session::setTranslationEngine(char *sv);

	char* Session::getGoogleURLTranslation();

	void update();
	bool read();



private:
	Session* _instance;
	const char* _nick; //  client nickname
	const char* _service; // service used to translation (Google, Bing,....)
	const char* _serverAddress;
	const char* _googleAPI;
	const char* _language;
	int _numbLanguageSelected;
	const char* _translationEngine;
};






#endif