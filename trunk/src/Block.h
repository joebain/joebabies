/* A pretty basic class which all the game 'objects' are sub classes of.
 * All this means is that everything has a display method and a depth value
 * for sorting. Though if the thing doesn't need to be depth sorted then
 * you don't need to worry about z_depth.
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "Vector3f.h"

class Block
{
private:
protected:
	float z_depth; //used for sorting transparent stuff
	Vector3f centre;
public:
	virtual void display() =0; //all blocks display something
	float get_z_depth() {return z_depth;}
	virtual Vector3f get_centre() { return centre; }
	float cam_dist;
};

#endif /*BLOCK_H_*/
