#include "raylib.h"

#include "running.hpp"
#include "render.hpp"


int main() 
{	
  SetTraceLogLevel(LOG_ERROR);
  
  unsigned int const initial_win_w = 1920u;
  unsigned int const initial_win_h = 1080u;
  InitWindow(initial_win_w, initial_win_h, "Title");
  
  App app = init_application();
  app.world = init_world();
  { //NOTE: TEMP
    int const test_entities_count = 0;
    for (unsigned int id = 0; id < test_entities_count; ++id)
    {
      float const max_vel = 100.0f;
      float const min_size = 10.0f;
      float const max_size = 50.0f;
      app.world.entities.push_back(
        Entity {
          id,
          EntityType::TURTLE,
          (float)GetRandomValue(0.0f, (int)app.world.w),
          (float)GetRandomValue(0.0f, (int)app.world.h),
          
          (float)GetRandomValue(0.0f, max_vel),
          (float)GetRandomValue(0.0f, max_vel),
          (float)GetRandomValue(min_size, max_size),
          (float)GetRandomValue(min_size, max_size),
          TurtleState::PATHING,
          Vector2{(float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight())},
          0.0f,
          Color {
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            (unsigned char)GetRandomValue(0, 255),
            255
          }
        }
      );
    }
    float const egg_size = 50.0f;
    float const egg_timer = 5.0f;
    app.world.entities.push_back(
      Entity {
        test_entities_count,
        EntityType::EGG,
        0.0f, 0.0f, 0.0f, 0.0f,
        egg_size, egg_size,
        TurtleState::IDLE,
        Vector2 { 0.0f, 0.0f },
        egg_timer,
        RED
      }
    );
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
      case AppState::EXIT: 
      {
        goto exit_app;
      }
    }
  }
  exit_app:
  CloseWindow();
}
