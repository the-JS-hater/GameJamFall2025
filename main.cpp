#include "raylib.h"
#include <vector>

#include "render.h"


struct Entity {
	float x,y,dx,dy;
	Color color;
};


struct World {
	float x,y,w,h;
	std::vector<Entity> entities;
	// NOTE: add additional game-level global data
};


enum struct AppState {
	PLAYING,
	PAUSED,
};


struct App {
	World world;
	AppState state;
  // NOTE: add additional application-level global data
};


int main() 
{	
	// === INIT ===
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
		render_scene(render_target);
		render_to_screen(render_target, res_w, res_h);
	}
	CloseWindow();
}
