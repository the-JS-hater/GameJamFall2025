#include "app.hpp"

#include "math.h"


App init_application()
{
  App app{};
  Settings settings {};
  settings.render_resolution = Vector2{1920.0f, 1080.0f};
  settings.scaling = Scaling::STRETCHED;
  app.settings = settings;
  
  auto [res_w, res_h] = settings.render_resolution;
  app.render_target = LoadRenderTexture((int)round(res_w), (int)(res_h));
  app.logical_resolution = Vector2{1920.0f, 1080.0f};
  app.state = AppState::GAMELOOP;
  
  app.camera = Camera2D {
    { res_w / 2.0f, res_h / 2.0f }, // Offset
    { // Camera target (rotation and zoom origin)
      app.logical_resolution.x / 2.0f,
      app.logical_resolution.y / 2.0f
    },
    0.0f, // Camera rotation in degrees
    1.0f // Camera zoom (scaling) 
  };
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