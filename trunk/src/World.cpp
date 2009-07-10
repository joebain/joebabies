#include "World.h"

#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <math.h>

#include "Block.h"

World::World()
{
	pick_state = NONE;
	y_lvl = 0.0f;
	snake_dest.init(0,0,0);
	this_dest.init(0,0,0);
	
	null_block = new Block;
	null_block->pos.init(0,0,0);
	picked_block = null_block;
	
	draw_rot = false;
	rotating = false;
	rot_plus.init(0,0,0);
	old_rot.init(0,0,0);
	//good_blocks = new Block[10];
	
	dir.init(1,0,0);
	
	up = YUP;
	up_known = true;
	front.init(0,0,1);
	locked_front.init(0,0,1);
	up_v.init(0,1,0);
	up_vi.init(0,1,0);
	
	act_rot.init(0,0,0);
	rot.init(45,45,0);
	tran.init(0,0,-20);
	
	start = time(NULL);
	snake_state = WAIT;
	
	last_ticks = clock();
}

World::~World()
{
	delete world_3d;
}

void World::load(char* f_name)
{
	ws_x = 10;
	ws_y = 4;
	ws_z = 10;
	
	//good_blocks = new Block[ws_x*ws_y*ws_z];
	//good_blocks = new Block[10];
	tmp_good_blocks = new Block[ws_x*ws_y*ws_z];
	
	Vector3i gp;
	
	block_count = 0;
	int i, j, k;
		
	world_3d = new Block ***[ws_x];
	
	for (i = 0; i < ws_x ; i++) {
		world_3d[i] = new Block **[ws_y];
		
		gp.x = i;
		for (j = 0; j < ws_y ; j++) {
			
			gp.y = j;
			
			world_3d[i][j] = new Block*[ws_z];
			
			for (k = 0 ; k < ws_z ; k++) {
				gp.z = k;
				world_3d[i][j][k] = null_block;
				
				if (j == 0)
				switch (rand()%6) {
					case 0:
					make_new_block(red_block,gp);
					block_count++;
					break;
					case 1:
					make_new_block(blue_block,gp);
					block_count++;
					break;
					case 2:
					make_new_block(green_block,gp);
					block_count++;
					break;
				}
			}
		}
	}
	
	
	//now copy those sneaky blocks to an array
	//Block* tmp_good_blocks = new Block[block_count];
	
	cout << "made the good block array" << endl;
	/*
	for (i = 0 ; i < block_count ; i++) {
		tmp_good_blocks[i] = good_blocks[i];
	}
	*/
	//delete[] good_blocks;
	good_blocks = new Block[block_count];
	for (i = 0 ; i < block_count ; i++) {
		good_blocks[i] = tmp_good_blocks[i];
		cout << "block " << i << " is at ";
		good_blocks[i].pos.print();
		cout << endl;
		world_3d[good_blocks[i].grid_pos.x][good_blocks[i].grid_pos.y][good_blocks[i].grid_pos.z] = &(good_blocks[i]);
	}
	delete[] tmp_good_blocks;
	
	
	sort_all_blocks();
	
	snake->up = &up_v;
}

void World::make_new_block(Block *templ, Vector3i gp)
{	
	tmp_good_blocks[block_count] = *(new Block);
	
	tmp_good_blocks[block_count].null = false;
	
	tmp_good_blocks[block_count].set_obj(templ->get_obj());
	tmp_good_blocks[block_count].set_shadow(clear_block->get_obj());
	
	tmp_good_blocks[block_count].set_pos(gp.to_real());
	tmp_good_blocks[block_count].set_shadow_pos(gp);
	
	cout << "made a block (" << block_count << ") at ";
	tmp_good_blocks[block_count].pos.print();
	cout << " null? " << tmp_good_blocks[block_count].null << endl;
	
}

