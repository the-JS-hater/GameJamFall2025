#pragma once
#define RUNNING_H

#include "app.hpp"


App init_application(void);

// Run a single gameloop cycle
void run_gameloop(App&);
void run_pausemenu(App&);
