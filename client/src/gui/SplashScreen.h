#pragma once
#include <chrono>
#include <thread>
#include "wx/splash.h"

class SplashScreen
{
public:
	static bool GetSplashScreen(wxBitmap bitmap, int duration);
	~SplashScreen();

private:
	SplashScreen();
	static int COUNTER;
};


