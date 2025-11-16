#include "render.hpp"
#include "raylib.h"
#include "math.h"
#include <algorithm>
#include <set>

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
Texture2D sand_tex;
Texture2D egg_tex;
Texture2D start_screen_tex;
Texture2D flugsvamp_tex;
Texture2D kantarell_tex;
Texture2D sopp_tex;
Texture2D rock_tex;
Texture2D stick_tex;
Texture2D dead_turtle_tex;
Texture2D bathtub1_tex; 
Texture2D bathtub2_tex;
Texture2D bathtub3_tex;
Texture2D donken_tex;


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
  sand_tex                = LoadTexture("resources/sand.png");
  egg_tex                 = LoadTexture("resources/Egg.png");
  start_screen_tex        = LoadTexture("resources/Start_Screen.png");
  flugsvamp_tex           = LoadTexture("resources/Flugsvamp.png");
  kantarell_tex           = LoadTexture("resources/Kantarell.png");
  sopp_tex                = LoadTexture("resources/Sopp.png");
  rock_tex                = LoadTexture("resources/Rock.png");
  stick_tex               = LoadTexture("resources/Stick.png");
  dead_turtle_tex         = LoadTexture("resources/Turtle_Dead.png");
  bathtub1_tex            = LoadTexture("resources/Bath_1.png");
  bathtub2_tex            = LoadTexture("resources/Bath_2.png");
  bathtub3_tex            = LoadTexture("resources/Bath_3.png");
  donken_tex              = LoadTexture("resources/Donken.png");
  
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
  Image sand_image                = LoadImageFromTexture(sand_tex);
  Image egg_image                 = LoadImageFromTexture(egg_tex);
  Image start_screen_image        = LoadImageFromTexture(start_screen_tex);
  Image flugsvamp_image           = LoadImageFromTexture(flugsvamp_tex);
  Image kantarell_image           = LoadImageFromTexture(kantarell_tex);
  Image sopp_image                = LoadImageFromTexture(sopp_tex);     
  Image rock_image                = LoadImageFromTexture(rock_tex);     
  Image stick_image               = LoadImageFromTexture(stick_tex);
  Image dead_turtle_image         = LoadImageFromTexture(dead_turtle_tex);
  Image bathtub1_image            = LoadImageFromTexture(bathtub1_tex);
  Image bathtub2_image            = LoadImageFromTexture(bathtub2_tex);
  Image bathtub3_image            = LoadImageFromTexture(bathtub3_tex);
  Image donken_image              = LoadImageFromTexture(donken_tex);
  
  int size = app.world.tileSize;
  ImageResize(&grass_image, size, size);
  ImageResize(&river_horizontal_image, size, size);
  ImageResize(&river_vertical_image, size, size);
  ImageResize(&river_bottom_left_image, size, size);
  ImageResize(&river_top_left_image, size, size);
  ImageResize(&river_bottom_right_image, size, size);
  ImageResize(&river_top_right_image, size, size);
  ImageResize(&sand_image, size, size);
  ImageResize(&egg_image, size, size);
  ImageResize(&stick_image, size, size);
  ImageResize(&flugsvamp_image, size, size);
  ImageResize(&kantarell_image, size, size);
  ImageResize(&sopp_image, size, size);

  int small_size = 0.33 * size;
  ImageResize(&rock_image, small_size, small_size);

  int big_size = 2 * size;
  ImageResize(&bathtub1_image, big_size, big_size);
  ImageResize(&bathtub2_image, big_size, big_size);
  ImageResize(&bathtub3_image, big_size, big_size);
  ImageResize(&donken_image, big_size, big_size);
  
  float const turtle_width = app.world.tileSize;
  float const turtle_height = 1.2f * turtle_width;
  ImageResize(&turtle_image, turtle_width, turtle_height);
  ImageResize(&turtle2_image, turtle_width, turtle_height);
  ImageResize(&turtle3_image, turtle_width, turtle_height);
  ImageResize(&dead_turtle_image, turtle_height, size);

  ImageResize(&start_screen_image, 1920u, 1080u);

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
  sand_tex                = LoadTextureFromImage(sand_image);
  egg_tex                 = LoadTextureFromImage(egg_image);
  start_screen_tex        = LoadTextureFromImage(start_screen_image);
  flugsvamp_tex           = LoadTextureFromImage(flugsvamp_image);
  kantarell_tex           = LoadTextureFromImage(kantarell_image);
  sopp_tex                = LoadTextureFromImage(sopp_image);     
  rock_tex                = LoadTextureFromImage(rock_image);     
  stick_tex               = LoadTextureFromImage(stick_image);    
  dead_turtle_tex         = LoadTextureFromImage(dead_turtle_image);
  bathtub1_tex            = LoadTextureFromImage(bathtub1_image);
  bathtub2_tex            = LoadTextureFromImage(bathtub2_image);
  bathtub3_tex            = LoadTextureFromImage(bathtub3_image);
  donken_tex              = LoadTextureFromImage(donken_image);
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
      auto tileImage = app.world.tileImages.find(std::make_pair(x, y));
      Texture2D* tex = &grass_tex; 
      if (tileImage != app.world.tileImages.end()) {
        switch (tileImage->second) {
        case TileImage::RIVER_BOTTOM_LEFT:
          tex = &river_bottom_left_tex;
          break;
        case TileImage::RIVER_BOTTOM_RIGHT:
          tex = &river_bottom_right_tex;
          break;
        case TileImage::RIVER_TOP_LEFT:
          tex = &river_top_left_tex;
          break;
        case TileImage::RIVER_TOP_RIGHT:
          tex = &river_top_right_tex;
          break;
        case TileImage::RIVER_HORIZONTAL:
          tex = &river_horizontal_tex;
          break;
        case TileImage::RIVER_VERTICAL:
          tex = &river_vertical_tex;
          break;
        case TileImage::SAND:
          tex = &sand_tex;
          break;
        }
      }
      Vector2 vec_pos = { (float)x * app.world.tileSize, (float)y * app.world.tileSize };
      DrawTextureEx(*tex, vec_pos, 0.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      if (tileImage == app.world.tileImages.end())
      {
        SetRandomSeed(x + y * 1000);
        switch (GetRandomValue(0, 20)) {
          case 4:
            DrawTextureEx(rock_tex, vec_pos, 0.0f /*rotation*/, 1.0f /*scale*/, WHITE);
            break;
          default:
            break;
        }
      }
    }
  }
  render_entities(app, selected_turtles);
  EndMode2D();
  EndTextureMode();
}

