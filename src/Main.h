#ifndef MAIN_H_
#define MAIN_H_

#include "World.h"


void call_update();
void call_keys(unsigned char key, int x, int y);
void call_s_keys(int key, int x, int y);
void call_mouse(int button, int state, int x, int y);
void call_active_mouse(int x, int y);
void call_resize(int w, int h);
void call_timer(int v);
int main (int argc, char** argv);
void *threadFunc1(void*);

#endif /*MAIN_H_*/
