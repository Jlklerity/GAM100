#pragma once
#include "cprocessing.h"
#include "utils.h"
#define MAX_LEVEL_OBJECTS 100

enum TypeofWall {
	BLUE_TELEPORT, RED_DESTROY, STAGEWALL, PLATFORM, DOOR, PRESSURE_PLATE, EXIT_DOOR, NORMAL
};

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
	int isOpen;
	int isActivated;
	enum TypeofWall type;
	float last_pressed_time;
	CP_Sound wall_sound;
}Wall;

extern Wall* g_stage_wall[MAX_LEVEL_OBJECTS];
extern Wall* g_level_platforms[MAX_LEVEL_OBJECTS];
extern Wall* g_level_pressure_plate[MAX_LEVEL_OBJECTS];
extern Wall* g_level_door[MAX_LEVEL_OBJECTS];
extern Wall* g_level_exit_door;
extern Wall* g_level_teleport_wall[MAX_LEVEL_OBJECTS];
extern Wall* g_level_destroy_wall[MAX_LEVEL_OBJECTS];
extern Wall* g_level_collidables[];
extern int g_level_collidable_count;
extern int g_laser_count;

void LoadLaserFromFile(const char* filename);
void LoadLevelFromFile(const char* filename);
