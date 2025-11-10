#include "raylib.h"
#include <vector>

#include "running.hpp"
#include "render.hpp"


// Run a single gameloop cycle
void run_gameloop(World world, RenderTexture2D render_target)
{
	float const dt = GetFrameTime();

	// === INPUT ===
	
	// === UPDATE ===
	
	// === RENDER ===
	
	ClearBackground(BLACK);
	render_scene(render_target);
	render_to_screen(
		render_target, 
		render_target.texture.width, 
		render_target.texture.height 
	);
}

