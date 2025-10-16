#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"
#include "levelthree.h"

static Player player;
static Orb orb;
//Orb orbs[3];

void LevelOne_Init(void) {
    Stage_wall_Init(stage_wall, &stage_wall_count);
    Player_Init(&player, &orb);
 //   Player_Init(&player);
	//Orb_Init(&orbs);
	//orbCount = 0;
	//MaxOrb = 5;
	//for (int i = 0; i < 3; i++) {
	//	orbs[i].active = 0;
	//}
}

void LevelOne_Update(void) {
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

	//orb direction
	switch (player.direction) {
	case PLAYER_RIGHT:
		player.degree = 0;
		break;

    if (CP_Input_KeyDown(KEY_S)) {
        if (player.direction == PLAYER_LEFT || player.direction == PLAYER_RIGHT) {
            player.last_direction = player.direction;
        }
        player.direction = PLAYER_DOWN;
    }
    if (CP_Input_KeyReleased(KEY_S)) {
        player.direction = player.last_direction;
    }

    // Update player degree for projectiles
    switch (player.direction) {
    case PLAYER_RIGHT:
        player.degree = 0;
        break;
    case PLAYER_LEFT:
        player.degree = 180;
        break;
    case PLAYER_UP:
        if (CP_Input_KeyDown(KEY_W)) {
            printf("Looking Up");
            player.degree += 10;
        }
        break;
    case PLAYER_DOWN:
        if (CP_Input_KeyDown(KEY_S)) {
            printf("Looking down");
            player.degree -= 10;
        }
        break;
    }

    // Jumping
    if (CP_Input_KeyTriggered(KEY_SPACE) && player.isGrounded) {
        printf("jumpped!");
        player.player_velocityY = -jump_strength;
        player.isGrounded = 0;
    }
	case PLAYER_UP:
		if (CP_Input_KeyDown(KEY_W)) {
			printf("Looking Up");
			player.degree = 270;
		}
		break;

	case PLAYER_DOWN:
		if (CP_Input_KeyDown(KEY_S)) {
			printf("Looking down");
			player.degree = 90;
		}
		break;
	}
	////shoot orb
	//if (CP_Input_KeyTriggered(KEY_O)) {
	//	if (orbCount < MaxOrb) {
	//		if (player.degree == 0) {
	//			orbs[orbCount].x = player.player_posX;
	//			orbs[orbCount].y = player.player_posY;
	//			orbs[orbCount].vx = 20.0f;
	//			orbs[orbCount].vy = 0.0f;
	//			orbs[orbCount].active = 1;
	//			orbCount++;
	//			printf("shoot right");
	//		}
	//		if (player.degree == 180) {
	//			orbs[orbCount].x = player.player_posX;
	//			orbs[orbCount].y = player.player_posY;
	//			orbs[orbCount].vx = -20.0f;
	//			orbs[orbCount].vy = 0.0f;
	//			orbs[orbCount].active = 1;
	//			orbCount++;
	//			printf("shoot left");
	//		}
	//		if (player.degree == 270) {
	//			orbs[orbCount].x = player.player_posX;
	//			orbs[orbCount].y = player.player_posY;
	//			orbs[orbCount].vx = 0.0f;
	//			orbs[orbCount].vy = -20.0f;
	//			orbs[orbCount].active = 1;
	//			orbCount++;
	//			printf("shoot up");
	//		}
	//	}
	//}
	//for (int i = 0; i < MaxOrb; i++) {
	//	if (orbs[i].active) {

	//		orbs[i].x += orbs[i].vx;
	//		orbs[i].y += orbs[i].vy;
	//	}
	//}

	////teleport to orb
	//if (CP_Input_KeyTriggered(KEY_P)) {
	//	for (int i = MaxOrb - 1, j = 0; i >= 0; i--) {
	//		if (orbs[i].active) {
	//			player.player_posX = orbs[i].x;
	//			player.player_posY = orbs[i].y - 20;
	//			orbs[i].active = 0;
	//			break;
	//		}
	//	}

	//}


	//jumping
	//printf("%0.3f, %0.3f\n", player.player_posX, player.player_posY);
	if (CP_Input_KeyTriggered(KEY_SPACE) && player.isGrounded) {
		printf("jumpped!");
		player.player_velocityY = -jump_strength;
		player.isGrounded = 0;
	}
	player.player_velocityY += gravity * deltaTime;  //constant gravity
	player.player_posY += player.player_velocityY * deltaTime;
	player.isGrounded = 0;

    // Apply gravity
    player.player_velocityY += gravity * deltaTime;
    player.player_posY += player.player_velocityY * deltaTime;
    player.isGrounded = 0;

    // ========== VERTICAL COLLISION DETECTION ==========
    AABB playerHitBoxY = {
        player.player_posX - (player.player_width / 2.0f),
        player.player_posY - (player.player_height / 2.0f),
        player.player_width,
        player.player_height
    };

    AABB platformHitBoxY = {

        level1_platform[0].x - (level1_platform[0].width / 2.0f),
        level1_platform[0].y - (level1_platform[0].height / 2.0f),
        level1_platform[0].width,
        level1_platform[0].height
    };

    AABB ExitDoorHitBox = {
        level1_exit_door.x - (level1_exit_door.width / 2.0f),
        level1_exit_door.y - (level1_exit_door.height / 2.0f),
        level1_exit_door.width,
        level1_exit_door.height
    };


    //check if player has opened the door
    if (checkAABBCollision(playerHitBoxY, ExitDoorHitBox) && CP_Input_KeyTriggered(KEY_W)) {
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

        if (checkAABBCollision(playerHitBoxY, stagewallHitBox)) {
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
    if (checkAABBCollision(playerHitBoxY, platformHitBoxY)) {
        if (player.player_velocityY > 0) {
            // Landing on top
            player.player_posY = platformHitBoxY.y - (player.player_height / 2.0f) - breathing_space;
            player.player_velocityY = 0.0f;
            player.isGrounded = 1;
        }
        else if (player.player_velocityY < 0) {
            // Hitting bottom
            player.player_posY = platformHitBoxY.y + platformHitBoxY.height + (player.player_height / 2.0f) + breathing_space;
            player.player_velocityY = 0.0f;
        }
    }

    // ========== HORIZONTAL COLLISION DETECTION ==========

    player.player_posX += player_moveX;
    AABB playerHitBoxX = {
        player.player_posX - (player.player_width / 2.0f),
        player.player_posY - (player.player_height / 2.0f),
        player.player_width,
        player.player_height
    };


    // Check stage wall collisions (horizontal)
    for (int i = 0; i < stage_wall_count; i++) {
        AABB stagewallHitBox = {
            stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f),
            stage_wall[i].stage_wallY - (stage_wall[i].stage_wallheight / 2.0f),
            stage_wall[i].stage_wallwidth,
            stage_wall[i].stage_wallheight
        };

        if (checkAABBCollision(playerHitBoxX, stagewallHitBox)) {
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
    if (checkAABBCollision(playerHitBoxX, platformHitBoxY)) {
        if (player_moveX > 0) {
            // Hit left side of platform
            player.player_posX = platformHitBoxY.x - (player.player_width / 2.0f) - breathing_space;
        }
        else if (player_moveX < 0) {
            // Hit right side of platform
            printf("contact with platform!");
            float platform_right_edge = platformHitBoxY.x + platformHitBoxY.width;
            printf("%0.2f\n", platform_right_edge);
            player.player_posX = platform_right_edge + (player.player_width / 2.0f) + breathing_space;
        }
    }

    // Draw exit door
    CP_Graphics_DrawRect(level1_exit_door.x, level1_exit_door.y, level1_exit_door.width, level1_exit_door.height);

    // Draw stage walls
    for (int i = 0; i < stage_wall_count; i++) {
        CP_Settings_Fill(stage_wall[i].stage_wall_color);
        CP_Graphics_DrawRect(stage_wall[i].stage_wallX, stage_wall[i].stage_wallY,
            stage_wall[i].stage_wallwidth, stage_wall[i].stage_wallheight);
    }
    // Draw stage platforms
    for (int i = 0; i < 3; i++) {
        CP_Graphics_DrawRectAdvanced(level1_platform[i].x, level1_platform[i].y, level1_platform[i].width, level1_platform[i].height, 0.0f, 0.0f);

    }

    // Draw player
    CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY,
        player.player_width, player.player_height, player.degree, 0);

    if (CP_Input_KeyTriggered(KEY_Q)) {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }

	////Draw Orb
	//CP_Settings_Fill(CP_Color_Create(0, 200, 255, 255));
	//for (int i = 0; i < MaxOrb; i++) {
	//	if (orbs[i].active) {
	//		CP_Graphics_DrawCircle(orbs[i].x, orbs[i].y, 10.0f);
	//	}
	//}

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
	}

}

void LevelOne_Exit(void) {

}