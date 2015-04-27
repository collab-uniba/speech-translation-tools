///-----------------------------------------------------------------
///
/// @file      ClientTsFrm.h
/// @author    Utente
/// Created:   07/10/2014 15:14:10
/// @section   DESCRIPTION
///            ClientTsFrm class declaration
///
///------------------------------------------------------------------

#pragma once

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/compiler.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif

#include "../lib/ClientTS.h"
#include "../data/Session.h"
#include "../data/Message.h"  
#include "../res/sendemail.xpm"

#include "FrmMailSending.h"
#include "FrmSettingMail.h"
#include "AudioWizard.h"
#include "NationList.h"
#include "LoginWarnings.h" 
#include "../ArchiveLog.h"

#include "FrmSaveChat.h"

#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>

#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include <wx/popupwin.h>

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"

#include <wx/tipwin.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>

#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/artprov.h>
#include <wx/clipbrd.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/wxhtml.h>
#include <wx/imaglist.h>
#include <wx/dataobj.h>
#include <wx/dcclient.h>
#include <wx/bmpbuttn.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/aui/framemanager.h>
#include <list>
//#include "../lib/Observer.h"

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802

/* ttListCtrl.h */
/* Ryan Day, http://www.ryanday.net/ */



class ttListCtrl : public wxListCtrl
{
private:
	Session *session;
	int cols, rows;

public:
	ttListCtrl() { 
	};
	ttListCtrl(wxWindow *parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT,
		const wxValidator& validator = wxDefaultValidator,
		const wxString &name = wxListCtrlNameStr)
	{
		//  Start with a 3x3 grid, and we can expand beyond that if necessary
		cols = rows = 3;
		session = Session::Instance();
		Create(parent, winid, pos, size, style, validator, name);
	}
	void OnMouseMotion(wxMouseEvent& event);
	void destroyTip(wxTimerEvent& event);
	/*void SetTooltip(int row, int col, MessagePTR tip);
	MessagePTR GetTooltip(int row, int col);*/
};


class ClientTsFrm : public wxFrame,
	private wxLog
{
protected:
	virtual void DoLogRecord(wxLogLevel level,
		const wxString& msg,
		const wxLogRecordInfo& info);
private:
	DECLARE_EVENT_TABLE();
	void askForSaving();
	ttListCtrl* CreateChatBox(wxPanel *panel);
	void WxButton1Click(wxCommandEvent& event);
	void btnsendClick(wxCommandEvent& event);
	void txtchatClick(wxRichTextEvent& event);
	void txtchatEnter(wxCommandEvent& event);
	void OnTimerTimeout(wxTimerEvent& event);
	void updateClientListTimer(wxTimerEvent& event);
	void txtmsgEnter(wxCommandEvent& event);
	void btnspeechClick(wxCommandEvent& event);
	void ClientTsFrmActivate(wxActivateEvent& event);
	void WxButton2Click(wxCommandEvent& event);
	void WxTimer2Timer(wxTimerEvent& event);
	void gridchatCellLeftClick(wxListEvent& event);
	void Debug(wxCommandEvent& event);
	void Wizard(wxCommandEvent& event);
	void WxBitmapButton1Click(wxCommandEvent& event);
	void Mail(wxCommandEvent& event);
	void SettingMail(wxCommandEvent& event);
	void Save(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void ToolBarSaveClickevent(wxCloseEvent &event);
	void OnUpdateUI(wxUpdateUIEvent& event)
	{
		//if (tb3->IsShown())
	}
	void OnPaneClose(wxAuiManagerEvent& evt);

	void clickMenuToolbarsPane(wxCommandEvent& event);

	// logging helper
	void DoLogLine(wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg);
public:

	ClientTsFrm(LoginWarnings *warn, wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("TeamTranslate"),
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxSYSTEM_MENU | wxCLOSE_BOX | wxRESIZE_BORDER);

	virtual ~ClientTsFrm(){};
	void updatePanelMsg(wxThreadEvent& event);

private:
	wxTextCtrl *m_txtctrl; //message variable for logging
	// old log target, we replace it with one using m_txtctrl during this
	// frame life time
	wxLog *m_oldLogger;
	wxAuiManager  m_mgr;
	//ttListCtrl* ListCtrlObject;
	unsigned int curRow;			//Initialize Row index
	Session* session;
	NationList *nations;
	wxImageList		*il;
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
	wxBoxSizer *sizer;
	wxGridSizer *gridsizer;
	wxMenuBar *WxMenuBar1;
	wxMenu *ID_MNU_FILE_1001_Mnu_Obj;
	wxMenu *ID_MNU_OPZIONI_1004_Mnu_Obj;
	wxMenu *ID_MNU_OPZIONI_VIEW;
	wxBitmapButton *WxBitmapButton1;
	std::unique_ptr<ClientTS> clientts;
	ttListCtrl* chatbox;//wxListCtrl* chatbox;
    COLORE *colors;
	wxAuiToolBar* tb1;
	wxAuiToolBarItem * m_toolbar1_save;
	wxAuiToolBarItem * m_toolbar1_email;
	wxAuiToolBar* tb2;
	wxAuiToolBarItem * m_toolbar2_sett;
	wxAuiToolBarItem * m_toolbar2_mic;
	wxAuiToolBar* tb3;
	enum
	{
		////GUI Enum Control ID Start
		ID_GRIDCLIENT = 1034,
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
		ID_MNU_VIEW = 1120,
		ID_WXBITMAPBUTTON1 = 1024,
		////GUI Enum Control ID End
		ID_DUMMY_VALUE_, //don't remove this value unless you have other enum values
		ID_MESSAGEIO,
		ID_tool_bar,
		ID_AllowFloating = 1150
	};
};


/*
class MyWorkerThread : public wxThread
{
public:
	MyWorkerThread(ClientTsFrm *frame);

	// thread execution starts here
	virtual void *Entry();

	// called when the thread exits - whether it terminates normally or is
	// stopped with Delete() (but not when it is Kill()ed!)
	virtual void OnExit();

public:
	ClientTsFrm *m_frame;
	unsigned m_count;
};
*/


class SimpleTransientPopup : public wxPopupTransientWindow
{
public:
	SimpleTransientPopup(wxWindow *parent, MessagePTR msg);
	virtual ~SimpleTransientPopup();

	// wxPopupTransientWindow virtual methods are all overridden to log them
	virtual void Popup(wxWindow *focus = NULL);
	virtual void OnDismiss();
	virtual bool ProcessLeftDown(wxMouseEvent& event);
	virtual bool Show(bool show = true);

private:
	wxScrolledWindow *m_panel;
	wxButton *m_button;
	wxSpinCtrl *m_spinCtrl;
	wxStaticText *m_mouseText;

private:
	void OnMouse(wxMouseEvent &event);
	void WxTimerClose(wxTimerEvent& event);
	/*void OnSize(wxSizeEvent &event);
	void OnSetFocus(wxFocusEvent &event);
	void OnKillFocus(wxFocusEvent &event);
	void OnButton(wxCommandEvent& event);
	void OnSpinCtrl(wxSpinEvent& event);*/
	/*
private:
	wxDECLARE_ABSTRACT_CLASS(SimpleTransientPopup);
*/
};	//wxDECLARE_EVENT_TABLE();


