#pragma once


#include <string>

using namespace std;

typedef struct Labels{

	// frame Login
	string nameHostServer = "";
	string language = "";
	string service = "";
	string confirm = "";

	// frame Client
	string gridMessage = "";
	string send = "";

	string saveMenu = "";
	string mailMenu = "";
	string exitMenu = "";

	string options = "";
	string audioMenu = "";
	string enable = "";
	string disable = "";

	// frame Audio
	string microphone = "";
	string min = "";
	string max = "";

	// frame Save
	string saveMessage = "";
	string no = "";
	string yes = "";
	string saveFormatMessage = "";
	string formatCsv = "";
	string formatTxt = "";
	string saveIn = "";
	string saveSuccess = "";
	string saveError = "";
	string noSave = "";
	string btnBrowse = "";
	string btnCancel = "";

	// frame Mail
	string mailTo = "";
	string mailSubject = "";
	string mailBody = "";
	string mailAttachmentTxt = "";
	string mailAttachmentCsv = "";
	string fileSelect = "";
	string dirSelect = "";
	string mailSuccess = "";
	string mailError = "";

	// frame Setting
	string emailSetting = "";
	string serverName = "";
	string serverPort = "";
	string messageSecure = "";
	string noSecure = "";
	string messageEmailSetting = "";
	

};

extern Labels labels;

extern char CURRENT_LANG[20];

