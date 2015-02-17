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

#include "../Data/config.h"

#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/grid.h>
#include "NationList.h"
#include "LoginWarnings.h" 
#include "../ArchiveLog.h"

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"
#include "FrmMailSending.h"
#include "FrmSettingMail.h"
#include "AudioWizard.h"
#include <list>
#include "FrmSaveChat.h"

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802



class ClientTsFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		double conta;
		void askForSaving();
		void WxButton1Click(wxCommandEvent& event);
		void btnsendClick(wxCommandEvent& event);
		void txtchatClick(wxRichTextEvent& event);
		void txtchatEnter(wxCommandEvent& event);
		void OnTimerTimeout(wxTimerEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		void txtmsgEnter(wxCommandEvent& event);
		void RefreshChat();
		void btnspeechClick(wxCommandEvent& event);
		void ClientTsFrmActivate(wxActivateEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxTimer2Timer(wxTimerEvent& event);
		void gridchatCellLeftClick(wxGridEvent& event);
		void Debug(wxCommandEvent& event);
		void Wizard(wxCommandEvent& event);
		void WxBitmapButton1Click(wxCommandEvent& event);
		void Mail(wxCommandEvent& event);
		void SettingMail(wxCommandEvent& event);
		void Save(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);

	public:
		
		ClientTsFrm(LoginWarnings *warn,wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("TeamTranslate"),
					const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
					long style = wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxRESIZE_BORDER);

		virtual ~ClientTsFrm();

	private:	
	
		NationList *nations;
		int REFRESHTIMER = 0;
		uint64 _sclogID;
		wxTimer *WxTimer2;
		wxTimer *WxTimer1;
		wxButton *btnspeech;
		wxRichTextCtrl *txtclient;
		wxTextCtrl *txtlingua;
		wxStaticText *lbllingua;
		wxStaticText *lblnick;
		wxTextCtrl *txtnick;
		wxRichTextCtrl *txtchat;
		wxButton *btnsend;
		wxTextCtrl *txtmsg;
		wxGrid *gridchat;
		wxGrid *gridclient;
		wxBoxSizer *sizer;
		wxGridSizer *gridsizer;
		wxMenuBar *WxMenuBar1;
		wxMenu *ID_MNU_FILE_1001_Mnu_Obj;
		wxMenu *ID_MNU_OPZIONI_1004_Mnu_Obj;
		wxBitmapButton *WxBitmapButton1;

		enum
		{
			////GUI Enum Control ID Start
			ID_GRIDCLIENT=1034,
			ID_GRIDCHAT = 1033,
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
			ID_MNU_SAVE_1002 = 1118,
			ID_MNU_MAIL_1004 = 1117,
			ID_MNU_SETTINGMAIL_1007 = 1119,
			ID_MNU_ESCI_1003 = 1113,
			ID_MNU_OPZIONI_1004 = 1114,
			ID_MNU_AUDIO_1005 = 1115,
			ID_MNU_SPEECH_1006 = 1116,
			ID_WXBITMAPBUTTON1 = 1024,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		
};

class MyGridCellRenderer : public wxGridCellStringRenderer
{
private:
	wxBitmap* bitmap;
public:
	virtual void Draw(wxGrid& grid,
		wxGridCellAttr& attr,
		wxDC& dc,
		const wxRect& rect,
		int row, int col,
		bool isSelected);
		void setPicture(wxString);

		MyGridCellRenderer(wxString name)
		{
			if (name == "") bitmap = new wxBitmap(NULL);
			else bitmap = new wxBitmap(name, wxBITMAP_TYPE_BMP);
		}
};
#endif
