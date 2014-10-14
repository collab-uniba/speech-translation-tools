//---------------------------------------------------------------------------
//
// Name:        ClientTsApp.h
// Author:      Utente
// Created:     07/10/2014 15:14:10
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __CLIENTTSFRMApp_h__
#define __CLIENTTSFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class ClientTsFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
