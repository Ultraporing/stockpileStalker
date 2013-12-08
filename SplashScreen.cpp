#include "SplashScreen.h"


SplashScreen::SplashScreen(std::string screenName, Stalker *stalker)
{
	m_screenName = screenName;
	m_stalker = stalker;
	m_screenType = ScreenTypes::SplashScreen;
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::Render()
{
	ALLEGRO_FONT *font = al_load_ttf_font("arial.ttf", 72, 0);
	if (!font)
	{
		out->printerr("Could not load 'arial.ttf'.\n");
		return;
	}

	al_draw_text(font, al_map_rgb(255, 255, 255), 50, 50, ALLEGRO_ALIGN_CENTER, "Im Alive!");
}
