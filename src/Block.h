#ifndef BLOCK_H_
#define BLOCK_H_

class Block
{
private:
protected:
	float z_depth;
public:
	virtual void display() =0;
	float get_z_depth() {return z_depth;}
};

#endif /*BLOCK_H_*/
