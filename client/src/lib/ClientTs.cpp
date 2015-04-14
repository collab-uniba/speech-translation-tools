#include "ClientTs.h"


//struct user* person = (struct user*) malloc(sizeof(struct user));			//Array of user to record client's information


/*cbClientTsFrm callbckFrmGUI;*/

/* ClientTsFrm* Observer;
void setClientFRM(ClientTsFrm* ob){
}
void registercb(cbClientTsFrm fn){
callbckFrmGUI = fn;
}

struct user*  getPerson(){
	return person;
}*/
/*
This procedure allows the use of TextToSpeech offered by Microsoft
it has two parameters: the language of message and body of message
*/


std::list<MESSAGE> diary;


wxSemaphore ClientTS::thread_semaphore = 0;
long ClientTS::text_to_speech = 0L;
bool ClientTS::flagSave = false;
Session* ClientTS::session = NULL;
ClientTS *ClientTS::m_instance = NULL;

IAudioRecorder* ClientTS::recorder = irrklang::createIrrKlangAudioRecorder(irrklang::createIrrKlangDevice());			//Flow of audio daa
 
void ClientTS::sendMessage(wxString *msgToSend){ 
	if (*msgToSend == "") return;	//if the message is empty exit
 	//session->write_flag = false;

	ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, "\n" + wxString::FromAscii(session->getLanguage()) + "\n" + msgToSend->ToUTF8(), (uint64)1, NULL);

	wxString scrive_msg = "\n" + wxString::FromAscii(session->getLanguage()) + "\n" + "write0";	//Inform other clients that we have finish to write
	ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, scrive_msg.mb_str(), (uint64)1, NULL);
	ts3client_logMessage("Message send on chat", LogLevel_INFO, "Chat message", Session::Instance()->scHandlerID);
}

void ClientTS::speak(const char *LANG, const char*MSG)
{
	HRESULT hr = S_OK;
	CComPtr <ISpVoice>		cpVoice;
	CComPtr <ISpObjectToken>	cpToken;
	CComPtr <IEnumSpObjectTokens>	cpEnum;
	wchar_t* voice = new wchar_t[1024];
	wcscpy(voice, L"Gender=Female;Language=");
	hr = cpVoice.CoCreateInstance(CLSID_SpVoice);
	if (strcmp(LANG, "Italian") == 0) wcscat(voice, L"410");
	if (strncmp(LANG, "English", 7) == 0) wcscat(voice, L"809");
	if (strcmp(LANG, "Portuguese") == 0) wcscat(voice, L"416");
	if (strncmp(LANG, "Spanish", 7) == 0) wcscat(voice, L"C0A");
	if (strncmp(LANG, "French", 6) == 0) wcscat(voice, L"40C");
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


void ClientTS::Print(char*word)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, word, -1, wString, 4096);
	MessageBox(NULL, wString, L"Test print handler", MB_OK);
}


size_t ClientTS::read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct WriteThis *pooh = (struct WriteThis *) userp;

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
http://www.cplusplusdevelop.com/1399_16286382/
*/

void ClientTS::writeWaveFile(const char* filename, SAudioStreamFormat format, void* data)
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
Initialize Client's label colors,the values are RGB
*/

void ClientTS::SetupColor(COLORE * colors)
{
	UserListPTR luser = Session::Instance()->getListUser();
	colors[0].red = 255;
	colors[0].green = 0;
	colors[0].blue = 0;

	colors[1].red = 0;
	colors[1].green = 0;
	colors[1].blue = 255;

	colors[2].red = 102;
	colors[2].green = 0;
	colors[2].blue = 102;

	colors[3].red = 148;
	colors[3].green = 0;
	colors[3].blue = 211;

	colors[4].red = 0;
	colors[4].green = 100;
	colors[4].blue = 0;

	for (auto it = luser->cbegin(); it != luser->cend(); ++it){
		(*it)->setSpeak(0);
	}
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

void ClientTS::onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	/* Failed to connect ? */
	if (newStatus == STATUS_DISCONNECTED && errorNumber == ERROR_failed_connection_initialisation) {
		ts3client_logMessage("No server running", LogLevel_ERROR, "Channel", session->scHandlerID);
		exit(-1);
	}
}

/*
* Callback for current channels being announced to the client after connecting to a server.
*
* Parameters:
*   serverConnectionHandlerID - Server connection handler ID
*   channelID                 - ID of the announced channel
*   channelParentID           - ID of the parent channel
*/


