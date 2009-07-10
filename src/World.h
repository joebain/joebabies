#ifndef WORLD_H_
#define WORLD_H_

#include "Block.h"
#include "Snake.h"
#include "Vector3i.h"
#include "Vector2i.h"
#include "Texture.h"

#include <vector>
#include <time.h>

#define GAP 2.2
#define GAP_BY2 1.1
#define XUP 0
#define XDN 1
#define YUP 2
#define YDN 3
#define ZUP 4
#define ZDN 5

class World
{
private:
	Block* ***world_3d;
	bool running;
	Vector3f move_to;
	void draw_block(Vector3f t, int c);
	void drawFloor();
	void make_new_block(Block *templ, Vector3i gp);
	time_t start, current;
	long last_ticks;
	enum {WAIT, JUMP, DECIDE} snake_state;
	double mod_f(double one, double two);
public:
	Vector3f dir;
	float y_lvl;
	int win_height, win_width;
	bool rotating;
	Vector3f rot_plus;
	Vector3f old_rot;
	Vector3i aim_rot, act_rot;
	float ratio;
	int block_count;
	int up;
	Vector3f up_v;
	Vector3i up_vi;
	bool up_known;
	Vector3f front, locked_front;
	bool draw_rot;
	Vector3f snake_dest, this_dest;
	Vector3f rot, tran;
	Texture* floor_tex;
	Vector2f proj_pos;
	void print_blocks();
	Block * good_blocks, * tmp_good_blocks;
	int ws_x, ws_y, ws_z;
	Snake *snake;
	Block *red_block,*blue_block,*white_block,*green_block,*clear_block, *null_block;
	Block* picked_block;
	Vector2i mouse_pos, mouse_down_at;
	enum { NONE, FIRST, PICKED, LAST } pick_state;
	Block* cur_block;
	World();
	virtual ~World();
	void main_loop();
	void draw();
	void trace();
	void load(char* f_name);
	void projectMouse();
	void setSnakeDest();
	void print_world();
	void sort_all_blocks();
	void rotate_w_mouse();
	void draw_rotation();
	void set_to_rotate();
	void find_up();
	void print(char* words);
	bool in_bounds(Vector3i loc);
	Vector3i find_space(Vector3i loc);
	bool good_space(Vector3i loc);
	Block* get_block(Vector3f);
};

#endif /*WORLD_H_*/
