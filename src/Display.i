%module Display
%include "Vector3f.i"
%{
class Display{
public:
	void translate(Vector3f t);
	void rotate(Vector3f r);
};
%}
class Display{
public:
	void translate(Vector3f t);
	void rotate(Vector3f r);
};
