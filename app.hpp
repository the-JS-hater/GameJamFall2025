#pragma once
#define APP_H

#include "raylib.h"
#include <vector>
#include <map>

// TODO:(morgan) move entities and world into more appropriate header

enum struct TurtleState {
  IDLE,
  PATHING
};

struct Entity {
  unsigned int id;
  float x,y,dx,dy,w,h;
  TurtleState state;
  Vector2 target;
  Color color;
};

enum struct TileType {
  GRASS,
  RIVER,
};

struct World {
  float x,y,w,h;
  std::vector<Entity> entities;
  float waterAmount = 0.0f;
  std::map<std::pair<int, int>, TileType> tiles;
  /*
  std::vector<std::vector<TileType>> tiles {
    {TileType::GRASS, TileType::GRASS, TileType::RIVER, TileType::RIVER,TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::RIVER,TileType::RIVER, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::RIVER, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::GRASS, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::GRASS, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::RIVER, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::RIVER, TileType::RIVER, TileType::RIVER,TileType::RIVER, TileType::RIVER, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::RIVER, TileType::RIVER, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS},
    {TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS,TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS, TileType::GRASS}
  };*/
  int tileSize = 128;
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
};

struct App {
  World world;
  AppState state;
  RenderTexture2D render_target;
  Settings settings;
  Vector2 logical_resolution;
  Camera2D camera;
  // array_size should match nr. of enums in Actions, see running.hpp
  KeyboardKey input_map[6]; 

  // NOTE: add additional application-level global data
};

App init_application(void);
World init_world(void); 
