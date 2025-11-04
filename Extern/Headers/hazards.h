#pragma once
#include "player.h"
#include "stage_wall.h"

typedef enum { RIGHT, LEFT, UP, DOWN } Direction;
typedef enum { LASER_IDLE, LASER_WARNING, LASER_FIRING } Laser_State;
typedef struct {
	float start_point_x;
	float start_point_y;
	float width_of_laser; // how wide the base of the laser is
	float timer; // for counting time elapsed
	Direction dir; // to check which direction the laser is firing
	Laser_State state; // to check what state the laser is in
} Laser;

void laser_hitbox_warning(float start_point_x, float start_point_y, float width_of_laser, Wall* wall[], int wall_count, Direction dir);
void laser_hitbox(float start_point_x, float start_point_y, float width_of_laser, Wall* wall, int wall_count, Player* player, Orb* orb, Direction dir);
void pitfall(float pitfall_x, float pitfall_y, float width_of_pitfall, float depth_of_pitfall, Wall* wall, Player* player);
