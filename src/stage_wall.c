#include "cprocessing.h"
#include "stage_wall.h"

Wall stage_wall[4];
Wall level1_platform[3];
Wall level2_platform[3];
Wall level1_pressure_plate;
Wall level2_pressure_plate;
Wall level1_door;
Wall level2_door;
Wall level2_exit_door;
Wall level1_exit_door;
Wall level2_teleport_wall;
int stage_wall_count = 0;

void Stage_wall_Init(Wall stage_wall[4], int* stage_wall_count) {
	
	*stage_wall_count = 0;

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float stage_wall_thickness = 20.0f;
    const float orb_diameter = 50.0f;
	CP_Color color = CP_Color_Create(255, 255, 255, 255);

    //top wall
    stage_wall[0] = (Wall){screen_width / 2.0f, stage_wall_thickness / 2.0f, screen_width, stage_wall_thickness, color, 0, 0, STAGEWALL}; //example

    //bottom wall
    stage_wall[1] = (Wall){ screen_width / 2.0f, screen_height - (stage_wall_thickness / 2.0f), screen_width, stage_wall_thickness, color, 0, 0,STAGEWALL };

    //left wall
    stage_wall[2] = (Wall){ stage_wall_thickness / 2.0f, screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };

    //right wall
    stage_wall[3] = (Wall){ screen_width - (stage_wall_thickness / 2.0f), screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };

    *stage_wall_count = 4;

    level1_platform[0] = (Wall){ screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color, 0, 0,PLATFORM };
    //Lower Door platform
    level1_platform[1] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color, 0, 0, PLATFORM };
    //Upper Door platform
    level1_platform[2] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color, 0, 0,PLATFORM };


    //lowest platform
    level2_platform[0] = (Wall){screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color, 0, 0, PLATFORM };
    //Lower Door platform
    level2_platform[1] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color, 0, 0, PLATFORM };
    //Upper Door platform
    level2_platform[2] = (Wall){screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color, 0, 0, PLATFORM };


    level2_pressure_plate = (Wall){ screen_width - stage_wall_thickness, screen_height - stage_wall_thickness, 100.0f, 10.0f, color, 0, 0, PRESSURE_PLATE };
    
    level1_door = (Wall){ screen_width - stage_wall_thickness, screen_height / 3, 50.0f, 300.0f, color, 0,0 , DOOR };
    level2_door = (Wall){ screen_width - stage_wall_thickness, screen_height / 3, 50.0f, 300.0f, color, 0,0 ,DOOR };

    level1_exit_door = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2.0f - 85.0f, 100.0f, 150.0f, color, 0,0, EXIT_DOOR };
    level2_exit_door = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height/2.0f - 85.0f, 100.0f, 150.0f, color,0,0,EXIT_DOOR};

    level2_teleport_wall = (Wall){ screen_width - stage_wall_thickness - 5.0f,screen_height / 2.0f - 100.0f,10.0f,180.0f,color, 0,0 ,BLUE_TELEPORT };
}



