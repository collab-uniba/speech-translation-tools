#ifndef __SESSION_H__
#define __SESSION_H__

#include <cstring>
#include <stdio.h>


/* 
 * Set and get functions
 */

class Session {
public:
	static Session* Instance();

	void setNick(char* nick);
	const char* getNick();

	void setService(char* serv);
	const char* getService();

	void setCurrentLang(char* lang);
	const char* getCurrentLang();

	const char* getServerAddress();
	void setServerAddress(char *sv);

	void setGoogleAPIKey(char* code);
	const char* getGoogleAPIKey();

protected:
	Session();
private:
	static Session* _instance;
	static const char* NICK; //  client nickname
	static const char* SERVICE; // service used to translation (Google, Bing,....)
	static const char* SERVER_ADDRESS;
	static const char* GOOGLE_API_KEY;
	static const char* CURRENT_LANG;
};

Session* Session::_instance = 0;




#endif