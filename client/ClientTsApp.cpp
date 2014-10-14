//---------------------------------------------------------------------------
//
// Name:        ClientTsApp.cpp
// Author:      Utente
// Created:     07/10/2014 15:14:10
// Description: 
//
//---------------------------------------------------------------------------

#include "ClientTsApp.h"
#include "ClientTsFrm.h"
#include "Login.h"

IMPLEMENT_APP(ClientTsFrmApp)

bool ClientTsFrmApp::OnInit()
{
    //ClientTsFrm* frame = new ClientTsFrm(NULL);
    Login * dialog= new Login(NULL);
    SetTopWindow(dialog);
    //frame->Show();
    dialog->Show();
    return true;
}
 
int ClientTsFrmApp::OnExit()
{
	return 0;
}
