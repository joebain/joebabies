#ifndef BLOCK2DTEXT_H
#define BLOCK2DTEXT_H

#include "Block2D.h"

#include <stdlib.h>

class Block2DText : public Block2D {
private:
	string text;
public:
	void display();
	void set_text(string text);
	string get_text();
};

#endif
