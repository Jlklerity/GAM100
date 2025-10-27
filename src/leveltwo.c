#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"
#include "levelthree.h"
#include "utils.h"

static float greenStartTime;
Player player;
Orb orb;
static int GameState = 1; //for pause state i guess...
static int DebugState = 0; //enable FPS and player coords
static float leveltime;

void LevelTwo_Init(void) {
    Stage_Walls_Init();
    level2_Object_Walls_Init();
    Player_Init(&player, &orb);
    greenStartTime = 0;
    level2_door.isActivated = 0; // Start with the door closed
    leveltime = 15.0f;
}

void LevelTwo_Update(void) {
    // ========== INITIALIZATION ==========

    float deltaTime = CP_System_GetDt();
    const float max_deltaTime = 0.02f;
    if (deltaTime > max_deltaTime) {
        deltaTime = max_deltaTime;
    }

    const float screen_width = (float)CP_System_GetWindowWidth();
    const float screen_height = (float)CP_System_GetWindowHeight();
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
    Player_Update(&player, &orb, deltaTime, &player_moveX, jump_strength);

    // Apply gravity
    player.player_velocityY += gravity * deltaTime;
    player.player_posY += player.player_velocityY * deltaTime;
    player.isGrounded = 0;

    //Orb movement, direction, change orb type
    Orb_Update(&player, &orb, &player_moveX, &orb_moveX, &orb_moveY, deltaTime);

    // ========== VERTICAL COLLISION DETECTION ==========

    AABB playerHitBoxY = Get_Player_HitBox(&player);
    AABB ExitDoorHitBox = Get_Wall_HitBox(&level2_exit_door);
    AABB Pressure_sense_DoorHitBox = Get_Wall_HitBox(&level2_door);
    AABB floor_sensor_DoorHitBox = Get_Wall_HitBox(&level2_pressure_plate);
    AABB TeleportWallHitBox = Get_Wall_HitBox(&level2_teleport_wall);
    AABB orbHitbox = Get_Orb_HitBox(&orb);
    // still need to initialize hitboxfor door and pressure plate, and need to write the function for both as well.

    player.player_posX += player_moveX;
    orb.x += orb_moveX;
    orb.y += orb_moveY;

    //check if player has opened the door
    if (checkAABBCollision(playerHitBoxY, ExitDoorHitBox) && CP_Input_KeyTriggered(KEY_W)) {
        CP_Engine_SetNextGameState(LevelThree_Init, LevelThree_Update, LevelThree_Exit);
    }

    // Check stage wall collisions (vertical)
    for (int i = 0; i < stage_wall_count; i++) {
        AABB stagewallHitBox = Get_Wall_HitBox(&stage_wall[i]);
        Resolve_Collision_Wall_Player_Y(playerHitBoxY, stagewallHitBox, &player, breathing_space);
        Resolve_Collision_Wall_Orb_Y(orbHitbox, stagewallHitBox, &orb, &player, breathing_space, orb_moveY);
    }
    for (int i = 0; i < 3; i++) {
        AABB platformHitBox = Get_Wall_HitBox(&level2_platform[i]);
        Resolve_Collision_Wall_Player_Y(playerHitBoxY, platformHitBox, &player, breathing_space);
        Resolve_Collision_Wall_Orb_Y(orbHitbox, platformHitBox, &orb, &player, breathing_space, orb_moveY);
    }

    // Check platform collision (vertical)
    Resolve_Collision_Wall_Orb_Y(orbHitbox, TeleportWallHitBox, &orb, &player, breathing_space, orb_moveY);
    // Check pressure door collision (vertical)
    if (level2_door.isActivated == 0) {
        Resolve_Collision_Wall_Player_Y(playerHitBoxY, Pressure_sense_DoorHitBox, &player, breathing_space);
        Resolve_Collision_Wall_Orb_Y(orbHitbox, Pressure_sense_DoorHitBox, &orb, &player, breathing_space, orb_moveY);
    }
    Resolve_Collision_FloorSensor_Player(playerHitBoxY, floor_sensor_DoorHitBox, &player, &level2_door, &level2_pressure_plate);

    // ========== HORIZONTAL COLLISION DETECTION ==========

    AABB playerHitBoxX = Get_Player_HitBox(&player);
    playerHitBoxY.x = player.player_posX - (player.player_width / 2.0f);
    AABB orbHitBoxX = Get_Orb_HitBox(&orb);
    orbHitbox.x = orb.x - (orb.diameter / 2.0f);

    // Check stage wall collisions (horizontal)
    for (int i = 0; i < stage_wall_count; i++) {
        AABB stagewallHitBox = Get_Wall_HitBox(&stage_wall[i]);
        Resolve_Collision_Wall_Player_X(playerHitBoxX, stagewallHitBox, &player, breathing_space, player_moveX);
        Resolve_Collision_Wall_Orb_X(orbHitbox, stagewallHitBox, &orb, &player, breathing_space, orb_moveX);
    }

    for (int i = 0; i < 3; i++) {
        AABB platformHitBox = Get_Wall_HitBox(&level2_platform[i]);
        Resolve_Collision_Wall_Player_X(playerHitBoxX, platformHitBox, &player, breathing_space, player_moveX);
        Resolve_Collision_Wall_Orb_X(orbHitbox, platformHitBox, &orb, &player, breathing_space, orb_moveX);
    }

    // Check platform collision (horizontal)
    Resolve_Collision_Wall_Orb_X(orbHitbox, TeleportWallHitBox, &orb, &player, breathing_space, orb_moveX);
    // Check pressure door collision (horizontal)
    if (level2_door.isActivated == 0) {
        Resolve_Collision_Wall_Player_X(playerHitBoxX, Pressure_sense_DoorHitBox, &player, breathing_space, player_moveX);
        Resolve_Collision_Wall_Orb_X(orbHitbox, Pressure_sense_DoorHitBox, &orb, &player, breathing_space, orb_moveX);
    }
    // Draw exit door
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(level2_exit_door.x, level2_exit_door.y, level2_exit_door.width, level2_exit_door.height);

    // Draw stage walls
    for (int i = 0; i < stage_wall_count; i++) {
        CP_Settings_Fill(stage_wall[i].color);
        CP_Graphics_DrawRect(stage_wall[i].x, stage_wall[i].y,
            stage_wall[i].width, stage_wall[i].height);
    }
    // Draw stage platforms
    for (int i = 0; i < 3; i++) {
        CP_Graphics_DrawRectAdvanced(level2_platform[i].x, level2_platform[i].y, level2_platform[i].width, level2_platform[i].height, 0.0f, 0.0f);

    }
    //Draw pressure sensitive wall
    if (level2_door.isActivated == 0) {
        CP_Settings_Fill(CP_Color_Create(113, 121, 126, 255));
        CP_Graphics_DrawRectAdvanced(level2_door.x, level2_door.y, level2_door.width, level2_door.height, 0.0f, 0.0f);
    }

    //Draw floor sensor
    CP_Settings_Fill(level2_pressure_plate.color);
    CP_Graphics_DrawRectAdvanced(level2_pressure_plate.x, level2_pressure_plate.y, level2_pressure_plate.width, level2_pressure_plate.height, 0.0f, 0.0f);


    //Draw Teleport Wall   
    CP_Settings_Fill(CP_Color_Create(0, RGBChange(greenStartTime), 255, 255));
    CP_Graphics_DrawRectAdvanced(level2_teleport_wall.x, level2_teleport_wall.y, level2_teleport_wall.width, level2_teleport_wall.height, 0.0f, 0.0f);

    // Draw player
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY,
        player.player_width, player.player_height, (float)player.degree, 0);

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

void LevelTwo_Exit(void) {
    
}