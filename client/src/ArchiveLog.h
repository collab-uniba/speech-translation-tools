#ifndef __ARCHIVELOG_H__
#define __ARCHIVELOG_H__

#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include <string>
#include <fstream>

/* This Class allows to create a new archive zip in a prespecific path (or customized path)
and to add new log files in it.
*/
class ArchiveLog{
public:
	ArchiveLog(char* nick);					//  Create a zip archive in the path -> logs/nick.zip
	ArchiveLog(char* nick, char* path);		//  Create a zip archive in the path -> path/nick.zip (slash before nick is already included)
	~ArchiveLog();
	int WriteOnArchive(char* pathlog);		//  Add new log file in the archive 
	void closeArchive();
	char* getPath();
	void setPath(char* path);
	char* getNick();
	void setNick(char* nick);
	char* getTimeStamp();
	void setTimeStamp(char* timeStamp);
	char* getCompletePath();
	void setCompletePath(char* CompletePath);

private:
	char path[200];
	char nick[50];
	char timeStamp[32];
	char CompletePath[200];
	wxFFileOutputStream* out;
	wxZipOutputStream* zip;
	int k = 0;
	//wxTextOutputStream* txt;
}; 

#endif
