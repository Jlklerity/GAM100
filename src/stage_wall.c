#include "cprocessing.h"
#include "stage_wall.h"

Stage_wall stage_wall[4];
int stage_wall_count = 0;

void Stage_wall_Init(Stage_wall stage_wall[4], int* stage_wall_count) {
	
	*stage_wall_count = 0;

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float stage_wall_thickness = 20.0f;
	CP_Color color = CP_Color_Create(255, 255, 255, 255);

    //top wall
    stage_wall[0] = (Stage_wall){ screen_width/2.0f, stage_wall_thickness / 2.0f, screen_width, stage_wall_thickness, color };

    //bottom wall
    stage_wall[1] = (Stage_wall){ screen_width/2.0f, screen_height - (stage_wall_thickness / 2.0f), screen_width, stage_wall_thickness, color };

    //left wall
    stage_wall[2] = (Stage_wall){ stage_wall_thickness / 2.0f, screen_height/2.0f, stage_wall_thickness, screen_height, color };

    //right wall
    stage_wall[3] = (Stage_wall){ screen_width - (stage_wall_thickness / 2.0f), screen_height / 2.0f, stage_wall_thickness, screen_height, color };

    *stage_wall_count = 4;
}


