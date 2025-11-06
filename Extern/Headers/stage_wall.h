#pragma once
#include "cprocessing.h"
#include "utils.h"

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
}Wall;

extern Wall* g_stage_wall[4];
extern Wall* g_level_platforms[3];
extern Wall* g_level_pressure_plate;
extern Wall* g_level_door;
extern Wall* g_level_exit_door;
extern Wall* g_level_teleport_wall;
extern Wall* g_level_destroy_wall;
extern Wall* g_level_collidables[];
extern int g_level_collidable_count;

void LoadLevelFromFile(const char* filename);
