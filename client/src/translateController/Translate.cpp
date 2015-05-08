#include "Translate.h"

/*
Save data from http request into string
*/
static size_t writefunc(void *ptr, size_t size, size_t nmemb, struct Translation::MemoryStruct  *s)
{
	size_t new_len = s->size + size*nmemb;
	s->memory = (char*)realloc(s->memory, new_len + 1);
	if (s->memory == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->memory + s->size, ptr, size*nmemb);
	s->memory[new_len] = '\0';
	s->size = new_len;

	return size*nmemb;
}

void Translation::TranslateX::init_string(struct Translation::MemoryStruct *s) {
	s->size = 0;
	s->memory = (char*)malloc(s->size + 1);
	if (s->memory == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->memory[0] = '\0';
}

void Translation::BingTranslate::translateThis(MessagePTR msg)
{
	time_t					timer;
	double					seconds;
	std::string				header;
	NationList				*nations;
	char					languagesrc[30]		= { NULL },
							languagedst[30]		= { NULL };
	CURL					*curl;
	struct MemoryStruct		response;
	std::string				url;
	struct curl_slist		*chunk				= NULL;
	CURLcode				res2;
	Document				document;

	if (m_expirationTime == NULL)  getToken();

	if (msg->getLanguageOrig() != msg->getLanguageSystem())
	{
		init_string(&response);
		time(&timer);
		seconds = difftime(m_expirationTime, timer);
		nations = new NationList();

		if (seconds < 10 ) getToken();
	
		header = "Authorization: Bearer " + m_access_token;
	
		nations->ReadFromFile(LOCALES_CODE_FILE);

		strcpy(languagesrc, nations->Search(&msg->getLanguageSystem(), APICODE));
		strcpy(languagedst, nations->Search(&msg->getLanguageOrig(), APICODE));

		curl = curl_easy_init();
		char *trueheader = curl_easy_unescape(curl, header.c_str(), 0, NULL);
		const char *BufferSource = curl_easy_escape(curl, msg->getMSG().ToUTF8(), strlen(msg->getMSG().ToUTF8()));
		//const char *BufferSource = curl_easy_escape(curl, msg->getMSG().mb_str().data(), msg->getMSG().Len());
	
		url = "http://api.microsofttranslator.com/V2/Http.svc/Translate?text=";
		url += BufferSource + std::string("&from=") + languagesrc + "&to=" + languagedst;

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		chunk = curl_slist_append(chunk, header.c_str());
		res2 = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		res2 = curl_easy_perform(curl);
	
		wxString text_convUTF8 = wxString::FromUTF8(response.memory);
		
		wxRegEx		responseText = "\">(.*)</string>";

		if (responseText.Matches(text_convUTF8))
			msg->setSrtTranslate(responseText.GetMatch(text_convUTF8, 1));
		else
			msg->setSrtTranslate(text_convUTF8);
		const char * mv = text_convUTF8.mb_str();
		
		//else manage error?

		curl_global_cleanup();
		free(response.memory);
		delete nations;
	}
	else{
		msg->setSrtTranslate(msg->getMSG());
	}


}

void Translation::BingTranslate::getToken(){

	CURL					*curl2;
	CURLcode				res2;
	char					url2[1024];
	char*					encode_key;
	struct MemoryStruct		token;
	time_t					timer;
	Document				document;

	time(&timer);
	init_string(&token);

	curl_global_init(CURL_GLOBAL_ALL);

	if (curl2 = curl_easy_init())
	{
		curl_easy_setopt(curl2, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13"); 
		//Set the url of http request
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0L);	//Use SSL Protocol
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0L);	//Use SSL protocol
		curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writefunc);	//Function to handle http request
		curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &token);				//Save answer into string 
		curl_easy_setopt(curl2, CURLOPT_POST, 1L);					//Inform the server to a post request
		curl_easy_setopt(curl2, CURLOPT_USERAGENT, "libcurl-agent/1.0");	//Fill user-agent to not decline our request
		curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);
		session->getBingKey();
			session->getBingKey();
		encode_key = curl_easy_escape(curl2, session->getBingKey(), strlen(session->getBingKey()));

		sprintf(url2,
			"client_id=%s&client_secret=%s&scope=http://api.microsofttranslator.com&grant_type=client_credentials",
			session->getBingID(),
			encode_key);

		curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, url2);
		res2 = curl_easy_perform(curl2);

		document.ParseInsitu<0>(token.memory);
		m_access_token = document["access_token"].GetString();
		m_expirationTime = std::stoi(document["expires_in"].GetString()) + timer;
	}
}


void Translation::GoogleTranslate::translateThis(MessagePTR msg)
{
	CURL				*curl;
	CURLcode			res;
	char				languagesrc[30],
						languagedst[30];
	struct MemoryStruct	response;
	std::string				url;
	wxRegEx				responseText	= "\"translatedText\": \"(.*)\"";
	wxString			text_convUTF8;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	if (msg->getLanguageOrig() != msg->getLanguageSystem())
	{
		curl = curl_easy_init();
		init_string(&response);
		NationList *nations = new NationList;
		nations->ReadFromFile(LOCALES_CODE_FILE);
		strcpy(languagesrc, nations->Search(&msg->getLanguageSystem(), APICODE));
		strcpy(languagedst, nations->Search(&msg->getLanguageOrig(), APICODE));

		if (curl)
		{
			const char *BufferSource = curl_easy_escape(curl, msg->getMSG().ToUTF8(), strlen(msg->getMSG().ToUTF8()));
			int m = msg->getMSG().Len();
			url = "https://www.googleapis.com/language/translate/v2?key=";
			url += std::string(session->getGoogleAPIKey()) + "&q=" + BufferSource + "&source="
				+ languagesrc + "&target=" +  languagedst;

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			res = curl_easy_perform(curl);

			text_convUTF8 = wxString::FromUTF8(response.memory);
		
			wxRegEx		responseText = "\"translatedText\": \"(.*)\"";
			
			if (responseText.Matches(text_convUTF8))
				msg->setSrtTranslate(responseText.GetMatch(text_convUTF8, 1));
			else
				msg->setSrtTranslate(text_convUTF8);
			
			curl_easy_cleanup(curl);
			curl_global_cleanup();
		}			

		delete nations;
	}
	else{
		msg->setSrtTranslate(msg->getMSG());
	}
}