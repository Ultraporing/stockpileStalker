#pragma once
// This is a generic plugin that does nothing useful apart from acting as an example... of a plugin that does nothing :D
#define SKIP_DFHACK_STDINT
#define DFHACK_WANT_PLATETYPES
// some headers required for a plugin. Nothing special, just the basics.
#include "Core.h"
#include <Console.h>
#include <Export.h>
#include <PluginManager.h>
#include <vector>


// DF data structure definition headers
#include "DataDefs.h"
#include "df/world.h"
#include "df\item.h"

using namespace DFHack;
using namespace df::enums;
using namespace std;

#define ALLEGRO_NO_MAGIC_MAIN //This is a DLL file. we got no main function.
#define ALLEGRO_HAVE_STDINT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/utf8.h>

// allegro leaks X headers, undef some of it here:
#undef TileShape
#undef None

#include <stdio.h>
#include <stdarg.h>

#define RELEASE

#define null 0

// My includes for helper stuff
#include "ProcessHelper.h"
#include "StalkerEnums.h"