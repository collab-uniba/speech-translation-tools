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
: wxFrame(parent, id, title, position, wxSize(924, 600), style)
{

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
	session = Session::Instance();
	clientts = make_unique<ClientTS>(this);
	colors = (COLORE*)malloc(10 * sizeof(COLORE));
	curRow = 0;			//Initialize Row index


	m_oldLogger = wxLog::GetActiveTarget();
	m_mgr.SetManagedWindow(this);

	wxPanel *main_panel_chat = new wxPanel(this, wxID_ANY);

	wxFlexGridSizer* boxSizerpanelChat = new wxFlexGridSizer(0, 1, 0, 0);
	boxSizerpanelChat->SetFlexibleDirection(wxBOTH);
	boxSizerpanelChat->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	boxSizerpanelChat->AddGrowableCol(0);
	boxSizerpanelChat->AddGrowableRow(0);
	main_panel_chat->SetSizer(boxSizerpanelChat);

	boxSizerpanelChat->Add(CreateChatBox(main_panel_chat), 1, wxALL | wxEXPAND, 5);

	wxFlexGridSizer* inputtextchat = new wxFlexGridSizer(0, 3, 0, 0);
	inputtextchat->SetFlexibleDirection(wxBOTH);
	inputtextchat->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	inputtextchat->AddGrowableCol(0);
	inputtextchat->AddGrowableRow(0);

	boxSizerpanelChat->Add(inputtextchat, 1, wxALL | wxEXPAND, 5);
	
	wxBitmap WxBitmapButton1_BITMAP(NULL);
	WxBitmapButton1 = new wxBitmapButton(main_panel_chat, ID_WXBITMAPBUTTON1, wxBitmap("../res/micro_cross.png", wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(50, 45), wxBU_AUTODRAW, wxDefaultValidator, _("WxBitmapButton1"));
	wxString enableSTTService;
	enableSTTService.Printf("%s %s", labels.enable, " SpeechToText Service");
	WxBitmapButton1->SetToolTip(_(enableSTTService));

	/* btnsend: botton which sends the message typed */
	btnsend = new wxButton(main_panel_chat, ID_WXBUTTON2, _(wxString::FromUTF8(labels.send.c_str())), wxDefaultPosition, wxSize(103, 48), 0, wxDefaultValidator, _("btnsend"));
	btnsend->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));

	/* Txtmsg: box where you can type a message*/
	txtmsg = new wxTextCtrl(main_panel_chat, ID_WXEDIT3, _(""), wxDefaultPosition, wxSize(-1, -1), wxTE_PROCESS_ENTER, wxDefaultValidator, _("txtmsg"));
	txtmsg->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, false));
	txtmsg->SetMinSize(wxSize(540, 45));
	txtmsg->SetFocus();

	inputtextchat->Add(txtmsg, 1, wxALL | wxEXPAND, 5);
	inputtextchat->Add(btnsend, 1, wxALL | wxEXPAND, 5);
	inputtextchat->Add(WxBitmapButton1, 1, wxALL | wxEXPAND, 5);



	tb1 = new wxAuiToolBar(this, ID_tool_bar, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT);

	tb1->SetToolBitmapSize(wxSize(16, 16));
	m_toolbar1_save = tb1->AddTool(ID_tool_bar + 1, wxT("Save"), wxBitmap("../res/save.png", wxBITMAP_TYPE_PNG));
	m_toolbar1_email = tb1->AddTool(ID_tool_bar + 2, wxT("Email"), wxBitmap("../res/email.png", wxBITMAP_TYPE_PNG));
	tb1->Realize();


	tb2 = new wxAuiToolBar(this, ID_tool_bar + 3, wxDefaultPosition, wxDefaultSize, wxAUI_TB_HORZ_LAYOUT);
	tb2->SetToolBitmapSize(wxSize(16, 16));

	m_toolbar2_sett = tb2->AddTool(ID_tool_bar + 4, wxT("Setting icon"), wxBitmap("../res/mail-settings-icon.png", wxBITMAP_TYPE_PNG));
	m_toolbar2_mic = tb2->AddTool(ID_tool_bar + 5, wxT("Microphone settings"), wxBitmap("../res/microphone-icon.png", wxBITMAP_TYPE_PNG));

	tb2->Realize();


	tb3 = new wxAuiToolBar(this, ID_tool_bar + 6, wxDefaultPosition, wxDefaultSize, wxAUI_TB_TEXT | wxAUI_TB_HORZ_TEXT);
	tb3->SetToolBitmapSize(wxSize(16, 16));

	wxString naz = this->nations->Search(&wxString(session->getLanguage()), COUNTRY);

	if (naz != "false")
	{
		tb3->AddTool(ID_tool_bar + 7, session->getNick(), wxBitmap("..\\res\\" + naz + ".png", wxBITMAP_TYPE_PNG))->SetSticky(true);
		//tb3->AddTool(ID_SampleItem + 1, , bitmap);
	}
	
	tb3->Realize();

	this->Connect(m_toolbar1_save->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( ClientTsFrm::Save));
	this->Connect(m_toolbar1_email->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ClientTsFrm::Mail));
	this->Connect(m_toolbar2_sett->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ClientTsFrm::SettingMail));
	this->Connect(m_toolbar2_mic->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(ClientTsFrm::Wizard));

	m_mgr.AddPane(tb1, wxAuiPaneInfo().
		Name(wxT("tb1")).Caption(wxT("Sample Bookmark Toolbar")).
		ToolbarPane().Top().Row(0));

	m_mgr.AddPane(tb2, wxAuiPaneInfo().
		Name(wxT("tb2")).Caption(wxT("Sample Bookmark Toolbar")).
		ToolbarPane().Top().Row(0));

	m_mgr.AddPane(tb3, wxAuiPaneInfo().
		Name(wxT("tb3")).Caption(wxT("Nickname")).
		ToolbarPane().Top().Row(0));

	
	txtclient = new wxRichTextCtrl(this, ID_WXRICHTEXTCTRL1, _("Loading... "), wxDefaultPosition, wxSize(200, -1), wxRE_READONLY, wxDefaultValidator, _("txtclient"));

	m_txtctrl = new wxTextCtrl(this, wxID_ANY, "...", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
	wxLog::SetActiveTarget(this);
	
	m_mgr.AddPane(main_panel_chat,
		wxAuiPaneInfo().
		Name(wxT("Online")).
		Center().Layer(1).Position(1).CloseButton(false));
	m_mgr.AddPane(m_txtctrl,
		wxAuiPaneInfo().
			Name(wxT("Log Panel")).
			Caption(wxT("Log Panel")).
			Bottom().Layer(1).Position(1).MaximizeButton(true));
	m_mgr.AddPane(txtclient,
		wxAuiPaneInfo().Left().Layer(1).Position(1).MaximizeButton(false));// .BestSize(1100, 100));
	m_mgr.Update();
	
	/***********************************/

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

	/*****MENU******/

	WxMenuBar1 = new wxMenuBar();
	ID_MNU_FILE_1001_Mnu_Obj = new wxMenu();
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_SAVE_1002, labels.saveMenu, _(""), wxITEM_NORMAL);
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_MAIL_1004, labels.mailMenu, _(""), wxITEM_NORMAL);
	ID_MNU_FILE_1001_Mnu_Obj->Append(ID_MNU_ESCI_1003, labels.exitMenu, _(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_FILE_1001_Mnu_Obj, _("File"));

	ID_MNU_OPZIONI_1004_Mnu_Obj = new wxMenu();
	ID_MNU_OPZIONI_1004_Mnu_Obj->Append(ID_MNU_SETTINGMAIL_1007, labels.emailSetting, _(""), wxITEM_NORMAL);
	ID_MNU_OPZIONI_1004_Mnu_Obj->Append(ID_MNU_AUDIO_1005, labels.audioMenu, _(""), wxITEM_NORMAL);

	ID_MNU_OPZIONI_1004_Mnu_Obj->AppendCheckItem(ID_MNU_SPEECH_1006, _(enableSTTService), _(""));
	WxMenuBar1->Append(ID_MNU_OPZIONI_1004_Mnu_Obj, labels.options);
	SetMenuBar(WxMenuBar1);

	/****MENU__END****/


	SetTitle(_("TeamTranslate"));
	SetIcon(wxNullIcon);
	//SetMinSize(wxSize(1024, 600));
	//Center();
	this->Centre(wxBOTH);

#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif

#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif

#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif

	/** checking if another user is typing**/
	WxTimer2 = new wxTimer();
	WxTimer2->SetOwner(this, ID_WXTIMER2);
	WxTimer2->Start(1000);

	 /**checking user online**/
	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(2000);

	/* TeamSpeak threads: start a client */
	HANDLE myHandle = CreateThread(0, 0, ClientTS::ClientStart, NULL, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, ClientTS::TTS_THREAD, NULL, 0, &myThreadID2);
	HANDLE myHandle3 = CreateThread(0, 0, ClientTS::STT_THREAD, NULL, 0, &myThreadID4);
	HANDLE myHandle4 = CreateThread(0, 0, ClientTS::CTRL_STT, NULL, 0, &myThreadID4);
	clientts->SetupColor(colors);


}