void render_start_menu(RenderTexture2D& render_target)
{
  BeginTextureMode(render_target);
  ClearBackground(WHITE);

  DrawTextureEx(start_screen_tex, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);

  char const *start_text= "PRESS SPACE TO START";
  Font GetFontDefault(void);
  int const font_size = 50; 
  int const spacing = 2;
  Vector2 text_size = MeasureTextEx(
    GetFontDefault(), 
    start_text, 
    font_size, 
    spacing
  );
  // Draw centered text
  DrawText(
    start_text, 
    render_target.texture.width / 2 - (int)(text_size.x / 2.0f), 
    render_target.texture.height * 0.90 - (int)(text_size.y / 2.0f), 
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
  
  { // TODO: temp
    char const *scaling = 
        app.settings.scaling == Scaling::STRETCHED ? 
        "STRETCHED" : "BLACK BARS";
    
    char const *resolution_printout = 
      TextFormat(
        "Resolution %d x %d, %s\nFPS: %d\nWater: %.0f\nSticks: %.0f\nMushrooms: %.0f\nBurgers: %.0f", 
        (int)res_w, 
        (int)res_h, 
        scaling, 
        GetFPS(),
        app.world.waterAmount,
        app.world.stick_amount,
        app.world.mushroom_amount,
        app.world.burger_amount
      );
    DrawText(resolution_printout, 10, 10, 20, RED);
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

Texture2D& pick_turtle_texture(Entity const& ent) {
  return ent.moistness < 20.0f ?
      turtle_tex : ent.moistness < 50.0f ?
        turtle2_tex : turtle3_tex;
}

void render_turtle(Entity const& ent) {
  static float const text_offset = 20.0f;
  static float const font_size = 10.0f;
  static float const spacing = 2.0f;

  Texture2D default_turtle_tex = pick_turtle_texture(ent); 
      
  switch (ent.state) 
  {
    case TurtleState::DEAD: 
      DrawTextureEx(dead_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
    case TurtleState::PATHING:
      DrawTextureEx(default_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
    case TurtleState::IDLE:
    {
      DrawTextEx(GetFontDefault(), "thinking...", { ent.x + (0.25f * ent.w), ent.y - text_offset}, font_size, spacing, WHITE);
      DrawTextureEx(default_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
    }
    case TurtleState::BATHING:
      DrawTextEx(GetFontDefault(), "~.~ ohhh", { ent.x + (0.25f * ent.w), ent.y - text_offset}, font_size, spacing, WHITE);
      DrawTextureEx(default_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
    case TurtleState::COLLECTING:
    case TurtleState::BUILDING:
      DrawTextEx(GetFontDefault(), "Working hard >.<", { ent.x + (0.25f * ent.w), ent.y - text_offset}, font_size, spacing, WHITE);
      DrawTextureEx(default_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
    case TurtleState::EATING:
      DrawTextEx(GetFontDefault(), "mmm... borgirs", { ent.x + (0.25f * ent.w), ent.y - text_offset}, font_size, spacing, WHITE);
      DrawTextureEx(default_turtle_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);
      break;
  }
}

Color ColorLerp_(Color col1, Color col2, float t) {
  float tp = 1.0f - t;
  return Color{
    (unsigned char)(col2.r * t + col1.r * tp),
    (unsigned char)(col2.g * t + col1.g * tp),
    (unsigned char)(col2.b * t + col1.b * tp),
    (unsigned char)(col2.a * t + col1.a * tp),
  };
}

void render_egg(Entity const& ent) {
  DrawTextureEx(egg_tex, { ent.x, ent.y }, 1.0f /*rotation*/, 1.0f /*scale*/, WHITE);  
}

void render_bath(Entity const& ent, float water_amount) {
  Texture2D tex = water_amount > 6000.0f ?
    bathtub3_tex : water_amount > 2000.0f ?
      bathtub2_tex : bathtub1_tex;
  float scale = 0.2 + ent.built_percent * (0.8 / 100);
  Color color = ColorLerp_(GRAY, WHITE, ent.built_percent * (1.0f / 100.0f));
  DrawTextureEx(tex, { ent.x, ent.y }, 1.0f /*rotation*/, scale, color);  
}

void render_stick(Entity const& ent) {
  DrawTexture(stick_tex, ent.x, ent.y, WHITE);
}

void render_donken(Entity const& ent) {
  float scale = 0.2 + ent.built_percent * (0.8 / 100);
  Color color = ColorLerp_(GRAY, WHITE, ent.built_percent * (1.0f / 100.0f));
  DrawTextureEx(donken_tex, { ent.x, ent.y }, 0.0f /*rotation*/, scale, color);  
}

void render_mushroom(Entity const& ent) {
  Texture2D tex;
  switch (ent.mushroom_type) {
    case MushroomType::BOLETUS:
    {
      tex = sopp_tex;
      break;
    }
    case MushroomType::CHANTERELLE:
    {
      tex = kantarell_tex;
      break;
    }
    case MushroomType::TOADSTOOL:
    {
      tex = flugsvamp_tex;
      break;
    }
    default:
    {
      TraceLog(LOG_WARNING, "tried to render entity with type mushroom but no valid mushroom type");
      tex = kantarell_tex;
      break;
    }
  }
  DrawTexture(tex, ent.x, ent.y, WHITE);  
}

void render_entities(App& app, std::set<unsigned int> const& selected_turtles) 
{ 
  std::sort(
    app.world.entities.begin(), 
    app.world.entities.end(), 
    [](const Entity& ent1, const Entity& ent2)
    { 
      return ent1.y + ent1.h < ent2.y + ent2.h; 
    }
  );
  for (Entity ent : app.world.entities) 
  {
    switch (ent.type)
    {
      case EntityType::TURTLE:
        render_turtle(ent);
        break;
      case EntityType::EGG:
        render_egg(ent);
        break;
      case EntityType::BATH:
        render_bath(ent, app.world.waterAmount);
        break;
      case EntityType::STICK:
        render_stick(ent);
        break;
      case EntityType::DONKEN:
        render_donken(ent);
        break;
      case EntityType::MUSHROOM:
        render_mushroom(ent);
        break;
    }
  }
}


void set_display_resolution(Vector2 resolution, App& app)
{
  app.settings.render_resolution = resolution;
  UnloadRenderTexture(app.render_target);
  auto [res_w, res_h] = resolution;
  app.render_target = 
    LoadRenderTexture((int)round(res_w), (int)round(res_h));
}
