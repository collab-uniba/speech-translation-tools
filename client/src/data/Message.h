#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <cstring>
#include <stdio.h>


enum MSGDirection{
	in,
	out
};

class Message {
public:
	Message(MSGDirection dir, const char* from, const char* message, const char* language) : _message(message), _dir(dir), _from(from), _language(language) { }
	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection* getIO();

	 

	void setFrom(char* dir);
	const char* getFrom();

	void setMSG(char* dir);
	const char* getMSG();
private:
	MSGDirection _dir;
	const char* _language;
	const char* _from;
	const char* _message;
};
 

#endif