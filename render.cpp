#include "raylib.h"
#include "math.h"
#include "algorithm"

#include "render.hpp"
#include "app.hpp"


void render_scene(App& app) 
{
  BeginTextureMode(app.render_target);
  ClearBackground(WHITE);

  float render_scale_x = 
    app.settings.render_resolution.x / app.logical_resolution.x;
  float render_scale_y = 
    app.settings.render_resolution.y / app.logical_resolution.y;

  BeginMode2D(app.camera);

  DrawRectangleRec(
    Rectangle{
      10.0f * render_scale_x, 
      10.0f * render_scale_y, 
      20.0f * render_scale_x, 
      40.0f * render_scale_y
    }, 
    RED
  );
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
  
  
void render_to_screen(App& app)
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
    
    char const *resolution_printout = TextFormat("Resolution %d x %d, %s", (int)res_w, (int)res_h, scaling);
    
    DrawText(resolution_printout, 10, 10, 20, LIME);
  }
  EndDrawing();
}
