#ifndef CONTROLLER_H
#define CONTROLLER_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>

using namespace std;

class Controller
{
public:
	Controller(string function);
	void set_lua(lua_State *l);
	void call();
private:
	string function;
	lua_State *l;
};

#endif
