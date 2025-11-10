#pragma once
#define RENDER_H

#include "raylib.h"

#include "app.hpp"

void render_scene(RenderTexture2D&); 
void render_pause_menu(RenderTexture2D&);
void render_to_screen(App&);
