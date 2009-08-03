#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <lua.hpp>

#include <string>

using namespace std;

class Controller
{
public:
	Controller(string function);
	~Controller();
	void set_lua(lua_State *l);
	void call();
private:
	string function;
	lua_State *l;
};

#endif
