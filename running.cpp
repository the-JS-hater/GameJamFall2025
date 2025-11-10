#include "raylib.h"

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"


void run_gameloop(App& app)
{
	while (app.state == AppState::GAMELOOP)
	{
		float const dt = GetFrameTime();

		// === INPUT ===
		
		if (IsKeyDown(KEY_ESCAPE)) {
			app.state = AppState::EXIT;
			return;
		}
		if (IsKeyDown(KEY_P)) {
			app.state = AppState::PAUSED;
			return;
		}

		// === UPDATE ===
		
		

		// === RENDER ===
		
		render_scene(app.render_target);
		render_to_screen(app);
	}
}


void run_pausemenu(App& app)
{
	while (app.state == AppState::PAUSED) 
	{
		// === INPUT ===
		if (IsKeyDown(KEY_ESCAPE)) {
			app.state = AppState::EXIT;
			return;
		}
		if (IsKeyDown(KEY_G)) {
			app.state = AppState::GAMELOOP;
			return;
		}
		if (IsKeyDown(KEY_B)) {
			app.settings.scaling = Scaling::BLACK_BARS; 
		}
		if (IsKeyDown(KEY_S)) {
			app.settings.scaling = Scaling::STRETCHED;
		}
		
		// === RENDERING ===
		render_pause_menu(app.render_target);
		render_to_screen(app);
	}
}