void World::draw()
{

	//cout << "drawing world(" << ws_x << "," << ws_y << "," << ws_z << ")" << endl;
	
	if (aim_rot.x > act_rot.x) act_rot.x += 5;
	else if (aim_rot.x < act_rot.x) act_rot.x -= 5;
	if (aim_rot.y > act_rot.y) act_rot.y += 5;
	else if (aim_rot.y < act_rot.y) act_rot.y -= 5;
	
	if ((aim_rot.x == act_rot.x) && (aim_rot.y == act_rot.y) && !up_known) find_up();
	
	glTranslatef(tran.x,tran.y,tran.z);
	
	glRotatef(rot.x, 1.0, 0.0, 0.0);
	glRotatef(rot.y, 0.0, 1.0, 0.0);
	
    glRotatef(act_rot.x, 1.0, 0.0, 0.0);
	glRotatef(act_rot.y, 0.0, 1.0, 0.0);
	  
    
    
    glTranslatef(-(ws_x/2 * GAP),-(ws_y/2 * GAP),-(ws_z/2 * GAP));
	
	drawFloor();
	
	glColor3f(1,1,0);
	glBegin(GL_TRIANGLES);
	/*
	glVertex3f(snake_dest.x,snake_dest.y+1,snake_dest.z);
	glVertex3f(snake_dest.x+1,snake_dest.y+1,snake_dest.z);
	glVertex3f(snake_dest.x,snake_dest.y+1,snake_dest.z+1);
	
	glVertex3f(this_dest.x,this_dest.y+1,this_dest.z);
	glVertex3f(this_dest.x+1,this_dest.y+1,this_dest.z);
	glVertex3f(this_dest.x,this_dest.y+1,this_dest.z+1);
	*/
	glEnd();

	//snake->draw();

	int i;
	for (i = 0; i < block_count ; i++) {
		//cout << "displaying block " << i << endl;
		good_blocks[i].display();
	}
	
	//if (draw_rot) draw_rotation();
}

void World::drawFloor()
{
	glBindTexture(GL_TEXTURE_2D, floor_tex->get_tex_num());
	
	glBegin(GL_QUADS);
	
	int i, j;
	
	for (i = 0 ; i < ws_x ; i++) {
		for (j = 0 ; j < ws_z ; j++) {
			
			glVertex3f(i*GAP-(GAP_BY2-0.1),-1,j*GAP-(GAP_BY2-0.1));
			glTexCoord2f(0,1);
			glNormal3f(0,1,0);
			glVertex3f(i*GAP-(GAP_BY2-0.1),-1,j*GAP+GAP_BY2);
			glTexCoord2f(0,0);
			glNormal3f(0,1,0);
			glVertex3f(i*GAP+GAP_BY2,-1,j*GAP+GAP_BY2);
			glTexCoord2f(1,0);
			glNormal3f(0,1,0);
			glVertex3f(i*GAP+GAP_BY2,-1,j*GAP-(GAP_BY2-0.1));
			glTexCoord2f(1,1);
			glNormal3f(0,1,0);
		}
	}
	glEnd();
}

void World::trace()
{
	
	glTranslatef(tran.x,tran.y,tran.z);
	
	glRotatef(rot.x, 1.0, 0.0, 0.0);
	glRotatef(rot.y, 0.0, 1.0, 0.0);
	
    glRotatef(act_rot.x, 1.0, 0.0, 0.0);
	glRotatef(act_rot.y, 0.0, 1.0, 0.0);  
	
	glTranslatef(-(ws_x/2 * GAP),-(ws_y/2 * GAP),-(ws_z/2 * GAP));
	
	int i;
	for (i = 0; i < block_count ; i++) {
		glLoadName(i);
		good_blocks[i].display();
	} 
}

void World::print_blocks()
{
	int i;
	for (i = 0 ; i < block_count ; i ++) {
		good_blocks[i].pos.print();
		cout << endl;
	}
	
}

void World::print(char* words)
{
	cout << words;
}

