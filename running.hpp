#pragma once
#define RUNNING_H

#include "app.hpp"

enum struct Actions {
  MOVE_LEFT   = 0,
  MOVE_RIGHT  = 1,
  MOVE_UP     = 2,
  MOVE_DOWN   = 3,
};

void run_gameloop(App&);
void run_pausemenu(App&);

void process_turtle(Entity&, float const, App&); 

// NOTE:(raylib.h) Use GetKeyPressed() to allow redefining
void setup_controls(KeyboardKey*); 
bool is_actionkey_pressed(Actions, KeyboardKey*);
bool is_actionkey_down(Actions, KeyboardKey*); 
