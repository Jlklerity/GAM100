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


extern Wall stage_wall[4];
extern Wall level1_platform[3];
extern Wall level1_pressure_plate;
extern Wall level1_door;
extern Wall level1_exit_door;
extern Wall level1_teleport_wall;
extern Wall level1_destroy_wall;
extern Wall* level1_walls[];

extern int stage_wall_count;
extern int level1_wall_count;
//extern Wall level2_pressure_plate;
//extern Wall level2_door;
//extern Wall level2_exit_door;
//extern Wall level2_teleport_wall;
//extern Wall level2_destroy_wall;
//extern Wall level2_platform[3];
//extern Wall* level2_walls[];

extern Wall* g_level_platforms[3];
extern Wall* g_level_pressure_plate;
extern Wall* g_level_door;
extern Wall* g_level_exit_door;
extern Wall* g_level_teleport_wall;
extern Wall* g_level_destroy_wall;
extern Wall* g_level_collidables[];
extern int g_level_collidable_count;

void Stage_Walls_Init(void);
void level1_Object_Walls_Init(void);
//void level2_Object_Walls_Init(void);