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
#include <malloc.h>
#include "utility.h"
FILE*config;
char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLingua[20];
char StringLoginServizio[20];
int  cmbelement=0;

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        printf("Errore nella risoluzione.\n");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}
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

	radbing = new wxRadioButton(this, ID_WXRADIOBUTTON2, _("Bing Translator"), wxPoint(32, 272), wxSize(161, 17), 0, wxDefaultValidator, _("radbing"));

	radgoogle = new wxRadioButton(this, ID_WXRADIOBUTTON1, _("Google Translator"), wxPoint(32, 240), wxSize(153, 17), 0, wxDefaultValidator, _("radgoogle"));

	lbltrad = new wxStaticText(this, ID_WXSTATICTEXT4, _("Seleziona il Traduttore:"), wxPoint(32, 192), wxDefaultSize, 0, _("lbltrad"));

	wxArrayString arrayStringFor_cmblingua;
	arrayStringFor_cmblingua.Add(_("Inglese"));
	arrayStringFor_cmblingua.Add(_("Italiano"));
	arrayStringFor_cmblingua.Add(_("Portoghese"));
	cmblingua = new wxComboBox(this, ID_WXCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblingua, 0, wxDefaultValidator, _("cmblingua"));

	lbllingua = new wxStaticText(this, ID_WXSTATICTEXT3, _("Seleziona una lingua:"), wxPoint(32, 136), wxDefaultSize, 0, _("lbllingua"));

	btnlogin = new wxButton(this, ID_WXBUTTON1, _("Login"), wxPoint(451, 332), wxSize(89, 25), 0, wxDefaultValidator, _("btnlogin"));

	txtnick = new wxTextCtrl(this, ID_WXEDIT2, _(""), wxPoint(248, 86), wxSize(121, 22), 0, wxDefaultValidator, _("txtnick"));

	lblnick = new wxStaticText(this, ID_WXSTATICTEXT2, _("Inserisci un nickname: "), wxPoint(30, 87), wxDefaultSize, 0, _("lblnick"));

	txtserver = new wxTextCtrl(this, ID_WXEDIT1, _("127.0.0.1"), wxPoint(249, 46), wxSize(121, 22), 0, wxDefaultValidator, _("txtserver"));

	lblserver = new wxStaticText(this, ID_WXSTATICTEXT1, _("Inserisci l'indirizzo del server: "), wxPoint(32, 45), wxDefaultSize, 0, _("lblserver"));

	SetTitle(_("Login"));
	SetIcon(wxNullIcon);
	SetSize(8,8,640,480);
	Center();
	
	////GUI Items Creation End
	
	
	if (config = fopen("..\\conf\\config.txt", "r"))
    {

        fscanf(config,"%s",&StringLoginServer);
        txtserver->SetValue(StringLoginServer);
        
        fscanf(config,"%s",&StringLoginNick);
        txtnick->SetValue(StringLoginNick);
        
        fscanf(config,"%d",&cmbelement);
        cmblingua->SetSelection(cmbelement);
        
        fscanf(config,"%s",&StringLoginLingua);
        cmblingua->SetValue(StringLoginLingua);
        
        fscanf(config,"%s",&StringLoginServizio);
        if(StringLoginServizio=="google")
        {
            radgoogle->SetValue(true);
            radbing->SetValue(false);
        }
        if(StringLoginServizio=="bing")
        {
            radgoogle->SetValue(false);
            radbing->SetValue(true);
        }
        
        fclose(config);
    }
    cmblingua->SetSelection(cmbelement);
	
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
	
    strncpy(StringLoginServer, (const char*)txtserver->GetValue().mb_str(wxConvUTF8), 20);
    strncpy(StringLoginNick, (const char*)txtnick->GetValue().mb_str(wxConvUTF8), 50);
    strncpy(StringLoginLingua, (const char*)cmblingua->GetStringSelection().mb_str(wxConvUTF8), 20);    
    
    char ip[100];
	hostname_to_ip(StringLoginServer , ip);
	
	
        config=fopen("..\\conf\\config.txt","w");
    	fprintf(config,"%s\n",ip);
    	fprintf(config,"%s\n",StringLoginNick);
    	fprintf(config,"%d\n",cmblingua->GetSelection());
    	fprintf(config,"%s\n",StringLoginLingua);
    	if(radgoogle->GetValue()==true) fprintf(config,"%s","google");
    	if(radbing->GetValue()==true)   fprintf(config,"%s","bing");
    	fflush(config);
    	fclose(config);
    
	ClientTsFrm* frame = new ClientTsFrm(NULL);
    frame->Show();
	this->Close();
}
