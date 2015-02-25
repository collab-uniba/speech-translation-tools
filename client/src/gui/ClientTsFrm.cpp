#include "ClientTsFrm.h"

ClientTS clientts;
BEGIN_EVENT_TABLE(ClientTsFrm, wxFrame)

	EVT_CLOSE(ClientTsFrm::OnClose)
	EVT_TIMER(ID_WXTIMER2, ClientTsFrm::WxTimer2Timer)
	EVT_TIMER(ID_WXTIMER1, ClientTsFrm::WxTimer1Timer)
	EVT_BUTTON(ID_WXBITMAPBUTTON1, ClientTsFrm::WxBitmapButton1Click)
	EVT_BUTTON(ID_WXBUTTON2, ClientTsFrm::btnsendClick)
	EVT_TEXT_ENTER(ID_WXEDIT3, ClientTsFrm::txtmsgEnter)
	EVT_BUTTON(ID_WXBUTTON1, ClientTsFrm::WxButton1Click)
	EVT_MENU(ID_MNU_MAIL_1004, ClientTsFrm::Mail)
	EVT_MENU(ID_MNU_SETTINGMAIL_1007, ClientTsFrm::SettingMail)
	EVT_MENU(ID_MNU_SAVE_1002, ClientTsFrm::Save)
	EVT_MENU(ID_MNU_ESCI_1003, ClientTsFrm::Debug)
	EVT_MENU(ID_MNU_AUDIO_1005, ClientTsFrm::Wizard)
	EVT_MENU(ID_MNU_SPEECH_1006, ClientTsFrm::btnspeechClick)
	EVT_GRID_CELL_LEFT_CLICK(ClientTsFrm::gridchatCellLeftClick)

