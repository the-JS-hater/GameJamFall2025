#pragma once
#define APP_H

#include "raylib.h"
#include "entities.hpp"

#include <utility>

enum struct Scaling {
  BLACK_BARS,
  STRETCHED
}; 

struct Settings {
  Vector2 render_resolution;
  Scaling scaling;
};

enum struct AppState {
  GAMELOOP,
  EXIT,
  START,
  GAMEOVER,
  TURTORIAL,
};

struct App {
  World world;
  AppState state;
  RenderTexture2D render_target;
  Settings settings;
  Vector2 logical_resolution;
  Camera2D camera;
  // array_size should match nr. of enums in Actions, see running.hpp
  KeyboardKey input_map[4]; 
};

App init_application(void);
World init_world(void); 
std::pair<int, int> world_to_tile_pos(World const&, float, float);
void create_bath(World&, float, float);