void World::main_loop()
{
	//running = true;
	
	//while(running) {
		
	sort_all_blocks();
	
	//cout << "this is in main" << endl;
	//print_blocks();
	
		//cout << "Stepping\n";
		//Snake control:
		//double delta = ((double)(clock()-last_ticks))/((double)CLOCKS_PER_SEC);
		//cout << "delta " << delta << endl;
		//last_ticks = clock();
		//cout << "last ticks " << last_ticks << " per sec " << CLOCKS_PER_SEC << endl;
		current = time(NULL);
		double step = mod_f(difftime(current,start),5.0); 
		//cout << "step is " << step << endl;
		if (step >= 0.0 && step <= 2.0 && snake_state == WAIT) {
			cout << "jump!!" << endl;
			snake_state = JUMP;
			snake->jump();
		}
		else if (step >= 3.0 && step <= 4.0 && snake_state == JUMP) {
			cout << "decide!!" << endl;
			snake_state = DECIDE;
			snake->decide(get_block(snake->h_pos + (up_v*-1)));
		}
		else if (step >= 4.0 && step <= 5.0 && snake_state == DECIDE) {
			cout << "wait!!" << endl;
			snake_state = WAIT;
		}
		
		snake->step();
		
		/*
		if (snake->h_pos.x/GAP > ws_x-1) {
			snake->h_pos.x -= 0.2;
			dir.init(0,0,1);
		}
		else if (snake->h_pos.x/GAP < 0) {
			snake->h_pos.x += 0.2; 
			dir.init(0,0,-1);
		}
		if (snake->h_pos.z/GAP > ws_z-1) {
			snake->h_pos.z -= 0.2;
			dir.init(-1,0,0);
		}
		else if (snake->h_pos.z/GAP < 0) {
			snake->h_pos.z += 0.2;
			dir.init(1,0,0);
		}
		snake->move(dir);
		
		*/
		
		
		//cout << "snake head at ";
		//snake->h_pos.print();
		//cout << endl;
		
		//the next, curent and last tile we will go over
		//Block* last_b = world_3d[(int)((snake->h_pos.x-dir.x)/GAP)][(int)((snake->h_pos.y-dir.y)/GAP)][(int)((snake->h_pos.z-dir.z)/GAP)];
		//Block* this_b = world_3d[(int)((snake->h_pos.x)/GAP)][(int)((snake->h_pos.y)/GAP)][(int)((snake->h_pos.z)/GAP)];
		//Block* next_b = world_3d[(int)((snake->h_pos.x+dir.x)/GAP)][(int)((snake->h_pos.y+dir.y)/GAP)][(int)((snake->h_pos.z+dir.z)/GAP)];
		
		//if (!next_b->null) cout << "a block is in front" << endl;
		
		//if the user is dragging
		
		Vector3i* cbp;
		Vector3i loc;
		if (pick_state != NONE) {
			cbp = &(picked_block->grid_pos);
		}
		switch (pick_state) {
			case NONE:
			//cout << "no pick" << endl;
			break;
			case FIRST:
			
			cout << "taken block from " << cbp->x << "," << cbp->y << "," << cbp->z << endl;
			
			world_3d[picked_block->grid_pos.x][picked_block->grid_pos.y][picked_block->grid_pos.z] = null_block;
		    
			//print_world();
			pick_state = PICKED;
			
			break;
			case PICKED:
			
			switch (up) {
				case YUP:
				move_to.y = picked_block->pos.y;
				move_to.x = proj_pos.x;
				move_to.z = proj_pos.y;
				break;
				case YDN:
				move_to.y = picked_block->pos.y;
				move_to.x = proj_pos.x;
				move_to.z = proj_pos.y;
				break;
				case XUP:
				move_to.x = picked_block->pos.x;
				move_to.z = proj_pos.x;
				move_to.y = proj_pos.y;
				break;
				case XDN:
				move_to.x = picked_block->pos.x;
				move_to.z = proj_pos.x;
				move_to.y = proj_pos.y;
				break;
				case ZUP:
				move_to.z = picked_block->pos.z;
				move_to.y = proj_pos.y;
				move_to.x = proj_pos.x;
				break;
				case ZDN:
				move_to.z = picked_block->pos.z;
				move_to.y = proj_pos.y;
				move_to.x = proj_pos.x;
				break;
			}
			
			
			/*
			//if we go over the boudaries
			if (move_to.x > (ws_x-1)*GAP) move_to.x = (ws_x-1)*GAP;
			else if (move_to.x < 0) move_to.x = 0;
			if (move_to.z > (ws_z-1)*GAP) move_to.z = (ws_z-1)*GAP;
			else if (move_to.z < 0) move_to.z = 0;
			if (move_to.y > (ws_y-1)*GAP) move_to.y = (ws_y-1)*GAP;
			else if (move_to.y < 0) move_to.y = 0;
			
			while (!world_3d[(int)(move_to.x/GAP)][(int)(move_to.y/GAP)][(int)(move_to.z/GAP)]->null) {
				move_to.x += up_v.x*GAP;
				move_to.y += up_v.y*GAP;
				move_to.z += up_v.z*GAP;
			}
			while (!world_3d[(int)(move_to.x/GAP)-up_v.x][(int)(move_to.y/GAP)-up_v.y][(int)(move_to.z/GAP)-up_v.z]->null) {
				move_to.x += up_v.x*GAP;
				move_to.y += up_v.y*GAP;
				move_to.z += up_v.z*GAP;
			}
			*/		
			//cout << "moving to " << move_to.x << "," << move_to.z << "," << move_to.y << endl;
			picked_block->set_pos(move_to);
			//cur_wx = (int)(picked_block->shadow_pos.x/GAP);
			//cur_wz = (int)(picked_block->shadow_pos.z/GAP);
			//cout << "setting shadow y to " << world[cur_wx][cur_wz] << " at " << cur_wx << "," << cur_wz << endl;
			//picked_block->shadow_pos.y = world [cbp->x][cbp->z]*GAP;
			loc.init((move_to.x+GAP/2)/GAP,(move_to.y+GAP/2)/GAP,(move_to.z+GAP/2)/GAP);
			
			loc = find_space(loc);
			if (loc.x != -1) {
				picked_block->set_shadow_pos(loc);
				
			} 
			 
			picked_block->has_shadow = true;
			picked_block->picked = true;
			
			break;
			case LAST:
			
			//picked_block->set_pos(picked_block->shadow_pos);
			//cur_wx = (int)(picked_block->shadow_pos.x/GAP);
			//cur_wz = (int)(picked_block->shadow_pos.z/GAP);
			cout << "letting go of block at " << cbp->x << "," << cbp->y << "," << cbp->z << endl;
			
			world_3d[picked_block->shadow_pos.x][picked_block->shadow_pos.y][picked_block->shadow_pos.z] = &(*picked_block);
			
			//print_world();
			picked_block->has_shadow = false;
			picked_block->picked = false;
			
			pick_state = NONE;
			
			break;
		}
		
		glutPostRedisplay();
		/*
		while ((double)(clock()-last_ticks)/(double)CLOCKS_PER_SEC < 0.0015) {
			usleep(100);
			cout << "time: " << (double)(clock()-last_ticks)/(double)CLOCKS_PER_SEC << endl;
		}
		*/
		//usleep(5000);
		
	//}
	
}

