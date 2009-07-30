#include "Main.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include <iostream>
#include <GL/glut.h>

#include "Display.h"
#include "World.h"
#include "Block.h"
#include "Block3D.h"
#include "Block2D.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "ModelLoader.h"
#include "Obj.h"
#include "Texture.h"
#include "Controller.h"
#include "Camera.h"
#include "Sky.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>

Display *d;
World *w;
lua_State *l;


int main (int argc, char** argv)
{
	/*

	Block* b1 = w->new_block("block.obj","red_block.bmp");
	Vector3f *v1 = new Vector3f(1.2,0,-5);
	b1->move(*v1);
	
	Block* b2 = w->new_block("block.obj","blue_block.bmp");
	Vector3f *v2 = new Vector3f(-1.2,0,-5);
	b2->move(*v2);
	
	cout << "Entering main loop\n";

	*/
	
	d = new Display(argc, argv);
	
	l = lua_open();
	
	w = new World(d,l);
	
	try {
		
		luaL_openlibs(l);
		/*
		luaopen_io(l); // provides io.*
		luaopen_base(l);
		luaopen_table(l);
		luaopen_string(l);
		luaopen_math(l);
		luaopen_loadlib(l);
		*/
		
		// Connect luaBind to this lua state
		luabind::open(l);
		
		// Export our classes with luaBind
		
		luabind::module(l) [
			luabind::class_<Vector3f>("Vector3f")
				.def(luabind::constructor<float,float,float>())
				.def_readwrite("x", &Vector3f::x)
				.def_readwrite("y", &Vector3f::y)
				.def_readwrite("z", &Vector3f::z)
		];
		
		luabind::module(l) [
			luabind::class_<Vector2f>("Vector2f")
				.def(luabind::constructor<float,float>())
				.def_readwrite("x", &Vector2f::x)
				.def_readwrite("y", &Vector2f::y)
		];
		
		luabind::module(l) [
			luabind::class_<Vector2i>("Vector2i")
				.def(luabind::constructor<int,int>())
				.def_readwrite("x", &Vector2i::x)
				.def_readwrite("y", &Vector2i::y)
		];
		
		luabind::module(l) [
			luabind::class_<Block>("Block")
		];
		
		luabind::module(l) [
			luabind::class_<Block3D>("Block3D")
				.def("move", &Block3D::move)
				.def("rotate", &Block3D::rotate)
				.def("get_pos", &Block3D::get_pos)
				.def("set_pos", &Block3D::set_pos)
		];
		
		luabind::module(l) [
			luabind::class_<Block2D>("Block2D")
				.def("move", &Block2D::move)
				.def("rotate", &Block2D::rotate)
				.def("set_depth", &Block2D::set_depth)
				.def("set_tex_size", &Block2D::set_tex_size)
		];
		
		luabind::module(l) [
			luabind::class_<Floor>("Floor")
				.def("get_height", &Floor::get_height)
		];
		
		luabind::module(l) [
			luabind::class_<Sky>("Sky")
				.def("set_scale", &Sky::set_scale)
		];
		
		luabind::module(l) [
			luabind::class_<Camera>("Camera")
				.def("follow", &Camera::follow)
		];
		
		luabind::module(l) [
			luabind::class_<Display>("Display")
				.def("get_camera", &Display::get_camera)
		];
		
		luabind::module(l) [
			luabind::class_<Controller>("Controller")
				.def(luabind::constructor<string>())
		];
		
		luabind::module(l) [
			luabind::class_<World>("World")
				.def("new_block3d", &World::new_block3d)
				.def("new_character", &World::new_character)
				.def("new_blockHUD", &World::new_blockHUD)
				.def("new_floor", &World::new_floor)
				.def("new_sky", &World::new_sky)
				.def("get_display", &World::get_display)
				.def("reg_key_down", &World::reg_key_down)
				.def("reg_key_up", &World::reg_key_up)
				.def("reg_key_left", &World::reg_key_left)
				.def("reg_key_right", &World::reg_key_right)
		];
		
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
