#include "raylib.h"

#include "running.hpp"


int main() 
{	
  SetTraceLogLevel(LOG_ERROR);
  
  unsigned int const initial_win_w = 1366u;
  unsigned int const initial_win_h = 768u;
  InitWindow(initial_win_w, initial_win_h, "Title");
  
  App app = init_application();
  app.world = init_world();
  { //NOTE: TEMP
    int const test_entities_count = 100;
    for (unsigned int id = 0; id < test_entities_count; ++id)
    {
      float const max_vel = 100.0f;
      float const min_size = 10.0f;
      float const max_size = 50.0f;
      app.world.entities.push_back(
        Entity {
          id,
          (float)GetRandomValue(0.0, (int)app.world.w),
          (float)GetRandomValue(0.0, (int)app.world.h),
          
          (float)GetRandomValue(0.0, max_vel),
          (float)GetRandomValue(0.0, max_vel),
          (float)GetRandomValue(min_size, max_size),
          (float)GetRandomValue(min_size, max_size),
          TurtleState::PATHING,
          Vector2{(float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight())},
          Color {
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255
          }
        }
      );
    }
  }
  setup_controls(app.input_map);
  
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
      case AppState::EXIT: 
      {
        goto exit_app;
      }
    }
  }
  exit_app:
  CloseWindow();
}
