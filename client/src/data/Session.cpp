#include "Session.h"



// Global static pointer used to ensure a single instance of the class.
Session* Session::m_pInstance = NULL; 

Session::Session(){
	this->m_luser = std::make_shared<UserList>();
	this->m_config = std::make_shared<Config>();
	this->m_pending = std::make_shared<std::vector<MessagePTR>>();
	this->m_queue = std::make_shared<std::vector<MessagePTR>>();
}

Session* Session::Instance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Session;
	return m_pInstance;
}

char* Session::getApiGoogle(){
	return "";
}


void Session::addMSG(MessagePTR msg){
	m_pending->push_back(msg);
	notify(EventTS::MSG_RCV);
}

char* Session::getGoogleURLTranslation(){
	return "https://www.googleapis.com/language/translate/v2?key=";
}