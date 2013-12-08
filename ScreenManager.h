#pragma once
#include "stockpileStalker.h"
#include "Stalker.h"
#include "SplashScreen.h"

class ScreenManager
{
	private:
	vector<Screen> m_screenCollection;
	std::string m_activeScreen;
	Stalker *m_stalker;

	public:
	ScreenManager(Stalker *stalker);
	~ScreenManager();

	int HandleInput();
	ReturnReason Update();
	void Render(ALLEGRO_DISPLAY *display);

	Screen* GetScreenByName(std::string screenName);
	void AddScreen(std::string screenName, ScreenTypes screenType);
	void RemoveScreen(std::string screenName);
	void RemoveAllScreens();
	void ActivateScreen(std::string screenName);
};

