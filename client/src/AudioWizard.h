///-----------------------------------------------------------------
///
/// @file      AudioWizard.h
/// @author    Utente
/// Created:   24/11/2014 09:25:23
/// @section   DESCRIPTION
///            AudioWizard class declaration
///
///------------------------------------------------------------------

#ifndef __AUDIOWIZARD_H__
#define __AUDIOWIZARD_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/statbmp.h>
////Header Include End

////Dialog Style Start
#undef AudioWizard_STYLE
#define AudioWizard_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class AudioWizard : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		AudioWizard(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("AudioWizard"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = AudioWizard_STYLE);
		void ConfermaClick(wxCommandEvent& event);
		virtual ~AudioWizard();
		void WxTimer1Timer(wxTimerEvent& event);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *btnconferma;
		wxStaticText *lblhelp;
		wxSlider *slideraudio;
		wxStaticBitmap *bmpfeed;
		wxTimer *WxTimer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
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

#endif
