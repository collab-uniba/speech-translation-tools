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
#include "../translatecontroller/translate.h"

#include "EventType.h" 

#include <vector>
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/grid.h>
#include "../gui/NationList.h"
#include "../gui/NationInfo.h" 
#include "../ArchiveLog.h"
#include <wx/thread.h>

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"
 
#include <list>
#include <functional> 

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802


using namespace Translation;

enum
{
	MSGTRANSLATE_THREAD_EVENT
};
/*
class TranslateMSGThread : public wxThread
{
public:
	TranslateMSGThread(wxFrame *dlg) : wxThread(wxTHREAD_JOINABLE)
	{
		m_dlg = dlg;
		//Sleep(5000);
	}

	virtual ExitCode Entry();

private:
	wxFrame *m_dlg;
	wxSemaphore m_thread_semaphore;
	BingTranslate m_bingtranslator;
};*/

class WorkerThread : public wxThread
{
public:
	WorkerThread(QueueMSG* pQueue, int id = 0) : m_pQueue(pQueue), m_ID(id) { assert(pQueue); wxThread::Create(); }

private:
	QueueMSG* m_pQueue;
	int m_ID;
	BingTranslate bng;
	virtual wxThread::ExitCode Entry()
	{
		Message::tCOMMANDS iErr;
		m_pQueue->Report(Message::eID_THREAD_STARTED, NULL, m_ID); // tell main thread that worker thread has successfully started
		try { 
			while (true) OnJob(); 
		} // this is the main loop: process jobs until a job handler throws
		catch (Message::tCOMMANDS& i) { 
			m_pQueue->Report(iErr = i, NULL, m_ID);
		} // catch return value from error condition
		return (wxThread::ExitCode)iErr; // and return exit code
	} // virtual wxThread::ExitCode Entry()

	virtual void OnJob()
	{
		MessagePTR job = m_pQueue->Pop(); // pop a job from the queue. this will block the worker thread if queue is empty
		bng.translateThis(job);
		switch (job->m_cmd)
		{
		case Message::eID_THREAD_EXIT: // thread should exit
			//Sleep(1000); // wait a while
			throw Message::eID_THREAD_EXIT; // confirm exit command
		case Message::eID_THREAD_JOB: // process a standard job
			//Sleep(2000);
			m_pQueue->Report(Message::eID_THREAD_JOB, job, m_ID); // report successful completion
			break;
		case Message::eID_THREAD_JOBERR: // process a job that terminates with an error
			m_pQueue->Report(Message::eID_THREAD_JOB, job, m_ID);
			//Sleep(1000);
			throw Message::eID_THREAD_EXIT; // report exit of worker thread
			break;
		case Message::eID_THREAD_NULL: // dummy command
		default: break; // default
		} // switch(job.m_cmd)
	} // virtual void OnJob()
}; // class WorkerThread : public wxThread




class QueueMSG
{
public:
	QueueMSG(wxEvtHandler* pParent) : m_pParent(pParent) {}
	void AddJob(MessagePTR job) // push a job with given priority class onto the FIFO
	{
		wxMutexLocker lock(m_MutexQueue); // lock the queue
		m_Jobs.push_back(job); // insert the prioritized entry into the multimap
		m_QueueCount.Post(); // new job has arrived: increment semaphore counter
	} // void AddJob(const tJOB& job, const tPRIORITY& priority=eNORMAL)
	MessagePTR Pop()
	{
		std::vector<MessagePTR>::iterator element;
		m_QueueCount.Wait(); // wait for semaphore (=queue count to become positive)
		m_MutexQueue.Lock(); // lock queue
		element = m_Jobs.begin(); // get the first entry from queue (higher priority classes come first)
		m_Jobs.erase(m_Jobs.begin()); // erase it
		m_MutexQueue.Unlock();// unlock queue
		return *element; // return job entry
	} // tJOB Pop()
	void Report(const Message::tCOMMANDS& cmd, MessagePTR arg, int iArg = 0) // report back to parent
	{
		wxThreadEvent evt(wxEVT_THREAD, wxID_ANY);// cmd); // create command event object
		evt.SetPayload<MessagePTR>(arg); // associate string with it
		
		 
		wxQueueEvent(m_pParent, evt.Clone());


		//m_pParent->AddPendingEvent(evt); // and add it to parent's event queue
	} // void Report(const tJOB::tCOMMANDS& cmd, const wxString& arg=wxEmptyString)
	size_t Stacksize() // helper function to return no of pending jobs
	{
		wxMutexLocker lock(m_MutexQueue); // lock queue until the size has been read
		return m_Jobs.size();
	}

private:
	wxEvtHandler* m_pParent;
	std::vector<MessagePTR> m_Jobs; // multimap to reflect prioritization: values with lower keys come first, newer values with same key are appended
	wxMutex m_MutexQueue; // protects queue access
	wxSemaphore m_QueueCount; // semaphore count reflects number of queued jobs
};



class ClientTS  {
public:
	wxFrame* observer;
	static  Session* session;
	static  ConfigPTR config;
	static bool flagSave;
	static  long text_to_speech;
	static  wxSemaphore thread_semaphore;
	//static ISoundEngine* engine;				//Audio Engine to record sound
	static IAudioRecorder* recorder;			//Flow of audio daa
	//static uint64 scHandlerID;
	struct ClientUIFunctions funcs;
	static  char identity[IDENTITY_BUFSIZE];
	static ClientTS *m_instance;
	TranslateMSGThread msg_thread;
	QueueMSG* m_pQueue;
	std::list<int> m_Threads;


public:
	ClientTS(wxFrame * frame) : msg_thread(frame){
		if (!m_instance)
			m_instance = this;
		observer = frame;
		m_pQueue = new QueueMSG(frame);
		session = Session::Instance();
		config = session->getConfig();
		// draw the bitmap from a secondary thread
		/*if (msg_thread.Create() != wxTHREAD_NO_ERROR ||
			msg_thread.Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("Can't create/run thread!"));
			return;
		}*/
		m_pQueue = new QueueMSG(frame);
		OnStart();
	}

	void OnStart() // start one worker thread
	{
		int id = m_Threads.empty() ? 1 : m_Threads.back() + 1;
		m_Threads.push_back(id);
		WorkerThread* pThread = new WorkerThread(m_pQueue, id); // create a new worker thread, increment thread counter (this implies, thread will start OK)
		pThread->Run();
	}

	virtual ~ClientTS(){
		//m_thread.Delete();
	}

	static void sendMessage(wxString *msgToSend);
	static void onTextMessageEventss(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
	static void disconnect(); 
	
	static IAudioRecorder* getIAudioRecorder(){ return recorder; }

	static bool getFlagSave(){ return flagSave; }

	static void setFlagSave(bool flg){ flagSave = flg; }
	template <typename Observer>
	static void setCBClientTSMSG(Observer && fn){ notifyMSGcb = std::forward<Observer>(fn); }
	static void speak(const char *LANG, const char*MSG);
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

/*
class msgEvent : public wxThreadEvent{

};*/
/*struct user* getPerson();
char* getLANG_MSG_SRC();
char* getMSG_SRC();
void emptyInputBuffer();
//void registercb(cbClientTsFrm fn);*/





