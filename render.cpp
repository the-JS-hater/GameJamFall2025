#include "raylib.h"
#include "algorithm"

#include "render.h"

void render_to_screen(RenderTexture2D render_target, int const res_w, int const res_h)
{
  float scale = std::min(
		(float)GetScreenWidth() / res_w,
    (float)GetScreenHeight() / res_h
	);
  float scaled_w = res_w * scale;
  float scaled_h = res_h * scale;
  float offset_x = (GetScreenWidth() - scaled_w) / 2;
  float offset_y = (GetScreenHeight() - scaled_h) / 2;
  Rectangle src = {
		0, 0, 
		(float)render_target.texture.width,
    -(float)render_target.texture.height
	};
  Rectangle dst = {offset_x, offset_y, scaled_w, scaled_h};
  DrawTexturePro(render_target.texture, src, dst, {0, 0}, 0.0f, WHITE);
}