bool World::good_space(Vector3i loc)
{
	if (in_bounds(loc)) {
		if (world_3d[loc.x][loc.y][loc.z]->null) return true;
	}
	return false;
}

bool World::in_bounds(Vector3i loc)
{
	if (loc.x >= 0 && loc.x < ws_x
	 && loc.y >= 0 && loc.y < ws_y
	 && loc.z >= 0 && loc.z < ws_z) return true;
	else return false;
}

Vector3i World::find_space(Vector3i loc)
{
	if (good_space(loc-up_vi)) return find_space(loc-up_vi);
	else if (good_space(loc)) return loc;
	else if (in_bounds(loc+up_vi)) return find_space(loc+up_vi);
	else {
		Vector3i no_loc;
		no_loc.init(-1,-1,-1);
		return no_loc;
	}
}

Block* World::get_block(Vector3f v)
{
	cout << "at ";
	v.print();
	cout << endl;
	
	if (v.x/GAP < 0 || v.x/GAP > ws_x || v.y/GAP < 0 || v.y/GAP > ws_y || v.z/GAP < 0 || v.z/GAP > ws_z) {
		cout << "out of bounds" << endl;
		return red_block; 
	}
	cout << "not out of bounds" << endl;
	
	Block *b =  world_3d[(int)(v.x/GAP)][(int)(v.y/GAP)][(int)(v.z/GAP)];
	
	cout << "att " << (int)(v.x/GAP) << "," << (int)(v.y/GAP) << "," << (int)(v.z/GAP) << endl;
	
	if (b->null) return red_block;
	
	return b;
}

