#include "raylib.h"
#include "math.h"
#include <algorithm>
#include <set>

#include "render.hpp"
#include "app.hpp"


Texture2D grass_tex;
Texture2D turtle_tex;
Texture2D turtle2_tex;
Texture2D turtle3_tex;
Texture2D river_horizontal_tex;
Texture2D river_vertical_tex;
Texture2D river_bottom_left_tex;
Texture2D river_top_left_tex;
Texture2D river_bottom_right_tex;
Texture2D river_top_right_tex;


void init_resources(App const& app) 
{
  grass_tex               = LoadTexture("resources/Grass.png");
  turtle_tex              = LoadTexture("resources/turtle.png");
  turtle2_tex             = LoadTexture("resources/turtle2.png");
  turtle3_tex             = LoadTexture("resources/turtle3.png");
  river_horizontal_tex    = LoadTexture("resources/River_Horizontal.png");
  river_vertical_tex      = LoadTexture("resources/River_vertical_.png");
  river_bottom_left_tex   = LoadTexture("resources/River_Bottom_Left.png");
  river_top_left_tex      = LoadTexture("resources/River_Top_Left.png");
  river_bottom_right_tex  = LoadTexture("resources/River_Bottom_Right.png");
  river_top_right_tex     = LoadTexture("resources/River_Top_Right.png");

  Image grass_image               = LoadImageFromTexture(grass_tex);
  Image turtle_image              = LoadImageFromTexture(turtle_tex);
  Image turtle2_image             = LoadImageFromTexture(turtle2_tex);             
  Image turtle3_image             = LoadImageFromTexture(turtle3_tex);
  Image river_horizontal_image    = LoadImageFromTexture(river_horizontal_tex);
  Image river_vertical_image      = LoadImageFromTexture(river_vertical_tex);
  Image river_bottom_left_image   = LoadImageFromTexture(river_bottom_left_tex);
  Image river_top_left_image      = LoadImageFromTexture(river_top_left_tex);         
  Image river_bottom_right_image  = LoadImageFromTexture(river_bottom_right_tex);
  Image river_top_right_image     = LoadImageFromTexture(river_top_right_tex);

  int size = app.world.tileSize;
  ImageResize(&grass_image, size, size);
  ImageResize(&river_horizontal_image, size, size);
  ImageResize(&river_vertical_image, size, size);
  ImageResize(&river_bottom_left_image, size, size);
  ImageResize(&river_top_left_image, size, size);
  ImageResize(&river_bottom_right_image, size, size);
  ImageResize(&river_top_right_image, size, size);
  
  float const turtle_height_ratio = 
    (float)turtle_image.height / (float)turtle_image.width;
  int const turtle_height = (int)((float)size * turtle_height_ratio);
  ImageResize(&turtle_image, size, turtle_height);
  ImageResize(&turtle2_image, size, turtle_height);
  ImageResize(&turtle3_image, size, turtle_height);

  grass_tex               = LoadTextureFromImage(grass_image);
  turtle_tex              = LoadTextureFromImage(turtle_image);
  turtle2_tex             = LoadTextureFromImage(turtle2_image); 
  turtle3_tex             = LoadTextureFromImage(turtle3_image);
  river_horizontal_tex    = LoadTextureFromImage(river_horizontal_image);
  river_vertical_tex      = LoadTextureFromImage(river_vertical_image);
  river_bottom_left_tex   = LoadTextureFromImage(river_bottom_left_image);
  river_top_left_tex      = LoadTextureFromImage(river_top_left_image);
  river_bottom_right_tex  = LoadTextureFromImage(river_bottom_right_image);
  river_top_right_tex     = LoadTextureFromImage(river_top_right_image);
}


