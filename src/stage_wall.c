#include "cprocessing.h"
#include "stage_wall.h"

Wall stage_wall[4];  // Shared walls 
int stage_wall_count = 0;
// Level 1 Objects
Wall level1_platform[3];
Wall level1_pressure_plate;
Wall level1_door;
Wall level1_exit_door;
Wall level1_teleport_wall;
Wall level1_destroy_wall;
// Level 2 Objects
Wall level2_platform[3];
Wall level2_pressure_plate;
Wall level2_door;
Wall level2_exit_door;
Wall level2_teleport_wall;

Wall* level1_walls[] = {
    &stage_wall[0], &stage_wall[1], &stage_wall[2], &stage_wall[3],
    &level1_platform[0], &level1_platform[1], &level1_platform[2],
    &level1_door, &level1_teleport_wall, & level1_destroy_wall
};
int level1_wall_count = sizeof(level1_walls) / sizeof(level1_walls[0]);

//Wall* level2_walls[] = {
//    &stage_wall[0], &stage_wall[1], &stage_wall[2], &stage_wall[3],
//    &level2_platform[0], &level2_platform[1], &level2_platform[2],
//    &level2_door, &level2_teleport_wall
//};
//int level2_wall_count = sizeof(level2_walls) / sizeof(level2_walls[0]);

void Stage_Walls_Init(void) {
    const float screen_width = (float)CP_System_GetWindowWidth();
    const float screen_height = (float)CP_System_GetWindowHeight();
    const float stage_wall_thickness = 20.0f;
    stage_wall_count = 4;
    //const float orb_diameter = 50.0f;
    CP_Color color = CP_Color_Create(255, 255, 255, 255);

    //top wall
    stage_wall[0] = (Wall){ screen_width / 2.0f, stage_wall_thickness / 2.0f, screen_width, stage_wall_thickness, color, 0, 0, STAGEWALL }; //example
    //bottom wall
    stage_wall[1] = (Wall){ screen_width / 2.0f, screen_height - (stage_wall_thickness / 2.0f), screen_width, stage_wall_thickness, color, 0, 0,STAGEWALL };
    //left wall
    stage_wall[2] = (Wall){ stage_wall_thickness / 2.0f, screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };
    //right wall
    stage_wall[3] = (Wall){ screen_width - (stage_wall_thickness / 2.0f), screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };

}
void level1_Object_Walls_Init(void) {	
    const float screen_width = (float)CP_System_GetWindowWidth();
    const float screen_height = (float)CP_System_GetWindowHeight();
    const float stage_wall_thickness = 20.0f;
    //const float orb_diameter = 50.0f;
    CP_Color color = CP_Color_Create(255, 255, 255, 255);

    //middle platform
    level1_platform[0] = (Wall){ screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color, 0, 0,PLATFORM };
    //Lower Door platform
    level1_platform[1] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color, 0, 0, PLATFORM };
    //Upper Door platform
    level1_platform[2] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color, 0, 0,PLATFORM };

    level1_pressure_plate = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height - stage_wall_thickness, 100.0f, 10.0f, CP_Color_Create(113,121,126,255), 0, 0, PRESSURE_PLATE };
    level1_door = (Wall){ screen_width - stage_wall_thickness - 190.0f, screen_height / 2.0f - 100.0f, 20.0f, 180.0f, CP_Color_Create(113,121,126,255), 0,0 , DOOR };
    level1_exit_door = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2.0f - 85.0f, 100.0f, 150.0f, color, 0,0, EXIT_DOOR };
    level1_teleport_wall = (Wall){ screen_width - stage_wall_thickness - 5.0f,screen_height / 2.0f - 100.0f,10.0f,180.0f,color, 0,0 ,BLUE_TELEPORT };
    level1_destroy_wall = (Wall){ screen_width - stage_wall_thickness - 195.0f,screen_height / 2.0f + 220.0f,10.0f,418.0f,color, 0,0 ,RED_DESTROY };
}
void level2_Object_Walls_Init(void) {
    const float screen_width = (float)CP_System_GetWindowWidth();
    const float screen_height = (float)CP_System_GetWindowHeight();
    const float stage_wall_thickness = 20.0f;
    CP_Color color = CP_Color_Create(255, 255, 255, 255);

    //middle platform
    level2_platform[0] = (Wall){ screen_width / 2.0f, screen_height - 300.0f, 100.0f, 20.0f, color, 0, 0, PLATFORM };
    //Lower Door platform
    level2_platform[1] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2, 200.0f, 20.0f, color, 0, 0, PLATFORM };
    //Upper Door platform
    level2_platform[2] = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2 - 200.0f, 200.0f, 20.0f, color, 0, 0, PLATFORM };

    level2_pressure_plate = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height - stage_wall_thickness, 100.0f, 10.0f, CP_Color_Create(113,121,126,255), 0, 0, PRESSURE_PLATE };
    level2_door = (Wall){ screen_width - stage_wall_thickness - 190.0f, screen_height / 2.0f - 100.0f, 20.0f, 180.0f, CP_Color_Create(113,121,126,255), 0,0 , DOOR };
    level2_exit_door = (Wall){ screen_width - stage_wall_thickness - 100.0f, screen_height / 2.0f - 85.0f, 100.0f, 150.0f, color, 0,0, EXIT_DOOR };
    level2_teleport_wall = (Wall){ screen_width - stage_wall_thickness - 5.0f,screen_height / 2.0f - 100.0f,10.0f,180.0f,color, 0,0 ,BLUE_TELEPORT };
}


 

