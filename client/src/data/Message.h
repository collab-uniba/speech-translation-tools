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
	enum tCOMMANDS // list of commands that are currently implemented
	{
		eID_THREAD_EXIT = wxID_EXIT, // thread should exit or wants to exit
		eID_THREAD_NULL = wxID_HIGHEST + 1, // dummy command
		eID_THREAD_STARTED, // worker thread has started OK
		eID_THREAD_JOB, // process normal job
		eID_THREAD_JOBERR // process errorneous job after which thread likes to exit
	}; // enum tCOMMANDS
	Message(MSGDirection dir, wxString from, wxString message, wxString language_org, wxString language_dest) : m_message(message), m_dir(dir), m_from(from), m_language_orig(language_org), m_language_dest(language_dest) , m_cmd(eID_THREAD_NULL){
	
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

	wxString getLanguageDest(){ return m_language_dest; }
	void  setSrtTranslate(wxString str){ m_translated = str; }
	tCOMMANDS m_cmd;
private:
	MSGDirection m_dir;
	wxString m_language_orig;
	wxString m_from;
	wxString m_message;
	wxString m_timestamp;
	wxString m_language_dest;
	wxString m_translated;
	
};
 

typedef std::shared_ptr<Message> MessagePTR;
typedef std::shared_ptr<std::vector<MessagePTR>> MessageQueuePTR;
