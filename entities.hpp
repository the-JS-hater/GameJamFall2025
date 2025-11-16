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

enum struct MushroomType {
  TOADSTOOL,
  CHANTERELLE,
  BOLETUS,
};

enum struct EntityType {
  TURTLE,
  EGG,
  BATH,
  DONKEN,
  STICK,
  MUSHROOM,
};

enum struct BuildingType {
  NONE,
  UN_BUILT_BATH,
  BUILT_BATH,
  UN_BUILT_DONKEN,
  BUILT_DONKEN,
  STICK,
  MUSHROOM,
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
  float hunger;
  float built_percent;
  Entity* assigned_building = nullptr;
  Vector2 push_force = Vector2{0.0f, 0.0f};
  MushroomType mushroom_type;

  Vector2 get_center();
};

enum struct TileType {
  GRASS,
  SAND,
  RIVER,
};

enum struct TileImage {
  GRASS,
  GRASS_SAND_1,
  GRASS_SAND_2,
  GRASS_SAND_3,
  GRASS_SAND_4,
  SAND,
  RIVER_HORIZONTAL,
  RIVER_VERTICAL,
  RIVER_BOTTOM_LEFT,
  RIVER_TOP_LEFT,
  RIVER_BOTTOM_RIGHT,
  RIVER_TOP_RIGHT,
};

enum struct ActionType {
  DEFAULT,
  BUILD_BATH,
  BUILD_DONKEN,
};

struct World {
  float x,y,w,h;
  std::vector<Entity> entities;
  float waterAmount = 0.0f;
  float stick_amount = 0.0f;
  float burger_amount = 0.0f;
  float mushroom_amount = 0.0f;
  std::map<std::pair<int, int>, TileType> tiles;
  std::map<std::pair<int, int>, TileImage> tileImages;
  int tileSize = 128;
  std::set<unsigned int> selected_turtles;
  ActionType current_action = ActionType::DEFAULT;
  unsigned int next_id = 0;
};


void spawn_turtle(World&, float, float);
void spawn_egg(World&, float, float);
void create_stick(World&, float, float);
void create_sticks_and_mushrooms(World&);
void create_donken(World&, float, float);
void create_mushroom(World&, float, float);