ttListCtrl* ClientTsFrm::CreateChatBox(wxPanel *panel)
{
	chatbox = new ttListCtrl(panel, ID_GRIDCHAT, wxPoint(0, 0), wxSize(-1, -1),
		wxLC_REPORT | wxLC_HRULES | wxLC_SINGLE_SEL);
	chatbox->SetMinSize(wxSize(570, 300));


	chatbox->Connect(wxEVT_MOTION, wxMouseEventHandler(ttListCtrl::OnMouseMotion));
	il = new wxImageList(16, 16, false, 0);

	il->Add(wxBitmap(L"../res/windows-icon.png", wxBITMAP_TYPE_PNG));
	il->Add(wxBitmap(L"../res/play.bmp", wxBITMAP_TYPE_BMP));
	chatbox->SetImageList(il, wxIMAGE_LIST_SMALL);

	wxListItem itemCol;
	itemCol.SetText(wxT("Data"));
	itemCol.SetImage(-1);
	itemCol.SetWidth(70);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	chatbox->InsertColumn(0, itemCol);

	itemCol.SetText(wxT("Nick"));
	itemCol.SetWidth(80);
	chatbox->InsertColumn(1, itemCol);

	itemCol.SetText(wxT("Message"));
	itemCol.SetWidth(520);
	chatbox->InsertColumn(2, itemCol);

	itemCol.SetText(wxT("#"));
	itemCol.SetWidth(24);
	chatbox->InsertColumn(3, itemCol);

	return chatbox;
}
 
