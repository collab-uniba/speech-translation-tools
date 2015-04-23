#include "Login.h"

 

char StringLoginServer[20];
char StringLoginNick[50];
char StringLoginLingua[20];
int  cmbelement = 0;

Labels labels; 
/*LanguageSetter Txto;
Txto.setCurrentLang("English"); //this declaration has no storage class or type specifier*/

// Session* session = Session::Instance();


BEGIN_EVENT_TABLE(Login, wxDialog)
	EVT_CLOSE(Login::OnClose)
	EVT_BUTTON(ID_WXBUTTON1, Login::btnloginClick)
	EVT_COMBOBOX(ID_WXCOMBOBOX1, Login::cmblingua_SelectionChange)
END_EVENT_TABLE()
//EVT_RADIOBUTTON(ID_GTRANSLATE, Login::Google_translate)


int hostname_to_ip(char * hostname, char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		// get the host info
		printf("Errore nella risoluzione.\n");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}

	return 1;
}



Login::Login(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style) : wxDialog(parent, id, title, position, size, style)
{
	try{
		session = Session::Instance();
	}
	catch (ErrorSession &e){
		wxMessageBox(e.what());
		wxMessageBox("Please, read the \"README\" attached  and add the keys in order to continue");
		Close(true);
	}

	const char* pr = session->getServerAddress();
	

	//config->setLanguage("English");

	this->nations = new NationList(); 
	try{
		this->nations->ReadFromFile(LOCALES_CODE_FILE);
	}
	catch (std::string &e)
	{
		wxMessageBox(e);
		wxMessageBox("This program will be closed.");
		this->Close(true);
	}

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->Centre(wxBOTH);
	this->SetSize(wxSize(600, 400));

	wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
	bSizer5->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap1 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(connect_xpm), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer5->Add(m_bitmap1, 0, wxALL, 5);

	bSizer2->Add(bSizer5, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);

	lblNameHost = new wxStaticText(this, wxID_ANY, wxT("Login"), wxDefaultPosition, wxSize(150, -1), 0);
	lblNameHost->Wrap(-1);
	bSizer3->Add(lblNameHost, 0, wxALIGN_CENTER | wxALL, 5);

	txtNameHost = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer3->Add(txtNameHost, 1, wxALL, 5);

	bSizer2->Add(bSizer3, 0, wxALIGN_CENTER | wxEXPAND, 5);

	wxBoxSizer* bSizer31  = new wxBoxSizer(wxHORIZONTAL);

	lblNickName = new wxStaticText(this, wxID_ANY, wxT("Nickname:"), wxDefaultPosition, wxSize(150, -1), 0);
	lblNickName->Wrap(-1);
	bSizer31->Add(lblNickName, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txtNickName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer31->Add(txtNickName, 1, wxALL, 5);


	bSizer2->Add(bSizer31, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer311  = new wxBoxSizer(wxHORIZONTAL);

	lblLanguage = new wxStaticText(this, wxID_ANY, labels.language, wxDefaultPosition, wxSize(150, -1), 0);
	lblLanguage->Wrap(-1);
	bSizer311->Add(lblLanguage, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	//cmbLingua = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	wxArrayString arrayStringFor_cmblingua;
	cmbLingua = new wxBitmapComboBox(this, ID_WXBITMAPCOMBOBOX1, _(""), wxPoint(248, 128), wxSize(145, 28), arrayStringFor_cmblingua, 0, wxDefaultValidator, _("cmblingua"));
	for (int i = 0; i < this->nations->GetSize(); i++)
	{
		char language[30];
		char nation[30];
		char path[50];
		bool loaded;

		strcpy(language, this->nations->GetList()->at(i).GetLanguage());
		strcpy(nation, this->nations->GetList()->at(i).GetNation());

		wxBitmap bitmap = wxBitmap();
		strcpy(path, "..\\res\\");
		strcat(path, nation);
		strcat(path, ".png");
		loaded = bitmap.LoadFile(path, wxBITMAP_TYPE_PNG);

		if (!loaded)
			bitmap.LoadFile("..\\res\\Default.png", wxBITMAP_TYPE_PNG);

		cmbLingua->Append(language, bitmap);
		//session->setLanguage(language);
		
	}
	
	bSizer311->Add(cmbLingua, 1, wxALL, 5);

	bSizer2->Add(bSizer311, 0, wxEXPAND, 5);

	bSizer2->Add(20, 20, 0, wxEXPAND, 5);

	lblService = new wxStaticText(this, wxID_ANY, labels.service, wxDefaultPosition, wxDefaultSize, 0);
	lblService->Wrap(-1);
	bSizer2->Add(lblService, 0, wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	radGoogle = new wxRadioButton(this, ID_GTRANSLATE, wxT("Google Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(radGoogle, 0, wxALL, 5);

	radBing = new wxRadioButton(this, wxID_ANY, wxT("Bing Translate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(radBing, 0, wxALL, 5);

	bSizer2->Add(bSizer7, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	bSizer6->Add(0, 0, 1, wxEXPAND, 5);

	cmdConfirm = new wxButton(this, wxID_ANY, labels.confirm, wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(cmdConfirm, 0, wxALL, 5);

	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);

	this->SetSizer(bSizer2);
	this->Layout();

	// Connect Events
	cmbLingua->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
	cmdConfirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::btnloginClick), NULL, this);

	ReadConfig();
	Login::SetLabel();
}

Login::~Login()
{
	// Disconnect Events
	free(this->nations);
	cmbLingua->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(Login::cmblingua_SelectionChange), NULL, this);
	cmdConfirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login::btnloginClick), NULL, this);
}

std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

void Login::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Login::ReadConfig()
{ 
	txtNameHost->SetValue(session->getServerAddress());
	txtNickName->SetValue(session->getNick());
	cmbLingua->SetSelection(session->getNumbLanguageSelected());
	if (!strcmp(session->getTranslationEngine(), "google"))
	{
		radGoogle->SetValue(true);
		radBing->SetValue(false);
	}else
	{
		radGoogle->SetValue(false);
		radBing->SetValue(true);
	}
	try
	{
		TranslateController::InitLanguageVariable((char*)session->getLanguage());
	}
	catch (exception& e)
	{
		wxMessageBox(e.what());
		wxMessageBox("This program will be closed.");
		this->Close(true);
	}
	
	cmbLingua->SetSelection(session->getNumbLanguageSelected());
}

void Login::cmblingua_SelectionChange(wxCommandEvent& event)
{
	char lang[20] = { "" };
	strcpy(lang, (char*)cmbLingua->GetStringSelection().mb_str().data());
	try
	{
		TranslateController::InitLanguageVariable(lang);
	}
	catch (ErrorLabels &e)
	{
		session->setLanguage("English(Uk)");
		session->setNumbLanguageSelected(20);
		TranslateController::InitLanguageVariable((char*)session->getLanguage());
		cmbLingua->SetSelection(session->getNumbLanguageSelected());
		wxMessageBox(e.what());
		wxMessageBox("setting up english by default");
	}

	
	Login::SetLabel();
}

void Login::SetLabel(){
	lblNameHost->SetLabel(labels.nameHostServer.append("/host server:").c_str());
	lblLanguage->SetLabel(labels.language.append(":").c_str());
	lblService->SetLabel(labels.service.append(":").c_str());
	cmdConfirm->SetLabel(labels.confirm.c_str());
}

void Login::btnloginClick(wxCommandEvent& event)
{
	if (!(txtNickName->GetValue().IsEmpty() || txtNickName->GetValue().IsEmpty())){
		LoginWarnings *warn = new LoginWarnings();
		strncpy(StringLoginServer, (const char*)txtNameHost->GetValue().mb_str(wxConvUTF8), 20);
		strncpy(StringLoginNick, (const char*)txtNickName->GetValue().mb_str(wxConvUTF8), 50);
		strncpy(StringLoginLingua, (const char*)cmbLingua->GetStringSelection().mb_str(wxConvUTF8), 20);

		char ip[20];
		hostname_to_ip(StringLoginServer, ip);

		session->setNumbLanguageSelected(cmbLingua->GetSelection());
		session->setNick(StringLoginNick);
		session->setLanguage(StringLoginLingua);
		session->setServerAddress(ip);
		if (radGoogle->GetValue()) session->setTranslationEngine("google");
		if (radBing->GetValue()) session->setTranslationEngine("bing");


		/*if (strncmp(StringLoginLingua, "English", 7) == 0)
		{
		strcpy(CURRENT_LANG, "English");
		wxMessageBox("Va bene " + wxString::FromUTF8(CURRENT_LANG));
		fprintf(config, "%s\n", CURRENT_LANG);
		}*/

		//else fprintf(config, "%s\n", StringLoginLingua);

		try{

			if (radGoogle->GetValue())
				Session::Instance()->getGoogleAPIKey();
			else
			{
				Session::Instance()->getBingID();
				Session::Instance()->getBingKey();
			}
					TranslateController::InitLanguageVariable((char*)session->getLanguage());
			ClientTsFrm * frame = new ClientTsFrm(warn, NULL);
			frame->Show();
			this->Close(true);
		}

		catch (ErrorSession &e){
			wxMessageBox(e.what());
			wxMessageBox("Please, read the \"README\" attached  and add the keys in order to continue");
			Close(true);
			//wxTheApp->OnExit();
			//wxTheApp->CleanUp();
		}
	}
	else{
		wxMessageBox("Please, fill name and host fields.");
	}
}

/*
void Login::Google_translate(wxCommandEvent& event){
	
	wxMessageDialog *d = new wxMessageDialog(NULL, wxT("Google Translate is a paid service and for that reason is not available"), wxT("Info"), wxOK);
	d->ShowModal();
		radGoogle->SetValue(false);
		radBing->SetValue(true);

}*/