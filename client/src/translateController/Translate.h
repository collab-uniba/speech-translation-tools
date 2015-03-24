#pragma once

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif
#include <wx/wx.h>
#include "../data/Message.h"

#include <curl/curl.h>

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
		void translateThis(MessagePTR msg);
	private:
		float GetRemainingTime();
		void getToken();
	private:
		UINT64	m_ExpirationTime;
		struct MemoryStruct token;
	};
}