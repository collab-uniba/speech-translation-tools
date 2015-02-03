#include "AudioWizard.h"

char immagine[50];
int valore;
FILE *mic;
//----------------------------------------------------------------------------
// AudioWizard
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(AudioWizard,wxDialog)
	////Manual Code Start
	////Manual Code End
	EVT_BUTTON(ID_WXBUTTON1, AudioWizard::ConfermaClick)
	EVT_TIMER(ID_WXTIMER1, AudioWizard::WxTimer1Timer)
	EVT_CLOSE(AudioWizard::OnClose)
END_EVENT_TABLE()
////Event Table End

AudioWizard::AudioWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

AudioWizard::~AudioWizard()
{
} 

void AudioWizard::CreateGUIControls()
{
	//TODO Completare la traduzione di AudioWizard usando le variabile statica labels

	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	btnconferma = new wxButton(this, ID_WXBUTTON1, labels.confirm.c_str(), wxPoint(344, 368), wxSize(75, 25), 0, wxDefaultValidator, _("btnconferma"));

	string audiotext = "";
	audiotext.append(labels.microphone);
	audiotext.append("\n\n");
	audiotext.append(labels.min);
	audiotext.append("\n\n");
	audiotext.append(labels.max);
	lblhelp = new wxStaticText(this, ID_WXSTATICTEXT1, audiotext.c_str(), wxPoint(20, 32), wxDefaultSize, 0, _("lblhelp"));
	
	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);
	WxTimer1->Start(1000);


	slideraudio = new wxSlider(this, ID_WXSLIDER1, 0, 0, 50, wxPoint(72, 195), wxSize(330, 65), wxSL_HORIZONTAL | wxSL_LABELS | wxSL_SELRANGE, wxDefaultValidator, _("slideraudio"));
	slideraudio->SetRange(-50,50);
	slideraudio->SetValue(1);
	/*wxBitmap bmpfeed_BITMAP(ledrosso_xpm);
	bmpfeed = new wxStaticBitmap(this, ID_WXSTATICBITMAP1, bmpfeed_BITMAP, wxPoint(216, 270), wxSize(32, 32));*/
	if (mic = fopen("..\\conf\\mic.txt", "r"))
	{
		fscanf(mic, "%d", &valore);
		slideraudio->SetValue(valore);
	}
	else
	{
		mic = fopen("..\\conf\\mic.txt", "w");
		slideraudio->SetValue(1);
	}
	fflush(mic);
	fclose(mic);

	SetTitle(_("AudioWizard"));
	SetIcon(wxNullIcon);
	SetSize(8,8,520,520);
	Center();
	
	////GUI Items Creation End
}

void AudioWizard::OnClose(wxCloseEvent& /*event*/)
{
	WxTimer1->Stop();
	this->Show(false);
	this->Destroy();
}

void AudioWizard::ConfermaClick(wxCommandEvent& event)
{
	FILE *mic = fopen("..\\conf\\mic.txt","w");
	fprintf(mic,"%d",slideraudio->GetValue());
	fflush(mic);
	//wxMessageBox(wxString::FromDouble(slideraudio->GetValue()));
}

void AudioWizard::WxTimer1Timer(wxTimerEvent& event)
{

}