void World::sort_all_blocks()
{
	//print_world();
	
	int cx = 0, cy = 0, cz = 0;
	switch (up) {
		case YUP:
		cy = -1;
		break;
		case YDN:
		cy = 1;
		break;
		case XDN:
		cx = 1;
		break;
		case XUP:
		cx = -1;
		break;
		case ZDN:
		cz = 1;
		break;
		case ZUP:
		cz = -1;
		break;
	}
	
	int i;
	for (i = 0 ; i < block_count ; i++) {
		if (good_blocks[i].falling == false) {
			int x = good_blocks[i].grid_pos.x+cx, y = good_blocks[i].grid_pos.y+cy, z = good_blocks[i].grid_pos.z+cz;
			if (x >= 0 && x < ws_x
			 && y >= 0 && y < ws_y
			 && z >= 0 && z < ws_z) {
				if (world_3d[x][y][z]->null) {
					world_3d[good_blocks[i].grid_pos.x][good_blocks[i].grid_pos.y][good_blocks[i].grid_pos.z] = null_block;
					world_3d[x][y][z] = &(good_blocks[i]);
					Vector3i new_pos;
					new_pos.init(x,y,z);
					good_blocks[i].fall_to(new_pos);					
				}
			}
		}
	}
	
	//print_world();
}

void World::print_world()
{
	cout << "---" << endl;
	int i,j,k;
	for (j = 0 ; j < ws_x ; j++) {
		for (i = 0; i < ws_y ; i++) {
			for (k = 0 ; k < ws_z ; k++) {
				cout << world_3d[j][i][k]->null << " ";	
			}
			cout << endl;
		}
		cout << "--" << endl;
	}
	cout << "---" << endl;
}

void World::setSnakeDest()
{
	snake_dest.x = proj_pos.x;
	snake_dest.z = proj_pos.y;
}

void World::projectMouse()
{
	int h = (picked_block->grid_pos * up_vi).sum();
	
	GLdouble x1, y1, z1, x2, y2, z2;
	
	int viewport[4];
    double mvmatrix[16];
    double projmatrix[16];
    
	glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	
	//gets the x,y,z at the two clipping planes
	gluUnProject(mouse_pos.x, glutGet(GLUT_WINDOW_HEIGHT)-mouse_pos.y, 0.0, mvmatrix, projmatrix, viewport, &x1, &y1, &z1);
	gluUnProject(mouse_pos.x, glutGet(GLUT_WINDOW_HEIGHT)-mouse_pos.y, 1.0, mvmatrix, projmatrix, viewport, &x2, &y2, &z2);
	
	//floor is at 0 so find x & z when y = 0
	//y = y1+(y2-y1)*tmp
	double tmp;
	switch (up) {
		case YUP:
		tmp = ((h*GAP)-y1)/(y2-y1);
		proj_pos.x = x1 + (x2-x1)*tmp;
		proj_pos.y = z1 + (z2-z1)*tmp;
		break;
		case YDN:
		tmp = ((h*GAP)-y1)/(y2-y1);
		proj_pos.x = x1 + (x2-x1)*tmp;
		proj_pos.y = z1 + (z2-z1)*tmp;
		break;
		case XUP:
		tmp = ((h*GAP)-x1)/(x2-x1);
		proj_pos.x = z1 + (z2-z1)*tmp;
		proj_pos.y = y1 + (y2-y1)*tmp;
		break;
		case XDN:
		tmp = ((h*GAP)-x1)/(x2-x1);
		proj_pos.x = z1 + (z2-z1)*tmp;
		proj_pos.y = y1 + (y2-y1)*tmp;
		break;
		case ZUP:
		tmp = ((h*GAP)-z1)/(z2-z1);
		proj_pos.x = y1 + (y2-y1)*tmp;
		proj_pos.y = x1 + (x2-x1)*tmp;
		break;
		case ZDN:
		tmp = ((h*GAP)-z1)/(z2-z1);
		proj_pos.x = y1 + (y2-y1)*tmp;
		proj_pos.y = x1 + (x2-x1)*tmp;
		break;
	}
	//cout << "Projected mouse pos is " << proj_pos.x << "," << proj_pos.y << endl; 
	
}

