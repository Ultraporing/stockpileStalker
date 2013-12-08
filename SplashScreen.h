#pragma once
#include "Screen.h"


class SplashScreen : public Screen
{
	public:
	SplashScreen(std::string screenName, Stalker *stalker);
	~SplashScreen();

	void Render() override;
};

