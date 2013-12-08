#include "Screen.h"

Screen::Screen():
m_screenType(ScreenTypes::None)
{}

Screen::Screen(std::string screenName, ScreenTypes screenType, Stalker *stalker) :
m_screenName(screenName),
m_screenType(screenType),
m_stalker(stalker)
{
	color_ostream_proxy outprox(Core::getInstance().getConsole());
	out = &outprox;
}

Screen::~Screen()
{
}

std::string Screen::GetScreenName()
{
	return m_screenName;
}