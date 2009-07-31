#ifndef WORLD_H_
#define WORLD_H_

#include "Display.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Block.h"
#include "Block3D.h"
#include "Block2D.h"
#include "Block2DText.h"
#include "Obj.h"
#include "Texture.h"
#include "Controller.h"
#include "Floor.h"
#include "Vector2i.h"
#include "Timer.h"
#include "Sky.h"

#include <string>
#include <list>
#include <time.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <luabind/luabind.hpp>

class World
{
private:
	bool running;
	Display* d;
	lua_State *l;
	list<Texture> textures;
	list<Obj> objects;
	list<Block3D> blocks3d;
	list<Block2D> blocks2d;
	list<Block2DText> blocks2dtext;
	Floor floor;
	Sky sky;
	Controller *left, *right, *up, *down;
	Timer time;
public:
	World(Display *d, lua_State *l);
	virtual ~World();
	void main_loop();
	Block3D* new_block3d(string object, string texture);
	Block3D* new_character(string object, string texture);
	Block2D* new_blockHUD(Vector2f size, string texture);
	Block2DText* new_blockText(Vector2f pos, string text);
	Floor* new_floor(string height_map, string texture, float scale);
	Sky* new_sky(string texture);
	Display* get_display();
	void reg_key_left(Controller* c);
	void reg_key_right(Controller* c);
	void reg_key_down(Controller* c);
	void reg_key_up(Controller* c);
};

#endif /*WORLD_H_*/
