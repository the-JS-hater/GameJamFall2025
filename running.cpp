#include "raylib.h"
#include "math.h"
#include "stdio.h"

#include "running.hpp"
#include "render.hpp"
#include "app.hpp"


// TODO: temp 
int res_idx = 0;

void run_gameloop(App& app)
{
	while (app.state == AppState::GAMELOOP)
	{
		float const dt = GetFrameTime();

		// === INPUT ===
		
		{ // NOTE: temp 
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
				app.settings.render_resolution = resolutions[res_idx];
				UnloadRenderTexture(app.render_target);
				auto [res_w, res_h] = resolutions[res_idx];
				app.render_target = 
					LoadRenderTexture((int)round(res_w), (int)round(res_h));
				res_idx++;
				res_idx %= 4;
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
				// NOTE: (morgan) does not work on home PC
				ToggleFullscreen();
			}
		}

		if (is_actionkey_pressed(Actions::MOVE_LEFT, app.input_map)) printf("MOVE LEFT\n");
		if (is_actionkey_pressed(Actions::MOVE_RIGHT, app.input_map)) printf("MOVE RIGHT\n");
		if (is_actionkey_pressed(Actions::MOVE_UP, app.input_map)) printf("MOVE UP\n");
		if (is_actionkey_pressed(Actions::MOVE_DOWN, app.input_map)) printf("MOVE DOWN\n");

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

void setup_controls(KeyboardKey* input_map) 
{
	input_map[(int)Actions::MOVE_LEFT] = KEY_A;
	input_map[(int)Actions::MOVE_RIGHT] = KEY_D;
	input_map[(int)Actions::MOVE_UP] = KEY_W;
	input_map[(int)Actions::MOVE_DOWN] = KEY_S;
}

bool is_actionkey_pressed(Actions action, KeyboardKey* input_map) 
{
	// forgive me father, for i have sinned
	return IsKeyPressed(input_map[(int)action]);
}
