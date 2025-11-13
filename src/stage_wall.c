#include "cprocessing.h"
#include "stage_wall.h"
#include "hazards.h"
#include <stdio.h>
#include <string.h>

//Wall stage_wall[4];  // Shared walls 
//int stage_wall_count = 0;

 
// This array holds the ACTUAL wall data for the currently loaded level
static Wall s_level_objects[MAX_LEVEL_OBJECTS];
static int s_level_object_count = 0;
static Laser s_level_lasers[MAXLASER];
static int s_level_laser_count = 0;

// These are POINTERS that level files (leveltwo.c)
// will use to access the loaded objects.
Wall* g_stage_wall[MAX_LEVEL_OBJECTS] = { 0 };
Wall* g_level_platforms[MAX_LEVEL_OBJECTS] = { 0 }; // Array for platforms
Wall* g_level_pressure_plate[MAX_LEVEL_OBJECTS] = { 0 };
Wall* g_level_door[MAX_LEVEL_OBJECTS] = { 0 };
Wall* g_level_exit_door = NULL;
Wall* g_level_teleport_wall[MAX_LEVEL_OBJECTS] = { 0 };
Wall* g_level_destroy_wall[MAX_LEVEL_OBJECTS] = { 0 };
Laser* g_level_laser[MAXLASER] = { 0 };

// Pointers to any other collidable objects (like platforms)
Wall* g_level_collidables[MAX_LEVEL_OBJECTS];
int g_level_collidable_count = 0;
int g_laser_count;

void LoadLaserFromFile(const char* filename) {
    s_level_laser_count = 0;
    g_laser_count = 0;
    memset(g_level_laser, 0, sizeof(g_level_laser));
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("ERROR: Could not load level file: %s\n", filename);
        return;
    }
    char line_buffer[256];
    char type_str[50];
    float x, y, width, time;
    int direction, state;
    int laser_index = 0; //to count laser
    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        // Skip comments and empty lines
        if (line_buffer[0] == '#' || line_buffer[0] == '\n') {
            continue;
        }
        int items_read = sscanf(line_buffer, "%s %f %f %f %f %d %d",
            type_str, &x, &y, &width, &time, &direction, &state);

        if (items_read == 7 && s_level_laser_count < MAXLASER) {
            Laser* new_laser = &s_level_lasers[s_level_laser_count];
            Direction dir = (Direction)direction;
            Laser_State laser_state = (Laser_State)state;
            *new_laser = (Laser){ x,y,width,time,dir,laser_state };
            if (laser_index < MAXLASER) {
                g_level_laser[laser_index++] = new_laser;
            }
            s_level_laser_count++;
            g_laser_count++;
        }
    }
    fclose(file);
}

void LoadLevelFromFile(const char* filename) {
    // 1. Reset all counters and pointers
    s_level_object_count = 0;
    g_level_collidable_count = 0;
    // Use memset to clear the arrays to all-bits-zero(NULL)
    // memset sets every variable inside the array to 0
    memset(g_level_pressure_plate, 0, sizeof(g_level_pressure_plate));
    memset(g_level_door, 0, sizeof(g_level_door));
    memset(g_level_teleport_wall, 0, sizeof(g_level_teleport_wall));
    memset(g_level_destroy_wall, 0, sizeof(g_level_destroy_wall));
    memset(g_level_platforms, 0, sizeof(g_level_platforms));
    memset(g_stage_wall, 0, sizeof(g_stage_wall));
    g_level_exit_door = NULL;
    
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
    int laser_index = 0;

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


 

