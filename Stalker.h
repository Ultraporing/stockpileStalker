#pragma once
#include "stockpileStalker.h"
#include "ScreenManager.h"

class ScreenManager;

class Stalker
{
	public:
	bool m_mapLoaded;
	bool m_stockpileStalkerStarted;
	bool m_shutDownThread;
	ALLEGRO_DISPLAY *m_display;
	ScreenManager *m_scrManager;
	ALLEGRO_EVENT_QUEUE *m_queue;

	public:
	ALLEGRO_THREAD *m_stalker_thread;

	Stalker();
	~Stalker();

	bool GetIsMapLoaded();
	void SetIsMapLoaded(bool isWorldLoaded);
	void SetTitle(const char *format, ...);

	static void SetStalkerStarted(bool isStarted, Stalker &stalker);
	static bool GetStalkerStarted(Stalker &stalker);
	static bool GetShutDownThread(Stalker &stalker);
	static void SetShutDownThread(bool shutDownThread, Stalker &stalker);
	static void* stalker_thread(ALLEGRO_THREAD *main_thread, void * parms);
	command_result StartStalker();

	ReturnReason MainLoop();
};

