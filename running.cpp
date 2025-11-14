#include "raylib.h"
#include "raymath.h"
#include "math.h"

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"


void run_gameloop(App& app)
{
  while (app.state == AppState::GAMELOOP)
  {
    float const dt = GetFrameTime();
    // === INPUT ===
    
    if (IsKeyPressed(KEY_ESCAPE)) {
      app.state = AppState::EXIT;
      return;
    }
    if (IsKeyPressed(KEY_P)) {
      app.state = AppState::PAUSED;
      return;
    }
    if (IsKeyPressed(KEY_F)) {
      ToggleBorderlessWindowed();
    }
    if (IsKeyPressed(KEY_Q)) {
      // NOTE: (morgan) does not work on home PC
      ToggleFullscreen();
    }
    
    static Vector2 target_pos = {
      (float)GetScreenWidth() / 2.0f, 
      (float)GetScreenHeight() / 2.0f
    };
    
    { //NOTE: TEMP

      float const camera_speed = 300.0f;
      if (is_actionkey_down(Actions::MOVE_LEFT, app.input_map)) 
      {
        target_pos.x -= dt * camera_speed;
      }
      if (is_actionkey_down(Actions::MOVE_RIGHT, app.input_map)) 
      {
        target_pos.x += dt * camera_speed;
      }
      if (is_actionkey_down(Actions::MOVE_UP, app.input_map)) 
      {
        target_pos.y -= dt * camera_speed;
      }
      if (is_actionkey_down(Actions::MOVE_DOWN, app.input_map)) 
      {
        target_pos.y += dt * camera_speed;
      }
    }

    // === UPDATE ===
    
    float const lerp_amount = 0.5f;
    app.camera.target.x = Lerp(app.camera.target.x, target_pos.x, lerp_amount);
    app.camera.target.y = Lerp(app.camera.target.y, target_pos.y, lerp_amount);

    // === RENDER ===
    
    render_scene(app);
    render_to_screen(app);
  }
}

void run_pausemenu(App& app)
{
  while (app.state == AppState::PAUSED) 
  {
    // === INPUT ===
    
    if (IsKeyPressed(KEY_ESCAPE)) {
      app.state = AppState::EXIT;
      return;
    }
    if (IsKeyPressed(KEY_G)) {
      app.state = AppState::GAMELOOP;
      return;
    }
    
    // === RENDERING ===
    
    render_pause_menu(app.render_target);
    render_to_screen(app);
  }
}

void setup_controls(KeyboardKey* input_map) 
{
  input_map[(int)Actions::MOVE_LEFT] = KEY_A;
  input_map[(int)Actions::MOVE_RIGHT] = KEY_D;
  input_map[(int)Actions::MOVE_UP] = KEY_W;
  input_map[(int)Actions::MOVE_DOWN] = KEY_S;
}

bool is_actionkey_pressed(Actions action, KeyboardKey* input_map) 
{
  return IsKeyPressed(input_map[(int)action]);
}

bool is_actionkey_down(Actions action, KeyboardKey* input_map) 
{
  return IsKeyDown(input_map[(int)action]);
}
