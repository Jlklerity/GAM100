#pragma once
#include "cprocessing.h"

typedef struct {
	float stage_wallX, stage_wallY;
	float stage_wallwidth, stage_wallheight;
	CP_Color stage_wall_color;
} Stage_wall;

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
} LevelPlatform;

extern Stage_wall stage_wall[4];
extern LevelPlatform level_platform;
extern int stage_wall_count;

void Stage_wall_Init(Stage_wall stage_wall[4], int *stage_wall_count);