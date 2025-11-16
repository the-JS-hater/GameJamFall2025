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
  setup_controls(app.input_map);
  init_resources(app);
  setup_world(app);
  
  ToggleBorderlessWindowed();
  
  while (!WindowShouldClose())
  { 
    switch (app.state) {
      case AppState::GAMELOOP: 
        run_gameloop(app);
        break;
      case AppState::START:
        run_startmenu(app);
        break;
      case AppState::GAMEOVER:
        run_gameover(app);
        break;
      case AppState::TURTORIAL:
        run_tutorial(app);
        break;
      case AppState::EXIT: 
        goto exit_app;
    }
  }
  exit_app:
  CloseWindow();
}
