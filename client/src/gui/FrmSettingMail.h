///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FRMSETTINGMAIL_H__
#define __FRMSETTINGMAIL_H__

#include <wx/artprov.h>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include "../translateController/translateVariable.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyPanel2
///////////////////////////////////////////////////////////////////////////////
class FrmSettingMail : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap2;
		wxStaticText* frmOptionsMail_lblServer;
		wxTextCtrl* frmOptionsMail_txtServerName;
		wxStaticText* frmOptionsMail_lblPort;
		wxTextCtrl* frmOptionsMail_txtPort;
		wxCheckBox* frmOptionsMail_chkUserPassword;
		wxStaticText* frmOptionsMail_lblusername;
		wxTextCtrl* frmOptionsMail_txtusername;
		wxStaticText* frmOptionsMail_lblPassword;
		wxTextCtrl* frmOptionsMail_txtPassword;
		wxStaticText* frmOptionsMail_lblSecureConnection;
		wxRadioButton* frmOptionsMail_optNO;
		wxRadioButton* frmOptionsMail_optTLSAv;
		wxRadioButton* frmOptionsMail_TLS;
		wxRadioButton* frmOptionsMail_optSSL;
		wxButton* frmOptionsMail_cmdOK;
		wxButton* frmOptionsMail_cmdCancel;
		
		
		void chkUserPsw_Check(wxCommandEvent& event);
		void cmdOKClick(wxCommandEvent& event);
		void cmdCancelClick(wxCommandEvent& event);
	
	public:
		
		FrmSettingMail(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxString("Dialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 400), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
		~FrmSettingMail();
	
};

#endif //__FRMSETTINGMAIL_H__
