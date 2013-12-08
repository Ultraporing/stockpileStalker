#include "ScreenManager.h"


ScreenManager::ScreenManager(Stalker *stalker) :
m_activeScreen("None"),
m_stalker(stalker)
{
	AddScreen("SplashScreen", ScreenTypes::SplashScreen);
}


ScreenManager::~ScreenManager()
{
}

Screen* ScreenManager::GetScreenByName(std::string screenName)
{
	if (m_screenCollection.size() > 0)
	{
		for (vector<Screen>::iterator it = m_screenCollection.begin(); it != m_screenCollection.end(); ++it)
		{
			if (!(*it).GetScreenName().compare(screenName))
				return &(*it);
		}
	}

	return NULL;
}

void ScreenManager::AddScreen(std::string screenName, ScreenTypes screenType)
{
	switch (screenType)
	{
		case ScreenTypes::SplashScreen:
			m_screenCollection.push_back((Screen)SplashScreen(screenName, m_stalker));
			break;
		case ScreenTypes::MainScreen:
			break;
		case ScreenTypes::Credits:
			break;
		default:
			break;
	}
	
}

void ScreenManager::RemoveScreen(std::string screenName)
{
	if (m_screenCollection.size() > 0)
	{
		for (vector<Screen>::iterator it = m_screenCollection.begin(); it != m_screenCollection.end(); ++it)
		{
			if (!(*it).GetScreenName().compare(screenName))
			{
				m_screenCollection.erase(it);
				return;
			}
		}
	}
}

void ScreenManager::RemoveAllScreens()
{
	if (m_screenCollection.size() > 0)
	{
		m_screenCollection.erase(m_screenCollection.begin(), m_screenCollection.end());	
	}
}

void ScreenManager::ActivateScreen(std::string screenName)
{
	m_activeScreen = screenName;
}

int ScreenManager::HandleInput()
{

	return 0;
}

ReturnReason ScreenManager::Update()
{

	return ReturnReason::Done;
}

void ScreenManager::Render(ALLEGRO_DISPLAY *display)
{
	if (m_screenCollection.size() > 0)
	{
		for (vector<Screen>::iterator it = m_screenCollection.begin(); it != m_screenCollection.end(); ++it)
		{
			if (!(*it).GetScreenName().compare(m_activeScreen))
			{
				(*it).Render();
				return;
			}
		}
	}
}