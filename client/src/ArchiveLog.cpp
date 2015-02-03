#include "ArchiveLog.h"

using namespace std;

ArchiveLog::ArchiveLog(char* nick){
	//Widget Archive declarations and creation
	char pathZip[80];
	strcpy(this->path, "logs");
	//strcat(this->path, sep.c_str());
	strcat(this->path, "/");
	strcpy(this->nick, nick);
	strcpy(pathZip, "logs");
	//strcat(pathZip, sep.c_str());
	strcat(pathZip, "/");
	strcat(pathZip, nick);
	strcat(pathZip, ".zip");
	this->out = new wxFFileOutputStream(pathZip);
	this->zip = new wxZipOutputStream(*(this->out));
	
}

ArchiveLog::ArchiveLog(char* nick, char* path){
	//Widget Archive declarations and creation
	char pathZip[200];
	strcpy(this->path, path);
	strcat(this->path, "/");
	strcpy(this->nick, nick);
	strcpy(pathZip, path);
	strcat(pathZip, "/");
	strcat(pathZip, nick);
	strcat(pathZip, ".zip");
	this->out = new wxFFileOutputStream(pathZip);
	this->zip = new wxZipOutputStream(this->out);
	//this->txt = new wxTextOutputStream(*(this->zip));
	wxString sep(wxFileName::GetPathSeparator());
}

ArchiveLog::~ArchiveLog(){
	//this->out->Close();
	this->zip->Close();
}

int ArchiveLog::WriteOnArchive(char* pathlog){

	wxTextOutputStream txt(*(this->zip));
	this->zip->PutNextEntry(pathlog);

	string text;
	string line;
	ifstream myfile(pathlog);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			text = text + line + "\n";
		}
		myfile.close();
	}

	//Write on file in Archive
	txt << text;
	
	return 1;
}

void ArchiveLog::closeArchive(){
	this->zip->Close();
}

char* ArchiveLog::getPath(){
	return this->path;
}

void ArchiveLog::setPath(char* path){
	strcpy(this->path, path);
}

char* ArchiveLog::getNick(){
	return this->nick;
}

void ArchiveLog::setNick(char* nick){
	strcpy(this->nick, nick);
}

char* ArchiveLog::getTimeStamp(){
	return this->timeStamp;
}

void ArchiveLog::setTimeStamp(char* timeStamp){
	strcpy(this->timeStamp, timeStamp);
}

char* ArchiveLog::getCompletePath(){
	return this->CompletePath;
}

void ArchiveLog::setCompletePath(char* timeStamp){
	char temp[200];
	strcpy(temp, this->path);
	strcat(temp, this->nick);
	strcat(temp, "_");
	strcat(temp, timeStamp);
	strcat(temp, ".txt");
	strcpy(this->CompletePath, temp);
}
