#include "Screen.h"


Screen::Screen()
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