#pragma once
#include "cprocessing.h"

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
extern Wall level2_platform[3];
extern Wall level1_platform[3];
extern Wall level1_pressure_plate;
extern Wall level2_pressure_plate;
extern Wall level2_door;
extern Wall level1_door;
extern Wall level2_exit_door;
extern Wall level1_exit_door;
extern Wall level2_teleport_wall;
extern int stage_wall_count;

void Stage_wall_Init(Wall stage_wall[4], int *stage_wall_count);