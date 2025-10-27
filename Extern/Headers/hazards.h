#pragma once
#include "player.h"

void laser_hitbox_warning(float start_point_x, float start_point_y, float width_of_laser, float height_of_laser);
void laser_hitbox(float start_point_x, float start_point_y, float width_of_laser, float height_of_laser, Player* player);
void pitfall(float pitfall_x, float pitfall_y, float width_og_pitfall, float depth_of_pitfall, Player* player);
