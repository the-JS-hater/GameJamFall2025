#pragma once
#define APP_H

#include "raylib.h"
#include <vector>
#include <map>
#include <set>

// TODO:(morgan) move entities and world into more appropriate header
enum struct TurtleState {
  IDLE,
  PATHING,
  COLLECTING,
  BATHING,
};

enum struct EntityType {
  TURTLE,
  EGG,
  BATH,
};

enum struct BuildingType {
  NONE,
  BATH,
};

struct Entity {
  unsigned int id;
  EntityType type;
  float x,y,dx,dy,w,h;
  TurtleState state;
  Vector2 target;
  float egg_timer;
  BuildingType touching;
};

enum struct TileType {
  GRASS,
  RIVER,
};

enum struct TileImage {
  GRASS,
  RIVER_HORIZONTAL,
  RIVER_VERTICAL,
  RIVER_BOTTOM_LEFT,
  RIVER_TOP_LEFT,
  RIVER_BOTTOM_RIGHT,
  RIVER_TOP_RIGHT,
};

struct World {
  float x,y,w,h;
  std::vector<Entity> entities;
  float waterAmount = 0.0f;
  std::map<std::pair<int, int>, TileType> tiles;
  std::map<std::pair<int, int>, TileImage> tileImages;
  int tileSize = 128;
  std::set<unsigned int> selected_turtles;
  // NOTE: add additional game-level global data
};

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
  PAUSED,
  EXIT,
  START,
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

  // NOTE: add additional application-level global data
};

App init_application(void);
World init_world(void); 
std::pair<int, int> world_to_tile_pos(World const& world, float x, float y);
