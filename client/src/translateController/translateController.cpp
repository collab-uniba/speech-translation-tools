#include "translateController.h"
#include "../data/session.h"


ConfigPTR configc = Session::Instance()->getConfig();

void TranslateController::InitLanguageVariable(char* lang)
{
	char filename[500] = { "" };
	 
	strcpy(filename, "lang\\");
	strcat(filename, lang);
	strcat(filename, ".xml");
	 
	ifstream file(filename, ios::in);
	if (file.is_open())
		TranslateController::readXmlLangDoc(filename); // read and set "labels"
	
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

void TranslateController::parseBing(char *word)
{
	char *buffer;
	unsigned int i;
	int result;
	buffer = strstr(word, ">");
	result = (int)(buffer - word + 1);
	if (buffer != NULL)
		printf("%s found at position %d\n", word, result);
	else
	{
		ts3client_logMessage("Can't parse Bing result", LogLevel_ERROR, "Bing translate", Session::Instance()->scHandlerID);
		return;
	}
	for (i = 1; i < strlen(buffer); i++) 
		buffer[i - 1] = buffer[i];
	buffer[strlen(buffer) - 10] = '\0';
	StringTranslate = wxString::FromAscii(buffer); // StringTranslate contains the text translate
}

void TranslateController::parseGoogle(char *str)
{
	unsigned int i = 0;
	int j = 0;
	char * pch;
	char * stringalpha;
	char finale[2048] = { "" };

	char buffer[512] = { "" };

	pch = strtok(str, ",.:\"'{}();200[]");
	while (pch != NULL)
	{
		strcat(buffer, pch);
		pch = strtok(NULL, ",.:\"'{}();200[]");
	}

	char prova[256];
	int quanto;
	char * p = strstr(buffer, "Text");
	if (p == NULL)
	{
		ts3client_logMessage("Can't parse Google result", LogLevel_ERROR, "Google translate", Session::Instance()->scHandlerID);
		return;
	}
	else
	{
		quanto = strlen(p);
		strncpy(prova, strstr(buffer, "Text"), quanto);
		prova[quanto] = '\0';
		stringalpha = strstr(prova, "Text");
		for (i = 4; i < strlen(strstr(prova, "Text")); i++)
		{
			finale[j] = stringalpha[i];
			j++;
		}
		StringTranslate = wxString::FromAscii(finale);	//StringTranslate contains the message translate
	}
}

char *TranslateController::richiestaBing(const wxString* StringSource, const wxString* lang)
{
	if (strcmp(lang->mb_str(), configc->getLanguage()) == 0) return (char*)StringSource->mb_str().data();	//If the message is written in client's language then return

	CURL *curl2;
	CURL *curl3;
	CURLcode res2;
	struct curl_slist *chunk = NULL;
	struct stringa f;
	ConnectionController::init_string(&f);
	struct stringa p;
	ConnectionController::init_string(&p);

	curl_global_init(CURL_GLOBAL_ALL);

	curl2 = curl_easy_init();
	if (curl2)
	{
		curl_easy_setopt(curl2, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13"); //Set the url of http request
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0L);	//Use SSL Protocol
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0L);	//Use SSL protocol
		curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);	//Function to handle http request
		curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &f);				//Save answer into string 
		curl_easy_setopt(curl2, CURLOPT_POST, 1L);					//Inform the server to a post request
		curl_easy_setopt(curl2, CURLOPT_USERAGENT, "libcurl-agent/1.0");	//Fill user-agent to not decline our request
		curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);

		FILE *bing;
		if (bing = fopen("..\\bin\\conf\\BING.txt", "r"))
		{
			char CLIENT_ID[50] = "";
			char CLIENT_SECRET[128] = "";

			fscanf(bing, "%s", CLIENT_ID);
			fscanf(bing, "%s", CLIENT_SECRET);

			char * encode_key = curl_easy_escape(curl2, CLIENT_SECRET, strlen(CLIENT_SECRET));	//Leave incorrect url characters from CLIENT_ID nad CLIENT_SECRET

			char url2[1024];
			sprintf(url2, "client_id=%s&client_secret=%s&scope=http://api.microsofttranslator.com&grant_type=client_credentials", CLIENT_ID, encode_key);
			curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, url2);
		}
		else
		{
			ts3client_logMessage("Can't find Bing config file", LogLevel_WARNING, "Bing translate", Session::Instance()->scHandlerID); 
			return "";
		}

		res2 = curl_easy_perform(curl2);
		/*
		Save into pagina.htm the json answer of access_token
		*/
		FILE *html;
		if (html = fopen("..\\conf\\pagina.htm", "w"))
		{
			fprintf(html, "%s", f.ptr);
			fflush(html);
			fclose(html);
		}

		else
		{
			ts3client_logMessage("Cannot load file pagina.htm", LogLevel_ERROR, "File loading", Session::Instance()->scHandlerID);
		}

		ConnectionController::JSON();	//Parse answer for access_token value to start the translation
		char auth[2048] = { "" };
		char header[2048 + 512] = { "" };

		FILE * jfile;
		if (jfile = fopen("..\\conf\\JSON.txt", "r+"))
		{
			fscanf(jfile, "%s", &auth);
			fflush(jfile);
			fclose(jfile);
		}
		else
		{
			ts3client_logMessage("Cannot create file JSON.txt", LogLevel_ERROR, "File saving", Session::Instance()->scHandlerID);
		}
		strcpy(header, "Authorization: Bearer ");
		strcat(header, auth);
		char languagesrc[30] = { "" };
		char languagedst[30] = { "" };
		NationList *nations = new NationList();
		nations->ReadFromFile("..\\conf\\locales_code.txt");

		strcpy(languagesrc, nations->Search(lang,APICODE));
		strcpy(languagedst, nations->Search(&wxString(configc->getLanguage()), APICODE));
		
		curl3 = curl_easy_init();
		char *trueheader = curl_easy_unescape(curl3, header, 0, NULL);


		const char *BufferSource = curl_easy_escape(curl3, (char*)StringSource->mb_str().data(), strlen((char*)StringSource->mb_str().data()));


		char url3[512] = { "" };
		strcpy(url3, "http://api.microsofttranslator.com/V2/Http.svc/Translate?text=");

		//strcat(url3, url_encode(pr).c_str());
		strcat(url3, BufferSource);
		strcat(url3, "&from=");
		strcat(url3, languagesrc);
		strcat(url3, "&to=");
		strcat(url3, languagedst);

		curl_easy_setopt(curl3, CURLOPT_URL, url3);
		curl_easy_setopt(curl3, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		chunk = curl_slist_append(chunk, header);
		res2 = curl_easy_setopt(curl3, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl3, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);
		curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &p);
		res2 = curl_easy_perform(curl3);


		if (res2 != CURLE_OK)
		{
			char errormessage[60];
			strcpy(errormessage, "curl_easy_perform() failed ");
			strcat(errormessage, curl_easy_strerror(res2));

			ts3client_logMessage(errormessage, LogLevel_ERROR, "Bing translate", Session::Instance()->scHandlerID);
		}
		curl_easy_cleanup(curl2);
	}
	curl_global_cleanup();

	FILE *html;
	if (html = fopen("..\\conf\\trad.htm", "w"))
	{
		fprintf(html, "%s", p.ptr);
		fflush(html);
		fclose(html);
	}
	return p.ptr;
}

