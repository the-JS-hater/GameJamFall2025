#include "raylib.h"

#include "running.hpp"
#include "render.hpp"
#include "entities.hpp"


int main() 
{	
  SetTraceLogLevel(LOG_WARNING);
  
  unsigned int const initial_win_w = 1920u;
  unsigned int const initial_win_h = 1080u;
  InitWindow(initial_win_w, initial_win_h, "Title");
  SetTargetFPS(60);
  
  App app = init_application();
  app.world = init_world();
  { //NOTE: TEMP
    int const test_entities_count = 10;
    for (unsigned int id = 0; id < test_entities_count; ++id)
    {
      spawn_turtle(
        app.world,
        (float)GetRandomValue(0, app.world.w),
        (float)GetRandomValue(0, app.world.h)
      );
      spawn_egg(
        app.world,
        (float)GetRandomValue(0, app.world.w),
        (float)GetRandomValue(0, app.world.h)
      );
    }
    create_bath(app.world, 400, 400);
  }
  create_sticks_and_mushrooms(app.world);
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
