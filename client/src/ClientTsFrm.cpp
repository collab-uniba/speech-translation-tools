///-----------------------------------------------------------------
///
/// @file      ClientTsFrm.cpp
/// @author    Utente
/// Created:   07/10/2014 15:14:10
/// @section   DESCRIPTION
///            ClientTsFrm class implementation
///
///------------------------------------------------------------------

#include "GlobalVariables.h"


/*
This procedure allows the use of TextToSpeech offered by Microsoft
it has two parameters: the language of message and body of message
*/
	void speak(char *LANG, char*MSG)
	{
		
		HRESULT hr = S_OK;
		CComPtr <ISpVoice>		cpVoice;
		CComPtr <ISpObjectToken>	cpToken;
		CComPtr <IEnumSpObjectTokens>	cpEnum;
		wchar_t* voice = new wchar_t[1024];
		wcscpy(voice, L"Gender=Female;Language=");
		hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
		if (strcmp(LANG, "Italian") == 0) wcscat(voice, L"410");
		if (strcmp(LANG, "English") == 0) wcscat(voice, L"809");
		if (strcmp(LANG, "Portuguese") == 0) wcscat(voice, L"416");
			
			if (SUCCEEDED(hr)) hr = SpEnumTokens(SPCAT_VOICES, voice, NULL, &cpEnum);
			if (SUCCEEDED(hr)) hr = cpEnum->Next(1, &cpToken, NULL);
			if (SUCCEEDED(hr)) hr = cpVoice->SetVoice(cpToken);

			if (SUCCEEDED(hr)) hr = cpVoice->SetOutput(NULL, TRUE);
		
			if (SUCCEEDED(hr))
			{
			wchar_t* wString = new wchar_t[1024];
			MultiByteToWideChar(CP_ACP, 0, MSG, -1, wString, 1024);
			hr = cpVoice->Speak(wString, 0, NULL);
			}

			cpVoice.Release();
			cpEnum.Release();
			cpToken.Release();
			
	}

	void Print(char*word)
	{
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, word, -1, wString, 4096);
		MessageBox(NULL, wString, L"Test print handler", MB_OK);
	}

	static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
	{
		struct WriteThis *pooh = (struct WriteThis *)userp;

		if (size*nmemb < 1)
			return 0;

		if (pooh->sizeleft) {
			*(char *)ptr = pooh->readptr[0]; /* copy one single byte */
			pooh->readptr++;                 /* advance pointer */
			pooh->sizeleft--;                /* less data left */
			return 1;                        /* we return 1 byte at a time! */
		}

		return 0;                          /* no more data left to deliver */
	}

	/*
	This procedure save the audio recorded into the file
	*/
	void writeWaveFile(const char* filename, SAudioStreamFormat format, void* data)
	{
		if (!data)
		{
			printf("Could not save recorded data to %s, nothing recorded\n", filename);
			return;
		}

		FILE* file = fopen(filename, "wb");

		if (file)
		{
			// write wave header 
			unsigned short formatType = 1;
			unsigned short numChannels = format.ChannelCount;
			unsigned long  sampleRate = format.SampleRate;
			unsigned short bitsPerChannel = format.getSampleSize() * 8;
			unsigned short bytesPerSample = format.getFrameSize();
			unsigned long  bytesPerSecond = format.getBytesPerSecond();
			unsigned long  dataLen = format.getSampleDataSize();

			const int fmtChunkLen = 16;
			const int waveHeaderLen = 4 + 8 + fmtChunkLen + 8;

			unsigned long totalLen = waveHeaderLen + dataLen;

			fwrite("RIFF", 4, 1, file);
			fwrite(&totalLen, 4, 1, file);
			fwrite("WAVE", 4, 1, file);
			fwrite("fmt ", 4, 1, file);
			fwrite(&fmtChunkLen, 4, 1, file);
			fwrite(&formatType, 2, 1, file);
			fwrite(&numChannels, 2, 1, file);
			fwrite(&sampleRate, 4, 1, file);
			fwrite(&bytesPerSecond, 4, 1, file);
			fwrite(&bytesPerSample, 2, 1, file);
			fwrite(&bitsPerChannel, 2, 1, file);

			// write data

			fwrite("data", 4, 1, file);
			fwrite(&dataLen, 4, 1, file);
			fwrite(data, dataLen, 1, file);

			// finish

			printf("Saved audio as %s\n", filename);
			fclose(file);
		}
		else
			printf("Could not open %s to write audio data\n", filename);
	}


	/*
	This function save into the file the access_key value for the bing
	translation transitions
	*/
int JSON()
{
    const char json[2048*2]={""};
	/*
	Load json string to parse
	*/
	FILE * jfile;
	if (jfile = fopen("..\\conf\\pagina.htm", "r"))
	{
		fscanf(jfile, "%s", &json);
		fflush(jfile);
		fclose(jfile);
	}
	Document document;	// Default template parameter uses UTF8 and MemoryPoolAllocator.

#if 0
	// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (document.Parse<0>(json).HasParseError())
		return 1;
#else
	// In-situ parsing, decode strings directly in the source string. Source must be string.
	char buffer[sizeof(json)];
	memcpy(buffer, json, sizeof(json));
	if (document.ParseInsitu<0>(buffer).HasParseError())
		return 1;
#endif

	////////////////////////////////////////////////////////////////////////////
	// 2. Access values in document. 

	printf("\nAccess values in document:\n");
	assert(document.IsObject());	// Document is a JSON value represents the root of DOM. Root can be either an object or array.

	assert(document.HasMember("token_type"));
	assert(document["token_type"].IsString());
	printf("hello = %s\n", document["token_type"].GetString());
	
	assert(document.HasMember("access_token"));
	assert(document["access_token"].IsString());
	printf("hello = %s\n", document["access_token"].GetString());
	
	assert(document.HasMember("expires_in"));
	assert(document["expires_in"].IsString());
	printf("hello = %s\n", document["expires_in"].GetString());
	
	assert(document.HasMember("scope"));
	assert(document["scope"].IsString());
	printf("hello = %s\n", document["scope"].GetString());
	
	/*
	Save into JSON.txt the access_key
	*/
	FILE*js;
	if (js = fopen("..\\conf\\JSON.txt", "w"))
	{
		fprintf(js, "%s", document["access_token"].GetString());
		fclose(js);
	}
	//return document["access_token"].GetString();
	return 0;
}

/*
	Initialize Client's label colors,the values are RGB
*/
void SetupColor()
{
    colors[0].red=255;
    colors[0].green=0;
    colors[0].blue=0;
    
    colors[1].red=0;
    colors[1].green=0;
    colors[1].blue=255;
	
	colors[2].red = 102;
	colors[2].green = 0;
	colors[2].blue = 102;

	colors[3].red = 148;
	colors[3].green = 0;
	colors[3].blue = 211;
	
	colors[4].red = 0;
	colors[4].green = 100;
	colors[4].blue = 0;

	int i;
	for (i = 0; i < MAX;i++) person[i].speak = 0;
}

/*
	Initialize string structure for HTTP interactions
*/
void init_string(struct stringa *s) {
  s->len = 0;
  s->ptr = (char*)malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

/*
	Save data from http request into string
*/
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct stringa *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = (char*)realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}


void parseBing(char *word)
{

    char *buffer;
    unsigned int i;
	int result;
    buffer=strstr(word,">");
	result = (int)(buffer - word + 1);
	if (buffer != NULL)
		printf("%s found at position %d\n", word, result);
	else
		
		return;
    for(i=1;i<strlen(buffer);i++) buffer[i-1]=buffer[i];
    buffer[strlen(buffer)-10]='\0';
    StringTranslate=wxString::FromAscii(buffer); // StringTranslate contains the text translate
}

