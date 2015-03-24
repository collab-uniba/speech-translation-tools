#include "Translate.h"

static UINT64 GetTimeStamp64()
{
	FILETIME FileTime;
	GetSystemTimeAsFileTime(&FileTime);
	return(*((PUINT64)&FileTime) / 10000);
}


float Translation::BingTranslate::GetRemainingTime()
{
	float d = (float)((double)(m_ExpirationTime - GetTimeStamp64()) * (double)(1.0 / 1000.0));
	return((d >= 0) ? d : 0);
}

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

void Translation::BingTranslate::translateThis(MessagePTR msg)
{


}

void Translation::BingTranslate::getToken(){

	CURL		*curl2;
	CURLcode	res2;
	char		url2[1024];
	char*		encode_key;

	curl_global_init(CURL_GLOBAL_ALL);

	if (curl2 = curl_easy_init())
	{
		curl_easy_setopt(curl2, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13"); //Set the url of http request
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0L);	//Use SSL Protocol
		curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0L);	//Use SSL protocol
		curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writefunc);	//Function to handle http request
		curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &token);				//Save answer into string 
		curl_easy_setopt(curl2, CURLOPT_POST, 1L);					//Inform the server to a post request
		curl_easy_setopt(curl2, CURLOPT_USERAGENT, "libcurl-agent/1.0");	//Fill user-agent to not decline our request
		curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);

		encode_key = curl_easy_escape(curl2, MY_KEY, strlen(MY_KEY));

		sprintf(url2,
			"client_id=%s&client_secret=%s&scope=http://api.microsofttranslator.com&grant_type=client_credentials",
			MY_ID,
			encode_key);

		curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, url2);
		res2 = curl_easy_perform(curl2);
	}

}