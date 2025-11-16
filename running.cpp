#include "raylib.h"
#include "raymath.h"
#include "math.h"
#include <algorithm>
#include <set>

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"



void find_next_state(World& world, Entity& ent) {
  if (ent.touching == BuildingType::BUILT_BATH)
  {
    ent.state = TurtleState::BATHING;
  }
  else if (ent.touching == BuildingType::UN_BUILT_BATH || ent.touching == BuildingType::UN_BUILT_DONKEN)
  {
    ent.state = TurtleState::BUILDING;
  }
  else if (ent.touching == BuildingType::BUILT_DONKEN)
  {
    ent.state = TurtleState::EATING;
  }
  else if (world.tiles[world_to_tile_pos(world, ent.x, ent.y)] == TileType::SAND && ent.hunger > 50.0f)
  {
    spawn_egg(world, ent.x, ent.y);
    ent.hunger -= 20.0f;
  }
  else if (world.tiles[world_to_tile_pos(world, ent.x, ent.y)] == TileType::RIVER
            || ent.touching == BuildingType::STICK
            || ent.touching == BuildingType::MUSHROOM)
  {
    ent.state = TurtleState::COLLECTING;
  }
  else
  {
    ent.state = TurtleState::IDLE;
  }
}

void process_turtle(Entity& ent, float const dt, App& app) 
{
  // Change the turtle stats like moistness and hunger
  {
    if (
      (ent.moistness < 0.0f || ent.hunger < 0.0f) && 
      ent.state != TurtleState::DEAD
    ) 
    {
      if (ent.moistness < 0.0f && ent.state != TurtleState::DEAD) {
        ent.state = TurtleState::DEAD;
        return;
      }
      float const moistness_depletion_rate = 0.3f;
      float const hunger_depletion_rate = 0.3f;
      ent.moistness -= dt * moistness_depletion_rate;
      ent.hunger -= dt * hunger_depletion_rate;
    }
  }

  // Start ideling if turtle is far away from target
  {
    if (ent.state != TurtleState::PATHING && Vector2Distance(ent.get_center(), ent.target) > app.world.tileSize)
    {
      ent.state = TurtleState::IDLE;
    }
  }

  {
    switch (ent.state) {
      case TurtleState::PATHING: 
      {
        Vector2 pos = ent.get_center();
        Vector2 direction = Vector2Subtract(ent.target, pos);
        direction = Vector2Normalize(direction);
        const float SPEED = (float)app.world.tileSize;
        ent.dx = SPEED * dt * direction.x;
        ent.dy = SPEED * dt * direction.y;
        ent.x += ent.dx;
        ent.y += ent.dy;
        
        if (Vector2Distance(pos, ent.target) < 16.0f) 
        {
          find_next_state(app.world, ent);
        }
        break;
      }
      case TurtleState::COLLECTING: 
      {
        float const collection_speed = 1.0f;
        if (ent.touching == BuildingType::STICK)
        {
          app.world.stick_amount += dt * collection_speed;
        }
        else if (ent.touching == BuildingType::MUSHROOM)
        {
          app.world.mushroom_amount += dt * collection_speed;
        }
        else if (app.world.tiles[world_to_tile_pos(app.world, ent.x, ent.y)] == TileType::RIVER)
        {
          app.world.waterAmount += dt * collection_speed;
        }
        else
        {
          ent.state = TurtleState::IDLE;
        }
        break;
      }
      case TurtleState::BATHING:
      {
        float const draining_speed = 200.0f;
        float const max_moistness = 100.0f;
        if (app.world.waterAmount > dt * draining_speed && ent.moistness < max_moistness) {
          app.world.waterAmount -= dt * draining_speed;
          ent.moistness += dt * draining_speed;
        }
        break;
      }
      case TurtleState::BUILDING:
      {
        if (ent.assigned_building->built_percent >= 100) {
          ent.state = TurtleState::IDLE;
        }

        float const stick_drainage = 2.0f;
        if (app.world.stick_amount >= stick_drainage * dt)
        {
          app.world.stick_amount -= stick_drainage * dt;
          float const building_speed = 1.0f;
          ent.assigned_building->built_percent += building_speed * dt;
        }
        break;
      }
      case TurtleState::EATING:
      {
        const float eat_speed = 10.0f;
        const float max_hunger = 100.0f;
        if (app.world.burger_amount > eat_speed * dt && ent.hunger < max_hunger) {
          app.world.burger_amount -= eat_speed * dt;
          ent.hunger += eat_speed * dt;
        }
        break;
      }
      case TurtleState::DEAD:
        ent.dead_time += dt * 1.0f;
        if (ent.dead_time > 15.0f) ent.to_be_removed = true;
      case TurtleState::IDLE: 
      default: 
        TraceLog(LOG_INFO, "UNKNOWN TURTLE STATE");
    }
  }
}

