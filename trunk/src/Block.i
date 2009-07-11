%module Block
%include "Vector3f.i"
%{
class Block{
public:
	void set_pos(Vector3f pos);
	Vector3f get_pos();
};
%}
class Block{
public:
	void set_pos(Vector3f pos);
	Vector3f get_pos();
};
