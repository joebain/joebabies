#ifndef VECTOR2I_H_
#define VECTOR2I_H_

#define R2D 57.295779506

class Vector2i
{
public:
	int x, y;
	Vector2i();
	virtual ~Vector2i();
	float angle_between(Vector2i other);
	Vector2i dir_between(Vector2i other);
	float mag();
};

#endif /*VECTOR2I_H_*/
