///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FrmSettingMail.h"

#include "../../res/mail-settings-icon.xpm"
#include<stdio.h>


///////////////////////////////////////////////////////////////////////////

MyPanel2::MyPanel2(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	CenterOnScreen();
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bitmap2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(mailsettingico), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer9->Add( m_bitmap2, 0, wxALL, 5 );
	
	
	bSizer8->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	frmOptionsMail_lblServer = new wxStaticText(this, wxID_ANY, labels.serverName.append(":"), wxDefaultPosition, wxSize(80, -1), 0);
	frmOptionsMail_lblServer->Wrap( -1 );
	bSizer10->Add( frmOptionsMail_lblServer, 0, wxALIGN_CENTER|wxALL, 5 );
	
	frmOptionsMail_txtServerName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( frmOptionsMail_txtServerName, 1, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer8->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxHORIZONTAL );
	
	frmOptionsMail_lblPort = new wxStaticText(this, wxID_ANY, labels.serverPort.append(":"), wxDefaultPosition, wxSize(80, -1), 0);
	frmOptionsMail_lblPort->Wrap( -1 );
	bSizer101->Add( frmOptionsMail_lblPort, 0, wxALIGN_CENTER|wxALL, 5 );
	
	frmOptionsMail_txtPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE );
	bSizer101->Add( frmOptionsMail_txtPort, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer8->Add( bSizer101, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1011;
	bSizer1011 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer25->Add( 20, 0, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	frmOptionsMail_lblusername = new wxStaticText( this, wxID_ANY, wxT("Username:"), wxDefaultPosition, wxSize( 60,-1 ), 0 );
	frmOptionsMail_lblusername->Wrap( -1 );
	bSizer18->Add( frmOptionsMail_lblusername, 0, wxALL, 5 );
	
	frmOptionsMail_txtusername = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), 0 );
	bSizer18->Add( frmOptionsMail_txtusername, 0, wxALL, 5 );
	
	
	bSizer26->Add( bSizer18, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer181;
	bSizer181 = new wxBoxSizer( wxHORIZONTAL );
	
	frmOptionsMail_lblPassword = new wxStaticText( this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxSize( 60,-1 ), 0 );
	frmOptionsMail_lblPassword->Wrap( -1 );
	bSizer181->Add( frmOptionsMail_lblPassword, 0, wxALL, 5 );
	
	frmOptionsMail_txtPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_PASSWORD );
	bSizer181->Add( frmOptionsMail_txtPassword, 0, wxALL, 5 );
	
	
	bSizer26->Add( bSizer181, 1, wxEXPAND, 5 );
	
	
	bSizer25->Add( bSizer26, 1, wxEXPAND, 5 );
	
	
	bSizer1011->Add( bSizer25, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer1011, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );
	
	frmOptionsMail_lblSecureConnection = new wxStaticText(this, wxID_ANY, labels.messageSecure.append(":"), wxDefaultPosition, wxDefaultSize, 0);
	frmOptionsMail_lblSecureConnection->Wrap( -1 );
	bSizer27->Add( frmOptionsMail_lblSecureConnection, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	frmOptionsMail_optNO = new wxRadioButton(this, wxID_ANY, labels.noSecure, wxDefaultPosition, wxDefaultSize, 0);
	frmOptionsMail_optNO->SetValue( false ); 
	bSizer28->Add( frmOptionsMail_optNO, 0, wxALL, 5 );
	
	frmOptionsMail_optSSL = new wxRadioButton( this, wxID_ANY, wxT("SSL"), wxDefaultPosition, wxDefaultSize, 0 );
	frmOptionsMail_optSSL->SetValue(false);
	bSizer28->Add( frmOptionsMail_optSSL, 0, wxALL, 5 );
	
	
	bSizer27->Add( bSizer28, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer27, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	frmOptionsMail_cmdOK = new wxButton(this, wxID_ANY, labels.confirm, wxDefaultPosition, wxDefaultSize, 0);
	bSizer14->Add( frmOptionsMail_cmdOK, 0, wxALL, 5 );
	
	frmOptionsMail_cmdCancel = new wxButton( this, wxID_ANY, labels.btnCancel, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( frmOptionsMail_cmdCancel, 0, wxALL, 5 );
	
	
	bSizer8->Add( bSizer14, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	// Connect Events
	frmOptionsMail_cmdOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyPanel2::cmdOKClick ), NULL, this );
	frmOptionsMail_cmdCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyPanel2::cmdCancelClick ), NULL, this );

	struct serverdata
	{
		char smtpservertxt[100];
		char serverporttxt[6];
		char username[100];
		char password[100];
		char protocol[100];
	} serversettings;

	FILE *config;
	if ((config=fopen("..\\bin\\conf\\email.txt", "r")) != NULL){
		fscanf(config, "%s", &serversettings.smtpservertxt);
		fscanf(config, "%s", &serversettings.serverporttxt);
		fscanf(config, "%s", &serversettings.username);
		fscanf(config, "%s", &serversettings.password);
		fscanf(config, "%s", &serversettings.protocol);
		if (strcmp(serversettings.protocol, "true") == 0){ frmOptionsMail_optSSL->SetValue(true); 	frmOptionsMail_optNO->SetValue(false); }
		else{ frmOptionsMail_optSSL->SetValue(false); 	frmOptionsMail_optNO->SetValue(true); }
		frmOptionsMail_txtServerName->SetValue(serversettings.smtpservertxt);
		frmOptionsMail_txtPort->SetValue(serversettings.serverporttxt);
		frmOptionsMail_txtusername->SetValue(serversettings.username);
		frmOptionsMail_txtPassword->SetValue(serversettings.password);
		fclose(config);
	}
	else{
		frmOptionsMail_optSSL->SetValue(false);
		frmOptionsMail_optNO->SetValue(true);
		frmOptionsMail_txtServerName->SetValue("");
		frmOptionsMail_txtPort->SetValue("");
		frmOptionsMail_txtusername->SetValue("");
		frmOptionsMail_txtPassword->SetValue("");
		
	}
	
	

}

