#include "raylib.h"
#include "raymath.h"
#include "math.h"
#include "stdio.h"
#include <algorithm>
#include <set>

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"



void process_turtle(Entity ent, float const dt, App& app) 
{
  {
    switch (ent.state) {
      case TurtleState::PATHING: 
      {
        Vector2 pos = Vector2{ent.x, ent.y};
        Vector2 direction = Vector2Subtract(ent.target, pos);
        direction = Vector2Normalize(direction);
        const float SPEED = app.world.tileSize;
        ent.dx = SPEED * dt * direction.x;
        ent.dy = SPEED * dt * direction.y;
        ent.x += ent.dx;
        ent.y += ent.dy;
        
        if (Vector2Distance(pos, ent.target) < 1) 
        {
          if (app.world.tiles[std::make_pair((int)(ent.x / app.world.tileSize), (int)(ent.y / app.world.tileSize))] == TileType::RIVER) {
            ent.state = TurtleState::COLLECTING;
          } else {
            ent.state = TurtleState::IDLE;
          }
        }
        break;
      }
      case TurtleState::COLLECTING: 
      {
        Vector2 pos = Vector2{ent.x, ent.y};
        switch (app.world.tiles[std::make_pair(ent.x, ent.y)]) 
        {
          case TileType::GRASS:
          {
            ent.state = TurtleState::IDLE;
            break;
          }
          case TileType::RIVER:
          {
            float const collection_speed = 100.0f;
            app.world.waterAmount += dt * collection_speed;
            break;
          }
        }
        break;
      }
      case TurtleState::IDLE: 
      {
        // fallthrough 
      }
      default: 
      {
        // empty
      }
    }
  }
}

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
    
    static Vector2 target_pos = {
      (float)GetScreenWidth() / 2.0f, 
      (float)GetScreenHeight() / 2.0f
    };
    
    { 
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

    static float initial_x = 0.0f; 
    static float initial_y  = 0.0f;
    static float final_x = 0.0f;
    static float final_y = 0.0f;

    bool make_selection = false;
    bool make_click = false;
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        auto [x, y] = GetMousePosition();
        initial_x = x;
        initial_y = y;
      }
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        auto [x, y] = GetMousePosition();
        final_x = x;
        final_y = y;
        if (Vector2Distance(Vector2{initial_x, initial_y}, Vector2{final_x, final_y}) < 16) {
          make_click = true;
        } else {
          app.world.selected_turtles.clear();
          make_selection = true;
        }
      }
    }

    // === UPDATE ===

    Vector2 point_initial = { initial_x, initial_y };
    Vector2 point_final = { final_x, final_y };
    point_initial = GetScreenToWorld2D(point_initial, app.camera); 
    point_final = GetScreenToWorld2D(point_final, app.camera);
    float x1 = point_initial.x;
    float y1 = point_initial.y;
    float x2 = point_final.x;
    float y2 = point_final.y;

    Rectangle selection_rect = {
      std::min(x2, x1),
      std::min(y2, y1),
      abs(x2 - x1),
      abs(y2 - y1)
    };

    for (Entity& ent : app.world.entities) 
    {
      // == SELECTION ==
      {
        if (
          make_selection && 
          CheckCollisionRecs(
            selection_rect,
            Rectangle { ent.x, ent.y, ent.w, ent.h }
          )
        ) {
          app.world.selected_turtles.insert(ent.id);
        }
        
        if (make_click && app.world.selected_turtles.find(ent.id) != app.world.selected_turtles.end()) {
          ent.target = Vector2{selection_rect.x, selection_rect.y};
          ent.state = TurtleState::PATHING;
        }
      }
       
      // == ENTITY STATE ==
      switch (ent.type) {
        case EntityType::TURTLE: 
        {
          process_turtle(ent, dt, app);
          break;
        }
        case EntityType::EGG:
        {
          break;
        }
        defualt: 
        { 
          TraceLog(LOG_WARNING, "Unknown entity type");
        }
      }
    }

    // === RENDER ===
    
    float const lerp_amount = 0.5f;
    app.camera.target.x = Lerp(app.camera.target.x, target_pos.x, lerp_amount);
    app.camera.target.y = Lerp(app.camera.target.y, target_pos.y, lerp_amount);
    
    render_scene(app, app.world.selected_turtles);
    render_to_screen(app, 
      Rectangle {
        std::min((float)GetMouseX(), initial_x),
        std::min((float)GetMouseY(), initial_y),
        abs((float)GetMouseX() - initial_x),
        abs((float)GetMouseY() - initial_y)
      }
    );
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
    render_to_screen(app, {0,0,0,0});
  }
}

void setup_controls(KeyboardKey* input_map) 
{
  input_map[(int)Actions::MOVE_LEFT]  = KEY_A;
  input_map[(int)Actions::MOVE_RIGHT] = KEY_D;
  input_map[(int)Actions::MOVE_UP]    = KEY_W;
  input_map[(int)Actions::MOVE_DOWN]  = KEY_S;
}

bool is_actionkey_pressed(Actions action, KeyboardKey* input_map) 
{
  return IsKeyPressed(input_map[(int)action]);
}

bool is_actionkey_down(Actions action, KeyboardKey* input_map) 
{
  return IsKeyDown(input_map[(int)action]);
}