void parseGoogle(char *str)
{
    unsigned int i=0;
    int j=0;
    char * pch;
    char * stringalpha;
    char finale[2048]={""};
  
  char buffer[512]={""};
  
  pch = strtok (str,",.:\"'{}();200[]");
  while (pch != NULL)
  {
    strcat(buffer,pch);
    pch = strtok (NULL, ",.:\"'{}();200[]");
  }

    char prova[256];
	int quanto;
	char * p = strstr(buffer, "Text");
	if (p == NULL)
	{
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

char * richiestaBing(wxString StringSource, char * lang)
{
    if(strcmp(lang,CURRENT_LANG)==0) return (char*)StringSource.mb_str().data();	//If the message is written in client's language then return
    
    CURL *curl2;
    CURL *curl3;
    CURLcode res2;
    struct curl_slist *chunk = NULL;
    struct stringa f;
    init_string(&f);
    struct stringa p;
    init_string(&p);
    
	
    curl_global_init(CURL_GLOBAL_ALL);
 
    curl2 = curl_easy_init();
    if(curl2) 
    {
  
    curl_easy_setopt(curl2, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13"); //Set the url of http request
    curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYHOST, 0L);	//Use SSL Protocol
    curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0L);	//Use SSL protocol
    curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writefunc);	//Function to handle http request
    curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &f);				//Save answer into string 
    curl_easy_setopt(curl2, CURLOPT_POST, 1L);					//Inform the server to a post request
    curl_easy_setopt(curl2, CURLOPT_USERAGENT, "libcurl-agent/1.0");	//Fill user-agent to not decline our request
    curl_easy_setopt(curl2, CURLOPT_VERBOSE, 1L);
     
    FILE *bing;
	if (bing = fopen("..\\conf\\BING.txt", "r"))
	{
    
    char CLIENT_ID[50]="";
    char CLIENT_SECRET[128]="";
    
    fscanf(bing,"%s",CLIENT_ID);
    fscanf(bing,"%s",CLIENT_SECRET);
    
    char * encode_key=curl_easy_escape(curl2,CLIENT_SECRET,strlen(CLIENT_SECRET));	//Leave incorrect url characters from CLIENT_ID nad CLIENT_SECRET
    char url2[1024]={""};
    strcpy(url2,"client_id=");
    strcat(url2,CLIENT_ID);
    strcat(url2,"&client_secret=");
    strcat(url2,encode_key);
    strcat(url2,"&scope=http://api.microsofttranslator.com&grant_type=client_credentials");
    curl_easy_setopt(curl2, CURLOPT_POSTFIELDS, url2);
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

    JSON(); //Parse answer for access_token value to start the translation
    char auth[2048]={""};
    char header[2048+512]={""};
    
	FILE * jfile;
	if (jfile = fopen("..\\conf\\JSON.txt", "r+"))
	{
		fscanf(jfile, "%s", &auth);
		fflush(jfile);
		fclose(jfile);
	}
    strcpy(header,"Authorization: Bearer ");
    strcat(header,auth);
    char languagesrc[30]={""};
    char languagedst[30]={""};
    if(strcmp(lang,"Italian")==0)
    {
        strcpy(languagesrc,"it");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    else if(strcmp(lang,"English")==0)
    {
        strcpy(languagesrc,"en");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    else if(strcmp(lang,"Portuguese")==0)
    {
        strcpy(languagesrc,"pt");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    curl3 = curl_easy_init();
    char *trueheader=curl_easy_unescape(curl3 , header , 0 , NULL);
	
	
    const char *BufferSource=curl_easy_escape(curl3, (char*)StringSource.mb_str().data(), strlen((char*)StringSource.mb_str().data()));
	
	
    char url3[512]={""};
    strcpy(url3,"http://api.microsofttranslator.com/V2/Http.svc/Translate?text=");
	
	//strcat(url3, url_encode(pr).c_str());
	strcat(url3, BufferSource);
    strcat(url3,"&from=");
    strcat(url3,languagesrc);
    strcat(url3,"&to=");
    strcat(url3,languagedst);
  
    curl_easy_setopt(curl3, CURLOPT_URL, url3);
    curl_easy_setopt(curl3, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    chunk = curl_slist_append(chunk, header);
    res2 = curl_easy_setopt(curl3, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl3, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl3, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl3, CURLOPT_WRITEDATA, &p);
    res2 = curl_easy_perform(curl3);
   
   
    if(res2 != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res2));
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


char* richiestaGoogle(wxString StringSource, char * lang)
{
  
    if(strcmp(lang,CURRENT_LANG)==0) return (char*)StringSource.mb_str().data();
    
	CURL *curl;
    CURLcode res;

    strcpy(url,"");
    char languagesrc[30]={""};
    char languagedst[30]={""};
    curl_global_init(CURL_GLOBAL_DEFAULT);
 
    curl = curl_easy_init();
    struct stringa s;
    init_string(&s);
    if(strcmp(lang,"Italian")==0)
    {
        strcpy(languagesrc,"it");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    else if(strcmp(lang,"English")==0)
    {
        strcpy(languagesrc,"en");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    else if(strcmp(lang,"Portuguese")==0)
    {
        strcpy(languagesrc,"pt");
        if(strcmp(CURRENT_LANG,"English")==0) strcpy(languagedst,"en");
        if(strcmp(CURRENT_LANG,"Italian")==0) strcpy(languagedst,"it");
        if(strcmp(CURRENT_LANG,"Portuguese")==0) strcpy(languagedst,"pt");
    }
    
    
    if(curl) 
    {
    strcpy(url,"https://www.googleapis.com/language/translate/v2?key=");
    strcat(url,GOOGLE_API_KEY);
    
    strcat(url,"&q=");
	const char *BufferSource = curl_easy_escape(curl, (char*)StringSource.mb_str().data(), strlen((char*)StringSource.mb_str().data()));
    strcat(url,BufferSource);
    strcat(url,"&source=");
    strcat(url,languagesrc);
    strcat(url,"&target=");
    strcat(url,languagedst);
   
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    res = curl_easy_perform(curl);
  
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    
    /* always cleanup */ 
    curl_easy_cleanup(curl);
    return s.ptr;
  }
 
  curl_global_cleanup();
}


/* This is a global variable to indicate if sound needs to be recorded.
   Normally one would have thread synchronization with locks etc. for
   thread safety. In the intterest of simplicity, this sample uses the
   most simple way to safely record, using this variable
*/
int recordSound = 0;

/* Enable to use custom encryption */
/* #define USE_CUSTOM_ENCRYPTION
#define CUSTOM_CRYPT_KEY 123 */

/*
 * Callback for connection status change.
 * Connection status switches through the states STATUS_DISCONNECTED, STATUS_CONNECTING, STATUS_CONNECTED and STATUS_CONNECTION_ESTABLISHED.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   newStatus                 - New connection status, see the enum ConnectStatus in clientlib_publicdefinitions.h
 *   errorNumber               - Error code. Should be zero when connecting or actively disconnection.
 *                               Contains error state when losing connection.
 */
void onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	printf("Connect status changed: %llu %d %d\n", (unsigned long long)serverConnectionHandlerID, newStatus, errorNumber);
	/* Failed to connect ? */
	if(newStatus == STATUS_DISCONNECTED && errorNumber == ERROR_failed_connection_initialisation) {
		printf("Looks like there is no server running, terminate!\n");
		exit(-1);
	}
	
}

/*
 * Callback for current channels being announced to the client after connecting to a server.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   channelID                 - ID of the announced channel
 *    channelParentID           - ID of the parent channel
 */
void onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID) {
	/* Query channel name from channel ID */
	char* name;
	unsigned int error;

	printf("onNewChannelEvent: %llu %llu %llu\n", (unsigned long long)serverConnectionHandlerID, (unsigned long long)channelID, (unsigned long long)channelParentID);
    if((error = ts3client_getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, &name)) == ERROR_ok) {
		printf("New channel: %llu %s \n", (unsigned long long)channelID, name);
        ts3client_freeMemory(name);  /* Release dynamically allocated memory only if function succeeded */
	} else {
		char* errormsg;
        if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
		    printf("Error getting channel name in onNewChannelEvent: %s\n", errormsg);
		    ts3client_freeMemory(errormsg);
        }
	}
}

/*
 * Callback for just created channels.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   channelID                 - ID of the announced channel
 *   channelParentID           - ID of the parent channel
 *    invokerID                 - ID of the client who created the channel
 *   invokerName               - Name of the client who created the channel
 */
void onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
    char* name;

	/* Query channel name from channel ID */
    if(ts3client_getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, &name) != ERROR_ok)
		return;
	printf("New channel created: %s \n", name);
	ts3client_freeMemory(name);  /* Release dynamically allocated memory only if function succeeded */
}

/*
 * Callback when a channel was deleted.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   channelID                 - ID of the deleted channel
 *   invokerID                 - ID of the client who deleted the channel
 *   invokerName               - Name of the client who deleted the channel
 */
void onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
	printf("Channel ID %llu deleted by %s (%u)\n", (unsigned long long)channelID, invokerName, invokerID);
}

/*
 * Called when a client joins, leaves or moves to another channel.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   clientID                  - ID of the moved client
 *   oldChannelID              - ID of the old channel left by the client
 *   newChannelID              - ID of the new channel joined by the client
 *   visibility                - Visibility of the moved client. See the enum Visibility in clientlib_publicdefinitions.h
 *                               Values: ENTER_VISIBILITY, RETAIN_VISIBILITY, LEAVE_VISIBILITY
 */
void onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
	printf("ClientID %u moves from channel %llu to %llu with message %s\n", clientID, (unsigned long long)oldChannelID, (unsigned long long)newChannelID, moveMessage);
}

/*
 * Callback for other clients in current and subscribed channels being announced to the client.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   clientID                  - ID of the announced client
 *   oldChannelID              - ID of the subscribed channel where the client left visibility
 *   newChannelID              - ID of the subscribed channel where the client entered visibility
 *   visibility                - Visibility of the announced client. See the enum Visibility in clientlib_publicdefinitions.h
 *                               Values: ENTER_VISIBILITY, RETAIN_VISIBILITY, LEAVE_VISIBILITY
 */
void onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
	char* name;

    /* Query client nickname from ID */
	if(ts3client_getClientVariableAsString(serverConnectionHandlerID, clientID, CLIENT_NICKNAME, &name) != ERROR_ok)
		return;
	printf("New client: %s \n", name);
	ts3client_freeMemory(name);  /* Release dynamically allocated memory only if function succeeded */
}

/*
 * Called when a client drops his connection.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   clientID                  - ID of the moved client
 *   oldChannelID              - ID of the channel the leaving client was previously member of
 *   newChannelID              - 0, as client is leaving
 *   visibility                - Always LEAVE_VISIBILITY
 *   timeoutMessage            - Optional message giving the reason for the timeout
 */
void onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage) {
	printf("ClientID %u timeouts with message %s\n", clientID, timeoutMessage);
	count_client--;
}

/*
 * This event is called when a client starts or stops talking.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   status                    - 1 if client starts talking, 0 if client stops talking
 *   isReceivedWhisper         - 1 if this event was caused by whispering, 0 if caused by normal talking
 *   clientID                  - ID of the client who announced the talk status change
 */
void onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID) {
	char* name;
	int i;
    /* Query client nickname from ID */
	if(ts3client_getClientVariableAsString(serverConnectionHandlerID, clientID, CLIENT_NICKNAME, &name) != ERROR_ok)
		return;
    if(status == STATUS_TALKING)
        {
		for (i = 0; i < MAX; i++)
		{
			if (person[i].name==name)
			{
				person[i].speak = 1;
			}
		}
        
		if (sound_flag == false && tasto_stt_flag==true)
		{
			sound_flag = true;
			recorder->startRecordingBufferedAudio();
		}
    } else {
		for (i = 0; i < MAX; i++)
		{
			if (person[i].name == name && person[i].speak==1)
			{
				person[i].speak = 0;
				break;
			}
		}
		
		if (tasto_stt_flag == true || sound_flag==true || finish_ctrl_flag==true)
		{
			if (recorder->isRecording() == false) return;
			recorder->stopRecordingAudio();
			writeWaveFile("recorded.wav", recorder->getAudioFormat(), recorder->getRecordedAudioData());
			
			if(strcmp(CURRENT_LANG,"Italian")==0) WinExec("java -jar ASR.jar -w recorded.wav -l it_IT", SW_HIDE);
			if (strcmp(CURRENT_LANG, "English") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l en_US", SW_HIDE);
			if (strcmp(CURRENT_LANG, "Portuguese") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l pt_BR", SW_HIDE);

		}
		/*else if (finish_ctrl_flag == true)
		{
			recorder->stopRecordingAudio();
			writeWaveFile("recorded.wav", recorder->getAudioFormat(), recorder->getRecordedAudioData());

			if (strcmp(CURRENT_LANG, "Italian") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l it_IT", SW_HIDE);
			if (strcmp(CURRENT_LANG, "English") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l en_US", SW_HIDE);
			if (strcmp(CURRENT_LANG, "Portuguese") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l pt_BR", SW_HIDE);
			finish_ctrl_flag = false;
		}*/
		
    }
	ts3client_freeMemory(name);  /* Release dynamically allocated memory only if function succeeded */
}

/*
 * This event is called when another client starts whispering to own client. Own client can decide to accept or deny
 * receiving the whisper by adding the sending client to the whisper allow list. If not added, whispering is blocked.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   clientID                  - ID of the whispering client
 */
void onIgnoredWhisperEvent(uint64 serverConnectionHandlerID, anyID clientID) {
	unsigned int error;

	/* Add sending client to whisper allow list so own client will hear the voice data.
	 * It is sufficient to add a clientID only once, not everytime this event is called. However it won't
	 * hurt to add the same clientID to the allow list repeatedly, but is is not necessary. */
	if((error = ts3client_allowWhispersFrom(serverConnectionHandlerID, clientID)) != ERROR_ok) {
		printf("Error setting client on whisper allow list: %u\n", error);
	}
	printf("Added client %d to whisper allow list\n", clientID);
}

void onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage) {
	printf("Error for server %llu: %s (%u) %s\n", (unsigned long long)serverConnectionHandlerID, errorMessage, error, extraMessage);
}

/*
 * Callback for user-defined logging.
 *
 * Parameter:
 *   logMessage        - Log message text
 *   logLevel          - Severity of log message
 *   logChannel        - Custom text to categorize the message channel
 *   logID             - Virtual server ID giving the virtual server source of the log event
 *   logTime           - String with the date and time the log entry occured
 *   completeLogString - Verbose log message including all previous parameters for convinience
 */
void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString) {
	/* Your custom error display here... */
	/* printf("LOG: %s\n", completeLogString); */
	if(logLevel == LogLevel_CRITICAL) {
		exit(1);  /* Your custom handling of critical errors */
	}
}

/*
 * Callback allowing to apply custom encryption to outgoing packets.
 * Using this function is optional. Do not implement if you want to handle the TeamSpeak 3 SDK encryption.
 *
 * Parameters:
 *   dataToSend - Pointer to an array with the outgoing data to be encrypted
 *   sizeOfData - Pointer to an integer value containing the size of the data array
 *
 * Apply your custom encryption to the data array. If the encrypted data is smaller than sizeOfData, write
 * your encrypted data into the existing memory of dataToSend. If your encrypted data is larger, you need
 * to allocate memory and redirect the pointer dataToSend. You need to take care of freeing your own allocated
 * memory yourself. The memory allocated by the SDK, to which dataToSend is originally pointing to, must not
 * be freed.
 *
 */
void onCustomPacketEncryptEvent(char** dataToSend, unsigned int* sizeOfData) {
#ifdef USE_CUSTOM_ENCRYPTION
	unsigned int i;
	for(i = 0; i < *sizeOfData; i++) {
		(*dataToSend)[i] ^= CUSTOM_CRYPT_KEY;
	}
#endif
}

/*
 * Callback allowing to apply custom encryption to incoming packets
 * Using this function is optional. Do not implement if you want to handle the TeamSpeak 3 SDK encryption.
 *
 * Parameters:
 *   dataToSend - Pointer to an array with the received data to be decrypted
 *   sizeOfData - Pointer to an integer value containing the size of the data array
 *
 * Apply your custom decryption to the data array. If the decrypted data is smaller than dataReceivedSize, write
 * your decrypted data into the existing memory of dataReceived. If your decrypted data is larger, you need
 * to allocate memory and redirect the pointer dataReceived. You need to take care of freeing your own allocated
 * memory yourself. The memory allocated by the SDK, to which dataReceived is originally pointing to, must not
 * be freed.
 */
void onCustomPacketDecryptEvent(char** dataReceived, unsigned int* dataReceivedSize) {
#ifdef USE_CUSTOM_ENCRYPTION
	unsigned int i;
	for(i = 0; i < *dataReceivedSize; i++) {
		(*dataReceived)[i] ^= CUSTOM_CRYPT_KEY;
	}
#endif
}

/*
 * Callback allowing access to voice data after it has been mixed by TeamSpeak 3
 * This event can be used to alter/add to the voice data being played by TeamSpeak 3.
 * But here we use it to record the voice data to a wave file.
 *
 * Parameters:
 *   serverConnectionHandlerID - Server connection handler ID
 *   samples - Pointer to a buffer containg 16 bit voice data samples at 48000 Hz. Channels are interleaved.
 *   sampleCount - The number of samples 1 channel of sample data contains.
 *   channels - The number of channels the sample data contains.
 *   channelSpeakerArray - A bitmask of the speakers for each channel.
 *   channelFillMask - A bitmask of channels that actually have valid data.
 *
 * -The size of the data "samples" points to is: sizeof(short)*sampleCount*channels
 * -channelSpeakerArray uses SPEAKER_ defined in public_definitions.h
 * -In the interrest of optimizations, a channel only contains data, if there is sound data for it. For example:
 * in 5.1 or 7.1 we (almost) never have data for the subwoofer. Teamspeak then leaves the data in this channel
 * undefined. This is more efficient for mixing.
 * This implementation will record sound to a 2 channel (stereo) wave file. This sample assumes there is only
 * 1 connection to a server
 * Hint: Normally you would want to defer the writing to an other thread because this callback is very time sensitive
 */
void onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask){
	#define OUTPUTCHANNELS 2
	static FILE *pfile = NULL;
	static struct WaveHeader header = { {'R','I','F','F'}, 0, {'W','A','V','E'}, {'f','m','t',' '}, 16, 1, 2, 48000, 48000*(16/2)*2, (16/2)*2, 16, {'d','a','t','a'}, 0 };

	int currentSampleMix[OUTPUTCHANNELS]; /*a per channel/sample mix buffer*/
	int channelCount[OUTPUTCHANNELS] = {0,0}; /*how many input channels does the output channel contain */

	int currentInChannel;
	int currentOutChannel;
	int currentSample;
	int channelBit;

	/*for clipping*/
	short shortval;
	int   intval;

	short* outputBuffer;

	int leftChannelMask  = SPEAKER_FRONT_LEFT  | SPEAKER_FRONT_CENTER | SPEAKER_BACK_LEFT  | SPEAKER_FRONT_LEFT_OF_CENTER  | SPEAKER_BACK_CENTER | SPEAKER_SIDE_LEFT  | SPEAKER_TOP_CENTER | SPEAKER_TOP_FRONT_LEFT  | SPEAKER_TOP_FRONT_CENTER | SPEAKER_TOP_BACK_LEFT  | SPEAKER_TOP_BACK_CENTER;
	int rightChannelMask = SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_RIGHT_OF_CENTER | SPEAKER_BACK_CENTER | SPEAKER_SIDE_RIGHT | SPEAKER_TOP_CENTER | SPEAKER_TOP_FRONT_RIGHT | SPEAKER_TOP_FRONT_CENTER | SPEAKER_TOP_BACK_RIGHT | SPEAKER_TOP_BACK_CENTER;

	/*detect state changes*/
	if (recordSound && (pfile == NULL)){
		/*start recording*/
		header.len = 0;
		header.dataLen = 0;
		if((pfile = fopen("..\\conf\\recordedvoices.wav", "wb")) == NULL) return;
		fwrite(&header, sizeof(struct WaveHeader), 1, pfile);
	} else if (!recordSound && (pfile != NULL)){
		/*stop recording*/
		header.len = sizeof(struct WaveHeader)+header.dataLen - 8;
		fseek (pfile, 0, SEEK_SET);
		fwrite(&header, sizeof(struct WaveHeader), 1, pfile);
		fclose(pfile);
		pfile = NULL;
	}

	/*if there is nothing to do, quit*/
	if (pfile == NULL || sampleCount == 0 || channels == 0) return;

	/* initialize channel mixing */
	channelBit = 0;
	currentInChannel = 0;
	/*loop over all possible speakers*/
	for (currentInChannel=0; currentInChannel < channels; ++currentInChannel) {
		/*if the speaker has actual data*/
		if ((*channelFillMask & (1<<currentInChannel)) != 0){
			/*add to the outChannelSpeakerSet*/
			if ((channelSpeakerArray[currentInChannel] & leftChannelMask) != 0) channelCount[0]++;
			if ((channelSpeakerArray[currentInChannel] & rightChannelMask) != 0) channelCount[1]++;
		}
	}

	/*get the outbut buffer*/
	outputBuffer = (short*) malloc( sizeof(short)*sampleCount*2 /*output channels*/);

	/* hint: if channelCount is 0 for all channels, we could write a zero buffer and quit here */

	/*mix the samples*/
	for (currentSample = 0; currentSample < sampleCount; currentSample++){
		currentSampleMix[0] = currentSampleMix[1] = 0;

		/*loop over all channels in this frame */
		for(currentInChannel =0; currentInChannel < channels; currentInChannel++){
			if ((channelSpeakerArray[currentInChannel] & leftChannelMask)  != 0) currentSampleMix[0] += samples[ (currentSample*channels)+currentInChannel ];
			if ((channelSpeakerArray[currentInChannel] & rightChannelMask) != 0) currentSampleMix[1] += samples[ (currentSample*channels)+currentInChannel ];
		}

		/*collected all samples, store mixed sample */
		for (currentOutChannel = 0; currentOutChannel < OUTPUTCHANNELS; currentOutChannel++){
			if (channelCount[currentOutChannel] == 0){
				outputBuffer[ (currentSample*OUTPUTCHANNELS) + currentOutChannel] = 0;
			} else {
				/*clip*/
				intval = currentSampleMix[currentOutChannel]/channelCount[currentOutChannel];
				if (intval >= SHRT_MAX) shortval = SHRT_MAX;
				else if (intval <= SHRT_MIN) shortval = SHRT_MIN;
				else shortval = (short) intval;
				/*store*/
				outputBuffer[ (currentSample*OUTPUTCHANNELS) + currentOutChannel] = shortval;
			}
		}
	}

	/*write data & update header */
	fwrite(outputBuffer, sampleCount*sizeof(short)*OUTPUTCHANNELS, 1, pfile);
	header.dataLen += sampleCount*sizeof(short)*OUTPUTCHANNELS;

	/*free buffer*/
	free(outputBuffer);
}

/*
 * Print all channels of the given virtual server
 */
void showChannels(uint64 serverConnectionHandlerID) {
    uint64 *ids;
    int i;
    unsigned int error;

    printf("\nList of channels on virtual server %llu:\n", (unsigned long long)serverConnectionHandlerID);
    if((error = ts3client_getChannelList(serverConnectionHandlerID, &ids)) != ERROR_ok) {  /* Get array of channel IDs */
        printf("Error getting channel list: %d\n", error);
        return;
    }
    if(!ids[0]) {
        printf("No channels\n\n");
        ts3client_freeMemory(ids);
        return;
    }
    for(i=0; ids[i]; i++) {
        char* name;
        if((error = ts3client_getChannelVariableAsString(serverConnectionHandlerID, ids[i], CHANNEL_NAME, &name)) != ERROR_ok) {  /* Query channel name */
            printf("Error getting channel name: %d\n", error);
            break;
        }
        printf("%llu - %s\n", (unsigned long long)ids[i], name);

        
        ts3client_freeMemory(name);
    }
    printf("\n");

    ts3client_freeMemory(ids);  /* Release array */
}

/*
 * Print all clients on the given virtual server in the specified channel
 */
