#include "cprocessing.h"
#include "stage_wall.h"

Stage_wall stage_wall[4];
LevelPlatform level2_platform[3];
LevelPlatform level1_platform[3];
PressurePlate level2_pressure_plate;
PressurePlate level1_pressure_plate;
InteractableWall level2_teleport_wall;
Door level1_door;
Door level2_door;
ExitDoor level2_exit_door;
ExitDoor level1_exit_door;
int stage_wall_count = 0;

void Stage_wall_Init(Stage_wall stage_wall[4], int* stage_wall_count) {
	
	*stage_wall_count = 0;

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float stage_wall_thickness = 20.0f;
    const float orb_diameter = 50.0f;
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

    level1_platform[0] = (LevelPlatform){ screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color };
    //Lower Door platform
    level1_platform[1] = (LevelPlatform){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color };
    //Upper Door platform
    level1_platform[2] = (LevelPlatform){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color };


    //lowest platform
    level2_platform[0] = (LevelPlatform){screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color};
    //Lower Door platform
    level2_platform[1] = (LevelPlatform){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color };
    //Upper Door platform
    level2_platform[2] = (LevelPlatform){screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color};

    level2_pressure_plate = (PressurePlate){ screen_width - stage_wall_thickness, screen_height - stage_wall_thickness, 100.0f, 10.0f, color };
    
    level1_door = (Door){ screen_width - stage_wall_thickness, screen_height / 3, 50.0f, 300.0f, color };
    level2_door = (Door){ screen_width - stage_wall_thickness, screen_height / 3, 50.0f, 300.0f, color };

    level1_exit_door = (ExitDoor){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2.0f - 85.0f, 100.0f, 150.0f, color };
    level2_exit_door = (ExitDoor){ screen_width - stage_wall_thickness - 100.0f, screen_height/2.0f - 85.0f, 100.0f, 150.0f, color};

    level2_teleport_wall = (InteractableWall){ screen_width - stage_wall_thickness - 5.0f,screen_height / 2.0f - 100.0f,10.0f,180.0f,color,0 };
}



