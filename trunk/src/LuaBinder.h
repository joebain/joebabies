#ifndef LUA_BINDER_H
#define LUA_BINDER_H

#include <lua.hpp>

#include <luabind/luabind.hpp>

class LuaBinder
{
private:

public:
	void bind(lua_State *l);
};

#endif
