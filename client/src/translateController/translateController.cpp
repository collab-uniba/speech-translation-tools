#include "translateController.h"



void TranslateController::InitLanguageVariable(char* lang)
{
	char filename[500] = { "" };
	 
	strcpy(filename, "lang\\");
	strcat(filename, lang);
	strcat(filename, ".xml");
	 
	ifstream file(filename, ios::in);

	if (file.is_open()) TranslateController::readXmlLangDoc(filename); // read and set "labels"
	else throw (ErrorLabels( "Language file has not been found"));
	
	file.close();
}

void TranslateController::readXmlLangDoc(char* filename){

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename);		
	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
	tinyxml2::XMLElement * pElement;

	tinyxml2::XMLNode *primoFiglio = pRoot->FirstChild();
	tinyxml2::XMLNode *pFratello = primoFiglio;

	do
	{
		const char* etichetta = pFratello->Value();
		tinyxml2::XMLNode *figlio = pFratello->FirstChild();

		const char* valFiglio = figlio->Value();

		// frame Login
		if (strcmp(etichetta, "nameHostServer") == 0) labels.nameHostServer = valFiglio;
		else if (strcmp(etichetta, "language") == 0) labels.language = valFiglio;
		else if (strcmp(etichetta, "service") == 0) labels.service = valFiglio;
		else if (strcmp(etichetta, "confirm") == 0) labels.confirm = valFiglio;

		// frame Client
		else if (strcmp(etichetta, "gridMessage") == 0) labels.gridMessage = valFiglio;
		else if (strcmp(etichetta, "send") == 0) labels.send = valFiglio;
		
		else if (strcmp(etichetta, "saveMenu") == 0) labels.saveMenu = valFiglio;		
		else if (strcmp(etichetta, "mailMenu") == 0) labels.mailMenu = valFiglio;			
		else if (strcmp(etichetta, "exitMenu") == 0) labels.exitMenu = valFiglio;
		
		else if (strcmp(etichetta, "options") == 0) labels.options = valFiglio;
		else if (strcmp(etichetta, "audioMenu") == 0) labels.audioMenu = valFiglio;
		else if (strcmp(etichetta, "enable") == 0) labels.enable = valFiglio;
		else if (strcmp(etichetta, "disable") == 0) labels.disable = valFiglio;

		// frame Audio
		else if (strcmp(etichetta, "microphone") == 0) labels.microphone = valFiglio;
		else if (strcmp(etichetta, "min") == 0) labels.min = valFiglio;
		else if (strcmp(etichetta, "max") == 0) labels.max = valFiglio;

		// frame Save
		else if (strcmp(etichetta, "saveMessage") == 0) labels.saveMessage = valFiglio;
		else if (strcmp(etichetta, "yes") == 0) labels.yes = valFiglio;
		else if (strcmp(etichetta, "no") == 0) labels.no = valFiglio;
		else if (strcmp(etichetta, "saveFormatMessage") == 0) labels.saveFormatMessage = valFiglio;
		else if (strcmp(etichetta, "formatCsv") == 0) labels.formatCsv = valFiglio;
		else if (strcmp(etichetta, "formatTxt") == 0) labels.formatTxt = valFiglio;
		else if (strcmp(etichetta, "saveIn") == 0) labels.saveIn = valFiglio;
		else if (strcmp(etichetta, "saveSuccess") == 0) labels.saveSuccess = valFiglio;
		else if (strcmp(etichetta, "saveError") == 0) labels.saveError = valFiglio;
		else if (strcmp(etichetta, "noSave") == 0) labels.noSave = valFiglio;
		else if (strcmp(etichetta, "btnBrowse") == 0) labels.btnBrowse = valFiglio;
		else if (strcmp(etichetta, "btnCancel") == 0) labels.btnCancel = valFiglio;

		// frame Mail
		else if (strcmp(etichetta, "mailTo") == 0) labels.mailTo = valFiglio;
		else if (strcmp(etichetta, "mailSubject") == 0) labels.mailSubject = valFiglio;
		else if (strcmp(etichetta, "mailBody") == 0) labels.mailBody = valFiglio;
		else if (strcmp(etichetta, "mailAttachmentTxt") == 0) labels.mailAttachmentTxt = valFiglio;
		else if (strcmp(etichetta, "mailAttachmentCsv") == 0) labels.mailAttachmentCsv = valFiglio;
		else if (strcmp(etichetta, "fileSelect") == 0) labels.fileSelect = valFiglio;
		else if (strcmp(etichetta, "mailSuccess") == 0) labels.mailSuccess = valFiglio;
		else if (strcmp(etichetta, "mailError") == 0) labels.mailError = valFiglio;

		// frame Settings
		else if (strcmp(etichetta, "emailSetting") == 0) labels.emailSetting = valFiglio;
		else if (strcmp(etichetta, "serverName") == 0) labels.serverName = valFiglio;
		else if (strcmp(etichetta, "serverPort") == 0) labels.serverPort = valFiglio;
		else if (strcmp(etichetta, "messageSecure") == 0) labels.messageSecure = valFiglio;
		else if (strcmp(etichetta, "noSecure") == 0) labels.noSecure = valFiglio;
		else if (strcmp(etichetta, "messageEmailSetting") == 0) labels.messageEmailSetting = valFiglio;

		pFratello = pFratello->NextSibling();

	} while (pFratello != NULL);
}

