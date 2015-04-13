#pragma once


#include <cstring>
#include <stdio.h>
#include <wx/string.h>
#include <vector>

#include <memory>

enum MSGDirection{
	in,
	out
};

class Message {

public:

	Message(MSGDirection dir, wxString from, wxString message, wxString language_org, wxString language_system) : m_message(message), m_dir(dir), m_from(from), m_language_orig(language_org), m_language_system(language_system){
	
		time_t			rawtime;
		struct tm*		timeinfo;
		char			timestamp[100];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timestamp, 100, "%c", timeinfo);
		m_timestamp = timestamp;
	}

	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection getIO(){ return m_dir; };
	void setFrom(char* dir);
	wxString getFrom(){ return m_from; };

	void setMSG(wxString dir){
		m_message = dir;
	};
	wxString getMSG(){ return m_message; }
	wxString getTranslated(){ return m_translated; }
	wxString getTimeStamp(){ return m_timestamp; }
	wxString getLanguageOrig(){ return m_language_orig; }

	wxString getLanguageSystem(){ return m_language_system; }
	void  setSrtTranslate(wxString str){ m_translated = str; }
private:
	MSGDirection m_dir;
	wxString m_language_orig;
	wxString m_from;
	wxString m_message;
	wxString m_timestamp;
	wxString m_language_system;
	wxString m_translated;
	
};
 

typedef std::shared_ptr<Message> MessagePTR;
typedef std::shared_ptr<std::vector<MessagePTR>> MessageQueuePTR;