void showChannelClients(uint64 serverConnectionHandlerID, uint64 channelID) {
    anyID* ids;
	anyID ownClientID;
    int i;
    unsigned int error;

    printf("\nList of clients in channel %llu on virtual server %llu:\n", (unsigned long long)channelID, (unsigned long long)serverConnectionHandlerID);
    if((error = ts3client_getChannelClientList(serverConnectionHandlerID, channelID, &ids)) != ERROR_ok) {  /* Get array of client IDs */
        printf("Error getting client list for channel %llu: %d\n", (unsigned long long)channelID, error);
        return;
    }
    if(!ids[0]) {
        printf("No clients\n\n");
        ts3client_freeMemory(ids);
        return;
    }

	/* Get own clientID as we need to call CLIENT_FLAG_TALKING with getClientSelfVariable for own client */
	if((error = ts3client_getClientID(serverConnectionHandlerID, &ownClientID)) != ERROR_ok) {
		printf("Error querying own client ID: %d\n", error);
		return;
	}

    for(i=0; ids[i]; i++) {
        char* name;
        int talkStatus;

        if((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, ids[i], CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
            printf("Error querying client nickname: %d\n", error);
            break;
        }

		if(ids[i] == ownClientID) {  /* CLIENT_FLAG_TALKING must be queried with getClientSelfVariable for own client */
			if((error = ts3client_getClientSelfVariableAsInt(serverConnectionHandlerID, CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying own client talk status: %d\n", error);
				break;
			}
		} else {
			if((error = ts3client_getClientVariableAsInt(serverConnectionHandlerID, ids[i], CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying client talk status: %d\n", error);
				break;
			}
		}

        printf("%u - %s (%stalking)\n", ids[i], name, (talkStatus == STATUS_TALKING ? "" : "not "));

        ts3client_freeMemory(name);
    }
    printf("\n");

    ts3client_freeMemory(ids);  /* Release array */
}

unsigned int  ts3client_requestSendPrivateTextMsg(uint64 serverConnectionHandlerID,  const char *message,
anyID targetClientID, const char *returnCode)
{
	return 0;
}

unsigned int ts3client_requestSendServerTextMsg(uint64 serverConnectionHandlerID, const char *message,
const char *returnCode)
{
	return 0;
}

void onTextMessageEvent(uint64 serverConnectionHandlerID,  anyID targetMode,  anyID toID, anyID fromID, const char* fromName,const char* fromUniqueIdentifier, const char* message)
{
    char *name;
    unsigned int error;
    wxString mystring = wxString::FromAscii(message);
    
     if((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, fromID, CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
     printf("Error querying client nickname: %d\n", error);
     return;
        }
        
		
       
		strtok((char*)name, "$");	//Extract from entire message the name value example: $Adam -> Adam
		strNick = wxString::FromAscii(strtok(NULL, "$"));
	    strcpy(LANG_MSG_SRC, strtok((char*)message, "\n"));	//Extract from entire message the language field
		strcpy(MSG_SRC, strtok(NULL, "\n"));				//Extract the body of message

		/*Example $Adam$English$How are you?
		strNick= Adam;
		LANG_MSG_SRC=English
		MSG_SRC=How are you?
		*/

		wxString parsata = wxString::FromAscii(MSG_SRC); //convert char * to wxString
		
		if (parsata == "write1")	//if it is true the client is typing a message
		{
			int i;
			for (i = 0; i < MAX; i++)
			{
				if (person[i].name == strNick)
				{
					person[i].write = 1;	//this person is writing
				}
			}
			return;
		}

		if (parsata == "write0")	//if it is true the client has stopped to write
		{
			int i;
			for (i = 0; i < MAX; i++)
			{
				if (person[i].name == strNick)
				{
					person[i].write = 0;

				}
			}
			return;
		}

        strGlobale=wxString::FromAscii(name)+": "+mystring;
		
		
        
        
		/*
		Ignore Debug value from Translation Service
		*/

		if (MSG_SRC[0] == '<') return;
		strMessage = wxString::FromAscii(MSG_SRC);

        
		if (parsata == "</html>") return;
		if (parsata == ">") return;

		

		gridptr->Scroll(curRow+20,curCol+20);	//ScrollDown chat when message is arrived
		
		if (strcmp(LANG_MSG_SRC, CURRENT_LANG) == 0)	//if the message's language is equal with my language then display without translation
		{
			index++;
			StringTranslate = wxString::FromAscii(MSG_SRC);
			return;
		}

        if(strcmp(SERVICE,"google")==0)
        {
		if (strcmp(MSG_SRC, richiestaGoogle(MSG_SRC, LANG_MSG_SRC)) == 0) StringTranslate = wxString::FromAscii(MSG_SRC);
		else
		{
			parseGoogle(richiestaGoogle(parsata, LANG_MSG_SRC));
			index++;
			diary[index].msgold = wxString::FromUTF8(parsata);	//Save original message
			diary[index].msgnew = StringTranslate;				//Save translate message
		}
        }
        
        if(strcmp(SERVICE,"bing")==0)
        {
			if (strcmp(MSG_SRC, richiestaBing(MSG_SRC, LANG_MSG_SRC)) == 0) StringTranslate = wxString::FromAscii(MSG_SRC);
			else
			{
				parseBing(richiestaBing(parsata, LANG_MSG_SRC));
				index++;
				diary[index].msgold = wxString::FromUTF8(parsata);	//Save original message
				diary[index].msgnew = StringTranslate;				//Save translate message
			}
        }

    return;
}

unsigned int  ts3client_requestSendChannelTextMsg(uint64 serverConnectionHandlerID,  const char *message,
anyID targetChannelID, const char *returnCode)
{
	return 0;
}

/*
 * Print all visible clients on the given virtual server
 */
void showClients(uint64 serverConnectionHandlerID) {
    anyID *ids;
	anyID ownClientID;
    int i;
    
    unsigned int error;
    count_client=0;

    printf("\nList of all visible clients on virtual server %llu:\n", (unsigned long long)serverConnectionHandlerID);
    if((error = ts3client_getClientList(serverConnectionHandlerID, &ids)) != ERROR_ok) {  /* Get array of client IDs */
        printf("Error getting client list: %d\n", error);
        return;
    }
    if(!ids[0]) {
        printf("No clients\n\n");
        ts3client_freeMemory(ids);
        return;
    }

	/* Get own clientID as we need to call CLIENT_FLAG_TALKING with getClientSelfVariable for own client */
	if((error = ts3client_getClientID(serverConnectionHandlerID, &ownClientID)) != ERROR_ok) {
		printf("Error querying own client ID: %d\n", error);
		return;
	}

	/*
	Reset informations about clients
	*/
	for (i = 0; i < MAX; i++)
	{
		person[i].name = "";
		person[i].used = 0;
		person[i].lang = "";
		person[i].speak = 0;
		
	}

    for(i=0; ids[i]; i++) 
	{
        char* name;
        int talkStatus;

        if((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, ids[i], CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
            printf("Error querying client nickname: %d\n", error);
            break;
        }

		if(ids[i] == ownClientID) {  /* CLIENT_FLAG_TALKING must be queried with getClientSelfVariable for own client */
			if((error = ts3client_getClientSelfVariableAsInt(serverConnectionHandlerID, CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying own client talk status: %d\n", error);
				break;
			}
		} else {
			if((error = ts3client_getClientVariableAsInt(serverConnectionHandlerID, ids[i], CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying client talk status: %d\n", error);
				break;
			}
		}
		
		
        //if(strcmp(name,NICK)==0) set_color_client=i;
        
		printf("%u - %s (%stalking)\n", ids[i], name, (talkStatus == STATUS_TALKING ? "" : "not "));
        count_client++;
        
		
		person[i].lang = strtok((char*)name, "$");
		person[i].name = strtok(NULL, "$");
        person[i].color=i;
        person[i].used=1;
		if (talkStatus == STATUS_TALKING) person[i].speak = 1;

        ts3client_freeMemory(name);
    }
    printf("\n");

    ts3client_freeMemory(ids);  /* Release array */
}

void emptyInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

uint64 enterChannelID() {
    uint64 channelID;
    int n;

    printf("\nEnter channel ID: ");
    n = scanf("%llu", (unsigned long long*)&channelID);
    emptyInputBuffer();
    if(n == 0) {
        printf("Invalid input. Please enter a number.\n\n");
        return 0;
    }
    return channelID;
}

void createDefaultChannelName(char *name) {
    static int i = 1;
    sprintf(name, "Channel_%d", i++);
}

void enterName(char *name) {
    char *s;
    printf("\nEnter name: ");
    fgets(name, NAME_BUFSIZE, stdin);
    s = strrchr(name, '\n');
    if(s) {
        *s = '\0';
    }
}

void createChannel(uint64 serverConnectionHandlerID, const char *name) {
    unsigned int error;

    /* Set data of new channel. Use channelID of 0 for creating channels. */
    CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_NAME,                name));
    CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_TOPIC,               "Test channel topic"));
    CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_DESCRIPTION,         "Test channel description"));
    CHECK_ERROR(ts3client_setChannelVariableAsInt   (serverConnectionHandlerID, 0, CHANNEL_FLAG_PERMANENT,      1));
    CHECK_ERROR(ts3client_setChannelVariableAsInt   (serverConnectionHandlerID, 0, CHANNEL_FLAG_SEMI_PERMANENT, 0));

    /* Flush changes to server */
    CHECK_ERROR(ts3client_flushChannelCreation(serverConnectionHandlerID, 0));

    printf("\nCreated channel\n\n");
    return;

on_error:
    printf("\nError creating channel: %d\n\n", error);
}

void deleteChannel(uint64 serverConnectionHandlerID) {
    uint64 channelID;
    unsigned int error;

    /* Query channel ID from user */
    channelID = enterChannelID();

    /* Delete channel */
    if((error = ts3client_requestChannelDelete(serverConnectionHandlerID, channelID, 0, NULL)) == ERROR_ok) {
        printf("Deleted channel %llu\n\n", (unsigned long long)channelID);
    } else {
        char* errormsg;
        if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
            printf("Error requesting channel delete: %s (%d)\n\n", errormsg, error);
            ts3client_freeMemory(errormsg);
        }
    }
}

void renameChannel(uint64 serverConnectionHandlerID) {
    uint64 channelID;
    unsigned int error;
    char name[NAME_BUFSIZE];

    /* Query channel ID from user */
    channelID = enterChannelID();

    /* Query new channel name from user */
    enterName(name);

    /* Change channel name and flush changes */
    CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, name));
    CHECK_ERROR(ts3client_flushChannelUpdates(serverConnectionHandlerID, channelID));

    printf("Renamed channel %llu\n\n", (unsigned long long)channelID);
    return;

on_error:
    printf("Error renaming channel: %d\n\n", error);
}

void switchChannel(uint64 serverConnectionHandlerID) {
    unsigned int error;

    /* Query channel ID from user */
    uint64 channelID = enterChannelID();

    /* Query own client ID */
    anyID clientID;
    if((error = ts3client_getClientID(serverConnectionHandlerID, &clientID)) != ERROR_ok) {
        printf("Error querying own client ID: %d\n", error);
        return;
    }

    /* Request moving own client into given channel */
    if((error = ts3client_requestClientMove(serverConnectionHandlerID, clientID, channelID, "", NULL)) != ERROR_ok) {
        printf("Error moving client into channel channel: %d\n", error);
        return;
    }
    printf("Switching into channel %llu\n\n", (unsigned long long)channelID);
}

void toggleVAD(uint64 serverConnectionHandlerID) {
    static short b = 1;
    unsigned int error;

    /* Adjust "vad" preprocessor value */
    if((error = ts3client_setPreProcessorConfigValue(serverConnectionHandlerID, "vad", b ? "false" : "true")) != ERROR_ok) {
        printf("Error toggling VAD: %d\n", error);
        return;
    }
    b = !b;
    printf("\nToggled VAD %s.\n\n", b ? "on" : "off");
}

void setVadLevel(uint64 serverConnectionHandlerID) {
	int vad, n;
	unsigned int error;
	char s[100];

	printf("\nEnter VAD level: ");
	n = scanf("%d", &vad);
	emptyInputBuffer();
	if (n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	
	/*
	Load vad value from file
	*/
	FILE *mic;
	if (mic = fopen("..\\conf\\mic.txt", "r"))
	{
		fscanf(mic, "%d", &vad);
		fflush(mic);
		fclose(mic);
	}
	else vad = 1;	//if the file isnt exist set vad to 1
	/* Adjust "voiceactivation_level" preprocessor value */
	snprintf(s, 100, "%d", vad);
	if ((error = ts3client_setPreProcessorConfigValue(serverConnectionHandlerID, "voiceactivation_level", s)) != ERROR_ok) {
		printf("Error setting VAD level: %d\n", error);
		return;
	}
	printf("\nSet VAD level to %s.\n\n", s);
}

void requestWhisperList(uint64 serverConnectionHandlerID) {
	int n;
	anyID clientID;
	uint64 targetID;
	unsigned int error;
	uint64 targetChannels[2];

	printf("\nEnter ID of the client whose whisper list should be modified (0 for own client): ");
	n = scanf("%hu", &clientID);
	emptyInputBuffer();
	if(n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	printf("\nEnter target channel ID: ");
	n = scanf("%llu", (unsigned long long*)&targetID);
	emptyInputBuffer();
	if(n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	targetChannels[0] = targetID;
	targetChannels[1] = 0;

	if((error = ts3client_requestClientSetWhisperList(serverConnectionHandlerID, clientID, targetChannels, NULL, NULL)) != ERROR_ok) {
		char* errormsg;
		if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error requesting whisperlist: %s\n", errormsg);
			ts3client_freeMemory(errormsg);
		}
		return;
	}
	printf("Whisper list requested for client %d in channel %llu\n", clientID, (unsigned long long)targetID);
}

void requestClearWhisperList(uint64 serverConnectionHandlerID) {
	int n;
	anyID clientID;
	unsigned int error;

	printf("\nEnter client ID: ");
	printf("\nEnter ID of the client whose whisper list should be cleared (0 for own client): ");
	n = scanf("%hu", &clientID);
	emptyInputBuffer();
	if(n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	if((error = ts3client_requestClientSetWhisperList(serverConnectionHandlerID, clientID, NULL, NULL, NULL)) != ERROR_ok) {
		char* errormsg;
		if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error clearing whisperlist: %s\n", errormsg);
			ts3client_freeMemory(errormsg);
		}
		return;
	}
	printf("Whisper list cleared for client %u\n", clientID);
}

void toggleRecordSound(uint64 serverConnectionHandlerID){
	unsigned int error;

	if (!recordSound){
		recordSound = 1;
		if((error = ts3client_startVoiceRecording(serverConnectionHandlerID)) != ERROR_ok){
			char* errormsg;
			if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
				printf("Error notifying server of startVoiceRecording: %s\n", errormsg);
				ts3client_freeMemory(errormsg);
				return;
			}
		}
		printf("Started recording sound to wav\n");
	} else {
		recordSound = 0;
		if((error = ts3client_stopVoiceRecording(serverConnectionHandlerID)) != ERROR_ok){
			char* errormsg;
			if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
				printf("Error notifying server of stopVoiceRecording: %s\n", errormsg);
				ts3client_freeMemory(errormsg);
				return;
			}
		}
		printf("Stopped recording sound to wav\n");
	}
}

int readIdentity(char* identity) {
    FILE *file;

    if((file = fopen("..\\conf\\identity.txt", "r")) == NULL) {
        printf("Could not open file 'identity.txt' for reading.\n");
        return -1;
    }

    fgets(identity, IDENTITY_BUFSIZE, file);
    if(ferror(file) != 0) {
        fclose (file);
        printf("Error reading identity from file 'identity.txt'.\n");
        return -1;
    }
    fclose (file);
    return 0;
}

int writeIdentity(const char* identity) {
    FILE *file;

    if((file = fopen("..\\conf\\identity.txt", "w")) == NULL) {
        printf("Could not open file 'identity.txt' for writing.\n");
        return -1;
    }

    fputs(identity, file);
    if(ferror(file) != 0) {
        fclose (file);
        printf("Error writing identity to file 'identity.txt'.\n");
        return -1;
    }
    fclose (file);
    return 0;
}

void showHelp() {
    printf("\n[q] - Disconnect from server\n[h] - Show this help\n[c] - Show channels\n[s] - Switch to specified channel\n");
    printf("[l] - Show all visible clients\n[L] - Show all clients in specific channel\n[n] - Create new channel with generated name\n[N] - Create new channel with custom name\n");
    printf("[d] - Delete channel\n[r] - Rename channel\n[R] - Record sound to wav\n[v] - Toggle Voice Activity Detection / Continuous transmission \n[V] - Set Voice Activity Detection level\n");
	printf("[w] - Set whisper list\n[W] - Clear whisper list\n\n");
	
}

unsigned int  ts3client_requestSendChannelTextMsg(uint64 serverConnectionHandlerID,  const char *message,
anyID targetChannelID, const char *returnCode);

DWORD WINAPI ClientStart(LPVOID lpParameter)
{
    uint64 scHandlerID;
	unsigned int error;
	char* mode;
	char** device;
	char *version;
	char identity[IDENTITY_BUFSIZE];
    
	/* Create struct for callback function pointers */
	struct ClientUIFunctions funcs;

	/* Initialize all callbacks with NULL */
	memset(&funcs, 0, sizeof(struct ClientUIFunctions));

	/* Callback function pointers */
	/* It is sufficient to only assign those callback functions you are using. When adding more callbacks, add those function pointers here. */
	funcs.onConnectStatusChangeEvent        = onConnectStatusChangeEvent;
	funcs.onNewChannelEvent                 = onNewChannelEvent;
	funcs.onNewChannelCreatedEvent          = onNewChannelCreatedEvent;
	funcs.onDelChannelEvent                 = onDelChannelEvent;
	funcs.onClientMoveEvent                 = onClientMoveEvent;
	funcs.onClientMoveSubscriptionEvent     = onClientMoveSubscriptionEvent;
	funcs.onClientMoveTimeoutEvent          = onClientMoveTimeoutEvent;
	funcs.onTalkStatusChangeEvent           = onTalkStatusChangeEvent;
	funcs.onTextMessageEvent                = onTextMessageEvent;
	funcs.onIgnoredWhisperEvent             = onIgnoredWhisperEvent;
	funcs.onServerErrorEvent                = onServerErrorEvent;
	funcs.onUserLoggingMessageEvent         = onUserLoggingMessageEvent;
	funcs.onCustomPacketEncryptEvent        = onCustomPacketEncryptEvent;
	funcs.onCustomPacketDecryptEvent        = onCustomPacketDecryptEvent;
	funcs.onEditMixedPlaybackVoiceDataEvent = onEditMixedPlaybackVoiceDataEvent;

	/* Initialize client lib with callbacks */
	/* Resource path points to the SDK\bin directory to locate the soundbackends folder when running from Visual Studio. */
	/* If you want to run directly from the SDK\bin directory, use an empty string instead to locate the soundbackends folder in the current directory. */
	if((error = ts3client_initClientLib(&funcs, NULL, LogType_FILE | LogType_CONSOLE | LogType_USERLOGGING, NULL, "..\\dll\\")) != ERROR_ok) {
		char* errormsg;
		if(ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			wxMessageBox("Error initialzing serverlib");
			ts3client_freeMemory(errormsg);
		}
		return 1;
	}

	/* Spawn a new server connection handler using the default port and store the server ID */
    if((error = ts3client_spawnNewServerConnectionHandler(0, &scHandlerID)) != ERROR_ok) {
        wxMessageBox("Error spawning server connection handler");
        return 1;
    }

    /* Get default capture mode */
    if((error = ts3client_getDefaultCaptureMode(&mode)) != ERROR_ok) {
        wxMessageBox("Error getting default capture mode");
        return 1;
    }
	printf("Default capture mode: %s\n", mode);

	/* Get default capture device */
	if((error = ts3client_getDefaultCaptureDevice(mode, &device)) != ERROR_ok) {
		wxMessageBox("Error getting default capture device");
		return 1;
	}
	//wxMessageBox("Default capture device");

    /* Open default capture device */
	/* Instead of passing mode and device[1], it would also be possible to pass empty strings to open the default device */
    if((error = ts3client_openCaptureDevice(scHandlerID, mode, device[1])) != ERROR_ok) {
        wxMessageBox("Error opening capture device");
    }

    /* Get default playback mode */
    if((error = ts3client_getDefaultPlayBackMode(&mode)) != ERROR_ok) {
        wxMessageBox("Error getting default playback mode");
        return 1;
    }
	printf("Default playback mode: %s\n", mode);

	/* Get default playback device */
	if((error = ts3client_getDefaultPlaybackDevice(mode, &device)) != ERROR_ok) {
		wxMessageBox("Error getting default playback device");
		return 1;
	}
	printf("Default playback device: %s %s\n", device[0], device[1]);

    /* Open default playback device */
	/* Instead of passing mode and device[1], it would also be possible to pass empty strings to open the default device */
    if((error = ts3client_openPlaybackDevice(scHandlerID, mode, device[1])) != ERROR_ok) {
        wxMessageBox("Error opening playback device");
    }

    /* Try reading identity from file, otherwise create new identity */
    if(readIdentity(identity) != 0) {
        char* id;
        if((error = ts3client_createIdentity(&id)) != ERROR_ok) {
            wxMessageBox("Error creating identity");
            return 0;
        }
        if(strlen(id) >= IDENTITY_BUFSIZE) {
            wxMessageBox("Not enough bufsize for identity string");
            return 0;
        }
        strcpy(identity, id);
        ts3client_freeMemory(id);
        writeIdentity(identity);
    }
    printf("Using identity: %s\n", identity);

	char final_nick[50] = { "" };
	strcpy(final_nick, CURRENT_LANG);
	strcat(final_nick,"$");
	strcat(final_nick, NICK);
	strcat(final_nick, "$");
    /* Connect to server on localhost:9987 with nickname "client", no default channel, no default channel password and server password "secret" */
	if((error = ts3client_startConnection(scHandlerID, identity, SERVER_ADDRESS, PORT, final_nick, NULL, "", "secret")) != ERROR_ok) {
		wxMessageBox("Error connecting to server");
		return 1;
	}

	printf("Client lib initialized and running\n");

	/* Query and print client lib version */
    if((error = ts3client_getClientLibVersion(&version)) != ERROR_ok) {
        wxMessageBox("Failed to get clientlib version");
        return 1;
    }
    printf("Client lib version: %s\n", version);
    ts3client_freeMemory(version);  /* Release dynamically allocated memory */
    version = NULL;

	SLEEP(300);

	/*While flagg==false the client is running*/
    while(!flag) 
	{
        SLEEP(50);
    }

	/* Disconnect from server */
    if((error = ts3client_stopConnection(scHandlerID, "leaving")) != ERROR_ok) {
        printf("Error stopping connection: %d\n", error);
        return 1;
    }

	SLEEP(300);

	/* Destroy server connection handler */
    if((error = ts3client_destroyServerConnectionHandler(scHandlerID)) != ERROR_ok) {
        printf("Error destroying clientlib: %d\n", error);
        return 1;
    }

	/* Shutdown client lib */
    if((error = ts3client_destroyClientLib()) != ERROR_ok) {
        printf("Failed to destroy clientlib: %d\n", error);
        return 1;
    }

	/* This is a small hack, to close an open recording sound file */
	recordSound = 0;
	onEditMixedPlaybackVoiceDataEvent(DEFAULT_VIRTUAL_SERVER, NULL, 0, 0, NULL, NULL);
	return 0;
}

DWORD WINAPI STT_THREAD(LPVOID lpParameter)
{
	while (1)
	{
		Sleep(100);
		FILE *trad;
		a:
		Sleep(100);
		if (trad = fopen("translate.txt", "r")) //if file exist read the string from nuance dragon service
		{
			fgets(translate_jar, 256, trad);
			fflush(trad);
			fclose(trad);
			if (strcmp(translate_jar, "") != 0)	//if translate_jar isn't empty
			{
				wxString final = "\n" + wxString::FromAscii(CURRENT_LANG) + "\n" + wxString::FromUTF8(translate_jar);
				ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, final, (uint64)1, NULL); //Send other clients the speechtotext message from dragon transaction
				strcpy(translate_jar, "");
				WinExec("Taskkill /IM java.exe /F", SW_HIDE);	//Kill java
				Sleep(50);
				WinExec("del /F translate.txt", SW_HIDE);		//Delete translate file
				remove("recorded.wav");
				remove("translate.txt");
				sound_flag = false;								//Inform all thread to finish operation
				finish_ctrl_flag=false;							//Inform the pushtotalk thread to finish operation
				
				
			}


		}
		else goto a;
	}
}
DWORD WINAPI TTS_THREAD(LPVOID lpParameter)
{
	while (1)
	{
		if (tts_flag == true)
		{
			speak(CURRENT_LANG, (char*)strSpeak.mb_str().data());
			Sleep(300);
			tts_flag = false;
		}
		Sleep(50);
	}
	return 0;
}


DWORD WINAPI CTRL_STT(LPVOID lpParameter)
{

	while (1 == 1)
	{
		if (GetAsyncKeyState(VK_CONTROL) && finish_ctrl_flag==false)
		{
			if (recorder->isRecording() == false)
			{
				recorder->startRecordingBufferedAudio();
				finish_ctrl_flag = true;
			}
				Sleep(50);
		}
		
		Sleep(50);

	}
	return 0;
}


	BEGIN_EVENT_TABLE(ClientTsFrm,wxFrame)
		
	EVT_CLOSE(ClientTsFrm::OnClose)
	EVT_TIMER(ID_WXTIMER2,ClientTsFrm::WxTimer2Timer)
	EVT_TIMER(ID_WXTIMER1,ClientTsFrm::WxTimer1Timer)
	EVT_BUTTON(ID_WXBITMAPBUTTON1,ClientTsFrm::btnspeechClick)
	EVT_BUTTON(ID_WXBUTTON2,ClientTsFrm::btnsendClick)
	EVT_TEXT_ENTER(ID_WXEDIT3,ClientTsFrm::txtmsgEnter)
	EVT_BUTTON(ID_WXBUTTON1,ClientTsFrm::WxButton1Click)
	EVT_MENU(ID_MNU_ESCI_1003, ClientTsFrm::Debug)
	EVT_MENU(ID_MNU_AUDIO_1005, ClientTsFrm::Wizard)
	EVT_MENU(ID_MNU_SPEECH_1006, ClientTsFrm::btnspeechClick)
	EVT_GRID_CELL_LEFT_CLICK(ClientTsFrm::gridchatCellLeftClick)

	END_EVENT_TABLE()


ClientTsFrm::ClientTsFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

ClientTsFrm::~ClientTsFrm()
{
}


void ClientTsFrm::CreateGUIControls()
{

	FILE * record;
	FILE * translate;
	if (record = fopen("recorded.wav", "r"))
	{
		remove("");
		fclose(record);
	}
	if (translate = fopen("translate.txt", "r")) 
	{
		remove("");
		fclose(translate);
	}
	gridchat = new wxGrid(this, ID_GRIDCHAT, wxPoint(211, 72), wxSize(722, 350));

	/*gridclient = new wxGrid(this, ID_GRIDCLIENT, wxPoint(10, 250), wxSize(184, 155));
	gridclient->CreateGrid(0, 3, wxGrid::wxGridSelectCells);
	gridclient->SetColLabelValue(0, "Nickname");
	gridclient->SetColLabelValue(1, "Country");
	gridclient->SetColLabelValue(2, "Status");

	gridclient->SetRowLabelSize(0);
	
	gridclient->AppendRows(4, true);
	gridclient->SetRowSize(0, 40);
	gridclient->SetRowSize(1, 40);
	gridclient->SetRowSize(2, 40);
	gridclient->SetRowSize(3, 40);

	gridclient->SetColSize(0, 75);
	gridclient->SetColSize(1, 60);
	gridclient->SetColSize(2, 60);*/
	

	gridchat->CreateGrid(0, 2, wxGrid::wxGridSelectCells);

	gridchat->SetColLabelValue(0, "Message");
	gridchat->SetColLabelValue(1, "Play");
	
	gridchat->SetRowSize(curRow+1, 40);
	gridchat->SetColSize(curCol, 610);
	gridchat->SetColSize(curCol + 1, 30);

	WxTimer2 = new wxTimer();
	WxTimer2->SetOwner(this, ID_WXTIMER2);
	WxTimer2->Start(250);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(100);


	txtclient = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _(""), wxPoint(10, 75), wxSize(184, 155), wxRE_READONLY, wxDefaultValidator, _("txtclient"));
	txtclient->SetMaxLength(0);
	txtclient->SetFocus();
	txtclient->SetInsertionPointEnd();
	txtclient->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	txtlingua = new wxTextCtrl(this, ID_WXEDIT2, _(""), wxPoint(367, 20), wxSize(103, 20), wxTE_READONLY, wxDefaultValidator, _("txtlingua"));
	txtlingua->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	lbllingua = new wxStaticText(this, ID_WXSTATICTEXT2, _("Language:"), wxPoint(299, 20), wxDefaultSize, 0, _("lbllingua"));
	lbllingua->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	lblnick = new wxStaticText(this, ID_WXSTATICTEXT1, _("Nickname:"), wxPoint(14, 20), wxDefaultSize, 0, _("lblnick"));
	lblnick->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	txtnick = new wxTextCtrl(this, ID_WXEDIT1, _(""), wxPoint(91, 20), wxSize(102, 20), wxTE_READONLY, wxDefaultValidator, _("txtnick"));
	txtnick->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	

	btnsend = new wxButton(this, ID_WXBUTTON2, _("Invia"), wxPoint(830, 450), wxSize(103, 48), 0, wxDefaultValidator, _("btnsend"));
	btnsend->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	txtmsg = new wxTextCtrl(this, ID_WXEDIT3, _(""), wxPoint(211, 450), wxSize(600, 45), wxTE_PROCESS_ENTER, wxDefaultValidator, _("txtmsg"));
	txtmsg->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));
	txtmsg->SetFocus();

	wxBitmap WxBitmapButton1_BITMAP(NULL);
	WxBitmapButton1 = new wxBitmapButton(this, ID_WXBITMAPBUTTON1, WxBitmapButton1_BITMAP, wxPoint(10, 450), wxSize(28, 25), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButton1"));
	WxBitmapButton1->SetToolTip(_("Abilita SpeechToText Service"));

	/*btnspeech = new wxButton(this, ID_WXBUTTON3, _("Speech to text disabilitato"), wxPoint(10, 450), wxSize(180, 31), 0, wxDefaultValidator, _("WxButton1"));
	btnspeech->Show(true);
	btnspeech->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));*/

	WxMenuBar1 = new wxMenuBar();
	ID_MNU_FILE_1001_Mnu_Obj = new wxMenu();
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_ESCI_1003, _("Esci"), _(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1001_Mnu_Obj, _("File"));

	ID_MNU_OPZIONI_1004_Mnu_Obj = new wxMenu();
	ID_MNU_OPZIONI_1004_Mnu_Obj->Append(ID_MNU_AUDIO_1005, _("Audio"), _(""), wxITEM_NORMAL);
	ID_MNU_OPZIONI_1004_Mnu_Obj->AppendCheckItem(ID_MNU_SPEECH_1006, _("Abilita SpeechToText Service"), _(""));
	WxMenuBar1->Append(ID_MNU_OPZIONI_1004_Mnu_Obj, _("Opzioni"));
	SetMenuBar(WxMenuBar1);

	SetTitle(_("TeamTranslate"));
	SetIcon(wxNullIcon);
	SetSize(8,8,1024,600);
	Center();
	#if wxUSE_LIBPNG
		wxImage::AddHandler(new wxPNGHandler);
	#endif

	#if wxUSE_LIBJPEG
		wxImage::AddHandler(new wxJPEGHandler);
	#endif

	#if wxUSE_GIF
		wxImage::AddHandler(new wxGIFHandler);
	#endif
	////GUI Items Creation End
	
	conta=10.0;
	FILE*config;
	FILE *api;
	if (config = fopen("..\\conf\\config.txt", "r"))
	{
    fscanf(config,"%s",&SERVER_ADDRESS);
    fscanf(config,"%s",&NICK);
    fscanf(config,"%d",&cmbel);
    fscanf(config,"%s",&CURRENT_LANG);
    fscanf(config,"%s",&SERVICE);
    fclose(config);
	}
	if (api = fopen("..\\conf\\GOOGLE.txt", "r"))
	{
		fscanf(api, "%s", GOOGLE_API_KEY);
		fclose(api);
	}

	txtnick->AppendText(NICK);
	txtlingua->AppendText(CURRENT_LANG);
	HANDLE myHandle = CreateThread(0, 0, ClientStart, NULL, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, TTS_THREAD, NULL, 0, &myThreadID2);
	HANDLE myHandle3 = CreateThread(0, 0, STT_THREAD, NULL, 0, &myThreadID4);
	HANDLE myHandle4 = CreateThread(0, 0, CTRL_STT, NULL, 0, &myThreadID4);
	SetupColor();
	engine = irrklang::createIrrKlangDevice();
	recorder = irrklang::createIrrKlangAudioRecorder(engine);
	gridptr = gridchat;
	

}

