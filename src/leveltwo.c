#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"
#include "levelthree.h"

static float greenStartTime;
static Player player;
Orb orb;

void LevelTwo_Init(void) {
    Stage_wall_Init(stage_wall, &stage_wall_count);
    Player_Init(&player, &orb);
    greenStartTime = 0;
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
    float currentTime = CP_System_GetSeconds();
    float elapsed = currentTime - greenStartTime;
    float pulseSpeed = 1.5f; // adjust for speed of pulsing
    float t = (currentTime - greenStartTime) * pulseSpeed;
    float greenValue = 115.0f + 75.0f * sinf(t);
    // 115 is midpoint, 75 is amplitude (115±75 = 40 to 190)
    int x = (int)greenValue;
    if (x < 0) x = 0;
    if (x > 255) x = 255;

    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    // ========== INPUT HANDLING ==========
    // Horizontal movement
    float player_moveX = 0.0f;
    if (CP_Input_KeyDown(KEY_D)) {
        player_moveX += player.player_velocityX * deltaTime;
        player.direction = PLAYER_RIGHT;
    }
    if (CP_Input_KeyDown(KEY_A)) {
        player_moveX -= player.player_velocityX * deltaTime;
        player.direction = PLAYER_LEFT;
    }

    // Vertical aiming
    if (CP_Input_KeyDown(KEY_W)) {
        if (player.direction == PLAYER_LEFT || player.direction == PLAYER_RIGHT) {
            player.last_direction = player.direction;
        }
        player.direction = PLAYER_UP;
    }
    if (CP_Input_KeyReleased(KEY_W)) {
        player.direction = player.last_direction;
    }

    if (CP_Input_KeyDown(KEY_S)) {
        if (player.direction == PLAYER_LEFT || player.direction == PLAYER_RIGHT) {
            player.last_direction = player.direction;
        }
        player.direction = PLAYER_DOWN;
    }
    if (CP_Input_KeyReleased(KEY_S)) {
        player.direction = player.last_direction;
    }

    // Jumping
    if (CP_Input_KeyTriggered(KEY_SPACE) && player.isGrounded) {
        printf("jumpped!");
        player.player_velocityY = -jump_strength;
        player.isGrounded = 0;
    }

   
    // Apply gravity
    player.player_velocityY += gravity * deltaTime;
    player.player_posY += player.player_velocityY * deltaTime;
    player.isGrounded = 0;

    if (CP_Input_KeyTriggered(KEY_1)) {
        player.orb_type = TELEPORT_ORB;
    }
    if (CP_Input_KeyTriggered(KEY_2)) {
        player.orb_type = DESTROY_ORB;
    }
    //Checking if orb is active in the air
    if (orb.isActive == 0) {
        if (CP_Input_KeyTriggered(KEY_J)) {
            orb.isActive = 1;
            orb.x = player.player_posX;
            orb.y = player.player_posY;
            orb.direction = player.direction;
        }
    }

    if(orb.isActive == 1){
        switch (orb.direction) {
        case PLAYER_RIGHT:
            player.degree = 0; //for sprite looking direction
            orb.x += orb.orb_velocity_x * deltaTime;
            if (CP_Input_KeyTriggered(KEY_K)) {
                player.player_posX = orb.x - player.player_width / 2;
                player.player_posY = orb.y;
                orb.isActive = 0;
            }
            break;
        case PLAYER_LEFT:
            player.degree = 180;
            orb.x -= orb.orb_velocity_x * deltaTime;
            if (CP_Input_KeyTriggered(KEY_K)) {
                player.player_posX = orb.x + player.player_width / 2;
                player.player_posY = orb.y;
                orb.isActive = 0;
            }
            break;
        case PLAYER_UP:
            orb.y -= orb.orb_velocity_Y * deltaTime;
            if (CP_Input_KeyTriggered(KEY_K)) {
                player.player_posX = orb.x;
                player.player_posY = orb.y + player.player_height / 2;
                orb.isActive = 0;
            }
            break;
        case PLAYER_DOWN:
            orb.y += orb.orb_velocity_Y * deltaTime;
            if (CP_Input_KeyTriggered(KEY_K)) {
                player.player_posX = orb.x;
                player.player_posY = orb.y - player.player_height / 2;
                orb.isActive = 0;
            }
            break;
        }
    //Change orb type
    switch (player.orb_type) {
        case TELEPORT_ORB:
            CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));            
            break;
        case DESTROY_ORB:
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));          
            break;
        default:
            CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
            break;
    }
        CP_Graphics_DrawCircle(orb.x, orb.y, orb.diameter);
}

    // ========== VERTICAL COLLISION DETECTION ==========
    /*AABB playerHitBox = {
        player.player_posX - (player.player_width / 2.0f),
        player.player_posY - (player.player_height / 2.0f),
        player.player_width,
        player.player_height
    };*/
    AABB playerHitBox = GetPlayerHitBox(&player);

    AABB platformHitBox = {
        
        level2_platform[0].x - (level2_platform[0].width / 2.0f),
        level2_platform[0].y - (level2_platform[0].height / 2.0f),
        level2_platform[0].width,
        level2_platform[0].height
    };

    AABB ExitDoorHitBox = {
        level2_exit_door.x - (level2_exit_door.width / 2.0f),
        level2_exit_door.y - (level2_exit_door.height / 2.0f),
        level2_exit_door.width,
        level2_exit_door.height
    };

    AABB orbHitbox = {
        orb.x,
        orb.y,
        orb.diameter,
        orb.diameter
    };
    
    player.player_posX += player_moveX;
    
    //check if player has opened the door
    if (checkAABBCollision(playerHitBox, ExitDoorHitBox) && CP_Input_KeyTriggered(KEY_W)) {
        CP_Engine_SetNextGameState(LevelThree_Init, LevelThree_Update, LevelThree_Exit);
    }
    // Check stage wall collisions (vertical)
    for (int i = 0; i < stage_wall_count; i++) {
        AABB stagewallHitBox = {
            stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f),
            stage_wall[i].stage_wallY - (stage_wall[i].stage_wallheight / 2.0f),
            stage_wall[i].stage_wallwidth,
            stage_wall[i].stage_wallheight
        };

        if (checkAABBCollision(playerHitBox, stagewallHitBox)) {
            if (player.player_velocityY > 0) {
                // Landing on top
                player.player_posY = stagewallHitBox.y - (player.player_height / 2.0f) - breathing_space;
                player.player_velocityY = 0.0f;
                player.isGrounded = 1;
            }
            else if (player.player_velocityY < 0) {
                // Hitting bottom
                player.player_posY = stagewallHitBox.y + stagewallHitBox.height + (player.player_height / 2.0f) + breathing_space;
                player.player_velocityY = 0.0f;
            }
            break;
        }
    }

    // Check platform collision (vertical)
    if (checkAABBCollision(playerHitBox, platformHitBox)) {
        if (player.player_velocityY > 0) {
            // Landing on top
            player.player_posY = platformHitBox.y - (player.player_height / 2.0f) - breathing_space;
            player.player_velocityY = 0.0f;
            player.isGrounded = 1;
        }
        else if (player.player_velocityY < 0) {
            // Hitting bottom
            player.player_posY = platformHitBox.y + platformHitBox.height + (player.player_height / 2.0f) + breathing_space;
            player.player_velocityY = 0.0f;
        }
    }

    // ========== HORIZONTAL COLLISION DETECTION ==========
   
    /*AABB playerHitBox = {
        player.player_posX - (player.player_width / 2.0f),
        player.player_posY - (player.player_height / 2.0f),
        player.player_width,
        player.player_height
    };*/

    playerHitBox.x = player.player_posX - (player.player_width / 2.0f);

    // Check stage wall collisions (horizontal)
    for (int i = 0; i < stage_wall_count; i++) {
        AABB stagewallHitBox = {
            stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f),
            stage_wall[i].stage_wallY - (stage_wall[i].stage_wallheight / 2.0f),
            stage_wall[i].stage_wallwidth,
            stage_wall[i].stage_wallheight
        };

        if (checkAABBCollision(playerHitBox, stagewallHitBox)) {
            printf("Contact!");

            if (player_moveX > 0) {
                // Hit left side of wall
                float wall_left_edge = stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f);
                player.player_posX = wall_left_edge - (player.player_width / 2.0f) - breathing_space;
            }
            else if (player_moveX < 0) {
                // Hit right side of wall
                float wall_right_edge = stage_wall[i].stage_wallX + (stage_wall[i].stage_wallwidth / 2.0f);
                player.player_posX = wall_right_edge + (player.player_width / 2.0f) + breathing_space;
            }
            break;
        }
    }

    // Check platform collision (horizontal)
    if (checkAABBCollision(playerHitBox, platformHitBox)) {
        if (player_moveX > 0) {
            // Hit left side of platform
            player.player_posX = platformHitBox.x - (player.player_width / 2.0f) - breathing_space;
        }
        else if (player_moveX < 0) {
            // Hit right side of platform
            printf("contact with platform!");
            float platform_right_edge = platformHitBox.x + platformHitBox.width;
            printf("%0.2f\n", platform_right_edge);
            player.player_posX = platform_right_edge + (player.player_width / 2.0f) + breathing_space;
        }
    }

    // Draw exit door
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(level2_exit_door.x, level2_exit_door.y, level2_exit_door.width, level2_exit_door.height);
  
    // Draw stage walls
    for (int i = 0; i < stage_wall_count; i++) {
        CP_Settings_Fill(stage_wall[i].stage_wall_color);
        CP_Graphics_DrawRect(stage_wall[i].stage_wallX, stage_wall[i].stage_wallY,
            stage_wall[i].stage_wallwidth, stage_wall[i].stage_wallheight);
    }
    // Draw stage platforms
    for (int i = 0; i < 3; i++) {
        CP_Graphics_DrawRectAdvanced(level2_platform[i].x, level2_platform[i].y, level2_platform[i].width, level2_platform[i].height, 0.0f, 0.0f);

    }
    
     
    ////default orb position
    //if (!(CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))) {
    //    orb.x = player.player_posX ;
    //    orb.y = player.player_posY ;
    //}
    //else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
    //     
    //    orb.x += player.player_velocityX * deltaTime;
    //    /*orb.y = player.player_posY - player.player_height;*/
    //}

    //Draw Teleport Wall   
    CP_Settings_Fill(CP_Color_Create(0, x, 255, 255));
    CP_Graphics_DrawRectAdvanced(level2_teleport_wall.x, level2_teleport_wall.y, level2_teleport_wall.width, level2_teleport_wall.height, 0.0f, 0.0f);
    
    // Draw player
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY,
        player.player_width, player.player_height, player.degree, 0);

    if (CP_Input_KeyTriggered(KEY_Q)) {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }
}

void LevelTwo_Exit(void) {

}