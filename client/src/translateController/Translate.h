#pragma once

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif
#include <wx/wx.h>
#include "../data/Message.h"


#include "rapidjson/document.h"		
#include "rapidjson/prettywriter.h"	
#include "rapidjson/filestream.h"

#include "../gui/NationList.h"
#include <curl/curl.h>

using namespace rapidjson;

const UINT MAX_INPUT_TEXT = 10000;
const float AUTH_TIME_MARGIN = 20.0f;

#define MY_ID  "daniteamspeak"
#define MY_KEY "4HqBNNb/0aVQB7Mj4VULgLLFIZnGx+yQfOUROsSwqrI"

namespace Translation{

	struct MemoryStruct
	{
		char *memory;
		size_t size;
	};

	class TranslateX {
	public:
		virtual void translateThis(MessagePTR msg) = 0;   // Pure virtual function.
	};


	class BingTranslate : public TranslateX {
	public:
		BingTranslate(){
			getToken();
		}
		~BingTranslate(){}
		void translateThis(MessagePTR msg);
	private:
		float GetRemainingTime();
		void init_string(struct Translation::MemoryStruct *s);
		void getToken();
		wxString clean(char *word);
	private:
		time_t	m_expirationTime;
		std::string	m_access_token;
	};

	/* not implemented -> API not public*/
	class GoogleTranslate : public TranslateX {
	public:
		GoogleTranslate(){}
		~GoogleTranslate(){}
		void translateThis(MessagePTR msg);
	private:
	private:
		time_t	m_expirationTime;
		std::string	m_access_token;
	};
}
