#pragma once


#include <cstring>
#include <stdio.h>


enum MSGDirection{
	in,
	out
};

class Message {
public:
	Message(MSGDirection dir,  char* from,  char* message,  char* language) : _message(message), _dir(dir), _from(from), _language(language) { }
	~Message(){ }

	void setIO(MSGDirection dir);
	MSGDirection* getIO();

	 

	void setFrom(char* dir);
	 char* getFrom();

	void setMSG(char* dir);
	 char* getMSG();
private:
	MSGDirection _dir;
	char* _language;
	char* _from;
	char* _message;
};
 

