#ifndef _GLOBALVARIABLES_H_
#define _GLOBALVARIABLES_H_

#include "utility.h"
#include <windows.h>
#include <atlbase.h>
#include <sphelper.h>

#include <list>
#include <memory>

#include <sapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sstream>
#include <time.h>
#include <limits.h>
#include <audiere.h>
#include <irrKlang.h>
#include <string.h>
#include <iostream>
#include <public_definitions.h>
#include <public_errors.h>
#include <clientlib_publicdefinitions.h>
#include <clientlib.h>
#include <curl/curl.h>
#include <wx/generic/grid.h>
#include <wx/msgdlg.h>
#include <wx/sstream.h>
#include <wx/protocol/http.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextstyles.h>
#include <wx/richtext/richtextxml.h>
#include <wx/richtext/richtexthtml.h>
#include <wx/richtext/richtextformatdlg.h>
#include <wx/richtext/richtextsymboldlg.h>
#include <wx/richtext/richtextstyledlg.h>
#include <wx/richtext/richtextprint.h>
#include <wx/richtext/richtextimagedlg.h>
#include "rapidjson/document.h"		
#include "rapidjson/prettywriter.h"	
#include "rapidjson/filestream.h"
#include <list>
#include "../res/keyboard.xpm"
#include "../res/microphone.xpm"
#include "../res/italy.xpm"
#include "../res/usa.xpm"
#include "../res/brasil.xpm"


#define MAX 30

#define DEFAULT_VIRTUAL_SERVER 1
#define NAME_BUFSIZE 1024
#define MAXCHATSIZE 1024

#define CHECK_ERROR(x) if((error = x) != ERROR_ok) { goto on_error; }
#define IDENTITY_BUFSIZE 1024

#ifdef _WIN32
#define snprintf sprintf_s
#define strdup _strdup
#define SLEEP(x) Sleep(x)
#else
#define SLEEP(x) usleep(x*1000)
#endif

using namespace audiere;
using namespace std;
using namespace ATL;
using namespace rapidjson;
using namespace irrklang;

struct WaveHeader {
	/* Riff chunk */
	char riffId[4];
	unsigned int len;
	char riffType[4];
	/* Format chunk */
	char fmtId[4];  // 'fmt '
	unsigned int fmtLen;
	unsigned short formatTag;
	unsigned short channels;
	unsigned int samplesPerSec;
	unsigned int avgBytesPerSec;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	/* Data chunk */
	char dataId[4];  // 'data'
	unsigned int dataLen;
};



typedef struct color
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
} COLORE;

struct user
{
	wxString name;
	unsigned short color;
	unsigned short used = 0;
	unsigned short speak = 0;
	unsigned short write = 0;
	wxString lang;
};

typedef struct stringa {
	char *ptr;
	size_t len;
};

typedef struct message
{
	wxString nick;
	wxString msgnew;
	wxString lang;
	wxString msgold;
	wxString timestamp;
	wxString msgDir;
} MESSAGE;

typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;            // sample_rate denotes the sampling rate.
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;         // subchunk2_size denotes the number of samples.
} header;


typedef struct header_file* header_p;

struct WriteThis {
	const char *readptr;
	long sizeleft;
};

static DWORD myThreadID;
static DWORD myThreadID2;
static DWORD myThreadID3;
static DWORD myThreadID4;

static int iresult;
static short flag = 0; //Flag to exit from client

static wxString strGlobale = "";
static wxString oldstrGlobale = "";
static wxString strNick = "";
static wxString strMessage = "";
static wxString oldStringTranslate = "";
static wxString StringOriginal = "";
static wxString strSpeak = "";


class Message;
typedef std::shared_ptr<Message> MessagePTR;
typedef std::list<MessagePTR> MessageQueue;

static unsigned short PORT = 9987;	//Number port of server
static int cmbel = 0;				//Index of comboBox choose
static int VAD_VALUE = 1;			//Minimum value to record audio
static COLORE colors[10];
static unsigned count_client;
static unsigned short set_color_client;	//Own client color name
static struct user person[MAX];			//Array of user to record client's information
static ISoundEngine* engine;				//Audio Engine to record sound
static IAudioRecorder* recorder;			//Flow of audio daa
static bool sound_flag = false;			//Flag to start/stop 
static bool tts_flag = false;				//Flag to start/stop TextToSpeech 		
static bool write_flag = false;			//Flag to recognize Typing
static bool tasto_stt_flag = false;		//Flag to activate Automatic SpeechToText
static bool finish_ctrl_flag = false;		//Flag to recognize CTRL press button
static bool automatic_stt_flag = false;
/*static wxRichTextCtrl *chatptr;				//Pointer to edit the chatptr
static unsigned int curRow = 0;			//Initialize Row index
static unsigned int curCol = 0;			//Initialize Column index
static wxGrid *gridptr;					//Pointer to edit the chatptr grid*/
static uint64 _sclogID;
//uint64 _sclogID;
//ArchiveLog * archivelog;
//extern MESSAGE diary[MAXCHATSIZE];				//Structure to record log chatptr

// DIARY LO FACCIO DIVENTARE LIST DI MESSAGE
// RISOLVI FLAGSAVE
extern list<MESSAGE> diary;


extern wxString StringTranslate ;
#endif /* _GLOBALVARIABLES_H_ */