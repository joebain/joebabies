%module Main
%include "World.i"
%{
void start();
World* get_world();
lua_State* get_lua();
%}
void start();
World* get_world();
lua_State* get_lua();