END_EVENT_TABLE()
ClientTsFrm::ClientTsFrm(LoginWarnings*warnings,wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	this->nations = new NationList();
	//registerObserver<ClientTsFrm>(&ClientTsFrm::notify, *this);
	this->nations->ReadFromFile("..\\conf\\locales_code.txt");
	session = Session::Instance();
	config = session->getConfig();
	//clientts = new ClientTS;
	//session->registerObserver<ClientTsFrm>(*this);
	//session->registerObserver<int>(6);

	//registercb(*this); // register itself into clientTs "class" in order to be notified about any change
	  curRow = 0;			//Initialize Row index
	 curCol = 0;
	
	if (warnings->IsHostnameEmpty())
		ts3client_logMessage("Hostname field is empty", LogLevel_WARNING, "Gui", _sclogID);
	if (warnings->IsNicknameEmpty())
		ts3client_logMessage("Nickname field is empty", LogLevel_WARNING, "Gui", _sclogID);
	//TODO Completare la traduzione di ClientTsFrm usando le variabile statica labels
	clientts->setFlagSave(true);

	FILE * record;
	FILE * translate;
	if (record = fopen("recorded.wav", "r"))
	{
		remove("");
		fclose(record);
	}
	if (translate = fopen("translate.txt", "r"))
	{
		remove("");
		fclose(translate);
	}
	gridchat = new wxGrid(this, ID_GRIDCHAT, wxPoint(211, 72), wxSize(722, 350));

	gridchat->CreateGrid(0, 2, wxGrid::wxGridSelectCells);

	gridchat->SetColLabelValue(0, wxString::FromUTF8(labels.gridMessage.c_str()));
	gridchat->SetColLabelValue(1, "Play");

	gridchat->SetRowSize(curRow + 1, 40);
	gridchat->SetColSize(curCol, 610);
	gridchat->SetColSize(curCol + 1, 30);

	WxTimer2 = new wxTimer();
	WxTimer2->SetOwner(this, ID_WXTIMER2);
	WxTimer2->Start(1000);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(100);


	txtclient = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _(""), wxPoint(10, 75), wxSize(184, 155), wxRE_READONLY, wxDefaultValidator, _("txtclient"));
	txtclient->SetMaxLength(0);
	txtclient->SetFocus();
	txtclient->SetInsertionPointEnd();
	txtclient->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	/*txtlingua shows the language chosen*/
	txtlingua = new wxTextCtrl(this, ID_WXEDIT2, _(""), wxPoint(367, 20), wxSize(103, 20), wxTE_READONLY, wxDefaultValidator, _("txtlingua"));
	txtlingua->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	lbllingua = new wxStaticText(this, ID_WXSTATICTEXT2, _(wxString::FromUTF8(labels.language.append(":").c_str())), wxPoint(299, 20), wxDefaultSize, 0, _("lbllingua"));
	lbllingua->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	lblnick = new wxStaticText(this, ID_WXSTATICTEXT1, _("Nickname:"), wxPoint(14, 20), wxDefaultSize, 0, _("lblnick"));
	lblnick->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	/*txtnick shows the name chosen*/
	txtnick = new wxTextCtrl(this, ID_WXEDIT1, _(""), wxPoint(91, 20), wxSize(102, 20), wxTE_READONLY, wxDefaultValidator, _("txtnick"));
	txtnick->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	/* btnsend: botton which sends the message typed */
	btnsend = new wxButton(this, ID_WXBUTTON2, _(wxString::FromUTF8(labels.send.c_str())), wxPoint(830, 450), wxSize(103, 48), 0, wxDefaultValidator, _("btnsend"));
	btnsend->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	/* Txtmsg: box where you can type a message*/
	txtmsg = new wxTextCtrl(this, ID_WXEDIT3, _(""), wxPoint(211, 450), wxSize(570, 45), wxTE_PROCESS_ENTER, wxDefaultValidator, _("txtmsg"));
	txtmsg->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));
	txtmsg->SetFocus();

	wxBitmap WxBitmapButton1_BITMAP(NULL);
	WxBitmapButton1 = new wxBitmapButton(this, ID_WXBITMAPBUTTON1, WxBitmapButton1_BITMAP, wxPoint(211 + 570, 450), wxSize(50, 45), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButton1"));
	string enableSTTService = "";
	enableSTTService.append(labels.enable);
	enableSTTService.append(" SpeechToText Service");
	WxBitmapButton1->SetToolTip(_(enableSTTService));

	WxMenuBar1 = new wxMenuBar();
	ID_MNU_FILE_1001_Mnu_Obj = new wxMenu();
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_SAVE_1002, labels.saveMenu, _(""), wxITEM_NORMAL);
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_MAIL_1004,labels.mailMenu, _(""), wxITEM_NORMAL);
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_ESCI_1003,labels.exitMenu, _(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1001_Mnu_Obj, _("File"));

	ID_MNU_OPZIONI_1004_Mnu_Obj = new wxMenu();
	ID_MNU_OPZIONI_1004_Mnu_Obj->Append(ID_MNU_SETTINGMAIL_1007, labels.emailSetting, _(""), wxITEM_NORMAL);
	ID_MNU_OPZIONI_1004_Mnu_Obj->Append(ID_MNU_AUDIO_1005, labels.audioMenu, _(""), wxITEM_NORMAL);

	ID_MNU_OPZIONI_1004_Mnu_Obj->AppendCheckItem(ID_MNU_SPEECH_1006, _(enableSTTService), _(""));
	WxMenuBar1->Append(ID_MNU_OPZIONI_1004_Mnu_Obj, labels.options);
	SetMenuBar(WxMenuBar1);

	SetTitle(_("TeamTranslate"));
	SetIcon(wxNullIcon);
	SetSize(8, 8, 1024, 600);
	Center();
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif

#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif

#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	////GUI Items Creation End

	conta = 10.0;
	FILE *api;
	/*FILE*config;
	
	if (config = fopen("..\\bin\\conf\\config.txt", "r"))
	{
		fscanf(config, "%s", &SERVER_ADDRESS);
		fscanf(config, "%s", &NICK);
		fscanf(config, "%d", &cmbel);
		fscanf(config, "%s", &CURRENT_LANG);
		fscanf(config, "%s", &SERVICE);
		fclose(config);
	}
	
	if (api = fopen("..\\bin\\conf\\GOOGLE.txt", "r"))
	{
		char API[200];
		fscanf(api, "%s", API);
		session->setGoogleAPIKey(API);
		fclose(api);
	}
	*/
	txtnick->AppendText(config->getNick());
	txtlingua->AppendText(config->getLanguage());
	HANDLE myHandle = CreateThread(0, 0, ClientStart, NULL, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, TTS_THREAD, NULL, 0, &myThreadID2);
	HANDLE myHandle3 = CreateThread(0, 0, STT_THREAD, NULL, 0, &myThreadID4);
	HANDLE myHandle4 = CreateThread(0, 0, CTRL_STT, NULL, 0, &myThreadID4);
	clientts->SetupColor();
	engine = irrklang::createIrrKlangDevice();
	recorder = irrklang::createIrrKlangAudioRecorder(engine);
	gridptr = gridchat;
	/*char *str = this->nations->Search(CURRENT_LANG, APICODE);
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wString, 4096);
	MessageBox(NULL, wString, L"Test print handler", MB_OK);*/
}

