#pragma once

#include <wx/wx.h>
#include <wx/artprov.h>
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
#include <wx/button.h>
#include <wx/filepicker.h>
#include <wx/dialog.h>
#include <stdio.h>


#include <ck/CkMailMan.h>
#include <ck/CkEmail.h>
#include "../tinyxml2.h"
#include "../../res/sendemail.xpm"

#include "../data/Session.h"
#include "../translateController/translateVariable.h"

using namespace std;

class FrmMailSending : public wxDialog
{

private:
	Session *session;
	void btnSendMailClick(wxCommandEvent& event);
	void btnCancelMailClick(wxCommandEvent& event);
	bool sendMail(char* subject, char* body, char* to, char*attachment, char* attachment2);
	void readXmlLangDoc(char* filename);

protected:
	wxStaticBitmap* m_bitmap1;
	
	wxStaticText* lblTo;
	wxTextCtrl* txtTo;
	wxStaticText* lblSubject;
	wxTextCtrl* txtSubject;
	wxStaticText* lblText;
	wxTextCtrl* txtText;
	wxFilePickerCtrl* filePicker;
	wxFilePickerCtrl* filePicker2;
	wxStaticText* lblAttachment;
	wxStaticText* lblAttachment2;
	wxButton* btnCancel;
	wxButton* btnSend;

public:
	FrmMailSending(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = labels.mailMenu, 
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 400),
		long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

	~FrmMailSending();

};