void MyGridCellRenderer::Draw(wxGrid& grid,
	wxGridCellAttr& attr,
	wxDC& dc,
	const wxRect& rect,
	int row, int col,
	bool isSelected)
{
	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	dc.DrawBitmap(*bitmap, 0, 0, 0);
	dc.DrawBitmap(*bitmap, rect.x+6, rect.y + 4);
}

void MyGridCellRenderer::setPicture(wxString name)
{
	return;
}

void ClientTsFrm::gridchatCellLeftClick(wxGridEvent& event)
{
	wxToolTip * tooltip = new wxToolTip(diary[event.GetRow()].msgold);
	tooltip->SetAutoPop(10000);
	tooltip->SetMaxWidth(200);
	strSpeak = wxString::FromAscii(strtok((char*)gridchat->GetCellValue(event.GetRow(), 0).mb_str().data(), ")"));
	strSpeak = wxString::FromAscii(strtok(NULL, ":"));
	if (event.GetCol() == 1) { tts_flag = true; }
	if (event.GetCol() == 0) { gridchat->GetGridWindow()->SetToolTip(tooltip); }

}
void ClientTsFrm::OnClose(wxCloseEvent& event)
{
    flag=1;
    Sleep(300);
	Destroy();
}


/*Refresh chat for new message or new clients*/
void ClientTsFrm::RefreshChat()
{
    int i;
	
    wxUniChar ch=':';
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    showClients(DEFAULT_VIRTUAL_SERVER);
    txtclient->Clear();	//Clear client window
    for (i=0;i<MAX;i++)
    {
        if(person[i].name!="") //if there is a client name
        {
			if (person[i].speak == 0 && person[i].write == 0) //gridclient->SetCellRenderer(i, 2, new MyGridCellRenderer(L""));
            txtclient->BeginTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue));
			if (person[i].speak == 1)	//if this client is speaking show microphone 
			{
				/*gridclient->SetCellTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue), i, 0);
				gridclient->SetCellValue(i, 0, person[i].name);*/
				txtclient->WriteText(person[i].name + "\t");
				if (person[i].lang == "Italian") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/italy.bmp"));*/ txtclient->WriteImage(wxBitmap(italy_xpm)); }
				if (person[i].lang == "English")  { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/usa.bmp"));*/ txtclient->WriteImage(wxBitmap(usa_xpm)); }
				if (person[i].lang == "Portuguese") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/brasil.bmp"));*/ txtclient->WriteImage(wxBitmap(brasil_xpm)); }
				txtclient->WriteText("\t");
				txtclient->WriteImage(wxBitmap(microphone_xpm));
				//gridclient->SetCellRenderer(i, 2, new MyGridCellRenderer(L"../res/microphone.bmp"));
			}
			else if (person[i].speak == 0)	//if this client is writing show keayboard
			{
				/*gridclient->SetCellTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue), i, 0);
				gridclient->SetCellValue(i, 0, person[i].name);*/
				txtclient->WriteText(person[i].name + "\t");
				if (person[i].lang == "Italian") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/italy.bmp"));*/ txtclient->WriteImage(wxBitmap(italy_xpm)); }
				if (person[i].lang == "English") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/usa.bmp")); */txtclient->WriteImage(wxBitmap(usa_xpm));}
				if (person[i].lang == "Portuguese") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/brasil.bmp"));*/ txtclient->WriteImage(wxBitmap(brasil_xpm)); }
				if (person[i].write == 1)
				{
					txtclient->WriteText("\t");
					txtclient->WriteImage(wxBitmap(keyboard_xpm));
					//gridclient->SetCellRenderer(i, 2, new MyGridCellRenderer(L"../res/keyboard.bmp"));
				}
				
				
			}
            txtclient->EndTextColour();
            txtclient->Newline();
        }
    }
        if(strGlobale!="" && StringTranslate!="" && StringTranslate!=oldStringTranslate/* strGlobale!=oldstrGlobale*/)
		{
			if (wxString::FromAscii(MSG_SRC) == ">" || wxString::FromAscii(MSG_SRC) == "</html>" || MSG_SRC[0] == '<' || MSG_SRC[0] == '>') return;
			gridchat->AppendRows(1, true); //Add a new message row
			if(strNick==NICK)
			{
					wxString messaggio = strNick + "(" + buf + "): " + wxString::FromUTF8(StringTranslate);
					gridchat->SetCellValue(messaggio,curRow,0);
					gridchat->SetCellRenderer(curRow++, 1, new MyGridCellRenderer(L"../res/play.bmp"));
			
					gridchat->AutoSizeRow(curRow - 1, true);
					gridchat->SetColSize(curCol + 1, 30);
			}
			else
			{
					for (i=0;i<MAX;i++)
					{
						if(strNick==person[i].name && person[i].used==1)
						{
                   
							wxString messaggio = strNick + "(" + buf + "): " + wxString::FromUTF8(StringTranslate);
							gridchat->SetCellTextColour(curRow, 0, wxColour(colors[person[i].color].red, colors[person[i].color].green, colors[person[i].color].blue));
							gridchat->SetCellValue(messaggio, curRow, 0);
							gridchat->SetRowSize(curRow, 40);
							gridchat->SetColSize(curCol, 578);
							gridchat->SetColSize(curCol + 1, 60);
							gridchat->SetCellRenderer(curRow++, 1, new MyGridCellRenderer(L"../res/play.bmp"));
                    
						}
					}
			}
       
		oldStringTranslate = StringTranslate;
        oldstrGlobale=strGlobale;
        strGlobale="";
    }
       
}


