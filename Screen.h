#pragma once
#include "stockpileStalker.h"
#include "Stalker.h"

class Screen
{
	protected:
	std::string m_screenName;
	ScreenTypes m_screenType;
	color_ostream_proxy *out;
	Stalker *m_stalker;

	public:
	Screen();
	Screen(std::string screenName, ScreenTypes screenType, Stalker *stalker);
	~Screen();

	virtual int InputHandling();
	virtual ReturnReason Update();
	virtual void Render();

	std::string Screen::GetScreenName();
};

