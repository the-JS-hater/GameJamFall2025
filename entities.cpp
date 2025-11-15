#include "entities.hpp"


void spawn_turtle(World& world, float x, float y)
{
  float const turtle_w = world.tileSize;
  float const turtle_h = 1.2f * turtle_w;
  Entity new_ent{ };
  new_ent.id = world.next_id++;
  new_ent.type = EntityType::TURTLE; 
  new_ent.x = x;
  new_ent.y = y;
  new_ent.w = turtle_w;
  new_ent.h = turtle_h;
  new_ent.dx = 0.0f;
  new_ent.dy = 0.0f;
  new_ent.state = TurtleState::IDLE,
  new_ent.moistness = 100.0f;
  new_ent.hunger = 100.0f;
  world.entities.push_back(new_ent);
}

void spawn_egg(World& world, float x, float y)
{
  float const egg_size = world.tileSize;
  float const egg_timer = 5.0f;
  Entity new_ent { };
  new_ent.id = world.next_id++;
  new_ent.type = EntityType::EGG; 
  new_ent.x = x;
  new_ent.y = y;
  new_ent.w = egg_size;
  new_ent.h = egg_size;
  new_ent.dx = 0.0f;
  new_ent.dy = 0.0f;
  new_ent.egg_timer = egg_timer;
  world.entities.push_back(new_ent);
}

void create_stick(World& world, float x, float y) {
  Entity stick;
  stick.id = world.next_id++;
  stick.type = EntityType::STICK;
  stick.x = x;
  stick.y = y;
  stick.w = world.tileSize;
  stick.h = world.tileSize;
  world.entities.push_back(stick);
}

void create_sticks(World& world) {
  for (int y = -30; y < 30; ++y) {
    for (int x = -30; x < 30; ++x) {
      if (GetRandomValue(0, 10) == 0 && world.tiles.find(std::make_pair(x, y)) == world.tiles.end()) {
        create_stick(world, x * world.tileSize, y * world.tileSize);
      }
    }
  }
}

void create_donken(World& world, float x, float y) {
  Entity donken;
  donken.id = world.next_id++;
  donken.type = EntityType::DONKEN;
  donken.x = x;
  donken.y = y;
  donken.w = world.tileSize;
  donken.h = world.tileSize;
  donken.built_percent = 0.0f;
  world.entities.push_back(donken);
}
