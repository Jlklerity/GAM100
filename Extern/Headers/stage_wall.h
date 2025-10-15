#pragma once
#include "cprocessing.h"

typedef struct {
	float stage_wallX, stage_wallY;
	float stage_wallwidth, stage_wallheight;
	CP_Color stage_wall_color;
} Stage_wall;

extern Stage_wall stage_wall[4];
extern int stage_wall_count;

void Stage_wall_Init(Stage_wall stage_wall[4], int *stage_wall_count);