void World::draw_rotation()
{
	
    //glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    
	
	glLoadIdentity();
	
	glOrtho(0.0,win_width,win_height,0.0,-4000.0,4000.0);
	
	glRotatef(0, 1.0, 0.0, 0.0);
	glRotatef(0, 0.0, 1.0, 0.0);  
	glRotatef(0, 0.0, 0.0, 1.0);
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	/*
	glVertex3f(mouse_down_at.x,mouse_down_at.y,0);
	glVertex3f(mouse_pos.x, mouse_pos.y,0);
	glVertex3f(0,0,0);
	*/
	glVertex3f(mouse_down_at.x,mouse_down_at.y,0);
	glVertex3f(mouse_pos.x, mouse_pos.y,0);
	glVertex3f(win_width/2,win_height/2,0);
	
	glEnd();
	
	glPopMatrix();
	
	//set the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45,ratio,1,1000);
	
	//cout << "set ratio to " << ratio << endl;
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void World::set_to_rotate()
{
	locked_front.init(0,0,1);
	locked_front.rotate(rot);
	locked_front.abs();
	
	cout << "lf " << locked_front.x << " " << locked_front.y << " " << locked_front.z << endl;
	
	locked_front.snap();
	
	cout << "lf " << locked_front.x << " " << locked_front.y << " " << locked_front.z << endl;
}

void World::find_up()
{
	up_v.init(0,1,0);
	cout << "act rot " << act_rot.x << " " << act_rot.y << " " << act_rot.z << endl;
	up_v.rotate(act_rot.to_f());
	cout << "up " << up_v.x << " " << up_v.y << " " << up_v.z << endl;
	up_v.snap();
	up_vi.init(up_v.x,up_v.y,up_v.z);
	cout << "up " << up_v.x << " " << up_v.y << " " << up_v.z << endl;
	if (up_v.x == 1) up = XUP;
	else if (up_v.x == -1) up = XDN;
	else if (up_v.y == 1) up = YUP;
	else if (up_v.y == -1) up = YDN;
	else if (up_v.z == 1) up = ZUP;
	else if (up_v.z == -1) up = ZDN;
	
	up_known = true;
}

void World::rotate_w_mouse()
{
	
	Vector2i centre;
	centre.x = win_width/2;
	centre.y = win_height/2;
	float r = centre.dir_between(mouse_down_at).angle_between(centre.dir_between(mouse_pos));
	/*
	front.init(0,0,1);
	front.rotate(rot);
	*/
	rot_plus.x = r*locked_front.x;
	rot_plus.y = r*locked_front.y;
	rot_plus.z = r*locked_front.z;
	
	//float x_r = abs(180-rot.x), y_r = abs(180-rot.y), z_r = abs(180-rot.z);
	
	//if (x_r < 45 && z_r < 45) up = YUP;
	//else if (x_r < 45 && z_r < 45) up = YDN;
	
}

double World::mod_f(double one, double two)
{
	return one - (double)(((int)(one/two)) * two);
}
