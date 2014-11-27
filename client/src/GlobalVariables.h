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

typedef struct colore
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
} COLORE;

struct user
{
	wxString nome;
	unsigned short colore;
	unsigned short usato = 0;
	unsigned short parla = 0;
	unsigned short scrive = 0;
	wxString lingua;
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
int numero;
int max;
short flag = 0;

wxString strGlobale = "";
wxString oldstrGlobale = "";
wxString strNick = "";
wxString strMessage = "";
wxDateTime data;
wxString StringTranslate = "";
wxString oldStringTranslate = "";
wxString StringOriginal = "";
wxString TESTTTS = "";
wxImage *immagine;
char SERVER_ADDRESS[20];
char NICK[50];
char LINGUA[20];
char SERVIZIO[20];
char LINGUA_MSG_SRC[20] = { "" };
char MSG_SRC[50] = { "" };
char GOOGLE_API_KEY[50] = { "" };
char url[256] = { "" };
char MSG_PARSE[1024] = { "" };
char traduzione_jar[512] = { "" };
wxString nome_parla = "";
wxString strSpeak = "";
unsigned short PORT = 9987;
int cmbel = 0;
int indice = -1;
int VAD_VALUE = 1;
COLORE colori[10];
unsigned conta_client;
unsigned short set_color_client;
unsigned short coloreClient[MAX];
struct user persona[MAX];
ISoundEngine* engine;
IAudioRecorder* recorder;
bool sound_flag = false;
bool tts_flag = false;
bool rec_flag = false;
bool write_flag = false;
bool tasto_stt_flag = false;
wxRichTextCtrl *chat;
unsigned int curRow = 0;
unsigned int curCol = 0;
MESSAGE diario[1024];
wxGrid *griglia;