/*
 * WxButton1Click
 */
void ClientTsFrm::WxButton1Click(wxCommandEvent& event)
{

}

/*
 * btnsendClick
 */
void ClientTsFrm::btnsendClick(wxCommandEvent& event)
{
	char str[1024]={""};
    strcpy(str,(const char*)txtmsg->GetValue().mb_str());
	wxString parsata=txtmsg->GetValue().ToUTF8(); //convert write message into UTF8
	if (parsata == "") return;	//if the message is empty exit
	txtmsg->DiscardEdits();		//Clear buffer of textbox
	write_flag = false;

    if(strcmp(CURRENT_LANG,"Italian")==0) ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER,"\nItalian\n"+parsata,(uint64)1,NULL);
	else if (strcmp(CURRENT_LANG, "English") == 0) ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, "\nEnglish\n" + parsata, (uint64)1, NULL);
	else if (strcmp(CURRENT_LANG, "Portuguese") == 0) ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, "\nPortuguese\n" + parsata, (uint64)1, NULL);
	
	wxString scrive_msg = "\n" + wxString::FromAscii(CURRENT_LANG) + "\n" + "write0";	//Inform other clients that we have finish to write
	ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, scrive_msg, (uint64)1, NULL);
	txtmsg->Clear();
	
	
}