void ClientTsFrm::ToolBarSaveClickevent(wxCloseEvent& event)
{
	Sleep(1);

}


void ClientTsFrm::gridchatCellLeftClick(wxListEvent& event)
{
	wxListCtrl *  o = (wxListCtrl*)event.GetEventObject();
	clientts->text_to_speech = event.GetIndex();
	wxTipWindow* tipWin;
	wxTimer *killTip;

	if (event.GetColumn() == 2){
		tipWin = new wxTipWindow(o, "textazo");
		// Bind() is only avail for 2.9.0 and later
		//Bind(wxTimerEvent, ttListCtrl::destroyTip, wxID_ANY, wxID_ANY, this);
		o->SetClientData(tipWin);
	//	o->Connect(wxEVT_TIMER, wxTimerEventHandler(ttListCtrl::destroyTip), NULL, this);
		killTip = new wxTimer(o, wxID_ANY);
		killTip->Start(1000, true);
	}
	else{
		clientts->thread_semaphore.Post();
	}
	
	chatbox->SetItemState(event.GetIndex(), 0, wxLIST_STATE_SELECTED);
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
		if (naz != "false")
		{
			bitmap.LoadFile("..\\res\\" + naz + ".png", wxBITMAP_TYPE_PNG);
			txtclient->WriteImage(bitmap);
		}
			
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
//	clientts->setVadLevel(DEFAULT_VIRTUAL_SERVER);
	if (txtmsg->IsModified()) 	session->setwrite_flag(true);
	int i;
	for (auto it = luser->cbegin(); it != luser->cend(); ++it)
	{
		if ((*it)->getName() == session->getNick())
		{
			if ((*it)->getWrite() == 0)// && session->getwrite_flag())
			{
				wxString scrive_msg = "\n" + wxString::FromAscii(session->getLanguage()) + "\n" + "write1";
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
		WxBitmapButton1->SetBitmap(wxBitmap("../res/micro_cross.png", wxBITMAP_TYPE_PNG));
	}
	else
	{
		session->setsound_flag(true);
		clientts->getIAudioRecorder()->startRecordingBufferedAudio();
		WxBitmapButton1->SetBitmap(wxBitmap("../res/micro.png", wxBITMAP_TYPE_PNG));
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

void ClientTsFrm::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}

	DoLogLine
		(
		m_txtctrl,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);
}

void
ClientTsFrm::DoLogLine(wxTextCtrl *text,
const wxString& timestr,
const wxString& threadstr,
const wxString& msg)
{
	text->AppendText(wxString::Format("%9s %10s %s", timestr, threadstr, msg));
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
	MessagePTR		msgptr			= event.GetPayload<MessagePTR>();
	long			itemIndexChat;

	//itemIndexChat = chatbox->InsertItem(curRow,  msgptr->getTimeStamp()); //want this for col. 1
	//chatbox->SetItem(itemIndexChat, 1, msgptr->getFrom()); //want this for col. 2

	long tmp = chatbox->InsertItem(curRow, msgptr->getHourMSG(), 0);
	chatbox->SetItemData(tmp, curRow);
	
	wxListItem info;
	info.SetImage(-1);
	info.SetId(curRow);
	info.SetColumn(0);
	chatbox->SetItem(info);
	
	info.SetColumn(1);
	info.SetText(msgptr->getFrom());
	chatbox->SetItem(info);

	info.SetColumn(2);
	info.SetImage(1);
	
	if (msgptr->getLanguageOrig() == msgptr->getLanguageSystem()){
		//chatbox->SetItem(itemIndexChat, 2, msgptr->getMSG()); //col. 3
		info.SetText(msgptr->getMSG());
	}
	else{
		//chatbox->SetItem(itemIndexChat, 2, msgptr->getTranslated() ); //col. 3
		//chatbox->SetTooltip(curRow, 3, msgptr);
		info.SetText(msgptr->getTranslated());
		chatbox->SetItem(info);

		info.SetColumn(3);
		info.SetImage(0);
		info.SetText("");
		
	}
	//chatbox->SetTooltip(curRow, 3, msgptr->getMSG());
	chatbox->SetItem(info);
	
	chatbox->ScrollList(0, curRow);
	curRow++;
}



/* ttListCtrl.cpp */
/* Ryan Day, http://www.ryanday.net/ */

/*
void ttListCtrl::SetTooltip(int row, int col, MessagePTR tip)
{
	int i, j;

	// If we are placing a tooltip beyond our predefined matrix, 
	// create a bigger matrix and copy the old matrix over. This
	// lets us have a dynamic sized tooltip grid.
	if ((row >= rows) || (col >= cols))
	{
		wxString* tmp = grid;
		grid = new wxString[(row + 5) * (col + 5)];

		for (i = 0; i<rows; i++)
		for (j = 0; j<cols; j++)
			grid[(i*cols) + j].Printf(wxT("%s"), tmp[(i*cols) + j]);
		delete[] tmp;
		rows = row + 5;
		cols = col + 5;
	}
	// We don't want to store a pointer to the user supplied tooltip,
	// we keep our own copy in the grid.
	grid[(row*cols) + col].Printf(wxT("%s"), tip);
}

*/

void ttListCtrl::OnMouseMotion(wxMouseEvent& event)
{
	ttListCtrl* o = (ttListCtrl*)event.GetEventObject();
	if (o == NULL) return;
	int id = event.GetEventType();
	int count = o->GetColumnCount();
	long row = -1, col = -1;
	int flags = 0, i = 0, totalWidth = 0, tmpWidth = 0;
	wxPoint pt;
	wxTipWindow* tipWin;
	wxTimer* killTip;
	MessagePTR toolTip;
	SimpleTransientPopup *m_simplePopup;

	if (id != wxEVT_MOTION)
		return;

	// We can get the row easily(HitTest) but the columns are more tricky.
	// We get all the column widths, and once our total width is beyoind where the
	// mouse is, we know which column the mouse is over.  This lets us resize the
	// columns during runtime and still get correct tooltips.
	pt = event.GetPosition();
	row = o->HitTest(pt, flags);

	for (i = 0; i<count; i++)
	{
		tmpWidth = o->GetColumnWidth(i);
		totalWidth += tmpWidth;
		if (pt.x < totalWidth)
		{
			col = i;
			break;
		}
	}

	// If things look valid, get the tooltip
	if (row > -1 && col == 3)
	{
		toolTip = session->getMessageQueue()->at(row);
	
		if (toolTip->getLanguageOrig() != toolTip->getLanguageSystem())
		{
			m_simplePopup = new SimpleTransientPopup(this, toolTip);
			wxWindow *btn = (wxWindow*)event.GetEventObject();
			wxPoint pos = btn->ClientToScreen(wxPoint(0, 0));
			wxSize sz = btn->GetSize();
			long x, y;
			event.GetPosition(&x, &y);
			m_simplePopup->Position(wxPoint(x, y), wxSize(200, 200));
			m_simplePopup->Popup();
		}
	// If we have a tooltip, we want to show is for 1 second, and then disappear. 
	// We use a timer for this.
	
		//tipWin = new wxTipWindow(o, toolTip);
		

		
		// Bind() is only avail for 2.9.0 and later
		//Bind(wxTimerEvent, ttListCtrl::destroyTip, wxID_ANY, wxID_ANY, this);
		/*SetClientData(m_simplePopup);
		Connect(wxEVT_TIMER, wxTimerEventHandler(ttListCtrl::destroyTip), NULL, this);
		killTip = new wxTimer(this, wxID_ANY);
		killTip->Start(1000, true);*/
	}
}

void ttListCtrl::destroyTip(wxTimerEvent& event)
{
	wxScrolledWindow *obj = (wxScrolledWindow*)GetClientData();
	if (obj) obj->Destroy();
}

enum
{
	Minimal_Quit = wxID_EXIT,
	Minimal_About = wxID_ABOUT,
	Minimal_TestDialog,
	Minimal_StartSimplePopup,
	Minimal_StartScrolledPopup,
	Minimal_LogWindow,
	Minimal_PopupButton,
	Minimal_PopupSpinctrl,
	PopUP_WXTIMER
};


/*
EVT_SIZE(SimpleTransientPopup::OnSize)
EVT_SET_FOCUS(SimpleTransientPopup::OnSetFocus)
EVT_KILL_FOCUS(SimpleTransientPopup::OnKillFocus)
EVT_BUTTON(Minimal_PopupButton, SimpleTransientPopup::OnButton)
EVT_SPINCTRL(Minimal_PopupSpinctrl, SimpleTransientPopup::OnSpinCtrl)
*/

SimpleTransientPopup::SimpleTransientPopup(wxWindow *parent, MessagePTR msg)
:wxPopupTransientWindow(parent)
{

	wxStaticText *text2;
	wxStaticText *text;
	wxTimer* killTip;
	wxBoxSizer *topSizer;

	m_panel = new wxScrolledWindow(this, wxID_ANY);
	m_panel->SetBackgroundColour(*wxLIGHT_GREY);

	// Keep this code to verify if mouse events work, they're required if
	// you're making a control like a combobox where the items are highlighted
	// under the cursor, the m_panel is set focus in the Popup() function

	//EVT_TIMER(PopUP_WXTIMER, SimpleTransientPopup::WxTimerPopUP)

	Connect(wxEVT_TIMER,
		wxTimerEventHandler(SimpleTransientPopup::WxTimerClose),
		NULL, this);

	killTip = new wxTimer(this, wxID_ANY);
	killTip->Start(1000, true); 

	text2 = new wxStaticText(m_panel, wxID_ANY,
			wxT("From ") +
			msg->getLanguageOrig() +
			wxT("\nto ")
			+ (msg->getLanguageSystem()));
		
	text = new wxStaticText(m_panel, wxID_ANY,
			msg->getMSG());

	topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(text2, 0, wxALL, 5);
	topSizer->Add(text, 0, wxALL, 5);

	m_panel->SetSizer(topSizer);

	// Use the fitting size for the panel if we don't need scrollbars.
	topSizer->Fit(m_panel);
	
	SetClientSize(m_panel->GetSize());
}

SimpleTransientPopup::~SimpleTransientPopup()
{
}

void SimpleTransientPopup::Popup(wxWindow* WXUNUSED(focus))
{
	wxPopupTransientWindow::Popup();
}

void SimpleTransientPopup::OnDismiss()
{
	wxPopupTransientWindow::OnDismiss();
}

bool SimpleTransientPopup::ProcessLeftDown(wxMouseEvent& event)
{
	return wxPopupTransientWindow::ProcessLeftDown(event);
}
bool SimpleTransientPopup::Show(bool show)
{
	return wxPopupTransientWindow::Show(show);
}

void SimpleTransientPopup::WxTimerClose(wxTimerEvent& event)
{
	this->Dismiss();
}