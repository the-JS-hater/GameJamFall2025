#include "app.hpp"


App init_application()
{
	App app{};
	Settings settings {};
	settings.resolution = (Vector2){640.0f, 480.0f};
	settings.scaling = Scaling::BLACK_BARS;
	app.settings = settings;
	auto [res_w, res_h] = settings.resolution;
	app.render_target = LoadRenderTexture(res_w, res_h);
	app.state = AppState::GAMELOOP;
	
	return app;
};


World init_world() 
{
	unsigned int const size = 1000;
	World world;
	world.x = 0;
	world.y = 0;
	world.w = size;
	world.h = size;
	world.entities = std::vector<Entity>();

	return world;
}
