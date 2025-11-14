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
      if (is_actionkey_down(Actions::ZOOM_IN, app.input_map)) 
      {
        app.camera.zoom -= dt * 0.5f;
      }
      if (is_actionkey_down(Actions::ZOOM_OUT, app.input_map)) 
      {
        app.camera.zoom += dt * 0.5f;
      }
    }

    // === UPDATE ===
    
    for (Entity& ent : app.world.entities) 
    {
      int const world_lim_x = (int)app.world.w;
      int const world_lim_y = (int)app.world.h;
      if (world_lim_x < ent.x) ent.dx *= -1;
      if (world_lim_y < ent.y) ent.dy *= -1;
      for (Entity& ent2 : app.world.entities) 
      {
        if (ent2.id == ent.id) continue;
        
        if (CheckCollisionRecs(
          Rectangle { ent.x, ent.y, ent.size, ent.size },
          Rectangle { ent2.x, ent2.y, ent2.size, ent2.size }
        ))
        {
          Vector2 pos1 = { ent.x, ent.y };
          Vector2 pos2 = { ent2.x, ent2.y };
          Vector2 dv1 = { ent.dx, ent.dy };
          Vector2 dv2 = { ent2.dx, ent2.dy };
          Vector2 rel_vel = Vector2Subtract(dv1, dv2);
          Vector2 collision_norm = Vector2Subtract(pos1, pos2);
          float dist_sqrt = Vector2LengthSqr(collision_norm);

          if (dist_sqrt == 0.0f) continue;
          collision_norm = 
            Vector2Scale(collision_norm, 1.0f / sqrtf(dist_sqrt));

          if (Vector2DotProduct(rel_vel, collision_norm) >= 0.0f) continue; 
        
          float const mass_factor = 1.0f;
          float impact = 
            Vector2DotProduct(rel_vel, collision_norm) * mass_factor;
          Vector2 vel_change = Vector2Scale(collision_norm, impact);
          dv1 = Vector2Subtract(dv1, vel_change);
          dv2 = Vector2Add(dv2, vel_change);

          ent.dx = dv1.x;
          ent.dy = dv1.y;
          ent2.dx = dv2.x;
          ent2.dy = dv2.y;
        }
      }
      ent.x += dt * ent.dx;
      ent.y += dt * ent.dy;
    }

    // === RENDER ===
    
    float const lerp_amount = 0.5f;
    app.camera.target.x = Lerp(app.camera.target.x, target_pos.x, lerp_amount);
    app.camera.target.y = Lerp(app.camera.target.y, target_pos.y, lerp_amount);
    
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
  input_map[(int)Actions::MOVE_LEFT]  = KEY_A;
  input_map[(int)Actions::MOVE_RIGHT] = KEY_D;
  input_map[(int)Actions::MOVE_UP]    = KEY_W;
  input_map[(int)Actions::MOVE_DOWN]  = KEY_S;
  input_map[(int)Actions::ZOOM_IN]    = KEY_J;
  input_map[(int)Actions::ZOOM_OUT]   = KEY_K;
}

bool is_actionkey_pressed(Actions action, KeyboardKey* input_map) 
{
  return IsKeyPressed(input_map[(int)action]);
}

bool is_actionkey_down(Actions action, KeyboardKey* input_map) 
{
  return IsKeyDown(input_map[(int)action]);
}
