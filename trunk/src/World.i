%module World
%naturalvar;
%include "std_string.i"
%include "Block.i"
%include "Display.i"
%{
class World {
public:
	Block* new_block(std::string object, std::string texture);
	Display* get_display();
	void set_lua(lua_State *L);
};
%}
class World {
public:
	Block* new_block(std::string object, std::string texture);
	Display* get_display();
	void set_lua(lua_State *L);
};
