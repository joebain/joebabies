%module Main
%include "World.i"
%{
void start();
World* get_world();
%}
void start();
World* get_world();
