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
	Vector2 resolution;
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
  // NOTE: add additional application-level global data
};


App init_application(void);
World init_world(void); 
