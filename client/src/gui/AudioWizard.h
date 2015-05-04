///-----------------------------------------------------------------
///
/// @file      AudioWizard.h
/// @author    Utente
/// Created:   24/11/2014 09:25:23
/// @section   DESCRIPTION
///            AudioWizard class declaration
///
///------------------------------------------------------------------

#pragma once

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

#include <wx/compiler.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/statbmp.h>

#include "../data/Session.h"
#include "../res/ledrosso.xpm"
#include "../res/ledverde.xpm"
#include "../translateController/translateVariable.h"

class AudioWizard : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		AudioWizard(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AudioWizard"), 
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
			long style = wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER);
		void ConfermaClick(wxCommandEvent& event);
		virtual ~AudioWizard();
		void WxTimer1Timer(wxTimerEvent& event);
	
	private:
		wxButton *btnconferma;
		wxStaticText *lblhelp;
		wxSlider *slideraudio;
		wxStaticBitmap *bmpfeed;
		wxTimer *WxTimer1;

		
	private:
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON1 = 1004,
			ID_WXSTATICTEXT1 = 1003,
			ID_WXSLIDER1 = 1002,
			ID_WXSTATICBITMAP1 = 1001,
			ID_WXTIMER1 = 1006,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

