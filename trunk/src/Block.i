%module Block
%include "Vector3f.i"
%{
class Block{
public:
	void set_pos(Vector3f pos);
	Vector3f get_pos();
	void move(Vector3f move);
};
%}
class Block{
public:
	void set_pos(Vector3f pos);
	Vector3f get_pos();
	void move(Vector3f move);
};
