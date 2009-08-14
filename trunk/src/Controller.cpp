#include "Controller.h"

#include <stdlib.h>
#include <iostream>

#include <luabind/luabind.hpp>

Controller::Controller(string function)
{
	this->function = function;
}

Controller::~Controller()
{
	cout << "deleting the controller" << endl; //debugging was supposed to be better than this joe, what went wrong
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
		cerr << lua_tostring(l, -1) << endl;
	}
}
