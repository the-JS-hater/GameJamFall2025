#include "app.hpp"

App init_application()
{
	App app{};
	app.res_w = 1920u;
	app.res_h = 1080u;
	app.render_target = LoadRenderTexture(app.res_w, app.res_h);
	app.state = AppState::GAMELOOP;
	
	return app;
};
