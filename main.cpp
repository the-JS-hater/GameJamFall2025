#include "raylib.h"

#include "running.hpp"


int main() 
{	
	SetTraceLogLevel(LOG_ERROR);

	unsigned int const initial_win_w = 1336u;
	unsigned int const initial_win_h = 768u;
	InitWindow(initial_win_w, initial_win_h, "Title");
	
	App app = init_application();
	app.world = init_world();
	
	while (!WindowShouldClose())
	{
		switch (app.state) {
			case AppState::GAMELOOP: {
				run_gameloop(app);
				break;
			}
			case AppState::PAUSED: {
				run_pausemenu(app);
				break;
			}
			case AppState::EXIT: {
				goto exit_app;
			}
		}
	}
	exit_app:
	CloseWindow();
}