void check_collisions(std::vector<Entity>& entities) {
  for (auto& a : entities) {
    a.touching = BuildingType::NONE;
    a.push_force = Vector2{0.0f, 0.0f};
    for (auto& b : entities) {
      if (a.id == b.id)
      {
        continue;
      }
      if (CheckCollisionRecs(Rectangle{a.x, a.y, a.w, a.h}, Rectangle{b.x, b.y, b.w, b.h}))
      {
        if (a.type == EntityType::TURTLE)
        {
          if (b.type == EntityType::BATH)
          {
            if (b.built_percent < 100)
            {
              a.touching = BuildingType::UN_BUILT_BATH;
              a.assigned_building = &b;
            }
            else
            {
              a.touching = BuildingType::BUILT_BATH;
            }
          }
          else if (b.type == EntityType::DONKEN)
          {
            if (b.built_percent < 100)
            {
              a.touching = BuildingType::UN_BUILT_DONKEN;
              a.assigned_building = &b;
            }
            else
            {
              a.touching = BuildingType::BUILT_DONKEN;
            }
          }
          else if (b.type == EntityType::STICK) 
          {
            a.touching = BuildingType::STICK;
          }
          else if (b.type == EntityType::MUSHROOM)
          {
            a.touching = BuildingType::MUSHROOM;
          }
        }
        if ((a.type == EntityType::TURTLE || a.type == EntityType::EGG)
             && (b.type == EntityType::TURTLE || b.type == EntityType::EGG)
             && a.id != b.id)
        {
          const float push_strength = 10.0f;
          Vector2 push_dir = Vector2Subtract(a.get_center(), b.get_center());
          float push = push_strength / std::max(Vector2Length(push_dir), 1.0f);
          a.push_force += Vector2Scale(Vector2Normalize(push_dir), push);
        }
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
    if (IsKeyPressed(KEY_B)) {
      app.world.current_action = ActionType::BUILD_BATH;
    }
    if (IsKeyPressed(KEY_N)) {
      app.world.current_action = ActionType::BUILD_DONKEN;
    }
    if (IsKeyPressed(KEY_M)) {
      app.world.current_action = ActionType::DEFAULT;
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

    check_collisions(app.world.entities);

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

    if (make_click && app.world.current_action == ActionType::BUILD_BATH) {
      create_bath(app.world, x1, y1);
      app.world.current_action = ActionType::DEFAULT;
    }
    else if (make_click && app.world.current_action == ActionType::BUILD_DONKEN) {
      create_donken(app.world, x1, y1);
      app.world.current_action = ActionType::DEFAULT;
    }
      
    // remove 15sec+ old corpses
    app.world.entities.erase(
      std::remove_if(
        app.world.entities.begin(), 
        app.world.entities.end(),
        [](Entity ent) { 
          return ent.to_be_removed;
        }
      ),
      app.world.entities.end()
    );

    unsigned int alive_count = 0;
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

      // == UPDATE PUSH_FORCE (SO THE TURTLES STAY APPART) ==
      {
        ent.x += ent.push_force.x;
        ent.y += ent.push_force.y;
      }
       
      // == ENTITY STATE ==
      switch (ent.type) {
        case EntityType::TURTLE: 
        {
          alive_count += (unsigned int)(ent.state != TurtleState::DEAD);
          process_turtle(ent, dt, app);
          break;
        }
        case EntityType::EGG:
        {
          ent.egg_timer -= 1.0f * dt;
          if (ent.egg_timer < 0.0f)
          {
            ent.type = EntityType::TURTLE;
            ent.moistness = 100.0f;
            ent.hunger = 50.0f;
          }
          break;
        }
        case EntityType::DONKEN:
        {
          float const cooking_speed = 10.0f;
          float const mushroom_depletion_speed = 10.0f;
          if (ent.built_percent >= 100.0f && app.world.mushroom_amount > mushroom_depletion_speed * dt)
          {
            app.world.burger_amount += cooking_speed * dt;
            app.world.mushroom_amount -= mushroom_depletion_speed * dt;
          }
          break;
        }
        default: 
        { 
          TraceLog(LOG_INFO, "Unknown entity type");
        }
      }
    }
    if (alive_count == 0) {
      app.state = AppState::GAMEOVER;
      return;
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

void run_startmenu(App& app)
{
  while (app.state == AppState::START) 
  {
    // === INPUT ===
    
    if (IsKeyPressed(KEY_ESCAPE)) {
      app.state = AppState::EXIT;
      return;
    }
    if (IsKeyPressed(KEY_SPACE)) {
      app.state = AppState::GAMELOOP;
      return;
    }
    
    // === RENDERING ===
    
    render_start_menu(app.render_target);
    render_to_screen(app, {0,0,0,0});
  }
}

void run_gameover(App& app)
{
  while (app.state == AppState::GAMEOVER)
  {
    // === INPUT ===
    
    if (IsKeyPressed(KEY_ESCAPE)) {
      app.state = AppState::EXIT;
      return;
    }
    if (IsKeyPressed(KEY_R)) {
      app.state = AppState::GAMELOOP;
      setup_world(app);
      
      return;
    }
    
    // === RENDERING ===
    
    render_gameover(app.render_target);
    render_to_screen(app, {0,0,0,0});
  }
}

void set_initial_entities(World& world)
{
  int const test_entities_count = 5;
  for (unsigned int id = 0; id < test_entities_count; ++id)
  {
    spawn_turtle(
      world,
      (float)GetRandomValue(0, (int)world.w),
      (float)GetRandomValue(0, (int)world.h)
    );
    spawn_egg(
      world,
      (float)GetRandomValue(0, (int)world.w),
      (float)GetRandomValue(0, (int)world.h)
    );
  }
}

void setup_world(App& app)
{
  app.world = init_world();
  set_initial_entities(app.world);
  create_sticks_and_mushrooms(app.world);
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
