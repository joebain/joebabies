#include "Controller.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <stdlib.h>
#include <iostream>

#include <luabind/luabind.hpp>

Controller::Controller(string function)
{
	this->function = function;
}

void Controller::set_lua(lua_State *l)
{
	this->l = l;
}

void Controller::call()
{
	try {
		luabind::call_function<void>(l, function.c_str(), 0);
	} catch(const std::exception &TheError) {
		cerr << TheError.what() << endl;
	}
}
