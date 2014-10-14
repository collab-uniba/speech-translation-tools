///-----------------------------------------------------------------
///
/// @file      Login.cpp
/// @author    Utente
/// Created:   08/10/2014 16:43:03
/// @section   DESCRIPTION
///            Login class implementation
///
///------------------------------------------------------------------

#include "Login.h"
#include "ClientTsFrm.h"
#include "utility.h"

FILE*config=fopen("config.txt","w");
//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Login
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Login,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(Login::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,Login::btnloginClick)
END_EVENT_TABLE()
////Event Table End

Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Login::~Login()
{
} 

void Login::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxArrayString arrayStringFor_cmblingua;
	arrayStringFor_cmblingua.Add(_("Inglese"));
	arrayStringFor_cmblingua.Add(_("Italiano"));
	arrayStringFor_cmblingua.Add(_("Portoghese"));
	cmblingua = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblingua, 0, wxDefaultValidator, _("cmblingua"));

	lbllingua = new wxStaticText(this, ID_WXSTATICTEXT1, _("Seleziona un linguaggio:"), wxPoint(32, 136), wxDefaultSize, 0, _("lbllingua"));

	btnlogin = new wxButton(this, ID_WXBUTTON1, _("Login"), wxPoint(347, 212), wxSize(89, 25), 0, wxDefaultValidator, _("btnlogin"));

	txtnick = new wxTextCtrl(this, ID_WXEDIT1, _(""), wxPoint(248, 86), wxSize(121, 22), 0, wxDefaultValidator, _("txtnick"));

	lblnick = new wxStaticText(this, ID_WXSTATICTEXT1, _("Inserisci un nickname: "), wxPoint(30, 87), wxDefaultSize, 0, _("lblnick"));

	txtserver = new wxTextCtrl(this, ID_WXEDIT1, _("neo.di.uniba.it"), wxPoint(249, 46), wxSize(121, 22), 0, wxDefaultValidator, _("txtserver"));

	lblserver = new wxStaticText(this, ID_WXSTATICTEXT1, _("Inserisci l'indirizzo del server: "), wxPoint(32, 45), wxDefaultSize, 0, _("lblserver"));

	SetTitle(_("Login"));
	SetIcon(wxNullIcon);
	SetSize(8,8,640,480);
	Center();
	
	////GUI Items Creation End
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

/*
 * btnloginClick
 */
void Login::btnloginClick(wxCommandEvent& event)
{
	// insert your code here
	//wxMessageBox(ip);
	char server[20];
	char nick[50];
	char lingua[20];
	
    strncpy(server, (const char*)txtserver->GetValue().mb_str(wxConvUTF8), 20);
    strncpy(nick, (const char*)txtnick->GetValue().mb_str(wxConvUTF8), 50);
    strncpy(lingua, (const char*)cmblingua->GetStringSelection().mb_str(wxConvUTF8), 20);    
    
    char ip[100];
	hostname_to_ip(server , ip);
	
	fprintf(config,"%s\n",ip);
	fprintf(config,"%s\n",nick);
	fprintf(config,"%s",lingua);
	fflush(config);
	fclose(config);
	ClientTsFrm* frame = new ClientTsFrm(NULL);
    frame->Show();
	this->Close();
}