char *TranslateController::richiestaGoogle(wxString* StringSource, wxString* lang)
{

	if (strcmp(lang->mb_str(), configc->getLanguage()) == 0) return (char*)StringSource->mb_str().data();

	CURL *curl;
	CURLcode res;
	char url[256];
	char languagesrc[30];
	char languagedst[30];
	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	struct stringa s;
	ConnectionController::init_string(&s);
	NationList *nations = new NationList;
	nations->ReadFromFile("..\\conf\\locales_code.txt");
	strcpy(languagesrc, nations->Search(lang, APICODE));
	strcpy(languagedst, nations->Search(&wxString(configc->getLanguage()), APICODE));

	if (curl)
	{
		/*strcpy(url, "https://www.googleapis.com/language/translate/v2?key=");
		FILE * google = fopen("..\\conf\\GOOGLE.txt", "r");
		fscanf(google,"%s",GOOGLE_API_KEY);
		strcat(url, GOOGLE_API_KEY);*/

		strcat(url, "&q=");
		const char *BufferSource = curl_easy_escape(curl, (char*)StringSource->mb_str().data(), strlen((char*)StringSource->mb_str().data()));
		strcat(url, BufferSource);
		strcat(url, "&source=");
		strcat(url, languagesrc);
		strcat(url, "&target=");
		strcat(url, languagedst);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ConnectionController::writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
		{
			char errormessage[60];
			strcpy(errormessage, "curl_easy_perform() failed");
			strcat(errormessage, curl_easy_strerror(res));
			ts3client_logMessage(errormessage, LogLevel_ERROR, "Google translate", Session::Instance()->scHandlerID);
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
		FILE *html;
		if (html = fopen("..\\conf\\tradg.htm", "w"))
		{
			fprintf(html, "%s", s.ptr);
			fflush(html);
			fclose(html);
		}
		return s.ptr;
	}

	curl_global_cleanup();
}