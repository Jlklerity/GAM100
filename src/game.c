#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
 
static Player player;
static Stage_wall stage_wall[4];
static int stage_wall_count = 0; 


void Game_Init(void)
{
	Stage_wall_Init(stage_wall, &stage_wall_count);
	Player_Init(&player);
}
void Game_Update(void)
{
	float deltaTime = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//Draw stage walls
	for (int i = 0; i < stage_wall_count; i++) {
		CP_Settings_Fill(stage_wall[i].stage_wall_color);
		CP_Graphics_DrawRect(stage_wall[i].stage_wallX, stage_wall[i].stage_wallY, stage_wall[i].stage_wallwidth, stage_wall[i].stage_wallheight);
	}

	//Draw player 
	CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY, player.player_width, player.player_height, player.degree, 0);
	
	AABB playerHitBox = {
		player.player_posX,
		player.player_posY,
		player.player_width,
		player.player_height
	};

	/*AABB stage_wallHitBox = {
		stage_wall[i].x, 
		stage_wall[i].y, 
		stage_wall[i].width, 
		stage_wall[i].height };
	};*/
	
	if (CP_Input_KeyDown(KEY_D)) {
		player.player_posX += player.player_speed * deltaTime;
		player.direction = PLAYER_RIGHT; 
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player.player_posX -= player.player_speed * deltaTime;
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
	// For future projectiles if statements.
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
	
	// Fullscreen and exit fullscreen
	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
	}
	// To get to Main Menu
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}