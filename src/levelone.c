#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"
#include "leveltwo.h"
#include "utils.h"


static float greenStartTime;
static Player player;
static Orb orb;
static int GameState = 1; //for pause state i guess...
static int DebugState = 0; //enable FPS and player coords
static float leveltime;

//fox animation sprite canvas
static int start_x = 0;
static int start_y = 128;
static int end_x = 64;
static int end_y = 192;

static float animation_timer;
static int frame_count = 0;   // counts frames for timing
static int idle_count = 0;    // counts idle frames
static int animation_speed = 10;


void LevelOne_Init(void) {
    //void Stage_Walls_Init();
    LoadLevelFromFile("Assets/Levels/level1.txt");
    Player_Init(&player, &orb);

    animation_timer = 0;  // added animation_timer (only dif in this void)

    greenStartTime = 0;
    // Loop to initialize all doors
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_door[i] != NULL) {
            g_level_door[i]->isActivated = 0;
        }
    }

    // Loop to initialize all destroyable walls
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_destroy_wall[i] != NULL) {
            g_level_destroy_wall[i]->isActivated = 0;
        }
    }

    leveltime = 99999.0f;
    orb.max_ammo = 3;
    orb.ammo = orb.max_ammo;
    orb.orb_type = TELEPORT_ORB;
}

