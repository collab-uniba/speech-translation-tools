#include "ClientTsFrm.h"


BEGIN_EVENT_TABLE(ClientTsFrm, wxFrame)

	EVT_CLOSE(ClientTsFrm::OnClose)
	EVT_TIMER(ID_WXTIMER2, ClientTsFrm::WxTimer2Timer)
	EVT_TIMER(ID_WXTIMER1, ClientTsFrm::updateClientListTimer)
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
	EVT_LIST_ITEM_SELECTED(ID_GRIDCHAT, ClientTsFrm::gridchatCellLeftClick)
	EVT_THREAD(wxID_ANY, ClientTsFrm::updatePanelMsg)

END_EVENT_TABLE()



ClientTsFrm::ClientTsFrm(LoginWarnings*warnings,wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	this->nations = new NationList();
	//session->registerObserver<ClientTsFrm>(&ClientTsFrm::notify, *this);
	this->nations->ReadFromFile("..\\conf\\locales_code.txt");
	session = Session::Instance();
	config = session->getConfig();
	clientts = make_unique<ClientTS>(this);

	colors = (COLORE*)malloc(10 * sizeof(COLORE));

//	session->registerObserver(EventTS::MSG_RCV, [](ClientTsFrm *fn) { fn->updatePanelMsg(); }, this);

	//registercb(*this); // register itself into clientTs "class" in order to be notified about any change
	 curRow = 0;			//Initialize Row index
	 //clientts->observer = this;
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

	chatbox = new wxListCtrl(this, ID_GRIDCHAT, wxPoint(211, 72), wxSize(722, 350), wxLC_REPORT, wxDefaultValidator, wxT("moviesTable"));

	chatbox->InsertColumn(1, wxT("Data"), wxLIST_FORMAT_LEFT, 70);
	chatbox->InsertColumn(2, wxT("Nick"), wxLIST_FORMAT_LEFT, 80);
	chatbox->InsertColumn(3, wxT("Message"), wxLIST_FORMAT_LEFT, 520);

	WxTimer2 = new wxTimer();
	WxTimer2->SetOwner(this, ID_WXTIMER2);
	WxTimer2->Start(200);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(2000);


	txtclient = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _(""), wxPoint(10, 75), wxSize(184, 155), wxRE_READONLY, wxDefaultValidator, _("txtclient"));
	txtclient->SetMaxLength(0);
	txtclient->SetFocus();
	txtclient->SetInsertionPointEnd();
	txtclient->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));
	txtclient->WriteText(wxString("Loading...."));

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

	txtnick->AppendText(config->getNick());
	txtlingua->AppendText(config->getLanguage());
	HANDLE myHandle = CreateThread(0, 0, ClientTS::ClientStart, NULL, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, ClientTS::TTS_THREAD, NULL, 0, &myThreadID2);
	HANDLE myHandle3 = CreateThread(0, 0, ClientTS::STT_THREAD, NULL, 0, &myThreadID4);
	HANDLE myHandle4 = CreateThread(0, 0, ClientTS::CTRL_STT, NULL, 0, &myThreadID4);
	clientts->SetupColor(colors);



	updateClientListTimer(wxTimerEvent());
}

 

void ClientTsFrm::gridchatCellLeftClick(wxListEvent& event)
{
	clientts->text_to_speech = event.GetIndex();
	clientts->thread_semaphore.Post();
}

void ClientTsFrm::OnClose(wxCloseEvent& event)
{
	askForSaving();
	clientts->disconnect();
	Sleep(300);
	Destroy();
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
	txtmsg->DiscardEdits();		//Clear buffer of textbox
	clientts->sendMessage(&txtmsg->GetValue());
	txtmsg->Clear();
}

/*
 * WxTimer1Timer
 */
