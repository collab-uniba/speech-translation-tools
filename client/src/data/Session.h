#pragma once

#include "User.h"

#include "../data/message.h"

#include <list>
#include <cstring>
#include <stdio.h>
#include <cstdlib> 
#include "../lib/eventtype.h"
#include "../lib/Subject.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif
#include <wx/richtext/richtextctrl.h>
#include <wx/grid.h> 


#include "../GlobalVariables.h"
#include "../parseini/SimpleIni.h"



typedef std::list<UserPTR> UserList;
typedef std::shared_ptr<UserList> UserListPTR;

class ErrorSession: public exception{
public:
	ErrorSession(const char* s) {
		reason = strdup(s);
	}
	virtual const char* what() const throw()
	{
		return reason;
	}
	
private:
	const char*  reason;
};


/* 
 * Set and get functions
 */

class Session{
public:
	static Session* Instance();
	bool sound_flag;			//Flag to start/stop 
	bool tts_flag;				//Flag to start/stop TextToSpeech 		
	bool write_flag;			//Flag to recognize Typing
	bool tasto_stt_flag;		//Flag to activate Automatic SpeechToText
	bool finish_ctrl_flag;		//Flag to recognize CTRL press button
	bool automatic_stt_flag;
	uint64 scHandlerID;
private:
	Session();  // Private so that it can  not be called
	Session(Session const&){};             // copy constructor is private
	Session& operator=(Session const&){};  // assignment operator is private
	static Session* m_pInstance;
 
public:
	bool getsound_flag(){ return sound_flag; }
	void setsound_flag(bool conf){ this->sound_flag = conf; }
	
	bool gettts_flag(){ return tts_flag; }
	void settts_flag(bool conf){ this->tts_flag = conf; }

	bool getwrite_flag(){ return write_flag; }
	void setwrite_flag(bool conf){ this->write_flag = conf; }

	bool gettasto_stt_flag(){ return tasto_stt_flag; }
	void settasto_stt_flag(bool conf){ this->tasto_stt_flag = conf; }

	bool getfinish_ctrl_flag(){ return finish_ctrl_flag; }
	void setfinish_ctrl_flag(bool conf){ this->finish_ctrl_flag = conf; }

	bool getautomatic_stt_flag(){ return automatic_stt_flag; }
	void setautomatic_stt_flag(bool conf){ this->automatic_stt_flag = conf; }

	UserListPTR getListUser(){ return m_luser; }
	void setListUser(UserListPTR luser){ this->m_luser = luser; }

	void setNick(const char* nick);
	const char* getNick();

	void setLanguage(const char* lang);
	const char* getLanguage();

	const char* getServerAddress();
	void setServerAddress(const char *sv);

	void setGoogleAPIKey(const char* code);
	const char* getGoogleAPIKey();

	void setNumbLanguageSelected(int v);
	int getNumbLanguageSelected();

	const char* getTranslationEngine();
	void setTranslationEngine(const char *sv);

	const char* getsmtpservertxt();
	void setsmtpservertxt(const char *sv);

	const char* getserverporttxt();
	void setserverporttxt(const char *sv);

	const char* getusername();
	void setusername(const char *sv);

	const char* getpassword();
	void setpassword(const char *sv);

	bool getprotocol();
	void setprotocol(bool sv);


	const char* getMicLevel();
	void setMicLevel(const char* sv);

	const char* getBingKey();
	void setBingKey(const char *sv);

	const char* getBingID();
	void setBingID(const char *sv);

	MessageQueuePTR getMessageQueue(){ return m_queue; }

	char* Session::getApiGoogle();

	UserPTR getUser(const char* name);
	void addNewUser(UserPTR u);
	void deleteUser(UserPTR u);
	bool checkUser(UserPTR u);	
	bool checkUser(const char* u);

	void addMsgToLog(MessagePTR msg);

	const char* getAPPIDDragon();
	const char* getAPPKeyDragon();
	const char* getAPPDeviceDragon();

private:
	Session* m_instance;
	UserListPTR m_luser;
	char* m_translationEngine;
	MessageQueuePTR m_queue;
	std::unique_ptr<CSimpleIniA> ini;
	wxTextCtrl *m_TextCtrl;
};


