#ifndef CONFIG_H
#define CONFIG_H

#include <wx/string.h>
#include <memory>


class Config{
public:

	~Config(){  }
	Config(){ read(); };  // Private so that it can  not be called
 

	/*static Session* Instance();*/

	void setNick(const char* nick);
	char* getNick();

	void setService(const char* serv);
	char* getService();

	void setLanguage(const char* lang);
	char* getLanguage();

	char* getServerAddress();
	void setServerAddress(const char *sv);

	void setGoogleAPIKey(const char* code);
	char* getGoogleAPIKey();

	void setNumbLanguageSelected(int v);
	int getNumbLanguageSelected();

	char* getTranslationEngine();
	void setTranslationEngine(const char *sv);

	void update();
	bool read();

private:
	char* _nick; //  client nickname
	char* _service; // service used to translation (Google, Bing,....)
	char* _serverAddress;
	char* _googleAPI;
	char* _language;
	int _numbLanguageSelected;
	char* _translationEngine;
};


typedef std::shared_ptr<Config> ConfigPTR;


#endif
