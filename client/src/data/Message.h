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
	Message(MSGDirection dir, wxString from, wxString message, wxString language) : m_message(message), m_dir(dir), m_from(from), m_language(language) { }
	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection* getIO();
	void setFrom(char* dir);
	wxString getFrom(){ return m_from; };

	void setMSG(wxString dir){
		m_from = dir;
	};
	wxString getMSG(){ return m_message; }
private:
	MSGDirection m_dir;
	wxString m_language;
	wxString m_from;
	wxString m_message;
};
 

typedef std::shared_ptr<Message> MessagePTR;
typedef std::shared_ptr<std::vector<MessagePTR>> MessageQueuePTR;
