#include "Main.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include <iostream>
#include <GL/glut.h>

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
	d = new Display(argc, argv);
	
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

	cout << "started" << endl;
	
	glutTimerFunc(30,&call_timer,0);
	
	glutMainLoop();
	
	delete d;
	delete w;
	
	return 0;
	
}

void call_update()
{
	d->update();
}

void call_keys(unsigned char key, int x, int y)
{
	d->keys(key,x,y);
}

void call_s_keys(int key, int x, int y)
{
	d->s_keys(key,x,y);
}

void call_s_keys_up(int key, int x, int y)
{
	d->s_keys_up(key,x,y);
}

void call_mouse(int button, int state, int x, int y)
{
	d->mouse(button,state,x,y);
}

void call_active_mouse(int x, int y)
{
	d->activeMouse(x,y);	
}

void call_resize(int w, int h)
{
	d->resizeWindow(w,h);
}

void call_timer(int v)
{
	w->main_loop();
	glutTimerFunc(30,&call_timer,0);
}
