#ifndef __CLIENTTS_H__
#define __CLIENTTS_H__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif

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
//#include "../gui/FrmSaveChat.h"

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802


bool getFlagSave();

void setFlagSave(bool flg);
 
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

 


DWORD WINAPI TTS_THREAD(LPVOID lpParameter);
DWORD WINAPI CTRL_STT(LPVOID lpParameter);
DWORD WINAPI ClientStart(LPVOID lpParameter);
DWORD WINAPI STT_THREAD(LPVOID lpParameter);

#endif