MyPanel2::~MyPanel2()
{
	// Disconnect Events
	frmOptionsMail_cmdOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyPanel2::cmdOKClick ), NULL, this );
	frmOptionsMail_cmdCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyPanel2::cmdCancelClick ), NULL, this );
	
}

void MyPanel2::chkUserPsw_Check(wxCommandEvent& event){

}

void MyPanel2::cmdOKClick(wxCommandEvent& event){
	struct serverdata
	{
		char smtpservertxt[100];
		char serverporttxt[6];
		char username[100];
		char password[100];
		char protocol[100];
	} serversettings;
	if (frmOptionsMail_optSSL->GetValue() == true) strcpy(serversettings.protocol, "true");
	else strcpy(serversettings.protocol, "false");
	
	strcpy(serversettings.smtpservertxt, (const char*)frmOptionsMail_txtServerName->GetValue().mb_str(wxConvUTF8));
	strcpy(serversettings.serverporttxt, (const char*)frmOptionsMail_txtPort->GetValue().mb_str(wxConvUTF8));
	strcpy(serversettings.username, (const char*)frmOptionsMail_txtusername->GetValue().mb_str(wxConvUTF8));
	strcpy(serversettings.password, (const char*)frmOptionsMail_txtPassword->GetValue().mb_str(wxConvUTF8));
	strcat(serversettings.smtpservertxt,"\0");
	strcat(serversettings.serverporttxt, "\0");
	strcat(serversettings.username, "\0");
	strcat(serversettings.password, "\0");
	strcat(serversettings.protocol, "\0");
	FILE *config = fopen("..\\bin\\conf\\email.txt", "w");
	fprintf(config, "%s\n", serversettings.smtpservertxt);
	fprintf(config, "%s\n", serversettings.serverporttxt);
	fprintf(config, "%s\n", serversettings.username);
	fprintf(config, "%s\n", serversettings.password);
	fprintf(config, "%s", serversettings.protocol);
	fclose(config);
	this->Close();
	wxMessageBox(labels.messageEmailSetting);


}
void MyPanel2::cmdCancelClick(wxCommandEvent& event){
	this->Close();
}
