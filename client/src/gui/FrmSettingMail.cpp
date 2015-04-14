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

FrmSettingMail::FrmSettingMail(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	CenterOnScreen();
	session = Session::Instance();
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
	bSizer181->Add(frmOptionsMail_txtPassword, 0, wxALL, 5);
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
	frmOptionsMail_cmdOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSettingMail::cmdOKClick ), NULL, this );
	frmOptionsMail_cmdCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSettingMail::cmdCancelClick ), NULL, this );

	//getting values from config file
	frmOptionsMail_optSSL->SetValue(session->getprotocol()); 
	frmOptionsMail_optNO->SetValue(!session->getprotocol());
	frmOptionsMail_txtServerName->SetValue(session->getsmtpservertxt());
	frmOptionsMail_txtPort->SetValue(session->getserverporttxt());
	frmOptionsMail_txtusername->SetValue(session->getusername());
	frmOptionsMail_txtPassword->SetValue(session->getpassword());
}

FrmSettingMail::~FrmSettingMail()
{
	// Disconnect Events
	frmOptionsMail_cmdOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSettingMail::cmdOKClick ), NULL, this );
	frmOptionsMail_cmdCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrmSettingMail::cmdCancelClick ), NULL, this );
}

void FrmSettingMail::chkUserPsw_Check(wxCommandEvent& event){

}

void FrmSettingMail::cmdOKClick(wxCommandEvent& event){

	//saving config
	session->setprotocol((const char*)frmOptionsMail_optSSL->GetValue());
	session->setsmtpservertxt((const char*)frmOptionsMail_txtServerName->GetValue().mb_str(wxConvUTF8));
	session->setserverporttxt((const char*)frmOptionsMail_txtPort->GetValue().mb_str(wxConvUTF8));
	session->setusername((const char*)frmOptionsMail_txtusername->GetValue().mb_str(wxConvUTF8));
	session->setpassword((const char*)frmOptionsMail_txtPassword->GetValue().mb_str(wxConvUTF8));

	wxMessageBox(labels.messageEmailSetting);

	this->Close();
}
void FrmSettingMail::cmdCancelClick(wxCommandEvent& event){
	this->Close();
}
