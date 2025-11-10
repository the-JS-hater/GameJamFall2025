#pragma once
#define RUNNING_H

#include "raylib.h"
#include <vector>

#include "render.hpp"


struct Entity {
	float x,y,dx,dy;
	Color color;
};


struct World {
	float x,y,w,h;
	std::vector<Entity> entities;
	// NOTE: add additional game-level global data
};


// Run a single gameloop cycle
void run_gameloop(World world, RenderTexture2D render_target);
