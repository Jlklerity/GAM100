#pragma once
#include "player.h"
#include "stage_wall.h"

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;

void laser_hitbox_warning(float start_point_x, float start_point_y, float width_of_laser, Wall* wall[], Direction dir);
void laser_hitbox(float start_point_x, float start_point_y, float width_of_laser, Wall* wall, Player* player, Direction dir);
void pitfall(float pitfall_x, float pitfall_y, float width_of_pitfall, float depth_of_pitfall, Wall* wall, Player* player);
