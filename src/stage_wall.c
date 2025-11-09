#include "cprocessing.h"
#include "stage_wall.h"
#include <stdio.h>
#include <string.h>

//Wall stage_wall[4];  // Shared walls 
//int stage_wall_count = 0;

 
// This array holds the ACTUAL wall data for the currently loaded level
static Wall s_level_objects[MAX_LEVEL_OBJECTS];
static int s_level_object_count = 0;

// These are POINTERS that level files (leveltwo.c)
// will use to access the loaded objects.
Wall* g_stage_wall[MAX_LEVEL_OBJECTS] = { 0 };
Wall* g_level_platforms[MAX_LEVEL_OBJECTS] = { 0 }; // Array for platforms
Wall* g_level_pressure_plate[MAX_LEVEL_OBJECTS] = { 0 };;
Wall* g_level_door[MAX_LEVEL_OBJECTS] = { 0 };;
Wall* g_level_exit_door = NULL;
Wall* g_level_teleport_wall[MAX_LEVEL_OBJECTS] = { 0 };;
Wall* g_level_destroy_wall[MAX_LEVEL_OBJECTS] = { 0 };;

// Pointers to any other collidable objects (like platforms)
Wall* g_level_collidables[MAX_LEVEL_OBJECTS];
int g_level_collidable_count = 0;


//void Stage_Walls_Init(void) {
//    const float screen_width = (float)CP_System_GetWindowWidth();
//    const float screen_height = (float)CP_System_GetWindowHeight();
//    const float stage_wall_thickness = 20.0f;
//    stage_wall_count = 4;
//    //const float orb_diameter = 50.0f;
//    CP_Color color = CP_Color_Create(255, 255, 255, 255);
//
//    //top wall
//    stage_wall[0] = (Wall){ screen_width / 2.0f, stage_wall_thickness / 2.0f, screen_width, stage_wall_thickness, color, 0, 0, STAGEWALL }; //example
//    //bottom wall
//    stage_wall[1] = (Wall){ screen_width / 2.0f, screen_height - (stage_wall_thickness / 2.0f), screen_width, stage_wall_thickness, color, 0, 0,STAGEWALL };
//    //left wall
//    stage_wall[2] = (Wall){ stage_wall_thickness / 2.0f, screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };
//    //right wall
//    stage_wall[3] = (Wall){ screen_width - (stage_wall_thickness / 2.0f), screen_height / 2.0f, stage_wall_thickness, screen_height, color, 0, 0,STAGEWALL };
//
//}

void LoadLevelFromFile(const char* filename) {
    // 1. Reset all counters and pointers
    s_level_object_count = 0;
    g_level_collidable_count = 0;
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_level_pressure_plate[i] = NULL;
    }
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_level_door[i] = NULL;
    }
    g_level_exit_door = NULL;
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_level_teleport_wall[i] = NULL;
    }
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_level_destroy_wall[i] = NULL;
    }
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_level_platforms[i] = NULL;
    }
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        g_stage_wall[i] = NULL;
    }
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("ERROR: Could not load level file: %s\n", filename);
        return;
    }

    char line_buffer[256];
    char type_str[50];
    float x, y, w, h;
    int wall_type_enum_int;

    int platform_index = 0; // To count platforms
    int pressure_plate_index = 0;
    int door_index = 0;
    int teleport_wall_index = 0;
    int destroy_wall_index = 0;
    int stage_wall_index = 0;

    // 2. Read file line by line
    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        // Skip comments and empty lines
        if (line_buffer[0] == '#' || line_buffer[0] == '\n') {
            continue;
        }

        // 3. Parse the line
        int items_read = sscanf(line_buffer, "%s %f %f %f %f %d",
                                type_str, &x, &y, &w, &h, &wall_type_enum_int);

        if (items_read == 6 && s_level_object_count < MAX_LEVEL_OBJECTS) {
            // Get the new wall object from our static pool
            Wall* new_wall = &s_level_objects[s_level_object_count];
            enum TypeofWall type = (enum TypeofWall)wall_type_enum_int;

            // 4. Assign its data
            *new_wall = (Wall){x, y, w, h, CP_Color_Create(255, 255, 255, 255), 0, 0, type};

            // 5. Assign global pointers based on type
            //    And set special colors
            switch (type) {
                case STAGEWALL: // You forgot to handle STAGEWALL
                    if (stage_wall_index < MAX_LEVEL_OBJECTS) {
                        g_stage_wall[stage_wall_index++] = new_wall;
                    }
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
                case PLATFORM:
                    if (platform_index < MAX_LEVEL_OBJECTS) {
                        g_level_platforms[platform_index++] = new_wall;
                    }
                    // Add to general collidable list
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
                case PRESSURE_PLATE:
                    if (pressure_plate_index < MAX_LEVEL_OBJECTS) {
                        g_level_pressure_plate[pressure_plate_index++] = new_wall;
                    }
                    new_wall->color = CP_Color_Create(113, 121, 126, 255);
                    // Don't add to collidables, it's handled special
                    break;
                case DOOR:
                    if (door_index < MAX_LEVEL_OBJECTS) {
                        g_level_door[door_index++] = new_wall;
                    }
                    new_wall->color = CP_Color_Create(113, 121, 126, 255);
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
                case EXIT_DOOR:
                    g_level_exit_door = new_wall;
                    // Not physically collidable
                    break;
                case BLUE_TELEPORT:
                    if (teleport_wall_index < MAX_LEVEL_OBJECTS) {
                        g_level_teleport_wall[teleport_wall_index++] = new_wall;
                    }
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
                case RED_DESTROY:
                    if (destroy_wall_index < MAX_LEVEL_OBJECTS) {
                        g_level_destroy_wall[destroy_wall_index++] = new_wall;
                    }
                    new_wall->color = CP_Color_Create(255, 0, 0, 255);
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
                default:
                    // Any other types
                    g_level_collidables[g_level_collidable_count++] = new_wall;
                    break;
            }
            s_level_object_count++;
        }
    }
    fclose(file);
}


 

