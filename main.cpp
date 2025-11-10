#include "raylib.h"

#include "running.hpp"


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
