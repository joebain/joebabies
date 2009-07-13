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
};
%}
class World {
public:
	Block* new_block(std::string object, std::string texture);
	Display* get_display();
};
