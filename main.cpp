#include "raylib.h"

#include "running.hpp"


enum struct AppState {
	GAMELOOP,
	PAUSED,
};

struct App {
	World world;
	AppState state;
	RenderTexture2D render_target;
  // NOTE: add additional application-level global data
};


App init_application()
{
	unsigned int const res_w = 1920u;
	unsigned int const res_h = 1080u;
	App app{};
	app.render_target = LoadRenderTexture(res_w, res_h);
	app.state = AppState::GAMELOOP;
	
	return app;
};


int main() 
{	
	SetTraceLogLevel(LOG_ERROR);

	unsigned int const win_w = 640u;
	unsigned int const win_h = 480u;
	InitWindow(win_w, win_h, "Title");
	
	App app = init_application();
	
	while (!WindowShouldClose())
	{
		switch (app.state) {
			case AppState::GAMELOOP: {
				run_gameloop(app.world, app.render_target);
				break;
			}
			case AppState::PAUSED: {
				// TODO: pause screen
				break;
			}
		}
	}
	CloseWindow();
}
