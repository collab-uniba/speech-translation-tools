#include "FrmSaveChat.h"
#include "../data/Session.h"


 


FrmSaveChat::FrmSaveChat(wxWindow* parent, wxWindowID id, const wxString &title, const wxPoint& position, const wxSize& size, long style) : wxDialog(parent, id, title, position, size, style)
{
	CenterOnScreen();

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);


	bSizer2->Add(0, 0, 1, wxEXPAND, 5);

	lblTitle = new wxStaticText(this, wxID_ANY, labels.saveFormatMessage, wxDefaultPosition, wxDefaultSize, 0);
	lblTitle->Wrap(-1);
	lblTitle->SetFont(wxFont(12, 70, 90, 90, false, wxEmptyString));

	bSizer2->Add(lblTitle, 0, wxALIGN_CENTER | wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);


	bSizer2->Add(0, 0, 1, wxEXPAND, 5);

	m_bitmap2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ico_save), wxDefaultPosition, wxSize(75, 75), 0);
	bSizer2->Add(m_bitmap2, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);


	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);


	bSizer7->Add(20, 1, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	chkCSV = new wxCheckBox(this, wxID_ANY, labels.formatCsv, wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(chkCSV, 0, wxALL, 5);

	chkTXT = new wxCheckBox(this, wxID_ANY, labels.formatTxt, wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(chkTXT, 0, wxALL, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);

	lblSaveIn = new wxStaticText(this, wxID_ANY, labels.saveIn, wxDefaultPosition, wxDefaultSize, 0);
	lblSaveIn->Wrap(-1);
	bSizer9->Add(lblSaveIn, 0, wxALIGN_CENTER | wxALL, 5);

	fpkBrowse = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, labels.dirSelect, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE, wxDefaultValidator, wxDirPickerCtrlNameStr);
	bSizer9->Add(fpkBrowse, 1, wxALL, 5);


	bSizer8->Add(bSizer9, 1, wxEXPAND, 5);
	bSizer7->Add(bSizer8, 1, wxEXPAND, 5);
	bSizer6->Add(bSizer7, 1, wxEXPAND, 5);
	bSizer5->Add(bSizer6, 1, wxEXPAND, 5);
	bSizer1->Add(bSizer5, 1, wxEXPAND, 5);
	bSizer1->Add(0, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);


	bSizer4->Add(0, 0, 1, wxEXPAND, 5);

	btnConfirm = new wxButton(this, wxID_ANY, labels.confirm, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(btnConfirm, 0, wxALL, 5);


	bSizer1->Add(bSizer4, 1, wxEXPAND, 5);

	btnConfirm->Disable();
	fpkBrowse->Disable();

	this->SetSizer(bSizer1);
	this->Layout();

	// Connect Events
	chkCSV->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveChat::checkBoxSelection), NULL, this);
	chkTXT->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveChat::checkBoxSelection), NULL, this);
	btnConfirm->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveChat::btnConfirmClick), NULL, this);

	this->Connect(-1, wxEVT_CLOSE_WINDOW, wxCloseEventHandler(FrmSaveChat::OnClose), NULL, this);
}

FrmSaveChat::~FrmSaveChat()
{
	// Disconnect Events
	btnConfirm->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrmSaveChat::btnConfirmClick), NULL, this);
	chkCSV->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveChat::checkBoxSelection), NULL, this);
	chkTXT->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FrmSaveChat::checkBoxSelection), NULL, this);
}

void FrmSaveChat::OnClose(wxCloseEvent& event) {
	this->EndModal(wxID_NO); // chat not saved
}

void FrmSaveChat::checkBoxSelection(wxCommandEvent& event){

	if (chkCSV->GetValue() || chkTXT->GetValue()) {
		btnConfirm->Enable();
		fpkBrowse->Enable();
	}
	else {
		btnConfirm->Disable();
		fpkBrowse->Disable();
	}
}

void FrmSaveChat::btnConfirmClick(wxCommandEvent& event)
{
	// to get timestamp
	FILE *config = fopen("..\\bin\\conf\\directory.txt", "w");
	char timestamp[100];
	time_t rawtime;
	struct tm * timeinfo;
	char temp[3000];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(timestamp, 100, "%d-%m-%Y_%H-%M-%S", timeinfo);
	puts(timestamp);
	// end timestamp
	
	wxString path = fpkBrowse->GetPath() + "\\chatLog_" + timestamp;
	
	
	if (chkCSV->GetValue()){
		saveChatCSV(path + ".csv");
		strcpy(destination, fpkBrowse->GetPath() + "\\chatLog_" + timestamp + ".csv");
		fprintf(config, "%s\n", destination);
	}
	else{
		strcpy(destination, "NoFile");
		fprintf(config, "%s\n", destination);
	}
	if (chkTXT->GetValue()){
		saveChatTXT(path + ".txt");
		strcpy(destination, fpkBrowse->GetPath() + "\\chatLog_" + timestamp + ".txt");
		fprintf(config, "%s\n", destination);
	}
	else{
		strcpy(destination, "NoFile");
		fprintf(config, "%s\n", destination);
	}
	fclose(config);
	this->EndModal(wxID_YES); // chat saved
}

void FrmSaveChat::saveChatCSV(const char* filename){
	config = fopen(filename, "w");

	list<MESSAGE>::iterator iter;
	for (iter = diary.begin(); iter != diary.end(); iter++){

		fprintf(config, "\"" + (*iter).nick + "\";");
		fprintf(config, "\"" + (*iter).timestamp + "\";");
		fprintf(config, "\"" + (*iter).msgDir + "\";");

		if (strcmp((*iter).msgDir, "-->"))
			fprintf(config, "\"" + (*iter).msgold + "\"\n");
		else
			fprintf(config, "\"" + (*iter).lang + ";\"" + (*iter).msgold + ";\"#orig#\";\"" + Session::Instance()->getLanguage() + ";\"" + (*iter).msgnew + "\"\n");
	}

	fflush(config);
	fclose(config);
}

void FrmSaveChat::saveChatTXT(const char* filename){

	config = fopen(filename, "w");

	list<MESSAGE>::iterator iter;
	for (iter = diary.begin(); iter != diary.end(); iter++){

		fprintf(config, (*iter).nick + " || ");
		fprintf(config, (*iter).timestamp + "  || ");
		fprintf(config, (*iter).msgDir + " ");

		if (strcmp((*iter).msgDir, "-->") == 0)
			fprintf(config, (*iter).msgold + "\n");
		else
			fprintf(config, "(" + (*iter).lang + ": " + (*iter).msgold + " #orig# " + Session::Instance()->getLanguage() + ": " + (*iter).msgnew + ")\n");
	}

	fflush(config);
	fclose(config);
}