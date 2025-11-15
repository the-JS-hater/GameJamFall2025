#include "app.hpp"

#include "math.h"

#include <vector>
#include <array>
#include <iostream>


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
  app.state = AppState::START;
  
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

/*
 * Generates the river from position, generating roughly length tiles in direction.
 * direction 1 means right, direction -1 means left, no other directions allowed pls.
 */
void generateRiver(World& world, std::pair<int, int>& position, int direction, int length) {
  while (--length) {
    world.tiles[position] = TileType::RIVER;
    // randomly decide which direction to go:
    // -1 means up, 0 means right/left depending on direction, 1 means down.
    switch (GetRandomValue(-1, 1)) {
    case -1:
      --position.second;
      world.tiles[position] = TileType::RIVER;
      position.first += direction;
      world.tiles[position] = TileType::RIVER;
      position.first += direction;
      break;
    case 0:
      position.first += direction;
      break;
    case 1:
      ++position.second;
      world.tiles[position] = TileType::RIVER;
      position.first += direction;
      world.tiles[position] = TileType::RIVER;
      position.first += direction;
    }
  }
}

TileImage get_river_bend_from_neighbors(std::vector<bool> const& neighbors) {
  if (neighbors == std::vector<bool>{true, true, false, false}) {
    return TileImage::RIVER_BOTTOM_LEFT;
  } else if (neighbors == std::vector<bool>{false, true, true, false}) {
    return TileImage::RIVER_BOTTOM_RIGHT;
  } else if (neighbors == std::vector<bool>{false, false, true, true}) {
    return TileImage::RIVER_TOP_RIGHT;
  } else if (neighbors == std::vector<bool>{true, false, false, true}) {
    return TileImage::RIVER_TOP_LEFT;
  } else if (neighbors == std::vector<bool>{true, false, true, false}) {
    return TileImage::RIVER_HORIZONTAL;
  } else if (neighbors == std::vector<bool>{false, true, false, true}) {
    return TileImage::RIVER_VERTICAL;
  }
}

void add_sand(World& world, std::pair<int, int> const& position) {
  world.tiles[position] = TileType::SAND;
  world.tileImages[position] = TileImage::SAND;
}

void generate_river_images(World& world, std::pair<int, int> const& start) {
  // use dfs to fill in the river images
  std::vector<std::pair<int, int>> queue = {start};
  std::set<std::pair<int, int>> visited = {start};
  while (!queue.empty()) {
    auto current = queue.back();
    queue.pop_back();
    std::vector<bool> neighbors;
    static std::array<std::pair<int, int>, 4> offsets = {std::make_pair(1, 0), std::make_pair(0, -1), std::make_pair(-1, 0), std::make_pair(0, 1)};
    for (int i = 0; i < 4; ++i) {
      auto offset = offsets[i];
      auto neighbour = std::make_pair(current.first + offset.first, current.second + offset.second);
      if (world.tiles[neighbour] == TileType::RIVER) {
        neighbors.push_back(true);
        if (visited.find(neighbour) == visited.end()) {
          queue.push_back(neighbour);
          visited.insert(neighbour);
        }
      } else {
        add_sand(world, neighbour);
        neighbors.push_back(false);
      }
    }
    world.tileImages[current] = get_river_bend_from_neighbors(neighbors);
    // add sand to diagonals:
    static std::array<std::pair<int, int>, 4> diagonal_offsets = {std::make_pair(1, -1), std::make_pair(-1, -1), std::make_pair(-1, 1), std::make_pair(1, 1)};
    for (int i = 0; i < 4; ++i) {
      auto offset = diagonal_offsets[i];
      auto neighbour = std::make_pair(current.first + offset.first, current.second + offset.second);
      if (world.tiles[neighbour] != TileType::RIVER) {
        add_sand(world, neighbour);
      }
    }
  }
}

World init_world() 
{
  unsigned int const size = 1000;
  World world;
  world.x = 0;
  world.y = 0;
  world.w = size;
  world.h = size;
  world.entities = std::vector<Entity>();
  // generate a river from (0, 0) to the right and to the left
  world.tiles[std::make_pair(0, 0)] = TileType::RIVER;
  auto start = std::make_pair(-1, 0);
  generateRiver(world, start, -1, 100);
  start = std::make_pair(1, 0);
  generateRiver(world, start, 1, 100);
  generate_river_images(world, std::make_pair(0, 0));
  
  return world;
}

std::pair<int, int> world_to_tile_pos(World const& world, float x, float y) {
  return std::make_pair((int)(x / (float)world.tileSize), (int)(y / (float)world.tileSize));
}

void create_bath(World& world, float x, float y) {
  Entity bath {};
  bath.id = world.next_id++;
  bath.type = EntityType::BATH;
  bath.x = x;
  bath.y = y;
  bath.w = 2.0f * world.tileSize;
  bath.h = 2.0f * world.tileSize;
  world.entities.push_back(bath);
}
