#include "SplashScreen.h"

int SplashScreen::COUNTER = 0;

SplashScreen::SplashScreen()
{

}

SplashScreen::~SplashScreen()
{

}

bool SplashScreen::GetSplashScreen(wxBitmap bitmap, int duration)
{
	bool flags = true;

	if (COUNTER == 0)
	{
		if (bitmap.IsNull())
		{
			flags = false;
		}
		else
		{
			COUNTER++;
			wxInitAllImageHandlers();

			wxSplashScreen* splash = new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT, duration, NULL, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE | wxSTAY_ON_TOP);
			std::this_thread::sleep_for(std::chrono::milliseconds(duration + 1));
			flags = true;
		}
	}
		wxYield();
		return flags;
}