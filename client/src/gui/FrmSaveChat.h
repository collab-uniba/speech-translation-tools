#ifndef __FRMSAVECHAT_H__
#define __FRMSAVECHAT_H__

#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/panel.h>
#include "../../res/ico_save.xpm"
#include <time.h>
#include <wx/checkbox.h>
#include <wx/filepicker.h>
#include <stdio.h>
#include "..\translateController\translateVariable.h"
#include "..\GlobalVariables.h"

class FrmSaveChat : public wxDialog
{
private:
	void OnClose(wxCloseEvent& event);
	void saveChatCSV(const char* filename);
	void saveChatTXT(const char* filename);
	FILE*config;
	char destination[3000];

protected:
	wxStaticText* lblTitle;
	wxStaticBitmap* m_bitmap2;
	wxCheckBox* chkCSV;
	wxCheckBox* chkTXT;
	wxStaticText* lblSaveIn;
	wxDirPickerCtrl* fpkBrowse;
	wxButton* btnConfirm;

	// Virtual event handlers, overide them in your derived class
	void btnConfirmClick(wxCommandEvent& event);
	void checkBoxSelection(wxCommandEvent& event);

public:

	FrmSaveChat(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString &title = labels.saveMenu,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxCLOSE_BOX | wxRESIZE_BORDER);
	~FrmSaveChat();

};

#endif
