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

#include <wx/radiobut.h>
#include <wx/combobox.h>
#include <wx/bmpcbox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>

#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <stdio.h>

#include "../translateController/translateController.h"
#include "../GlobalVariables.h"
#include "../translateController/translateVariable.h"
#include "../res/connect.xpm"
#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include "NationList.h"

#include "../data/Session.h"
#include "ClientTsFrm.h"
#include "AudioWizard.h"
#include "NationList.h"

#include "../data/Session.h"

using namespace std;


class Login : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
	public:
		Login(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Login"), 
			const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
			long style = wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER);
		virtual ~Login();

		void btnloginClick(wxCommandEvent& event);
		void txtserverUpdated(wxCommandEvent& event);
		void cmblingua_SelectionChange(wxCommandEvent& event);
		void SetLabel();
	
	private:
		Session* session;
		NationList *nations;
		wxStaticBitmap* m_bitmap1;
		wxStaticText* lblNameHost;
		wxTextCtrl* txtNameHost;
		wxStaticText* lblNickName;
		wxTextCtrl* txtNickName;
		wxStaticText* lblLanguage;
		wxBitmapComboBox* cmbLingua;
		wxStaticText* lblService;
		wxRadioButton* radGoogle;
		wxRadioButton* radBing;
		wxButton* cmdConfirm;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBITMAPCOMBOBOX1 = 1012,
			ID_WXRADIOBUTTON2 = 1011,
			ID_WXRADIOBUTTON1 = 1009,
			ID_WXSTATICTEXT4 = 1008,
			ID_WXCOMBOBOX1 = 1007,
			ID_WXSTATICTEXT3 = 1006,
			ID_WXBUTTON1 = 1005,
			ID_WXEDIT2 = 1004,
			ID_WXSTATICTEXT2 = 1003,
			ID_WXEDIT1 = 1002,
			ID_WXSTATICTEXT1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ ,//don't remove this value unless you have other enum values
			ID_GTRANSLATE = 1220
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void ReadConfig();
		void Google_translate(wxCommandEvent& event);
};
 