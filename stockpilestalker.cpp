#include "stockpilestalker.h"
#include "Stalker.h"



// Here go all the command declarations...
// mostly to allow having the mandatory stuff on top of the file and commands on the bottom
command_result stockpilestalker(color_ostream &out, std::vector <std::string> & parameters);

// A plugin must be able to return its name and version.
// The name string provided must correspond to the filename - skeleton.plug.so or skeleton.plug.dll in this case
DFHACK_PLUGIN("stockpilestalker");

Stalker m_stockStalker;

// Mandatory init function. If you have some global state, create it here.
DFhackCExport command_result plugin_init(color_ostream &out, std::vector <PluginCommand> &commands)
{
	// Fill the command list with your commands.
	commands.push_back(PluginCommand(
		"stockpilestalker", "Opens the \"Stockpile Stalker Plugin\" Window and displays your Item Stock.",
		stockpilestalker, false, /* true means that the command can't be used from non-interactive user interface */
		// Extended help string. Used by CR_WRONG_USAGE and the help command:
		"  This command has no parameters.\n"
		));
	return CR_OK;
}

//And the shutdown command.
DFhackCExport command_result plugin_shutdown(color_ostream &out)
{
	if (m_stockStalker.m_stalker_thread) {
		al_join_thread(m_stockStalker.m_stalker_thread, NULL);
	}
	al_uninstall_system();

	return CR_OK;
}

// Called to notify the plugin about important state changes.
// Invoked with DF suspended, and always before the matching plugin_onupdate.
// More event codes may be added in the future.

DFhackCExport command_result plugin_onstatechange(color_ostream &out, state_change_event event)
{
	switch (event) {
		case SC_MAP_LOADED:
			m_stockStalker.SetIsMapLoaded(true);
		break;

		case SC_MAP_UNLOADED:
			m_stockStalker.SetIsMapLoaded(false);
		break;
		
		default:
		break;

		
	}
	return CR_OK;
}


// Whatever you put here will be done in each game step. Don't abuse it.
// It's optional, so you can just comment it out like this if you don't need it.
/*
DFhackCExport command_result plugin_onupdate(color_ostream &out)
{
	
	// whetever. You don't need to suspend DF execution here.
	if (m_stockStalker.GetStalkerStarted(m_stockStalker))
	{
		if (m_stockStalker.GetShutDownThread(m_stockStalker))
		{
			if (m_stockStalker.m_stalker_thread) {
				al_join_thread(m_stockStalker.m_stalker_thread, NULL);

				m_stockStalker.SetShutDownThread(false, m_stockStalker);
				m_stockStalker.SetStalkerStarted(false, m_stockStalker);
			}
			al_uninstall_system();
		}
	}
	

return CR_OK;
}
*/


// A command! It sits around and looks pretty. And it's nice and friendly.
command_result stockpilestalker(color_ostream &out, std::vector <std::string> & parameters)
{
	// It's nice to print a help message you get invalid options
	// from the user instead of just acting strange.
	// This can be achieved by adding the extended help string to the
	// PluginCommand registration as show above, and then returning
	// CR_WRONG_USAGE from the function. The same string will also
	// be used by 'help your-command'.
	if (!parameters.empty())
		return CR_WRONG_USAGE;

	// Commands are called from threads other than the DF one.
	// Suspend this thread until DF has time for us. If you
	// use CoreSuspender, it'll automatically resume DF when
	// execution leaves the current scope.
	CoreSuspender suspend;
	// Actually do something here. Yay.
	vector<df::item*> stockpileVec = df::global::world->items.all;
	/*
	for (vector<df::item*>::iterator it = stockpileVec.begin(); it != stockpileVec.end(); ++it)
	{
		string itemName;
		(*it)->getItemBasicName(&itemName);
		out.print("Item %i\n", *it);
		//out.print("Item %i: %s\n", *it, itemName.c_str());
		//(*it)->getItemBasicName;
	}*/


	
	// Give control back to DF.
	return m_stockStalker.StartStalker();
}