ClientTsFrm::~ClientTsFrm()
{
}

void MyGridCellRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected)
{
	wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, isSelected);

	dc.DrawBitmap(*bitmap, 0, 0, 0);
	dc.DrawBitmap(*bitmap, rect.x + 6, rect.y + 4);
}

void MyGridCellRenderer::setPicture(wxString name)
{
	return;
}

void ClientTsFrm::gridchatCellLeftClick(wxGridEvent& event)
{
	list<MESSAGE>::iterator iter;
	iter = diary.begin();
	for (int i = 0; i < event.GetRow(); i++) iter++; //point to the selected message in the grid

	wxToolTip * tooltip = new wxToolTip((*iter).msgold);
	tooltip->SetAutoPop(10000);
	tooltip->SetMaxWidth(200);
	strSpeak = wxString::FromAscii(strtok((char*)gridchat->GetCellValue(event.GetRow(), 0).mb_str().data(), ")"));
	strSpeak = wxString::FromAscii(strtok(NULL, ":"));
	if (event.GetCol() == 1) { tts_flag = true; }
	if (event.GetCol() == 0) { gridchat->GetGridWindow()->SetToolTip(tooltip); }

}

void ClientTsFrm::OnClose(wxCloseEvent& event)
{
	askForSaving();
	flag = 1;
	Sleep(300);
	Destroy();
}

/*Refresh chat for new message or new clients*/
void ClientTsFrm::RefreshChat()
{
	int i=0;
	UserListPTR luser = Session::Instance()->getListUser(); 

	wxUniChar ch = ':';
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);
	clientts->showClients(DEFAULT_VIRTUAL_SERVER);
	txtclient->Clear();	//Clear client window
	for (auto it = luser->cbegin(); it != luser->cend(); ++it)
	{
		UserPTR uptr = *it;
		if (uptr->getName() != "") //if there is a client name
		{
			if (uptr->getSpeak() == 0 && uptr->getWrite() == 0) //gridclient->SetCellRenderer(i, 2, new MyGridCellRenderer(L""));
				txtclient->BeginTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue));
			if (uptr->getSpeak() == 1)	//if this client is speaking show microphone 
			{
				wxString naz = this->nations->Search(uptr->getLang().ToStdString(), COUNTRY);
				wxBitmap bitmap = wxBitmap();
				bitmap.LoadFile("..\\res\\" + naz + ".png", wxBITMAP_TYPE_PNG);
				txtclient->WriteImage(bitmap);

				txtclient->WriteText(uptr->getName() + "\t");
				//if (person[i].lang == "Italian") { 
					//txtclient->WriteImage(wxBitmap(italy_xpm));
				//}

				//if (strncmp(person[i].lang,"English",7)==0)  { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/usa.bmp"));*/ txtclient->WriteImage(wxBitmap(usa_xpm)); }
				//if (person[i].lang == "Portuguese") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/brasil.bmp"));*/ txtclient->WriteImage(wxBitmap(brasil_xpm)); }
				txtclient->WriteText("\t");
				txtclient->WriteImage(wxBitmap(microphone_xpm));
			}
			else if (uptr->getSpeak() == 0)	//if this client is writing show keayboard
			{ 
				wxString naz = this->nations->Search(uptr->getLang().ToStdString(), COUNTRY);
				wxBitmap bitmap = wxBitmap();
				bitmap.LoadFile("..\\res\\" + naz + ".png", wxBITMAP_TYPE_PNG);
				txtclient->WriteImage(bitmap);
				/*gridclient->SetCellTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue), i, 0);
				gridclient->SetCellValue(i, 0, person[i].name);*/
				txtclient->WriteText(uptr->getName() + "\t");
				//if (person[i].lang == "Italian") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/.bmp"));*/ txtclient->WriteImage(wxBitmap(italy_xpm)); }
				//if (strncmp(person[i].lang, "English", 7) == 0) { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/usa.bmp")); */txtclient->WriteImage(wxBitmap(usa_xpm)); }
				//if (person[i].lang == "Portuguese") { /*gridclient->SetCellRenderer(i, 1, new MyGridCellRenderer(L"../res/brasil.bmp"));*/ txtclient->WriteImage(wxBitmap(brasil_xpm)); }
				if (uptr->getWrite() == 1)
				{
					txtclient->WriteText("\t");
					txtclient->WriteImage(wxBitmap(keyboard_xpm));
					//gridclient->SetCellRenderer(i, 2, new MyGridCellRenderer(L"../res/keyboard.bmp"));
				}


			}
			txtclient->EndTextColour();
			txtclient->Newline();
			i++;
		}
	}


}

