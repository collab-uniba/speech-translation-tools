#pragma once

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif
 
#include "../data/Session.h"
#include "../data/Message.h"
#include "../data/Config.h"

#include "EventType.h" 

#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/grid.h>
#include "../gui\NationList.h"
#include "../gui\NationInfo.h" 
#include "../ArchiveLog.h"

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"
 
#include <list>
#include <functional> 

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802


typedef std::function<void()> cbClientTsFrm;
/*class ClientTsFrm; 

typedef std::function<void(const ClientTsFrm&)> cbClientTsFrm;*/
/*
void registerObserver(cbClientTsFrm fn, ClientTsFrm &obj);

template <typename T> 
struct ClientTS{
	cbClientTsFrm cbfrm;
	T clientfrm;
	void registerObserver(cbClientTsFrm fn, T &obj){
		cbfrm = fn;
		clientfrm = obj;
		fn(obj);
	}
};*/
 

/*class ClientTsFrm;

typedef std::function<void(const ClientTsFrm&)> cbClientTsFrm;*/


class ClientTS  {
public:
	static Session* session;
	static ConfigPTR config;
	static bool flagSave;
	static char LANG_MSG_SRC[500];
	static char MSG_SRC[500];
	static cbClientTsFrm notifyMSGcb;
	//static ISoundEngine* engine;				//Audio Engine to record sound
	static IAudioRecorder* recorder;			//Flow of audio daa
	//static uint64 scHandlerID;

	static char identity[IDENTITY_BUFSIZE];

	/* Create struct for callback function pointers */
	static struct ClientUIFunctions funcs;
public:
	ClientTS(){
		session = Session::Instance();
		config = session->getConfig();
	}
	virtual ~ClientTS(){}

	static void disconnect();
	static char* getLANG_MSG_SRC(){ return LANG_MSG_SRC; }

	static char* getMSG_SRC(){ return MSG_SRC; }
	static IAudioRecorder* getIAudioRecorder(){ return recorder; }

	static bool getFlagSave(){ return flagSave; }

	static void setFlagSave(bool flg){ flagSave = flg; }
	template <typename Observer>
	static void setCBClientTSMSG(Observer && fn){ notifyMSGcb = std::forward<Observer>(fn); }

	static void speak(char *LANG, char*MSG);
	static void Print(char*word);
	static size_t read_callback(static void *ptr, size_t size, size_t nmemb, static void *userp);
	static void writeWaveFile(const char* filename, SAudioStreamFormat format, static void* data);
	static void SetupColor(COLORE *c);
	static void onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
	static void onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID);
	static void onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	static void onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	static void onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
	static void onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
	static void onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
	static void onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID);
	static void onIgnoredWhisperEvent(uint64 serverConnectionHandlerID, anyID clientID);
	static void onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
	static void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
	static void onCustomPacketEncryptEvent(char** dataToSend, unsigned int* sizeOfData);
	static void onCustomPacketDecryptEvent(char** dataReceived, unsigned int* dataReceivedSize);
	static void onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask);
	static void showChannels(uint64 serverConnectionHandlerID);
	static void showChannelClients(uint64 serverConnectionHandlerID, uint64 channelID);
	static void onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
	static void showClients(uint64 serverConnectionHandlerID);
	static void createChannel(uint64 serverConnectionHandlerID, const char *name);
	static void deleteChannel(uint64 serverConnectionHandlerID);
	static void renameChannel(uint64 serverConnectionHandlerID);
	static void switchChannel(uint64 serverConnectionHandlerID);
	static void toggleVAD(uint64 serverConnectionHandlerID);
	static void setVadLevel(uint64 serverConnectionHandlerID);
	static void requestWhisperList(uint64 serverConnectionHandlerID);
	static void requestClearWhisperList(uint64 serverConnectionHandlerID);
	static void toggleRecordSound(uint64 serverConnectionHandlerID);
	static int readIdentity(char* identity);
	static int writeIdentity(const char* identity);
	static uint64  enterChannelID();
	static void createDefaultChannelName(char *name);
	static void enterName(char *name); 
	static void emptyInputBuffer();

	static DWORD WINAPI TTS_THREAD(LPVOID lpParameter);
	static DWORD WINAPI CTRL_STT(LPVOID lpParameter);
	static DWORD WINAPI ClientStart(LPVOID lpParameter);
	static DWORD WINAPI STT_THREAD(LPVOID lpParameter);
};

/*struct user* getPerson();
char* getLANG_MSG_SRC();
char* getMSG_SRC();
void emptyInputBuffer();
//void registercb(cbClientTsFrm fn);*/




