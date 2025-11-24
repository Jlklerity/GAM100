#pragma once
#include "player.h"
#include "stagewall.h"
#define MAXLASER 100

typedef enum { RIGHT, LEFT, UP, DOWN } Direction;
typedef enum { LASER_IDLE, LASER_WARNING, LASER_FIRING, LASER_CONTINUOUS } Laser_State;
typedef struct {
	float start_point_x;
	float start_point_y;
	float width_of_laser; // how wide the base of the laser is
	float timer; // for counting time elapsed
	Direction dir; // to check which direction the laser is firing
	Laser_State state; // to check what state the laser is in
} Laser;

typedef struct {
	float x; // midpoint x
	float y; // midpoint y
	float w; // width
	float h; // height
} LaserRect;

CP_Image kill_laser;
CP_Image Warning_laser;
 
void update_laser(Laser* laser, float delta_time, Wall* wall[], int wall_count, Player* player, Orb* orbs);
extern Laser* g_level_laser[MAXLASER];

// hazards.h
void draw_laser(Laser* laser, Wall* wall[], int wall_count);
// update_laser remains the same
void update_laser(Laser* laser, float delta_time, Wall* wall[], int wall_count, Player* player, Orb* orbs);