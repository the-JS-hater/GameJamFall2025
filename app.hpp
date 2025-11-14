#pragma once
#define APP_H

#include "raylib.h"
#include <vector>


struct Entity {
	float x,y,dx,dy;
	Color color;
};

struct World {
	float x,y,w,h;
	std::vector<Entity> entities;
	// NOTE: add additional game-level global data
};

enum struct Scaling {
	BLACK_BARS,
	STRETCHED
}; 

struct Settings {
	Vector2 render_resolution;
	Scaling scaling;
};

enum struct AppState {
	GAMELOOP,
	PAUSED,
	EXIT,
};

struct App {
	World world;
	AppState state;
	RenderTexture2D render_target;
	Settings settings;
	Vector2 logical_resolution;
	Camera2D camera;
	// array_size should match nr. of enums in Actions, see running.hpp
	KeyboardKey input_map[4]; 
  
	// NOTE: add additional application-level global data
};


App init_application(void);
World init_world(void); 
