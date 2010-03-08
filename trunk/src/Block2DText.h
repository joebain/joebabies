#ifndef BLOCK2DTEXT_H
#define BLOCK2DTEXT_H

#define C_SPACE 0.142857143

#include "Block2D.h"

#include <stdlib.h>

class Block2DText : public Block2D {
private:
	string text;
public:
	Block2DText() : Block2D(0) {}
	void display();
	void set_text(string text);
	string get_text();
	Vector2f get_tcs(char c);
	bool operator==(const Block2DText& rhs);
};

#endif