/*
 * WxButton1Click
 */
void ClientTsFrm::WxButton1Click(wxCommandEvent& event)
{

}

/*
 * btnsendClick
 */
void ClientTsFrm::btnsendClick(wxCommandEvent& event)
{
	char str[1024] = { "" };
	strcpy(str, (const char*)txtmsg->GetValue().mb_str());
	wxString parsata = txtmsg->GetValue().ToUTF8(); //convert write message into UTF8
	if (parsata == "") return;	//if the message is empty exit
	txtmsg->DiscardEdits();		//Clear buffer of textbox
	write_flag = false;

	ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, "\n" + wxString::FromAscii(config->getLanguage()) + "\n" + parsata, (uint64)1, NULL);

	wxString scrive_msg = "\n" + wxString::FromAscii(config->getLanguage()) + "\n" + "write0";	//Inform other clients that we have finish to write
	ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, scrive_msg, (uint64)1, NULL);
	txtmsg->Clear();
	ts3client_logMessage("Message send on chat", LogLevel_INFO, "Chat message", _sclogID);
}

/*
 * WxTimer1Timer
 */
void ClientTsFrm::WxTimer1Timer(wxTimerEvent& event)
{

	RefreshChat();
}

/*
 * txtmsgEnter
 */
void ClientTsFrm::txtmsgEnter(wxCommandEvent& event)
{
	btnsendClick(event);
}

/*
 * btnspeechClick
 */
void ClientTsFrm::btnspeechClick(wxCommandEvent& event)
{
	automatic_stt_flag = !automatic_stt_flag;
	if (automatic_stt_flag == false)
	{
		string stdisabled = "";
		stdisabled.append(labels.enable);
		stdisabled.append(" Speech to text");
		ID_MNU_OPZIONI_1004_Mnu_Obj->SetLabel(ID_MNU_SPEECH_1006, wxString::FromUTF8(stdisabled.c_str()));
		ID_MNU_OPZIONI_1004_Mnu_Obj->Check(ID_MNU_SPEECH_1006, false);
		WxBitmapButton1->Enable(true);
	}
	else
	{
		string stenabled = "";
		stenabled.append(labels.disable);
		stenabled.append(" Speech to text");
		ID_MNU_OPZIONI_1004_Mnu_Obj->SetLabel(ID_MNU_SPEECH_1006, wxString::FromUTF8(stenabled.c_str()));
		ID_MNU_OPZIONI_1004_Mnu_Obj->Check(ID_MNU_SPEECH_1006, true);
		WxBitmapButton1->Enable(false);
	}
}

/*
 * WxTimer2Timer
 */
void ClientTsFrm::WxTimer2Timer(wxTimerEvent& event)
{
	UserListPTR luser = Session::Instance()->getListUser();
	clientts->setVadLevel(DEFAULT_VIRTUAL_SERVER);
	if (txtmsg->IsModified()) 	write_flag = true;
	int i;
	for (auto it = luser->cbegin(); it != luser->cend(); ++it)
	{
		if ((*it)->getName() == config->getNick())
		{
			if ((*it)->getWrite() == 0 && write_flag)
			{
				wxString scrive_msg = "\n" + wxString::FromAscii(config->getLanguage()) + "\n" + "write1";
				ts3client_requestSendChannelTextMsg(DEFAULT_VIRTUAL_SERVER, scrive_msg, (uint64)1, NULL);
			}
		}
	}

}

void ClientTsFrm::Debug(wxCommandEvent& event)
{
	askForSaving();
	flag = 1;
	Sleep(300);
	Destroy();
}

void ClientTsFrm::Wizard(wxCommandEvent& event)
{
	// insert your code here
	AudioWizard* dialog = new AudioWizard(NULL);
	dialog->Show(true);
}

void ClientTsFrm::WxBitmapButton1Click(wxCommandEvent& event)
{
	tasto_stt_flag = !tasto_stt_flag;
	if (tasto_stt_flag == false)
	{
		ID_MNU_OPZIONI_1004_Mnu_Obj->Enable(ID_MNU_SPEECH_1006, true);
		WxBitmapButton1->SetBitmap(NULL);
	}
	else
	{
		sound_flag = true;
		recorder->startRecordingBufferedAudio();
		WxBitmapButton1->SetBitmap(microphone_xpm);
		ID_MNU_OPZIONI_1004_Mnu_Obj->Enable(ID_MNU_SPEECH_1006, false);
	}
}

