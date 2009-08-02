#include "Main.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include <iostream>

#include "Display.h"
#include "World.h"
#include "LuaBinder.h"

extern "C" {
#include "lua.h"
}

Display *d;
World *w;
lua_State *l;


int main (int argc, char** argv)
{
	d = new Display();
	
	l = lua_open();
	
	w = new World(d,l);
	
	try {
		luaL_openlibs(l);
				
		luabind::open(l);
		
		LuaBinder lb;
		lb.bind(l);
	
		luaL_dofile(l,"lua/grind.lua");
		
		luabind::call_function<void>(l, "start",w);
	
	} catch(const std::exception &TheError) {
		cerr << TheError.what() << endl;
		cerr << lua_tostring(l, -1) << endl;
	}

	w->main_loop();
	
	delete d;
	delete w;
	
	return 0;
	
}
