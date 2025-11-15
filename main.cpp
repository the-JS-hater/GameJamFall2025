#include "raylib.h"

#include "running.hpp"
#include "render.hpp"

static unsigned entity_id = 0;


void spawn_turtle(App& app, float x, float y)
{
  float const turtle_w = app.world.tileSize;
  float const turtle_h = 1.2f * turtle_w;
  Entity new_ent{ };
  new_ent.id = entity_id++;
  new_ent.type = EntityType::TURTLE; 
  new_ent.x = x;
  new_ent.y = y;
  new_ent.w = turtle_w;
  new_ent.h = turtle_h;
  new_ent.dx = 0.0f;
  new_ent.dy = 0.0f;
  new_ent.state = TurtleState::IDLE,
  app.world.entities.push_back(new_ent);
}

void spawn_egg(App& app, float x, float y)
{
  float const egg_size = app.world.tileSize;
  float const egg_timer = 5.0f;
  Entity new_ent { };
  new_ent.id = entity_id++;
  new_ent.type = EntityType::EGG; 
  new_ent.x = x;
  new_ent.y = y;
  new_ent.w = egg_size;
  new_ent.h = egg_size;
  new_ent.dx = 0.0f;
  new_ent.dy = 0.0f;
  new_ent.egg_timer = egg_timer;
  app.world.entities.push_back(new_ent);
}

void create_bath(World& world, float x, float y) {
  Entity bath {};
  bath.id = entity_id++;
  bath.type = EntityType::BATH;
  bath.x = x;
  bath.y = y;
  world.entities.push_back(bath);
}

int main() 
{	
  SetTraceLogLevel(LOG_ERROR);
  
  unsigned int const initial_win_w = 1920u;
  unsigned int const initial_win_h = 1080u;
  InitWindow(initial_win_w, initial_win_h, "Title");
  
  App app = init_application();
  app.world = init_world();
  { //NOTE: TEMP
    int const test_entities_count = 10;
    for (unsigned int id = 0; id < test_entities_count; ++id)
    {
      spawn_turtle(
        app,
        (float)GetRandomValue(0, app.world.w),
        (float)GetRandomValue(0, app.world.h)
      );
      spawn_egg(
        app,
        (float)GetRandomValue(0, app.world.w),
        (float)GetRandomValue(0, app.world.h)
      );
    }
    create_bath(app.world, 400, 400);
  }
  setup_controls(app.input_map);
  init_resources(app);
  
  ToggleBorderlessWindowed();
  
  while (!WindowShouldClose())
  { 
    switch (app.state) {
      case AppState::GAMELOOP: 
      {
        run_gameloop(app);
        break;
      }
      case AppState::PAUSED: 
      {
        run_pausemenu(app);
        break;
      }
      case AppState::START:
      { 
        run_startmenu(app);
        break;
      }
      case AppState::EXIT: 
      {
        goto exit_app;
      }
    }
  }
  exit_app:
  CloseWindow();
}
