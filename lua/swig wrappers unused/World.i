%module World
%naturalvar;
%include "std_string.i"
%include "Block.i"
%{
class World {
public:
	Block* new_block(std::string object, std::string texture);
};
%}
class World {
public:
	Block* new_block(std::string object, std::string texture);
};
