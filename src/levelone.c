#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"

 

static Player player;
Orb orbs[3];

void LevelOne_Init(void) {
	
    Stage_wall_Init(stage_wall, &stage_wall_count);
    Player_Init(&player);
	Orb_Init(&orbs);
	orbCount = 0;
	MaxOrb = 5;
	for (int i = 0; i < 3; i++) {
		orbs[i].active = 0;
	}
}

void LevelOne_Update(void) {
    float deltaTime = CP_System_GetDt();
    const float max_deltaTime = 0.02f; // cap deltaTime to be lower than 0.02f prevents collision tunneling
    if (deltaTime > max_deltaTime) {
        deltaTime = max_deltaTime;
    }
	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    float player_moveX = 0.0f;
    const float gravity = 2200.0f;
    const float jump_strength = 1200.0f;
	if (CP_Input_KeyDown(KEY_D)) {

		player_moveX += player.player_velocityX * deltaTime;
		player.direction = PLAYER_RIGHT;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player_moveX -= player.player_velocityX * deltaTime;
		player.direction = PLAYER_LEFT;
	}
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

	//orb direction
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
	//shoot orb
	if (CP_Input_KeyTriggered(KEY_O)) {
		if (orbCount < MaxOrb) {
			if (player.degree == 0) {
				orbs[orbCount].x = player.player_posX;
				orbs[orbCount].y = player.player_posY;
				orbs[orbCount].vx = 20.0f;
				orbs[orbCount].vy = 0.0f;
				orbs[orbCount].active = 1;
				orbCount++;
				printf("shoot right");
			}
			if (player.degree == 180) {
				orbs[orbCount].x = player.player_posX;
				orbs[orbCount].y = player.player_posY;
				orbs[orbCount].vx = -20.0f;
				orbs[orbCount].vy = 0.0f;
				orbs[orbCount].active = 1;
				orbCount++;
				printf("shoot left");
			}
			if (player.degree == 270) {
				orbs[orbCount].x = player.player_posX;
				orbs[orbCount].y = player.player_posY;
				orbs[orbCount].vx = 0.0f;
				orbs[orbCount].vy = -20.0f;
				orbs[orbCount].active = 1;
				orbCount++;
				printf("shoot up");
			}
		}
	}
	for (int i = 0; i < MaxOrb; i++) {
		if (orbs[i].active) {

			orbs[i].x += orbs[i].vx;
			orbs[i].y += orbs[i].vy;
		}
	}

	//teleport to orb
	if (CP_Input_KeyTriggered(KEY_P)) {
		for (int i = MaxOrb - 1, j = 0; i >= 0; i--) {
			if (orbs[i].active) {
				player.player_posX = orbs[i].x;
				player.player_posY = orbs[i].y - 20;
				orbs[i].active = 0;
				break;
			}
		}

	}


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

	AABB playerHitBoxY = {
		player.player_posX - (player.player_width / 2.0f),
		player.player_posY - (player.player_height / 2.0f),
		player.player_width,
		player.player_height
	};

	float platformTopLeftX = level_platform.x - (level_platform.width / 2.0f) ;
	float platformTopLeftY = level_platform.y - (level_platform.height / 2.0f) ;
	//printf("%0.2f %0.2f\n", platformTopLeftX, platformTopLeftY);
	AABB platform = {
		platformTopLeftX, platformTopLeftY,100.0f, 20.0f
	};

	for (int i = 0; i < stage_wall_count; i++) {
		AABB stagewallHitBox = {
			stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f),
			stage_wall[i].stage_wallY - (stage_wall[i].stage_wallheight / 2.0f),
			stage_wall[i].stage_wallwidth,
			stage_wall[i].stage_wallheight
		};

		if (checkAABBCollision(playerHitBoxY, stagewallHitBox)) {
			const float breathing_space = 0.1f;
			if (player.player_velocityY > 0) {
				player.player_posY = stagewallHitBox.y - (player.player_height / 2.0f) - breathing_space;
				player.player_velocityY = 0.0f;
				player.isGrounded = 1;
			}
			else if (player.player_velocityY < 0) {
				player.player_posY = stagewallHitBox.y + stagewallHitBox.height + (player.player_height / 2.0f) + breathing_space;
				player.player_velocityY = 0.0f;
				}
					break;
				}
	}
			if (checkAABBCollision(playerHitBoxY, platform)) {
				const float breathing_space = 0.1f;
				if (player.player_velocityY > 0) {
					float platform_top_edge = platform.y;
					player.player_posY = platform_top_edge - (player.player_height / 2.0f) - breathing_space;
					player.player_velocityY = 0.0f;
					player.isGrounded = 1;
				}
				else if (player.player_velocityY < 0) {
					float platform_bottom_edge = platform.y;
					player.player_posY = platform_bottom_edge + (player.player_height / 2.0f) + breathing_space;
					player.player_velocityY = 0.0f;
				}
			}
	player.player_posX += player_moveX;
	float playerTopLeftX = player.player_posX - (player.player_width / 2.0f);
	float playerTopLeftY = player.player_posY - (player.player_height / 2.0f);

	AABB playerHitBoxX = {
		playerTopLeftX,
		playerTopLeftY,
		player.player_width,
		player.player_height
	};
	

	for (int i = 0; i < stage_wall_count; i++) {
		float stage_TopLeftwallX = stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f);
		float stage_TopLeftwallY = stage_wall[i].stage_wallY - (stage_wall[i].stage_wallheight / 2.0f);

		AABB stagewallHitBox = {
			stage_TopLeftwallX,
			stage_TopLeftwallY,
			stage_wall[i].stage_wallwidth,
			stage_wall[i].stage_wallheight
		};
		if (checkAABBCollision(playerHitBoxX, stagewallHitBox)) {
			printf("Contact!");

			const float breathing_space = 0.1f;

			if (player_moveX > 0) {
				float wall_left_edge = stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f);
				player.player_posX = wall_left_edge - (player.player_width / 2.0f) - breathing_space;

			}
			else if (player_moveX < 0) {
				float wall_right_edge = stage_wall[i].stage_wallX + (stage_wall[i].stage_wallwidth / 2.0f);
				player.player_posX = wall_right_edge + (player.player_width / 2.0f) + breathing_space;

			}
			break;
		}
	}

	 
			/*printf("player: %0.2f\n", playerHitBoxX.x);*/
	if (checkAABBCollision(playerHitBoxX, platform)) {

		const float breathing_space = 0.1f;

		if (player_moveX > 0) {
			float platform_left_edge = platform.x ;
			 
			player.player_posX = platform_left_edge - (player.player_width / 2.0f) - breathing_space;
			

		}
		else if (player_moveX < 0) {
			printf("contact with platform!");
			float platform_right_edge = platform.x + (platform.width);
			printf("%0.2f\n", platform_right_edge);
			player.player_posX = platform_right_edge + (player.player_width / 2.0f) + breathing_space;
			
		}
	}
	//Draw stage walls
	for (int i = 0; i < stage_wall_count; i++) {
		CP_Settings_Fill(stage_wall[i].stage_wall_color);
		CP_Graphics_DrawRect(stage_wall[i].stage_wallX, stage_wall[i].stage_wallY, stage_wall[i].stage_wallwidth, stage_wall[i].stage_wallheight);
	}
	//Draw stage platforms
	CP_Graphics_DrawRectAdvanced(screen_width/2,screen_height-80.0f, 100.0f, 20.0f, 0.0f, 0.0f);

	//Draw player 
	CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY, player.player_width, player.player_height, player.degree, 0);

	//Draw Orb
	CP_Settings_Fill(CP_Color_Create(0, 200, 255, 255));
	for (int i = 0; i < MaxOrb; i++) {
		if (orbs[i].active) {
			CP_Graphics_DrawCircle(orbs[i].x, orbs[i].y, 10.0f);
		}
	}

	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
	}
}

void LevelOne_Exit(void) {
    
}