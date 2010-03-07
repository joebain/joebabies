#ifndef RECTANGLEF_H
#define RECTANGLEF_H

class Rectanglef
{
	public:
		Rectanglef() {
			right = 0;
			bottom = 0;
			top = 0;
			left = 0;
		}
		Rectanglef(float width, float height) {
			this->left = width;
			this->top = height;
			right = 0;
			bottom = 0;
		}
		Rectanglef(float right, float left, float bottom, float top) {
			this->right = right;
			this->left = left;
			this->top = top;
			this->bottom = bottom;
		}
		float right, left, top, bottom;
		float get_width() { return right - left; }
		float get_height() { return bottom - top; }
		float get_area() { return get_width() * get_height(); }
};

#endif // RECTANGLE_H
