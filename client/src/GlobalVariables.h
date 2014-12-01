#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include "Login.h"
#include "utility.h"
#include <windows.h>
#include <atlbase.h>
#include <sphelper.h>
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

#include "../res/keyboard.xpm"
#include "../res/microphone.xpm"
#include "../res/italy.xpm"
#include "../res/usa.xpm"
#include "../res/brasil.xpm"

#define MAX 30

#define DEFAULT_VIRTUAL_SERVER 1
#define NAME_BUFSIZE 1024

#define CHECK_ERROR(x) if((error = x) != ERROR_ok) { goto on_error; }
#define IDENTITY_BUFSIZE 1024

#ifdef _WIN32
#define snprintf sprintf_s
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

struct stringa {
	char *ptr;
	size_t len;
};

typedef struct message
{
	wxString nick;
	wxString msgnew;
	wxString lang;
	wxString msgold;
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

DWORD myThreadID;
DWORD myThreadID2;
DWORD myThreadID3;
DWORD myThreadID4;

int iresult;
short flag = 0; //Flag to exit from client

wxString strGlobale = "";
wxString oldstrGlobale = "";
wxString strNick = "";
wxString strMessage = "";
wxString StringTranslate = "";
wxString oldStringTranslate = "";
wxString StringOriginal = "";
wxString strSpeak = "";

char SERVER_ADDRESS[20];
char NICK[50];
char CURRENT_LANG[20];
char SERVICE[20];
char LANG_MSG_SRC[20] = { "" };
char MSG_SRC[50] = { "" };
char GOOGLE_API_KEY[50] = { "" };
char url[256] = { "" };
char MSG_PARSE[1024] = { "" };
char translate_jar[512] = { "" };


unsigned short PORT = 9987;	//Number port of server
int cmbel = 0;				//Index of comboBox choose
int index = -1;
int VAD_VALUE = 1;			//Minimum value to record audio
COLORE colors[10];
unsigned count_client;
unsigned short set_color_client;	//Own client color name
struct user person[MAX];			//Array of user to record client's information
ISoundEngine* engine;				//Audio Engine to record sound
IAudioRecorder* recorder;			//Flow of audio daa
bool sound_flag = false;			//Flag to start/stop 
bool tts_flag = false;				//Flag to start/stop TextToSpeech 		
bool write_flag = false;			//Flag to recognize Typing
bool tasto_stt_flag = false;		//Flag to activate Automatic SpeechToText
bool finish_ctrl_flag = false;		//Flag to recognize CTRL press button
wxRichTextCtrl *chatptr;				//Pointer to edit the chatptr
unsigned int curRow = 0;			//Initialize Row index
unsigned int curCol = 0;			//Initialize Column index
MESSAGE diary[1024];				//Structure to record log chatptr
wxGrid *gridptr;					//Pointer to edit the chatptr grid