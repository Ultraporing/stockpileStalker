#include "Stalker.h"

using namespace DFHack;
using namespace df::enums;
using namespace std;



Stalker::Stalker():
m_mapLoaded(false),
m_shutDownThread(false)
{
	
}

Stalker::~Stalker()
{
}

bool Stalker::GetIsMapLoaded()
{
	return m_mapLoaded;
}

void Stalker::SetIsMapLoaded(bool isWorldLoaded)
{
	m_mapLoaded = isWorldLoaded;
}

void Stalker::SetStalkerStarted(bool isStarted, Stalker &stalker)
{
	stalker.m_stockpileStalkerStarted = isStarted;
}

bool Stalker::GetStalkerStarted(Stalker &stalker)
{
	return stalker.m_stockpileStalkerStarted;
}

bool Stalker::GetShutDownThread(Stalker &stalker)
{
	return stalker.m_shutDownThread;
}

void Stalker::SetShutDownThread(bool shutDownThread, Stalker &stalker)
{
	stalker.m_shutDownThread = shutDownThread;
}

void Stalker::SetTitle(const char *format, ...)
{
	ALLEGRO_USTR *buf;
	va_list ap;
	const char *s;

	/* Fast path for common case. */
	if (0 == strcmp(format, "%s")) {
		va_start(ap, format);
		s = va_arg(ap, const char *);
		al_set_window_title(m_display, s);
		va_end(ap);
		return;
	}

	va_start(ap, format);
	buf = al_ustr_new("");
	al_ustr_vappendf(buf, format, ap);
	va_end(ap);

	al_set_window_title(m_display, al_cstr(buf));

	al_ustr_free(buf);
}

command_result Stalker::StartStalker()
{
	color_ostream_proxy out(Core::getInstance().getConsole());

	if (m_stockpileStalkerStarted) {
		out.print("Stockpilestalker already running.\n");
		return CR_OK;
	}

	if (!GetIsMapLoaded())
	{
		out.print("Map is Not Loaded\n");
		return CR_OK;
	}
		
	SetStalkerStarted(true, *this);

	if (!al_is_system_installed()) {
		if (!al_init()) {
			out.printerr("Could not init Allegro.\n");
			return CR_FAILURE;
		}

		if (!al_init_image_addon()) {
			out.printerr("al_init_image_addon failed. \n");
			return CR_FAILURE;
		}
		if (!al_init_primitives_addon()) {
			out.printerr("al_init_primitives_addon failed. \n");
			return CR_FAILURE;
		}
		al_init_font_addon();
		if (!al_init_ttf_addon()) {
			out.printerr("al_init_ttf_addon failed. \n");
			return CR_FAILURE;
		}
	}
	
	m_stalker_thread = al_create_thread(stalker_thread, this);
	al_start_thread(m_stalker_thread);

	out.print("Stockpilestalker Started\n");

	return CR_OK;
}

void* Stalker::stalker_thread(ALLEGRO_THREAD *main_thread, void * parms)
{
	Stalker *stalkerInstance = (Stalker*)parms;
	color_ostream_proxy out(Core::getInstance().getConsole());

	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_DIRECT3D_INTERNAL | ALLEGRO_RESIZABLE);

	stalkerInstance->m_display = al_create_display(800, 600);
	if (!stalkerInstance->m_display) {
		out.printerr("al_create_display failed\n");
		stalkerInstance->m_stockpileStalkerStarted = false;
		return NULL;
	}
	if (!al_is_keyboard_installed()) {
		if (!al_install_keyboard()) {
			out.printerr("Stockpilestalker: al_install_keyboard failed\n");
		}
	}
	if (!al_is_mouse_installed()) {
		if (!al_install_mouse()) {
			out.printerr("Stockpilestalker: al_install_mouse failed\n");
		}
	}
	stalkerInstance->SetTitle("Stockpilestalker");

	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_ALPHA_TEST | ALLEGRO_MIN_LINEAR | ALLEGRO_MIPMAP);

	stalkerInstance->m_queue = al_create_event_queue();
	if (!stalkerInstance->m_queue) {
		out.printerr("al_create_event_queue failed\n");
		stalkerInstance->m_stockpileStalkerStarted = false;
		return NULL;
	}

	al_register_event_source(stalkerInstance->m_queue, al_get_keyboard_event_source());
	al_register_event_source(stalkerInstance->m_queue, al_get_display_event_source(stalkerInstance->m_display));
	al_register_event_source(stalkerInstance->m_queue, al_get_mouse_event_source());

	stalkerInstance->m_scrManager = &ScreenManager(stalkerInstance);
	stalkerInstance->m_scrManager->AddScreen("Splash", ScreenTypes::SplashScreen);
	stalkerInstance->m_scrManager->ActivateScreen("Splash");

	while (!al_get_thread_should_stop(main_thread))
	{
		if (stalkerInstance->MainLoop() != ReturnReason::Done)
		{
			al_join_thread(main_thread, NULL);
		}
	}
	
	al_destroy_display(stalkerInstance->m_display);
	
	stalkerInstance->m_stockpileStalkerStarted = false;
	return NULL;
}

ReturnReason Stalker::MainLoop()
{
	ALLEGRO_COLOR clearCol;
	clearCol.r = 0.0f;
	clearCol.g = 0.0f;
	clearCol.b = 0.0f;
	clearCol.a = 1.0f;

	al_clear_to_color(clearCol);

	m_scrManager->Render(m_display);


	al_flip_display();

	return ReturnReason::Done;
}