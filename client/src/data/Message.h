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
	Message(MSGDirection dir, wxString from, wxString message, wxString language, wxString translated, wxString timestamp) : m_message(message), m_dir(dir), m_from(from), m_language(language), m_translated(translated), m_timestamp(timestamp) { }
	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection getIO(){ return m_dir; };
	void setFrom(char* dir);
	wxString getFrom(){ return m_from; };

	void setMSG(wxString dir){
		m_from = dir;
	};
	wxString getMSG(){ return m_message; }
	wxString getTranslated(){ return m_translated; }
	wxString getTimestamp(){ return m_timestamp; }
	wxString getLaguage(){ return m_language; }
private:
	MSGDirection m_dir;
	wxString m_language;
	wxString m_from;
	wxString m_message;
	wxString m_timestamp;
	wxString m_translated;
};
 

typedef std::shared_ptr<Message> MessagePTR;
typedef std::shared_ptr<std::vector<MessagePTR>> MessageQueuePTR;