void LevelOne_Update(void) {
    // ========== INITIALIZATION ==========

    float deltaTime = CP_System_GetDt();
    const float max_deltaTime = 0.02f;
    if (deltaTime > max_deltaTime) {
        deltaTime = max_deltaTime;
    }

    const float gravity = 2200.0f;
    const float jump_strength = 1200.0f;
    const float breathing_space = 0.1f;

    //get color to change for cp color create for green value

    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    // ========== INPUT HANDLING ==========

    // Horizontal movement
    float player_moveX = 0.0f;
    float orb_moveX = 0.0f;
    float orb_moveY = 0.0f;

    //Player movement, direction. x and y velocity, jumping
    Player_Update(&player, deltaTime, &player_moveX, jump_strength);

    // Apply gravity
    player.player_velocityY += gravity * deltaTime;
    player.player_posY += player.player_velocityY * deltaTime;
    player.isGrounded = 0;

    //Orb movement, direction, change orb type
    Orb_Update(&player, &orb, &player_moveX, &orb_moveX, &orb_moveY, deltaTime);

    // ========== VERTICAL COLLISION DETECTION ==========

    AABB playerHitBoxY = Get_Player_HitBox(&player);
    AABB ExitDoorHitBox = Get_Wall_HitBox(g_level_exit_door);
    AABB orbHitbox = Get_Orb_HitBox(&orb);
    // still need to initialize hitboxfor door and pressure plate, and need to write the function for both as well.

    player.player_posX += player_moveX;
    orb.x += orb_moveX;
    orb.y += orb_moveY;

    //check if player has opened the door
    if (checkAABBCollision(playerHitBoxY, ExitDoorHitBox) && CP_Input_KeyTriggered(KEY_W)) {
        CP_Engine_SetNextGameState(LevelTwo_Init, LevelTwo_Update, LevelTwo_Exit);
    }


    for (int i = 0; i < g_level_collidable_count; i++) {
        Wall* current_wall = g_level_collidables[i];
        if (current_wall->isActivated == 1) {
            continue;
        }
        AABB platformHitBox = Get_Wall_HitBox(current_wall);

        // --- Player Collision (always happens) ---
        Resolve_Collision_Wall_Player_Y(playerHitBoxY, platformHitBox, &player, breathing_space);

        // --- Orb Collision (check wall type) ---
        if (current_wall->type == RED_DESTROY) {
            Resolve_Collision_Destroy_Wall_Orb_Y(orbHitbox, platformHitBox, &orb, current_wall, breathing_space, orb_moveY);
        }
        else {
            Resolve_Collision_Wall_Orb_Y(orbHitbox, platformHitBox, &orb, &player, breathing_space, orb_moveY);
        }
    }


    // Loop and link plate[i] to door[i]
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_pressure_plate[i] == NULL || g_level_door[i] == NULL) {
            continue; // Skip if this pair doesn't exist
        }

        AABB floor_sensor_DoorHitBox = Get_Wall_HitBox(g_level_pressure_plate[i]);
        Resolve_Collision_FloorSensor_Player(playerHitBoxY, floor_sensor_DoorHitBox, g_level_door[i], g_level_pressure_plate[i]);
    };


    // ========== HORIZONTAL COLLISION DETECTION ==========

    AABB playerHitBoxX = Get_Player_HitBox(&player);
    playerHitBoxY.x = player.player_posX - (player.player_width / 2.0f);
    orbHitbox.x = orb.x - (orb.diameter / 2.0f);

    for (int i = 0; i < g_level_collidable_count; i++) {
        Wall* current_wall = g_level_collidables[i];
        if (current_wall->isActivated == 1) {
            continue;
        }
        AABB platformHitBox = Get_Wall_HitBox(current_wall);

        // --- Player Collision (always happens) ---
        Resolve_Collision_Wall_Player_X(playerHitBoxX, platformHitBox, &player, breathing_space, player_moveX);

        // --- Orb Collision (check wall type) ---
        if (current_wall->type == RED_DESTROY) {
            Resolve_Collision_Destroy_Wall_Orb_X(orbHitbox, platformHitBox, &orb, current_wall, breathing_space, orb_moveX);
        }
        else {
            Resolve_Collision_Wall_Orb_X(orbHitbox, platformHitBox, &orb, &player, breathing_space, orb_moveX);
        }
    }


    // Draw exit door
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(g_level_exit_door->x, g_level_exit_door->y, g_level_exit_door->width, g_level_exit_door->height);

    // Draw all platforms
    for (int i = 0; i < g_level_collidable_count; i++) {
        // Check if this object is a platform
        if (g_level_collidables[i]->type == PLATFORM || g_level_collidables[i]->type == STAGEWALL) {
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
            CP_Graphics_DrawRectAdvanced(g_level_collidables[i]->x, g_level_collidables[i]->y, g_level_collidables[i]->width, g_level_collidables[i]->height, 0.0f, 0.0f);
        }
    }
    //Draw all sensitive doors
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_door[i] != NULL && g_level_door[i]->isActivated == 0) {
            CP_Settings_Fill(CP_Color_Create(113, 121, 126, 255));
            CP_Graphics_DrawRectAdvanced(g_level_door[i]->x, g_level_door[i]->y, g_level_door[i]->width, g_level_door[i]->height, 0.0f, 0.0f);
        }
    }

    //Draw all floor sensors  
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_pressure_plate[i] != NULL) {
            CP_Settings_Fill(g_level_pressure_plate[i]->color);
            CP_Graphics_DrawRectAdvanced(g_level_pressure_plate[i]->x, g_level_pressure_plate[i]->y, g_level_pressure_plate[i]->width, g_level_pressure_plate[i]->height, 0.0f, 0.0f);
        }
    }
    //Draw Teleport Walls   
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_teleport_wall[i] != NULL) {
            CP_Settings_Fill(CP_Color_Create(0, RGBChange(greenStartTime), 255, 255));
            CP_Graphics_DrawRectAdvanced(g_level_teleport_wall[i]->x, g_level_teleport_wall[i]->y, g_level_teleport_wall[i]->width, g_level_teleport_wall[i]->height, 0.0f, 0.0f);
        }
    }
    //Draw Destroy Walls
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_destroy_wall[i] != NULL && g_level_destroy_wall[i]->isActivated == 0) {
            CP_Settings_Fill(g_level_destroy_wall[i]->color);
            CP_Graphics_DrawRectAdvanced(g_level_destroy_wall[i]->x, g_level_destroy_wall[i]->y, g_level_destroy_wall[i]->width, g_level_destroy_wall[i]->height, 0.0f, 0.0f);
        }
    }
    // Draw player
 /*   CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY,
        player.player_width, player.player_height, (float)player.degree, 0);*/

        // Draw Fox
    CP_Image_DrawSubImage(player.fox_sprite, player.player_posX, player.player_posY - 30.0f, player.player_width * 3.0f, player.player_height * 3.0f, (float)start_x, (float)start_y, (float)end_x, (float)end_y, 255);


    // Fox keyboard movement
    if (CP_Input_KeyDown(KEY_A)) {
        start_y = 0;       // walk left
        end_y = 64;
        idle_count = 0;
        animation_speed = 10;
    }
    else if (CP_Input_KeyDown(KEY_D)) {
        start_y = 64;      // walk right
        end_y = 128;
        idle_count = 0;
        animation_speed = 10;
    }
    else {
        idle_count++;
        if (idle_count < 300) { // ~10 frames idle before sleeping
            start_y = 128; // idle
            end_y = 192;
            animation_speed = 10;
        }
        else {
            start_y = 192; // sleep
            end_y = 256;
            animation_speed = 50;

        }
    }

    // animating the frames
   // --- animate frames roughly 3 FPS ---
    frame_count++;
    if (frame_count >= animation_speed) {  // every 10 frames change sprite (adjust to speed)
        frame_count = 0;

        start_x += 64;
        end_x += 64;

        if (start_x >= 64 * 4) { // 4 columns
            start_x = 0;
            end_x = 64;
        }
    }

    if (CP_Input_KeyTriggered(KEY_Q)) {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }

    //Level Timer 15s 
    LevelTimer(&leveltime);

    //FPS Counter & Player coordinates & Mouse coordinates & player pov
    if (CP_Input_KeyTriggered(KEY_LEFT_ALT)) {
        DebugState = 1 - DebugState;
    }
    if (DebugState == 1) {
        FPSCount();
        Player_Coords(&player);
        MousePos();
        PlayerPov(&player);
    }

    //Ammo counter
    OrbCount(&orb);

    //Pause screen
    if (CP_Input_KeyTriggered(KEY_P)) {
        GameState = 1 - GameState;
    }
    if (GameState == 0) {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 100));
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 20));
        CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2.0f, (float)CP_System_GetWindowHeight() / 2.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
    }
}

void LevelOne_Exit(void) {
    CP_Image_Free(player.fox_sprite);
}