void render_scene(App& app, std::set<unsigned int> const& selected_turtles) 
{

  BeginTextureMode(app.render_target);
  ClearBackground(WHITE);

  BeginMode2D(app.camera);

  for (int screenY = -app.world.tileSize; screenY < GetScreenHeight() + app.world.tileSize; screenY += app.world.tileSize) {
    for (int screenX = -app.world.tileSize; screenX < GetScreenWidth() + app.world.tileSize; screenX += app.world.tileSize) {
      Vector2 position = GetScreenToWorld2D(Vector2{(float)screenX, (float)screenY}, app.camera);
      int x = (int)(position.x / app.world.tileSize);
      int y = (int)(position.y / app.world.tileSize);
      Color color = GREEN;
      auto tileType = app.world.tiles.find(std::make_pair(x, y));
      if (tileType != app.world.tiles.end() && tileType->second == TileType::RIVER) {
        color = BLUE;
      }
      float const scale = app.world.tileSize / (float)grass_tex.width;
      Vector2 vec_pos = { (float)x * app.world.tileSize, (float)y * app.world.tileSize };
      DrawTextureEx(grass_tex, vec_pos, 1.0f /*rotation*/, 1.0f, WHITE);  
    }
  }
    
  for (Entity ent : app.world.entities) 
  {
    Texture2D choosen_turtle_tex = 
      ent.id % 3 ?
      turtle_tex : ent.id % 7 ?
        turtle2_tex : turtle3_tex;

    DrawTextureEx(choosen_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);  
  }
  EndMode2D();
  EndTextureMode();
}


void render_pause_menu(RenderTexture2D& render_target)
{
  BeginTextureMode(render_target);
  ClearBackground(WHITE);
  	
  char const *pause_text = "GAME IS PAUSED";
  Font GetFontDefault(void);
  int const font_size = 60; 
  int const spacing = 2;
  Vector2 text_size = MeasureTextEx(
    GetFontDefault(), 
    pause_text, 
    font_size, 
    spacing
  );
  // Draw centered text
  DrawText(
    pause_text, 
    render_target.texture.width / 2 - (int)(text_size.x / 2.0f), 
    render_target.texture.height / 2 - (int)(text_size.y / 2.0f), 
    font_size,
    RED
  );
  EndTextureMode();
}
  
  
void render_to_screen(App& app, Rectangle selection)
{
  BeginDrawing();
  ClearBackground(BLACK);
  
  auto [res_w, res_h] = app.settings.render_resolution;
  float scaled_w;
  float scaled_h;
  	
  switch (app.settings.scaling) {
    case Scaling::BLACK_BARS: 
    {
      float scale = std::min(
        (float)GetScreenWidth() / res_w,
        (float)GetScreenHeight() / res_h 
      );
      scaled_w = res_w * scale;
      scaled_h = res_h * scale;
      break;
    }
    case Scaling::STRETCHED: 
    {
      scaled_w = (float)GetScreenWidth(); 
      scaled_h = (float)GetScreenHeight();
      break;
    }
    default: 
    {
      TraceLog(LOG_ERROR, "No scaling set in settings");
    }
  }
  float offset_x = (GetScreenWidth() - scaled_w) / 2.0f;
  float offset_y = (GetScreenHeight() - scaled_h) / 2.0f;
  Rectangle src = { 0.0f, 0.0f, res_w, -res_h };
  Rectangle dst = { offset_x, offset_y, scaled_w, scaled_h };
  
  DrawTexturePro(app.render_target.texture, src, dst, {0, 0}, 0.0f, WHITE);
  
  // TODO: temp
  {
    char const *scaling = 
        app.settings.scaling == Scaling::STRETCHED ? 
        "STRETCHED" : "BLACK BARS";
    
    char const *resolution_printout = 
      TextFormat(
        "Resolution %d x %d, %s\nFPS: %d\nWater: %d", 
        (int)res_w, 
        (int)res_h, 
        scaling, 
        GetFPS(),
        app.world.waterAmount
      );
    DrawText(resolution_printout, 10, 10, 20, LIME);
  }

  float const line_thicc = 5.0f;
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
  {
    DrawRectangleLinesEx(
      selection, 
      line_thicc, 
      RED
    );
  }


  EndDrawing();
}


void set_display_resolution(Vector2 resolution, App& app)
{
  app.settings.render_resolution = resolution;
  UnloadRenderTexture(app.render_target);
  auto [res_w, res_h] = resolution;
  app.render_target = 
    LoadRenderTexture((int)round(res_w), (int)round(res_h));
}