void ClientTsFrm::Mail(wxCommandEvent& event)
{
	FrmMailSending *frame = new FrmMailSending(NULL);
	frame->ShowModal();
}

void ClientTsFrm::SettingMail(wxCommandEvent& event)
{
	FrmSettingMail *frame2 = new FrmSettingMail(NULL);
	frame2->ShowModal();
}
void ClientTsFrm::Save(wxCommandEvent& event)
{
	askForSaving();
}

void ClientTsFrm::askForSaving(){
	if (!clientts->getFlagSave()){
		wxMessageDialog *dial = new wxMessageDialog(NULL, labels.saveMessage, labels.saveMenu, wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION);
		dial->SetYesNoLabels(_(labels.yes), _(labels.no));

		int result = dial->ShowModal();
		if (result == wxID_YES)
		{
			FrmSaveChat *frame = new FrmSaveChat(NULL);
			result = frame->ShowModal();
			if (result == wxID_YES){
				clientts->setFlagSave(true); // chat saved
				wxMessageBox(labels.saveSuccess);
			}
		}
		else
			// first the user has decided to save the chat session, then he has changed his decision
			clientts->setFlagSave(false); // chat not saved
	}
	else
		wxMessageBox(labels.noSave);
}

void ClientTsFrm::notifyMsg(MessagePTR msg){
	/****
	* add new message to chat grid
	* ***/

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);

	UserListPTR luser = Session::Instance()->getListUser();

	if (strGlobale != "" && StringTranslate != oldStringTranslate/* strGlobale!=oldstrGlobale && StringTranslate != "" */)
	{
		if (wxString::FromAscii(getMSG_SRC()) == ">" || wxString::FromAscii(getMSG_SRC()) == "</html>" || getMSG_SRC()[0] == '<' || getMSG_SRC()[0] == '>')
			return;

		gridchat->AppendRows(1, true); //Add a new message row
		if (strNick == config->getNick())
		{
			wxString messaggio = wxString::FromUTF8(msg->getMSG())+ "(" + buf + "): " + wxString::FromUTF8(msg->getMSG());
//			gridchat->SetCellValue(messaggio, Session::Session::curRow, 0);
			gridchat->SetCellRenderer(curRow++, 1, new MyGridCellRenderer(L"../res/play.bmp"));
			gridchat->AutoSizeRow(curRow - 1, true);
			gridchat->SetColSize(curCol + 1, 30);
		}
		else
		{
			for (auto it = luser->cbegin(); it != luser->cend(); ++it)
			{
				if (wxString::FromUTF8(msg->getMSG()) == (*it)->getName() && (*it)->getUsed() == 1)
				{
					wxString messaggio = wxString::FromUTF8(msg->getMSG()) +"(" + buf + "): " + wxString::FromUTF8(msg->getMSG());
					gridchat->SetCellTextColour(curRow, 0, wxColour(colors[(*it)->getColor()].red, colors[(*it)->getColor()].green, colors[(*it)->getColor()].blue));
					gridchat->SetCellValue(messaggio, curRow, 0);
					gridchat->SetRowSize(curRow, 40);
					gridchat->SetColSize(curCol, 578);
					gridchat->SetColSize(curCol + 1, 60);
					gridchat->SetCellRenderer(curRow++, 1, new MyGridCellRenderer(L"../res/play.bmp"));
				}
			}
		}

		oldStringTranslate = StringTranslate;
		oldstrGlobale = strGlobale;
		strGlobale = "";
	}
	else
	{
		if (count_client == 0 && REFRESHTIMER > 50)   //ho sostituito empty_room e messo il timer
		{
			ts3client_logMessage("No such clients found", LogLevel_ERROR, "Channel", _sclogID);
			REFRESHTIMER = 0;
		}
	}
}
/*
void ClientTsFrm::notify(ClientTsFrm fn){

	std::cout << "i did it";
}*/
/*
template <typename T_object>
CallbackHandler::Callback_ID NotifyOnNewMail(T_object* object, void(T_object::*function)(void*, void*), void* user_data)
{
	new_mail_callbacks.RegisterCallback(object, function, user_data);
}*/

 