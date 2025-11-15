#pragma once
#define RENDER_H

#include "raylib.h"
#include <set>

#include "app.hpp"

void render_scene(App&, std::set<unsigned int> const&); 
void render_start_menu(RenderTexture2D&);
void render_to_screen(App&, Rectangle);
void set_display_resolution(Vector2, App&);
void init_resources(App const&); 
