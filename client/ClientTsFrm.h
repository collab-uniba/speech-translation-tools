///-----------------------------------------------------------------
///
/// @file      ClientTsFrm.h
/// @author    Utente
/// Created:   07/10/2014 15:14:10
/// @section   DESCRIPTION
///            ClientTsFrm class declaration
///
///------------------------------------------------------------------

#ifndef __CLIENTTSFRM_H__
#define __CLIENTTSFRM_H__

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
//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef ClientTsFrm_STYLE
#define ClientTsFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class ClientTsFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		double conta;
		
	public:
		ClientTsFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("ClientTs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ClientTsFrm_STYLE);
		virtual ~ClientTsFrm();
		void WxButton1Click(wxCommandEvent& event);
		void txtsendClick(wxCommandEvent& event);
		void aggiorna(wxString);
		void txtchatClick(wxRichTextEvent& event);
		void txtchatEnter(wxCommandEvent& event);
		void OnTimerTimeout(wxTimerEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void txtmsgEnter(wxCommandEvent& event);
		void RefreshChat();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTimer *WxTimer1;
		wxRichTextCtrl *txtclient;
		wxTextCtrl *txtlingua;
		wxStaticText *lbllingua;
		wxStaticText *lblnick;
		wxTextCtrl *txtnick;
		wxRichTextCtrl *txtchat;
		wxButton *txtsend;
		wxTextCtrl *txtmsg;
		wxButton *WxButton1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXTIMER1 = 1006,
			ID_WXRICHTEXTCTRL2 = 1012,
			ID_WXEDIT3 = 1011,
			ID_WXSTATICTEXT2 = 1010,
			ID_WXSTATICTEXT1 = 1009,
			ID_WXEDIT2 = 1008,
			ID_WXRICHTEXTCTRL1 = 1005,
			ID_WXBUTTON2 = 1004,
			ID_WXEDIT1 = 1003,
			ID_WXBUTTON1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};
#endif
