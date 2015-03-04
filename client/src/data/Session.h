#pragma once

#include "User.h"
#include "Config.h"

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


typedef std::list<UserPTR> UserList;
typedef std::shared_ptr<UserList> UserListPTR;

/* 
 * Set and get functions
 */
class ClientTsFrm;
class Session : public Subject<EventTS, ClientTsFrm> {
public:
	static Session* Instance();
	private:
	Session();  // Private so that it can  not be called
	Session(Session const&){};             // copy constructor is private
	Session& operator=(Session const&){};  // assignment operator is private
	static Session* m_pInstance;
 
public:
	/*static Session* Instance();*/

	char* Session::getGoogleURLTranslation();

	ConfigPTR getConfig(){ return m_config; }
	void setConfig(ConfigPTR conf){ this->m_config = conf; }

	UserListPTR getListUser(){ return m_luser; }
	void setListUser(UserListPTR luser){ this->m_luser = luser; }

	MessageQueuePTR getMessageQueue(){ return m_pending; }

	char* Session::getApiGoogle();

	UserPTR getUser(const char* name);
	void addNewUser(UserPTR u);
	void deleteUser(UserPTR u);
	bool checkUser(UserPTR u);	
	bool checkUser(const char* u);


	void addMSG(MessagePTR msg);


/*	static wxRichTextCtrl *chatptr;				//Pointer to edit the chatptr
	static unsigned int curRow;			//Initialize Row index
	static unsigned int curCol;			//Initialize Column index
	static wxGrid *gridptr;					//Pointer to edit the chatptr grid*/

private:
	Session* m_instance;
	ConfigPTR m_config;
	UserListPTR m_luser;
	char* m_translationEngine;
	MessageQueuePTR m_pending;
	MessageQueuePTR m_queue;
};


