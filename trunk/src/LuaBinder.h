#ifndef LUA_BINDER_H
#define LUA_BINDER_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>

class LuaBinder
{
private:

public:
	void bind(lua_State *l);
};

#endif
