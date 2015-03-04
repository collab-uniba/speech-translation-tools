#pragma once


#include <cstring>
#include <stdio.h>
#include <vector>

#include <memory>

enum MSGDirection{
	in,
	out
};


class Message {
public:
	Message(MSGDirection dir, char* from, char* message, char* language) : m_message(message), m_dir(dir), m_from(from), m_language(language) { }
	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection* getIO();
	void setFrom(char* dir);
	char* getFrom(){ return m_from; };

	void setMSG(char* dir){ m_from = strupr(dir); };
	char* getMSG(){ return m_message; }
private:
	MSGDirection m_dir;
	char* m_language;
	char* m_from;
	char* m_message;
};
 

typedef std::shared_ptr<Message> MessagePTR;
typedef std::shared_ptr<std::vector<MessagePTR>> MessageQueuePTR;
