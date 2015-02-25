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

#include "../gui/ClientTsFrm.h"
#include "../data/Session.h"
#include "../data/Message.h"
#include "../data/Config.h" 

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
//#include "..\gui\LoginWarnings.h"
#include "../ArchiveLog.h"

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"
/*#include "../gui/FrmMailSending.h"
#include "../gui/FrmSettingMail.h"
#include "../gui/AudioWizard.h"*/
#include <list>
#include <functional>
#include "Subject.h"

#include "EventType.h"


//#include "../gui/FrmSaveChat.h"

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802

/**/class ClientTsFrm; 

typedef std::function<void(const ClientTsFrm&)> cbClientTsFrm;
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

static bool flagSave = true;
bool getFlagSave();

void setFlagSave(bool flg);

void registerObserver(cbClientTsFrm fn, ClientTsFrm &obj);

	void speak(char *LANG, char*MSG);
	void Print(char*word);
	static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);
	void writeWaveFile(const char* filename, SAudioStreamFormat format, void* data);
	void SetupColor();
	void onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
	void onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID);
	void onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	void onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	void onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
	void onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
	void showClients(uint64 serverConnectionHandlerID);
	void setVadLevel(uint64 serverConnectionHandlerID);
	void onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
	void onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID);
	void onIgnoredWhisperEvent(uint64 serverConnectionHandlerID, anyID clientID);
	void onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
	void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
	void onCustomPacketEncryptEvent(char** dataToSend, unsigned int* sizeOfData);
	void onCustomPacketDecryptEvent(char** dataReceived, unsigned int* dataReceivedSize);
	void onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask);
	void showChannels(uint64 serverConnectionHandlerID);
	void showChannelClients(uint64 serverConnectionHandlerID, uint64 channelID);
	void onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
	void showClients(uint64 serverConnectionHandlerID);
	void createChannel(uint64 serverConnectionHandlerID, const char *name);
	void deleteChannel(uint64 serverConnectionHandlerID);
	void renameChannel(uint64 serverConnectionHandlerID);
	void switchChannel(uint64 serverConnectionHandlerID);
	void toggleVAD(uint64 serverConnectionHandlerID);
	void setVadLevel(uint64 serverConnectionHandlerID);
	void requestWhisperList(uint64 serverConnectionHandlerID);
	void requestClearWhisperList(uint64 serverConnectionHandlerID);
	void toggleRecordSound(uint64 serverConnectionHandlerID);
	int readIdentity(char* identity);
	int writeIdentity(const char* identity);
 

struct user* getPerson();
char* getLANG_MSG_SRC();
char* getMSG_SRC();
//void registercb(cbClientTsFrm fn);


DWORD WINAPI TTS_THREAD(LPVOID lpParameter);
DWORD WINAPI CTRL_STT(LPVOID lpParameter);
DWORD WINAPI ClientStart(LPVOID lpParameter);
DWORD WINAPI STT_THREAD(LPVOID lpParameter);
