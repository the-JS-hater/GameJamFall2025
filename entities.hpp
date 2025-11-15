#pragma once
#define ENTITIES_H

#include "raylib.h"
#include <utility>
#include <set>
#include <map>
#include <vector>

enum struct TurtleState {
  IDLE,
  PATHING,
  COLLECTING,
  BATHING,
  BUILDING,
  EATING,
  DEAD,
};

enum struct EntityType {
  TURTLE,
  EGG,
  BATH,
  DONKEN,
  STICK,
};

enum struct BuildingType {
  NONE,
  UN_BUILT_BATH,
  BUILT_BATH,
  UN_BUILT_DONKEN,
  BUILT_DONKEN,
  STICK,
};

struct Entity {
  unsigned int id;
  EntityType type;
  float x,y,dx,dy,w,h;
  TurtleState state;
  Vector2 target;
  float egg_timer;
  BuildingType touching;
  float moistness;
  float built_percent;
  Entity* assigned_building = nullptr;
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

enum struct ActionType {
  MOVE,
  BUILD_BATH,
  BUILD_DONKEN,
};

struct World {
  float x,y,w,h;
  std::vector<Entity> entities;
  float waterAmount = 0.0f;
  float stick_amount = 0.0f;
  float burger_amount = 0.0f;
  std::map<std::pair<int, int>, TileType> tiles;
  std::map<std::pair<int, int>, TileImage> tileImages;
  int tileSize = 128;
  std::set<unsigned int> selected_turtles;
  ActionType current_action = ActionType::MOVE;
  unsigned int next_id = 0;
};


void spawn_turtle(World&, float, float);
void spawn_egg(World&, float, float);
void create_stick(World&, float, float);
void create_sticks(World&);
void create_donken(World&, float, float);
