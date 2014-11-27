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
#include <wx/grid.h>
////Header Include End

////Dialog Style Start
#undef ClientTsFrm_STYLE
#define ClientTsFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX
////Dialog Style End

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801

class ClientTsFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		double conta;
		
	public:
		ClientTsFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("ClientTs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ClientTsFrm_STYLE);
		virtual ~ClientTsFrm();
		void WxButton1Click(wxCommandEvent& event);
		void btnsendClick(wxCommandEvent& event);
		void aggiorna(wxString);
		void txtchatClick(wxRichTextEvent& event);
		void txtchatEnter(wxCommandEvent& event);
		void OnTimerTimeout(wxTimerEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void txtmsgEnter(wxCommandEvent& event);
		void RefreshChat();
		void txttranslateClick(wxCommandEvent& event);
		void ClientTsFrmActivate(wxActivateEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxTimer2Timer(wxTimerEvent& event);
		void WxGrid1CellLeftClick(wxGridEvent& event);
		void Debug(wxCommandEvent& event);
		void Wizard(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTimer *WxTimer2;
		wxTimer *WxTimer1;
		wxButton *txttranslate;
		wxRichTextCtrl *txtclient;
		wxTextCtrl *txtlingua;
		wxStaticText *lbllingua;
		wxStaticText *lblnick;
		wxTextCtrl *txtnick;
		wxRichTextCtrl *txtchat;
		wxButton *btnsend;
		wxTextCtrl *txtmsg;
		wxButton *WxButton1;
		wxGrid *WxGrid1;
		wxMenuBar *WxMenuBar1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXGRID1 = 1033,
			ID_WXTIMER2 = 1014,
			ID_WXTIMER1 = 1006,
			ID_WXBUTTON3 = 1013,
			ID_WXRICHTEXTCTRL1 = 1012,
			ID_WXEDIT2 = 1011,
			ID_WXSTATICTEXT2 = 1010,
			ID_WXSTATICTEXT1 = 1009,
			ID_WXEDIT1 = 1008,
			ID_WXRICHTEXTCTRL2 = 1005,
			ID_WXBUTTON2 = 1004,
			ID_WXEDIT3 = 1003,
			ID_WXBUTTON1 = 1001,
			ID_MNU_FILE_1001 = 1111,
			ID_MNU_ESCI_1003 = 1113,
			ID_MNU_OPZIONI_1004 = 1114,
			ID_MNU_AUDIO_1005 = 1115,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};
class MyGridCellRenderer : public wxGridCellStringRenderer
{
public:
	virtual void Draw(wxGrid& grid,
		wxGridCellAttr& attr,
		wxDC& dc,
		const wxRect& rect,
		int row, int col,
		bool isSelected);
};
#endif