void ClientTsFrm::updateClientListTimer(wxTimerEvent& event)
{
	int			i			= 0;
	UserListPTR luser		= Session::Instance()->getListUser();
	wxUniChar   ch			= ':';
	time_t		now			= time(0);
	struct tm	tstruct;
	char		buf[80];

	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);
	clientts->showClients(DEFAULT_VIRTUAL_SERVER);

	txtclient->Clear();	//Clear client window

	for (auto it = luser->cbegin(); it != luser->cend(); ++it)
	{
		UserPTR uptr = *it;
		txtclient->BeginTextColour(wxColour(colors[i].red, colors[i].green, colors[i].blue));
			
		wxString naz = this->nations->Search(&uptr->getLang(), COUNTRY);
		wxBitmap bitmap = wxBitmap();
		bitmap.LoadFile("..\\res\\" + naz + ".png", wxBITMAP_TYPE_PNG);
		txtclient->WriteImage(bitmap);

		txtclient->WriteText(" " +uptr->getName() + "\t");

		if (uptr->getSpeak() == 1)	//if this client is speaking, show microphone 
		{
			txtclient->WriteText("\t");
			txtclient->WriteImage(wxBitmap(microphone_xpm));
		}

		if (uptr->getWrite() == 1)
		{
			txtclient->WriteText("\t");
			txtclient->WriteImage(wxBitmap(keyboard_xpm));
		}
		
		txtclient->EndTextColour();
		txtclient->Newline();
		i++;
	}
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
	session->setautomatic_stt_flag(!session->getautomatic_stt_flag());
	if (session->getautomatic_stt_flag() == false)
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
	if (txtmsg->IsModified()) 	session->setwrite_flag(true);
	int i;
	for (auto it = luser->cbegin(); it != luser->cend(); ++it)
	{
		if ((*it)->getName() == config->getNick())
		{
			if ((*it)->getWrite() == 0 && session->getwrite_flag())
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
	clientts->disconnect();
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
	session->settasto_stt_flag(!session->gettasto_stt_flag());
	if (session->gettasto_stt_flag() == false)
	{
		ID_MNU_OPZIONI_1004_Mnu_Obj->Enable(ID_MNU_SPEECH_1006, true);
		WxBitmapButton1->SetBitmap(NULL);
	}
	else
	{
		session->setsound_flag(true);
		clientts->getIAudioRecorder()->startRecordingBufferedAudio();
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
			if (result == wxID_YES)
			{
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

void ClientTsFrm::updatePanelMsg(wxThreadEvent& event){
	/****
	* add new message to chat grid
	****/

	wxImageList		*il;
	MessagePTR		msgptr			= event.GetPayload<MessagePTR>();
	long			itemIndexChat;

//	if (!(msgptr->getMSG() == ">" || msgptr->getMSG() == "</html>" || msgptr->getMSG()[0] == '<' || msgptr->getMSG()[0] == '>'))
	{
		itemIndexChat = chatbox->InsertItem(curRow,  msgptr->getTimeStamp()); //want this for col. 1

		chatbox->SetItem(itemIndexChat, 1, msgptr->getFrom()); //want this for col. 2

		il = new wxImageList(16, 16, false, 0);
		il->Add(wxBitmap(L"../res/play.bmp", wxBITMAP_TYPE_BMP));
		chatbox->SetImageList(il, wxIMAGE_LIST_SMALL);
		chatbox->SetItem(itemIndexChat, 2, msgptr->getMSG()); //col. 3
		chatbox->ScrollList(0, curRow);
		curRow++;
	}


	/*

		oldStringTranslate = StringTranslate;
		oldstrGlobale = strGlobale;
		strGlobale = "";
	}
	/*else
	{
		if (count_client == 0 && REFRESHTIMER > 50)   //ho sostituito empty_room e messo il timer
		{
			ts3client_logMessage("No such clients found", LogLevel_ERROR, "Channel", _sclogID);
			REFRESHTIMER = 0;
		}
	}*/
}
/*
MyWorkerThread::MyWorkerThread(ClientTsFrm *frame)
: wxThread()
{
	m_frame = frame;
	m_count = 0;
	//session->registerObserver(EventTS::MSG_RCV, [](ClientTsFrm *fn) { fn->updatePanelMsg(); }, this);
}

MyWorkerThread::Entry()
{


	
	wxThreadEvent event(wxEVT_THREAD, WORKER_EVENT);
	event.SetInt(-1); // that's all
	wxQueueEvent(m_frame, event.Clone());


	return NULL;
}*/