void ClientTS::onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID) {
	/* Query channel name from channel ID */
	char* name;
	unsigned int error;

	if ((error = ts3client_getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, &name)) == ERROR_ok) {
	//	printf("New channel: %llu %s \n", (unsigned long long)channelID, name);
		ts3client_freeMemory(name);  /* Release dynamically allocated memory only if function succeeded */
	}
	else {
		char* errormsg;
		if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			//printf("Error getting channel name in onNewChannelEvent: %s\n", errormsg);
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
*   invokerID                 - ID of the client who created the channel
*   invokerName               - Name of the client who created the channel
*/


void ClientTS::onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
	char* name;
	/* Query channel name from channel ID */
	if (ts3client_getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, &name) != ERROR_ok)
		return; 
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
void ClientTS::onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
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
void ClientTS::onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
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
void ClientTS::onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
	char* name;

	/* Query client nickname from ID */
	if (ts3client_getClientVariableAsString(serverConnectionHandlerID, clientID, CLIENT_NICKNAME, &name) != ERROR_ok)
	{
		ts3client_logMessage("No such clients found", LogLevel_ERROR, "Channel", session->scHandlerID);
		return;
	}

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
void ClientTS::onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage) {
	printf("ClientID %u timeouts with message %s\n", clientID, timeoutMessage);

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

void ClientTS::onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID) {
	char* name;
	int i;
	UserListPTR userList = session->getListUser();

	/* Query client nickname from ID */
	if (ts3client_getClientVariableAsString(serverConnectionHandlerID, clientID, CLIENT_NICKNAME, &name) != ERROR_ok)
		return;
	if (status == STATUS_TALKING)
	{
		if (session->automatic_stt_flag)
		{
			session->sound_flag = true;
			recorder->startRecordingBufferedAudio();
		}

		for (auto it = userList->cbegin(); it != userList->cend(); ++it){
			if ((*it)->getName() == name)
			{
				(*it)->setSpeak(1);
			}
		}


		if (!session->sound_flag && session->tasto_stt_flag)
		{
			session->sound_flag = true;
			recorder->startRecordingBufferedAudio();
		}
	}
	else {
		for (auto it = userList->cbegin(); it != userList->cend(); ++it){
			(*it)->setSpeak(0);
			if ((*it)->getName() == name && (*it)->getSpeak() == 1)
			{
				(*it)->setSpeak(0);
				break;
			}
		}

		if (session->tasto_stt_flag  || session->sound_flag  || session->finish_ctrl_flag )
		{
			if (!recorder->isRecording()) return;
			recorder->stopRecordingAudio();
			writeWaveFile("recorded.wav", recorder->getAudioFormat(), recorder->getRecordedAudioData());

			if (strcmp(session->getLanguage(), "Italian") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l it_IT", SW_HIDE);
			if (strcmp(session->getLanguage(), "English") == 0)
				WinExec("java -jar ASR.jar -w recorded.wav -l en_US", SW_HIDE);
			if (strcmp(session->getLanguage(), "Portuguese") == 0) WinExec("java -jar ASR.jar -w recorded.wav -l pt_BR", SW_HIDE);

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

void ClientTS::onIgnoredWhisperEvent(uint64 serverConnectionHandlerID, anyID clientID) {
	unsigned int error;

	/* Add sending client to whisper allow list so own client will hear the voice data.
	* It is sufficient to add a clientID only once, not everytime this event is called. However it won't
	* hurt to add the same clientID to the allow list repeatedly, but is is not necessary. */
	if ((error = ts3client_allowWhispersFrom(serverConnectionHandlerID, clientID)) != ERROR_ok) {
		printf("Error setting client on whisper allow list: %u\n", error);
	}
	printf("Added client %d to whisper allow list\n", clientID);
}


void ClientTS::onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage) {
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

void ClientTS::onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString) {
	/* Your custom error display here... */
	/* printf("LOG: %s\n", completeLogString); */
	if (logLevel == LogLevel_CRITICAL) {
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

void ClientTS::onCustomPacketEncryptEvent(char** dataToSend, unsigned int* sizeOfData) {
#ifdef USE_CUSTOM_ENCRYPTION
	unsigned int i;
	for (i = 0; i < *sizeOfData; i++) {
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

void ClientTS::onCustomPacketDecryptEvent(char** dataReceived, unsigned int* dataReceivedSize) {
#ifdef USE_CUSTOM_ENCRYPTION
	unsigned int i;
	for (i = 0; i < *dataReceivedSize; i++) {
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

void ClientTS::onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask){
#define OUTPUTCHANNELS 2
	 FILE *pfile = NULL;
	 struct WaveHeader header = { { 'R', 'I', 'F', 'F' }, 0, { 'W', 'A', 'V', 'E' }, { 'f', 'm', 't', ' ' }, 16, 1, 2, 48000, 48000 * (16 / 2) * 2, (16 / 2) * 2, 16, { 'd', 'a', 't', 'a' }, 0 };

	int currentSampleMix[OUTPUTCHANNELS]; /*a per channel/sample mix buffer*/
	int channelCount[OUTPUTCHANNELS] = { 0, 0 }; /*how many input channels does the output channel contain */

	int currentInChannel;
	int currentOutChannel;
	int currentSample;
	int channelBit;

	/*for clipping*/
	short shortval;
	int   intval;

	short* outputBuffer;

	int leftChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_CENTER | SPEAKER_BACK_LEFT | SPEAKER_FRONT_LEFT_OF_CENTER | SPEAKER_BACK_CENTER | SPEAKER_SIDE_LEFT | SPEAKER_TOP_CENTER | SPEAKER_TOP_FRONT_LEFT | SPEAKER_TOP_FRONT_CENTER | SPEAKER_TOP_BACK_LEFT | SPEAKER_TOP_BACK_CENTER;
	int rightChannelMask = SPEAKER_FRONT_RIGHT | SPEAKER_FRONT_CENTER | SPEAKER_BACK_RIGHT | SPEAKER_FRONT_RIGHT_OF_CENTER | SPEAKER_BACK_CENTER | SPEAKER_SIDE_RIGHT | SPEAKER_TOP_CENTER | SPEAKER_TOP_FRONT_RIGHT | SPEAKER_TOP_FRONT_CENTER | SPEAKER_TOP_BACK_RIGHT | SPEAKER_TOP_BACK_CENTER;

	/*detect state changes*/
	if (recordSound && (pfile == NULL)){
		/*start recording*/
		header.len = 0;
		header.dataLen = 0;
		if ((pfile = fopen("..\\conf\\recordedvoices.wav", "wb")) == NULL) return;
		fwrite(&header, sizeof(struct WaveHeader), 1, pfile);
	}
	else if (!recordSound && (pfile != NULL)){
		/*stop recording*/
		header.len = sizeof(struct WaveHeader) + header.dataLen - 8;
		fseek(pfile, 0, SEEK_SET);
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
	for (currentInChannel = 0; currentInChannel < channels; ++currentInChannel) {
		/*if the speaker has actual data*/
		if ((*channelFillMask & (1 << currentInChannel)) != 0){
			/*add to the outChannelSpeakerSet*/
			if ((channelSpeakerArray[currentInChannel] & leftChannelMask) != 0) channelCount[0]++;
			if ((channelSpeakerArray[currentInChannel] & rightChannelMask) != 0) channelCount[1]++;
		}
	}

	/*get the outbut buffer*/
	outputBuffer = (short*)malloc(sizeof(short)*sampleCount * 2 /*output channels*/);

	/* hint: if channelCount is 0 for all channels, we could write a zero buffer and quit here */

	/*mix the samples*/
	for (currentSample = 0; currentSample < sampleCount; currentSample++){
		currentSampleMix[0] = currentSampleMix[1] = 0;

		/*loop over all channels in this frame */
		for (currentInChannel = 0; currentInChannel < channels; currentInChannel++){
			if ((channelSpeakerArray[currentInChannel] & leftChannelMask) != 0) currentSampleMix[0] += samples[(currentSample*channels) + currentInChannel];
			if ((channelSpeakerArray[currentInChannel] & rightChannelMask) != 0) currentSampleMix[1] += samples[(currentSample*channels) + currentInChannel];
		}

		/*collected all samples, store mixed sample */
		for (currentOutChannel = 0; currentOutChannel < OUTPUTCHANNELS; currentOutChannel++){
			if (channelCount[currentOutChannel] == 0){
				outputBuffer[(currentSample*OUTPUTCHANNELS) + currentOutChannel] = 0;
			}
			else {
				/*clip*/
				intval = currentSampleMix[currentOutChannel] / channelCount[currentOutChannel];
				if (intval >= SHRT_MAX) shortval = SHRT_MAX;
				else if (intval <= SHRT_MIN) shortval = SHRT_MIN;
				else shortval = (short)intval;
				/*store*/
				outputBuffer[(currentSample*OUTPUTCHANNELS) + currentOutChannel] = shortval;
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

void ClientTS::showChannels(uint64 serverConnectionHandlerID) {
	uint64 *ids;
	int i;
	unsigned int error;

	//printf("\nList of channels on virtual server %llu:\n", (unsigned long long)serverConnectionHandlerID);
	if ((error = ts3client_getChannelList(serverConnectionHandlerID, &ids)) != ERROR_ok) {  /* Get array of channel IDs */
		//printf("Error getting channel list: %d\n", error);
		return;
	}
	if (!ids[0]) {
		printf("No channels\n\n");
		ts3client_freeMemory(ids);
		return;
	}
	for (i = 0; ids[i]; i++) {
		char* name;
		if ((error = ts3client_getChannelVariableAsString(serverConnectionHandlerID, ids[i], CHANNEL_NAME, &name)) != ERROR_ok) {  /* Query channel name */
		//	printf("Error getting channel name: %d\n", error);
			break;
		}
		//wxPrintf("%llu - %s\n", (unsigned long long)ids[i], name);
		ts3client_freeMemory(name);
	}

	ts3client_freeMemory(ids);  /* Release array */
}

/*
* Print all clients on the given virtual server in the specified channel
*/

void ClientTS::showChannelClients(uint64 serverConnectionHandlerID, uint64 channelID) {
	anyID* ids;
	anyID ownClientID;
	int i;
	unsigned int error;

	//printf("\nList of clients in channel %llu on virtual server %llu:\n", (unsigned long long)channelID, (unsigned long long)serverConnectionHandlerID);
	if ((error = ts3client_getChannelClientList(serverConnectionHandlerID, channelID, &ids)) != ERROR_ok) {  /* Get array of client IDs */
		printf("Error getting client list for channel %llu: %d\n", (unsigned long long)channelID, error);
		return;
	}
	if (!ids[0]) {
		printf("No clients\n\n");
		ts3client_freeMemory(ids);
		return;
	}

	/* Get own clientID as we need to call CLIENT_FLAG_TALKING with getClientSelfVariable for own client */
	if ((error = ts3client_getClientID(serverConnectionHandlerID, &ownClientID)) != ERROR_ok) {
		printf("Error querying own client ID: %d\n", error);
		return;
	}

	for (i = 0; ids[i]; i++) {
		char* name;
		int talkStatus;

		if ((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, ids[i], CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
			printf("Error querying client nickname: %d\n", error);
			break;
		}

		if (ids[i] == ownClientID) {  /* CLIENT_FLAG_TALKING must be queried with getClientSelfVariable for own client */
			if ((error = ts3client_getClientSelfVariableAsInt(serverConnectionHandlerID, CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying own client talk status: %d\n", error);
				break;
			}
		}
		else {
			if ((error = ts3client_getClientVariableAsInt(serverConnectionHandlerID, ids[i], CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
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


unsigned int  ts3client_requestSendPrivateTextMsg(uint64 serverConnectionHandlerID, const char *message, anyID targetClientID, const char *returnCode)
{
	return 0;
}

unsigned int ts3client_requestSendServerTextMsg(uint64 serverConnectionHandlerID, const char *message, const char *returnCode)
{
	return 0;
}


void ClientTS::onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message)
{
	char			*name;
	unsigned int	error;
	UserListPTR		luser			= Session::Instance()->getListUser();
	MessagePTR		msg_text;
	wxString		mystring		= wxString::FromAscii(message);
	wxString		strNick,
					strMessage,
					strMessageLang;


	if ((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, fromID, CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
		ts3client_logMessage("Error querying client nickname: %d\n", LogLevel_ERROR, "Channel", session->scHandlerID);
		return;
	}

	strtok((char*)name, "$");	//Extract from entire message the name value example: $Adam -> Adam
	strNick = wxString::FromUTF8(strtok(NULL, "$"));
	strMessageLang = wxString::FromUTF8(strtok((char*)message, "\n"));	//Extract from entire message the language 
	strMessage = wxString::FromUTF8(strtok(NULL, "\n")); //Extract the body of message

	/* Example $Adam$English$How are you?
	strNick= Adam;
	LANG_MSG_SRC=English
	MSG_SRC=How are you? */
	 
	if (strMessage == "write1")	//if it is true the client is typing a message
	{
		for (auto it = luser->cbegin(); it != luser->cend(); ++it){
			if ((*it)->getName() == strNick)
				(*it)->setWrite(1);
		}
		return;
	}

	if (strMessage == "write0")	//if it is true the client has stopped to write
	{
		for (auto it = luser->cbegin(); it != luser->cend(); ++it){
			if ((*it)->getName() == strNick)
				(*it)->setWrite(0);
		}
		return;
	}
	
	/* 	Ignore Debug value from Translation Service  */
	if (strMessage[0] == '<') return; 
	if (strMessage == "</html>") return;
	if (strMessage == ">") return;

	/******* begin adding new entry to the log variable  ******/

	msg_text = make_shared<Message>(strNick == session->getNick() ? MSGDirection::out : MSGDirection::in, strNick, strMessage, session->getLanguage(), strMessageLang);// it's the same that Message* Message = new Message ();
		
	session->addMsgToLog(msg_text);
	m_instance->m_pQueue->AddJob(msg_text);
	
}

unsigned int  ts3client_requestSendChannelTextMsg(uint64 serverConnectionHandlerID, const char *message, anyID targetChannelID, const char *returnCode)
{
	return 0;
}

/*
* Print all visible clients on the given virtual server
*/

void ClientTS::showClients(uint64 serverConnectionHandlerID) {
	anyID *ids;
	anyID ownClientID;
	int i;
	unsigned int error;
	int count_client = 0;

	UserListPTR luserOLD = Session::Instance()->getListUser();
	UserListPTR luser = make_shared<UserList>();


	printf("\nList of all visible clients on virtual server %llu:\n", (unsigned long long)serverConnectionHandlerID);
	if ((error = ts3client_getClientList(serverConnectionHandlerID, &ids)) != ERROR_ok) {  /* Get array of client IDs */
		printf("Error getting client list: %d\n", error);
		return;
	}
	if (!ids[0]) {
		printf("No clients\n\n");
		ts3client_freeMemory(ids);
		return;
	}

	/* Get own clientID as we need to call CLIENT_FLAG_TALKING with getClientSelfVariable for own client */
	if ((error = ts3client_getClientID(serverConnectionHandlerID, &ownClientID)) != ERROR_ok) {
		printf("Error querying own client ID: %d\n", error);
		return;
	}

	/*
	Reset informations about clients
	*/

	for (i = 0; ids[i]; i++)
	{
		char* name;
		int talkStatus;

		if ((error = ts3client_getClientVariableAsString(serverConnectionHandlerID, ids[i], CLIENT_NICKNAME, &name)) != ERROR_ok) {  /* Query client nickname... */
			printf("Error querying client nickname: %d\n", error);
			break;
		}

		if (ids[i] == ownClientID) {  /* CLIENT_FLAG_TALKING must be queried with getClientSelfVariable for own client */
			if ((error = ts3client_getClientSelfVariableAsInt(serverConnectionHandlerID, CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying own client talk status: %d\n", error);
				break;
			}
		}
		else{
			if ((error = ts3client_getClientVariableAsInt(serverConnectionHandlerID, ids[i], CLIENT_FLAG_TALKING, &talkStatus)) != ERROR_ok) {
				printf("Error querying client talk status: %d\n", error);
				break;
			}
		}


		//if(strcmp(name,NICK)==0) set_color_client=i;

		//printf("%u - %s (%stalking)\n", ids[i], name, (talkStatus == STATUS_TALKING ? "" : "not "));
		count_client++;

		char* lang = strtok((char*)name, "$");
		char* name2 = strtok(NULL, "$");
		int color = i;
		int used = 1;
		bool findit = false;

		for (auto it = luserOLD->cbegin(); it != luserOLD->cend() && !findit; ++it){
			UserPTR uptr = *it;
			if (uptr->getName() == name2){
				uptr->setColor(i);
				uptr->setLang(lang);
				uptr->setUsed(1);
				if (talkStatus == STATUS_TALKING) uptr->setWrite(1);
				else uptr->setWrite(0);
				luser->push_back(uptr);
				findit = true;
			}
		}

		if (!findit){
			//User(wxString name, unsigned short color, unsigned short used, unsigned short speak, unsigned short write, wxString lang) 
			UserPTR uptr = make_shared<User>(name2, i, 1, 0, (talkStatus == STATUS_TALKING ? 1 : 0), lang);
			luser->push_back(uptr);
		}

		Session::Instance()->setListUser(luser);

		ts3client_freeMemory(name);
	}
	printf("\n");

	ts3client_freeMemory(ids);  /* Release array */
}



uint64 ClientTS::enterChannelID() {
	uint64 channelID;
	int n = 0;

	printf("\nEnter channel ID: ");
//	n = scanf("%llu", (unsigned long long*)&channelID);
	emptyInputBuffer();
	if (n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return 0;
	}
	return channelID;
}

void ClientTS::createDefaultChannelName(char *name) {
	static int i = 1;
	sprintf(name, "Channel_%d", i++);
}

void ClientTS::enterName(char *name) {
	char *s;
	printf("\nEnter name: ");
	fgets(name, NAME_BUFSIZE, stdin);
	s = strrchr(name, '\n');
	if (s) {
		*s = '\0';
	}
}


void ClientTS::createChannel(uint64 serverConnectionHandlerID, const char *name) {
	unsigned int error;

	/* Set data of new channel. Use channelID of 0 for creating channels. */
	CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_NAME, name));
	CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_TOPIC, "Test channel topic"));
	CHECK_ERROR(ts3client_setChannelVariableAsString(serverConnectionHandlerID, 0, CHANNEL_DESCRIPTION, "Test channel description"));
	CHECK_ERROR(ts3client_setChannelVariableAsInt(serverConnectionHandlerID, 0, CHANNEL_FLAG_PERMANENT, 1));
	CHECK_ERROR(ts3client_setChannelVariableAsInt(serverConnectionHandlerID, 0, CHANNEL_FLAG_SEMI_PERMANENT, 0));

	/* Flush changes to server */
	CHECK_ERROR(ts3client_flushChannelCreation(serverConnectionHandlerID, 0));

	printf("\nCreated channel\n\n");
	return;

on_error:
	printf("\nError creating channel: %d\n\n", error);
}


void ClientTS::deleteChannel(uint64 serverConnectionHandlerID) {
	uint64 channelID;
	unsigned int error;

	/* Query channel ID from user */
	channelID = enterChannelID();

	/* Delete channel */
	if ((error = ts3client_requestChannelDelete(serverConnectionHandlerID, channelID, 0, NULL)) == ERROR_ok) {
		printf("Deleted channel %llu\n\n", (unsigned long long)channelID);
	}
	else {
		char* errormsg;
		if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error requesting channel delete: %s (%d)\n\n", errormsg, error);
			ts3client_freeMemory(errormsg);
		}
	}
}


void ClientTS::renameChannel(uint64 serverConnectionHandlerID) {
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

void ClientTS::switchChannel(uint64 serverConnectionHandlerID) {
	unsigned int error;

	/* Query channel ID from user */
	uint64 channelID = enterChannelID();

	/* Query own client ID */
	anyID clientID;
	if ((error = ts3client_getClientID(serverConnectionHandlerID, &clientID)) != ERROR_ok) {
		printf("Error querying own client ID: %d\n", error);
		return;
	}

	/* Request moving own client into given channel */
	if ((error = ts3client_requestClientMove(serverConnectionHandlerID, clientID, channelID, "", NULL)) != ERROR_ok) {
		printf("Error moving client into channel channel: %d\n", error);
		return;
	}
	printf("Switching into channel %llu\n\n", (unsigned long long)channelID);
}


void toggleVAD(uint64 serverConnectionHandlerID) {
	static short b = 1;
	unsigned int error;

	/* Adjust "vad" preprocessor value */
	if ((error = ts3client_setPreProcessorConfigValue(serverConnectionHandlerID, "vad", b ? "false" : "true")) != ERROR_ok) {
		printf("Error toggling VAD: %d\n", error);
		return;
	}
	b = !b;
	printf("\nToggled VAD %s.\n\n", b ? "on" : "off");
}

void ClientTS::setVadLevel(uint64 serverConnectionHandlerID) {
	int vad;
	unsigned int error;
	/*
	Load vad value from file
	*/
	if ((error = ts3client_setPreProcessorConfigValue(serverConnectionHandlerID, "voiceactivation_level", session->getMicLevel())) != ERROR_ok) {
		printf("Error setting VAD level: %d\n", error);
		return;
	}
	//printf("\nSet VAD level to %s.\n\n", s);
}


void ClientTS::requestWhisperList(uint64 serverConnectionHandlerID) {
	int n;
	anyID clientID;
	uint64 targetID;
	unsigned int error;
	uint64 targetChannels[2];

	printf("\nEnter ID of the client whose whisper list should be modified (0 for own client): ");
	n = scanf("%hu", &clientID);
	emptyInputBuffer();
	if (n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	printf("\nEnter target channel ID: ");
	n = scanf("%llu", (unsigned long long*)&targetID);
	emptyInputBuffer();
	if (n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	targetChannels[0] = targetID;
	targetChannels[1] = 0;

	if ((error = ts3client_requestClientSetWhisperList(serverConnectionHandlerID, clientID, targetChannels, NULL, NULL)) != ERROR_ok) {
		char* errormsg;
		if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error requesting whisperlist: %s\n", errormsg);
			ts3client_freeMemory(errormsg);
		}
		return;
	}
	printf("Whisper list requested for client %d in channel %llu\n", clientID, (unsigned long long)targetID);
}


void ClientTS::requestClearWhisperList(uint64 serverConnectionHandlerID) {
	int n;
	anyID clientID;
	unsigned int error;

	printf("\nEnter client ID: ");
	printf("\nEnter ID of the client whose whisper list should be cleared (0 for own client): ");
	n = scanf("%hu", &clientID);
	emptyInputBuffer();
	if (n == 0) {
		printf("Invalid input. Please enter a number.\n\n");
		return;
	}

	if ((error = ts3client_requestClientSetWhisperList(serverConnectionHandlerID, clientID, NULL, NULL, NULL)) != ERROR_ok) {
		char* errormsg;
		if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			printf("Error clearing whisperlist: %s\n", errormsg);
			ts3client_freeMemory(errormsg);
		}
		return;
	}
	printf("Whisper list cleared for client %u\n", clientID);
}

void ClientTS::toggleRecordSound(uint64 serverConnectionHandlerID){
	unsigned int error;

	if (!recordSound){
		recordSound = 1;
		if ((error = ts3client_startVoiceRecording(serverConnectionHandlerID)) != ERROR_ok){
			char* errormsg;
			if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
				printf("Error notifying server of startVoiceRecording: %s\n", errormsg);
				ts3client_freeMemory(errormsg);
				return;
			}
		}
		printf("Started recording sound to wav\n");
	}
	else {
		recordSound = 0;
		if ((error = ts3client_stopVoiceRecording(serverConnectionHandlerID)) != ERROR_ok){
			char* errormsg;
			if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
				printf("Error notifying server of stopVoiceRecording: %s\n", errormsg);
				ts3client_freeMemory(errormsg);
				return;
			}
		}
		printf("Stopped recording sound to wav\n");
	}
}


int ClientTS::readIdentity(char* identity) {
	FILE *file;

	if ((file = fopen("..\\conf\\identity.txt", "r")) == NULL) {
		printf("Could not open file 'identity.txt' for reading.\n");
		return -1;
	}

	fgets(identity, IDENTITY_BUFSIZE, file);
	if (ferror(file) != 0) {
		fclose(file);
		printf("Error reading identity from file 'identity.txt'.\n");
		return -1;
	}
	fclose(file);
	return 0;
}


int ClientTS::writeIdentity(const char* identity) {
	FILE *file;

	if ((file = fopen("..\\conf\\identity.txt", "w")) == NULL) {
		//printf("Could not open file 'identity.txt' for writing.\n");
		return -1;
	}

	fputs(identity, file);
	if (ferror(file) != 0) {
		fclose(file);
		//printf("Error writing identity to file 'identity.txt'.\n");
		return -1;
	}
	fclose(file);
	return 0;
}


/*
unsigned int  ClientTS::ts3client_requestSendChannelTextMsg(uint64 serverConnectionHandlerID, const char *message, anyID targetChannelID, const char *returnCode);*/


DWORD WINAPI ClientTS::ClientStart(LPVOID lpParameter)
{
	
	unsigned int error = 0;
	char* mode;
	char** device;
	char *version;
	char identity[IDENTITY_BUFSIZE];

	ClientTS *cn = ClientTS::m_instance;

	/* Create struct for callback function pointers */
	/* Initialize all callbacks with NULL */
	memset(&cn->funcs, 0, sizeof(struct ClientUIFunctions));

	/* Callback function pointers */
	/* It is sufficient to only assign those callback functions you are using. When adding more callbacks, add those function pointers here. */
	cn->funcs.onConnectStatusChangeEvent = ClientTS::onConnectStatusChangeEvent;
	cn->funcs.onNewChannelEvent = ClientTS::onNewChannelEvent;
	cn->funcs.onNewChannelCreatedEvent = ClientTS::onNewChannelCreatedEvent;
	cn->funcs.onDelChannelEvent = ClientTS::onDelChannelEvent;
	cn->funcs.onClientMoveEvent = ClientTS::onClientMoveEvent;
	cn->funcs.onClientMoveSubscriptionEvent = ClientTS::onClientMoveSubscriptionEvent;
	cn->funcs.onClientMoveTimeoutEvent = ClientTS::onClientMoveTimeoutEvent;
	cn->funcs.onTalkStatusChangeEvent = ClientTS::onTalkStatusChangeEvent;

	cn->funcs.onTextMessageEvent = ClientTS::onTextMessageEvent;
	cn->funcs.onIgnoredWhisperEvent = ClientTS::onIgnoredWhisperEvent;
	cn->funcs.onServerErrorEvent = ClientTS::onServerErrorEvent;

	cn->funcs.onUserLoggingMessageEvent = ClientTS::onUserLoggingMessageEvent;
	cn->funcs.onCustomPacketEncryptEvent = ClientTS::onCustomPacketEncryptEvent;
	cn->funcs.onCustomPacketDecryptEvent = ClientTS::onCustomPacketDecryptEvent;
	cn->funcs.onEditMixedPlaybackVoiceDataEvent = ClientTS::onEditMixedPlaybackVoiceDataEvent;

 
	/* Initialize client lib with callbacks */
	/* Resource path points to the SDK\bin directory to locate the soundbackends folder when running from Visual Studio. */
	/* If you want to run directly from the SDK\bin directory, use an empty string instead to locate the soundbackends folder in the current directory. */

	if ((error = ts3client_initClientLib(&cn->funcs, NULL, LogType_FILE | LogType_CONSOLE | LogType_USERLOGGING, NULL, "..\\dll\\")) != ERROR_ok) {
		char* errormsg;
		if (ts3client_getErrorMessage(error, &errormsg) == ERROR_ok) {
			//wxMessageBox("Error initialzing serverlib");
			ts3client_freeMemory(errormsg);
		}
		return 1;
	}

	/* Spawn a new server connection handler using the default port and store the server ID */
	if ((error = ts3client_spawnNewServerConnectionHandler(0, &Session::Instance()->scHandlerID)) != ERROR_ok) {
		wxMessageBox("Error spawning server connection handler");
		return 1;
	}

	/* Get default capture mode */
	if ((error = ts3client_getDefaultCaptureMode(&mode)) != ERROR_ok) {
		wxMessageBox("Error getting default capture mode");
		return 1;
	}
	//printf("Default capture mode: %s\n", mode);

	/* Get default capture device */
	if ((error = ts3client_getDefaultCaptureDevice(mode, &device)) != ERROR_ok) {
		wxMessageBox("Error getting default capture device");
		return 1;
	}
	//wxMessageBox("Default capture device");

	/* Open default capture device */
	/* Instead of passing mode and device[1], it would also be possible to pass empty strings to open the default device */
	error = ts3client_openCaptureDevice(Session::Instance()->scHandlerID, mode, device[1]);
	if (error != ERROR_ok) {
		wxMessageBox("Error opening capture device");
	}

	/* Get default playback mode */
	if ((error = ts3client_getDefaultPlayBackMode(&mode)) != ERROR_ok) {
		wxMessageBox("Error getting default playback mode");
		return 1;
	}

	/* Get default playback device */
	if ((error = ts3client_getDefaultPlaybackDevice(mode, &device)) != ERROR_ok) {
		wxMessageBox("Error getting default playback device");
		return 1;
	}

	/* Open default playback device */
	/* Instead of passing mode and device[1], it would also be possible to pass empty strings to open the default device */
	if ((error = ts3client_openPlaybackDevice(Session::Instance()->scHandlerID, mode, device[1])) != ERROR_ok) {
		wxMessageBox("Error opening playback device");
	}


	/* Try reading identity from file, otherwise create new identity */
	if (ClientTS::readIdentity(identity) != 0) {
		char* id;
		if ((error = ts3client_createIdentity(&id)) != ERROR_ok) {
			wxMessageBox("Error creating identity");
			return 0;
		}
		if (strlen(id) >= IDENTITY_BUFSIZE) {
			wxMessageBox("Not enough bufsize for identity string");
			return 0;
		}
		strcpy(identity, id);
		ts3client_freeMemory(id);
		ClientTS::writeIdentity(identity);
	}


	char final_nick[50];
	strcpy(final_nick, Session::Instance()->getLanguage());
	strcat(final_nick, "$");
	strcat(final_nick, Session::Instance()->getNick());
	strcat(final_nick, "$");

	/* Connect to server on localhost:9987 with nickname "client", no default channel, no default channel password and server password "secret" */
	if ((error = ts3client_startConnection(Session::Instance()->scHandlerID, identity, Session::Instance()->getServerAddress(), PORT, final_nick, NULL, "", "secret")) != ERROR_ok) {
		wxMessageBox("Error connecting to server");
		ts3client_logMessage("Error connecting to server", LogLevel_ERROR, "Channel", 10);
		return 1;
	}

	/* Query and print client lib version */
	if ((error = ts3client_getClientLibVersion(&version)) != ERROR_ok) {
		wxMessageBox("Failed to get clientlib version");
		return 1;
	}

	ts3client_setChannelVariableAsInt(Session::Instance()->scHandlerID, 1, CHANNEL_CODEC_QUALITY, 7);
	ts3client_freeMemory(version);  /* Release dynamically allocated memory */
	version = NULL;

	/* Disconnect from server */
	return 0;
}

void ClientTS::disconnect(){
	unsigned int error;
	if ((error = ts3client_stopConnection(session->scHandlerID, "leaving")) != ERROR_ok) {
		printf("Error stopping connection: %d\n", error);
		return;
	}

	SLEEP(300);

	/* Destroy server connection handler */
	if ((error = ts3client_destroyServerConnectionHandler(session->scHandlerID)) != ERROR_ok) {
		printf("Error destroying clientlib: %d\n", error);
		return;
	}

	/* Shutdown client lib */
	if ((error = ts3client_destroyClientLib()) != ERROR_ok) {
		printf("Failed to destroy clientlib: %d\n", error);
		return;
	}

	/* This is a small hack, to close an open recording sound file */
	recordSound = 0;
	ClientTS::onEditMixedPlaybackVoiceDataEvent(DEFAULT_VIRTUAL_SERVER, NULL, 0, 0, NULL, NULL);

}

void ClientTS::emptyInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


DWORD WINAPI ClientTS::STT_THREAD(LPVOID lpParameter)
{
	char translate_jar[512] = { "" }; //tsclient
	FILE *trad;
	while (1)
	{
		Sleep(500);
		if (trad = fopen("translate.txt", "r")) //if file exist read the string from nuance dragon service
		{
			fgets(translate_jar, 256, trad);
			fflush(trad);
			fclose(trad);
			if (strcmp(translate_jar, "") != 0)	//if translate_jar isn't empty
			{
				wxString final = "\n" + wxString::FromAscii(Session::Instance()->getLanguage()) + "\n" + wxString::FromUTF8(translate_jar);
				ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, final, (uint64)1, NULL); //Send other clients the speechtotext message from dragon transaction
				strcpy(translate_jar, "");
				WinExec("Taskkill /IM java.exe /F", SW_HIDE);	//Kill java
				Sleep(50);
				WinExec("del /F translate.txt", SW_HIDE);		//Delete translate file
				remove("recorded.wav");
				remove("translate.txt");
				Session::Instance()->sound_flag = false;								//Inform all thread to finish operation
				Session::Instance()->finish_ctrl_flag = false;							//Inform the pushtotalk thread to finish operation
			}
		}
	}
}

DWORD WINAPI ClientTS::TTS_THREAD(LPVOID lpParameter)
{
	while (1)
	{
		thread_semaphore.Wait();
		MessageQueuePTR ld = Session::Instance()->getMessageQueue();
		auto se = ld->begin() + text_to_speech;  
		ClientTS::speak((char*)Session::Instance()->getLanguage(), (*se)->getMSG().mb_str().data());
	}
	return 0;
}

DWORD WINAPI ClientTS::CTRL_STT(LPVOID lpParameter)
{

	while (1)
	{
		if (GetAsyncKeyState(VK_CONTROL) && !Session::Instance()->finish_ctrl_flag)
		{
			if (!recorder->isRecording())
			{
				recorder->startRecordingBufferedAudio();
				Session::Instance()->finish_ctrl_flag = true;
			}
			Sleep(50);
		}
		Sleep(50);
	}
	return 1;
}

/*
wxThread::ExitCode TranslateMSGThread::Entry()
{
	while (1){
		thread_semaphore.Wait();
	}
	return (ExitCode)0;

}*/

void QueueMSG::AddJob(MessagePTR job) // push a job with given priority class onto the FIFO
{
	wxMutexLocker lock(m_MutexQueue); // lock the queue
	m_Jobs.push_back(job); // insert the prioritized entry into the multimap
	m_QueueCount.Post(); // new job has arrived: increment semaphore counter
} // void AddJob(const tJOB& job, const tPRIORITY& priority=eNORMAL)

MessagePTR QueueMSG::Pop()
{
	MessagePTR msg;
	m_QueueCount.Wait(); // wait for semaphore (=queue count to become positive)
	{
		m_MutexQueue.Lock();// lock queue
		auto element = m_Jobs.begin();// get the first entry from queue (higher priority classes come first)
		msg = *element;
		m_Jobs.erase(element);
		m_MutexQueue.Unlock(); // unlock queue
	}
	return msg; 
} // tJOB Pop()

void QueueMSG::Report(MessagePTR arg) // report back to parent
{
	wxThreadEvent evt(wxEVT_THREAD, wxID_ANY);// cmd); // create command event object
	evt.SetPayload<MessagePTR>(arg); // associate string with it
	wxQueueEvent(m_pParent, evt.Clone());
	//m_pParent->AddPendingEvent(evt); // and add it to parent's event queue
} // void Report(const tJOB::tCOMMANDS& cmd, const wxString& arg=wxEmptyString)

void WorkerThread::OnJob()
{
	MessagePTR job = m_pQueue->Pop(); // pop a job from the queue. this will block the worker thread if queue is empty
	bng->translateThis(job);
	m_pQueue->Report(job); // report successful completion
} // virtual void OnJob()

wxThread::ExitCode WorkerThread::Entry()
{
	//m_pQueue->Report(Message::eID_THREAD_STARTED, NULL); // tell main thread that worker thread has successfully started
	if (strcmp(Session::Instance()->getTranslationEngine(), "google") == 0)
		bng = std::make_unique<Translation::GoogleTranslate>();
	else bng = std::make_unique<Translation::BingTranslate>();

	while (true)
			OnJob();
 
} // virtual wxThread::ExitCode Entry()