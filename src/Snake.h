#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>

#include "Obj.h"
#include "Vector3f.h"
#include "Block.h"

class Snake
{
private:
	vector<Vector3f> b_pos;
	vector<Vector3f> b_rot;
	float speed;
	float min_dist;
	Vector3f forward;
	double jump_prog;
	Vector3f aim;
public:
	enum {HIGH, FAR, NORMAL} jump_type;
	Vector3f h_pos;
	Vector3f *up;
	Obj *head, *body, *tail;
	Snake();
	virtual ~Snake();
	void draw();
	void step();
	void move(Vector3f dir);
	void jump();
	void decide(Block *block);
	void wait();
	Vector3f set_speed(Vector3f dir);
};

#endif /*SNAKE_H_*/
