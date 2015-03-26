#include "Session.h"



// Global static pointer used to ensure a single instance of the class.
Session* Session::m_pInstance = NULL; 

Session::Session(){
	this->m_luser = std::make_shared<UserList>();
	this->m_config = std::make_shared<Config>();
	this->m_queue = std::make_shared<std::vector<MessagePTR>>();
	sound_flag = false;			//Flag to start/stop 
	tts_flag = false;				//Flag to start/stop TextToSpeech 		
	write_flag = false;			//Flag to recognize Typing
	tasto_stt_flag = false;		//Flag to activate Automatic SpeechToText
	finish_ctrl_flag = false;		//Flag to recognize CTRL press button
	automatic_stt_flag = false;
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


void Session::addMsgToLog(MessagePTR msg){
	m_queue->push_back(msg);
}

char* Session::getGoogleURLTranslation(){
	return "https://www.googleapis.com/language/translate/v2?key=";
}