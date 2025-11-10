#include "raylib.h"
#include "algorithm"

#include "render.hpp"
#include "app.hpp"


void render_scene(RenderTexture2D& render_target) 
{
	BeginTextureMode(render_target);
	ClearBackground(WHITE);
	
	//NOTE: put actual graphics logic here
	DrawRectangle(10, 10, 200, 200, RED);
	
	EndTextureMode();
}


void render_pause_menu(RenderTexture2D& render_target)
{
	BeginTextureMode(render_target);
	ClearBackground(WHITE);
  	
	// NOTE: text does not scale well with low resolution
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
	
	auto [res_w, res_h] = app.settings.resolution;
  float scaled_w;
	float scaled_h;
		
	switch (app.settings.scaling) {
		case Scaling::BLACK_BARS: {
			float scale = std::min(
				(float)GetScreenWidth() / res_w,
  		  (float)GetScreenHeight() / res_h
			);
  		scaled_w = res_w * scale;
  		scaled_h = res_h * scale;
			break;
		}
		case Scaling::STRETCHED: {
  		scaled_w = res_w * (float)GetScreenWidth() / res_w;
  		scaled_h = res_h * (float)GetScreenHeight() / res_h;
			break;
		}
		default: {
			TraceLog(LOG_ERROR, "No scaling set in settings");
		}
	}
	float offset_x = (GetScreenWidth() - scaled_w) / 2.0f;
  float offset_y = (GetScreenHeight() - scaled_h) / 2.0f;
  Rectangle src = { 0, 0, res_w, -res_h };
  Rectangle dst = {offset_x, offset_y, scaled_w, scaled_h};

  DrawTexturePro(app.render_target.texture, src, dst, {0, 0}, 0.0f, WHITE);
	
	EndDrawing();
}