/*
 * WxTimer1Timer
 */
void ClientTsFrm::WxTimer1Timer(wxTimerEvent& event)
{
	
	RefreshChat();
}

/*
 * txtmsgEnter
 */
void ClientTsFrm::txtmsgEnter(wxCommandEvent& event)
{
	btnsendClick(event);
}

/*
 * btnspeechClick
 */
void ClientTsFrm::btnspeechClick(wxCommandEvent& event)
{
	//speak(CURRENT_LANG,(char*)StringTranslate.mb_str().data());
	tasto_stt_flag = !tasto_stt_flag;
	if (tasto_stt_flag == false)
	{
		ID_MNU_OPZIONI_1004_Mnu_Obj->SetLabel(ID_MNU_SPEECH_1006, "Speech to text disabilitato");
		ID_MNU_OPZIONI_1004_Mnu_Obj->Check(ID_MNU_SPEECH_1006, false);
		WxBitmapButton1->SetBitmap(NULL);
	}
	else
	{
		sound_flag = true;
		recorder->startRecordingBufferedAudio();
		ID_MNU_OPZIONI_1004_Mnu_Obj->SetLabel(ID_MNU_SPEECH_1006, "Speech to text abilitato");
		WxBitmapButton1->SetBitmap(microphone_xpm);
		ID_MNU_OPZIONI_1004_Mnu_Obj->Check(ID_MNU_SPEECH_1006, true);
	}
	
	
}

/*
 * WxTimer2Timer
 */
void ClientTsFrm::WxTimer2Timer(wxTimerEvent& event)
{
	setVadLevel(DEFAULT_VIRTUAL_SERVER);
	if (txtmsg->IsModified() == true) 	write_flag = true;
	int i;
	for (i = 0; i < MAX; i++)
	{
		if (person[i].name == NICK)
		{
			if (person[i].write == 0 && write_flag==true)
			{
				wxString scrive_msg = "\n" + wxString::FromAscii(CURRENT_LANG) + "\n" + "write1";
				ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, scrive_msg, (uint64)1, NULL);
			}
		}
	}
	
}

void ClientTsFrm::Debug(wxCommandEvent& event)
{
	// insert your code here
	flag = 1;
	Sleep(300);
	Destroy();
}

void ClientTsFrm::Wizard(wxCommandEvent& event)
{
	// insert your code here
	AudioWizard* dialog = new AudioWizard(NULL);
	dialog->Show(true);
}

void ClientTsFrm::WxBitmapButton1Click(wxCommandEvent& event)
{
	// insert your code here
	btnspeechClick(event);
}
