#include "Session.h"



// Global static pointer used to ensure a single instance of the class.
Session* Session::m_pInstance = NULL; 

Session::Session(){
	this->_luser = std::make_shared<UserList>();
	this->_config = std::make_shared<Config>();
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

char* Session::getGoogleURLTranslation(){
	return "https://www.googleapis.com/language/translate/v2?key=";
}