#pragma once

#include "cprocessing.h"

struct Stage_wall {
	float stage_wall_coords[8];
	CP_Color stage_wall_color;
};

void Stage_wall_Init(struct Stage_wall stage_wall[4], int *stage_wall_count);