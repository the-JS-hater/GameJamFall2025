#include "raylib.h"
#include "math.h"

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"

// TODO: temp 
int test_idx = 0;

void run_gameloop(App& app)
{
	while (app.state == AppState::GAMELOOP)
	{
		float const dt = GetFrameTime();

		// === INPUT ===
		// NOTE: temp 
		
		if (IsKeyPressed(KEY_ESCAPE)) {
			app.state = AppState::EXIT;
			return;
		}
		if (IsKeyPressed(KEY_P)) {
			app.state = AppState::PAUSED;
			return;
		}

		Vector2 resolutions[4] = {
			{960.0f, 544.0f},
			{1064.0f, 600.0f},
			{1336.0f, 768.0f},
			{1920.0f, 1080.0f}
		}; 
		if (IsKeyPressed(KEY_N)) {
			app.settings.render_resolution = resolutions[test_idx];
			UnloadRenderTexture(app.render_target);
			auto [res_w, res_h] = resolutions[test_idx];
			app.render_target = LoadRenderTexture((int)round(res_w), (int)round(res_h));
			test_idx++;
			test_idx %= 4;
		}

		if (IsKeyPressed(KEY_B)) {
			app.settings.scaling = Scaling::BLACK_BARS; 
		}
		if (IsKeyPressed(KEY_S)) {
			app.settings.scaling = Scaling::STRETCHED;
		}
		if (IsKeyPressed(KEY_F)) {
			ToggleBorderlessWindowed();
		}
		if (IsKeyPressed(KEY_Q)) {
			// NOTE: does not work on home PC
			ToggleFullscreen();
		}

		// === UPDATE ===
		
		

		// === RENDER ===
		
		render_scene(app);
		render_to_screen(app);
	}
}

void run_pausemenu(App& app)
{
	while (app.state == AppState::PAUSED) 
	{
		// === INPUT ===
		if (IsKeyPressed(KEY_ESCAPE)) {
			app.state = AppState::EXIT;
			return;
		}
		if (IsKeyPressed(KEY_G)) {
			app.state = AppState::GAMELOOP;
			return;
		}
		
		// === RENDERING ===
		render_pause_menu(app.render_target);
		render_to_screen(app);
	}
}
