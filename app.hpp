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

enum struct AppState {
	GAMELOOP,
	PAUSED,
	EXIT,
};

struct App {
	World world;
	AppState state;
	unsigned int res_w, res_h;
	RenderTexture2D render_target;
  // NOTE: add additional application-level global data
};


App init_application(void);
