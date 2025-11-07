#include "raylib.h"
#include "render.h"


int main() 
{	
	// === SETUP ===
	SetTraceLogLevel(LOG_ERROR);

	unsigned int const win_w = 640u;
	unsigned int const win_h = 480u;
	InitWindow(win_w, win_h, "Title");

	unsigned int const res_w = 1920u;
	unsigned int const res_h = 1080u;
	RenderTexture2D render_target = LoadRenderTexture(res_w, res_h);
	
	// === GAME LOOP ===
	while (!WindowShouldClose()) 
	{
		float const dt = GetFrameTime();

		// === INPUT ===
		
		// === UPDATE ===
		
		// === RENDER ===
		
		ClearBackground(BLACK);
		
		// render to texture (frame buffer)
		BeginTextureMode(render_target);
		DrawRectangle(10, 10, 200, 200, RED);
		EndTextureMode();
		
		// render to screen
		BeginDrawing();
		render_to_screen(render_target, res_w, res_h);
		EndDrawing();
	}
	CloseWindow();
}
