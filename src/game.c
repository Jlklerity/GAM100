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

void Game_Init(void)
{
	Stage_wall_Init(stage_wall, &stage_wall_count);
	Player_Init(&player);
	if (newX != 0) {
		player.player_posX = newX;
	}
	if (newY != 0) {
		player.player_posY = newY;
	}
}
void Game_Update(void)
{
	float deltaTime = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));
	
	float player_moveX = 0.0f;
	float player_moveY = 0.0f;

	if (CP_Input_KeyDown(KEY_D)) {
		
		player_moveX += player.player_speed * deltaTime;
		player.direction = PLAYER_RIGHT; 
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player_moveX -= player.player_speed * deltaTime;
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
	player.player_posX += player_moveX;
	
	float playerTopLeftX = player.player_posX - (player.player_width / 2.0f);
	float playerTopLeftY = player.player_posY - (player.player_height / 2.0f);
	AABB playerHitBox = {
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
		if (checkAABBCollision(playerHitBox, stagewallHitBox)) {
			printf("Contact!");
			player.player_posX -= player_moveX;
			 
			if (player_moveX > 0) {
				float wall_left_edge = stage_wall[i].stage_wallX - (stage_wall[i].stage_wallwidth / 2.0f);
				player.player_posX = wall_left_edge - (player.player_width / 2.0f);
			}
			else if (player_moveX < 0) {
				float wall_right_edge = stage_wall[i].stage_wallX + (stage_wall[i].stage_wallwidth / 2.0f);
				player.player_posX = wall_right_edge + (player.player_width / 2.0f);
			}
			const float breathing_space = 0.01f;
			if (player_moveX > 0) player.player_posX -= breathing_space;
			if (player_moveX < 0) player.player_posX += breathing_space;
			break;
		}
	}
	//Draw stage walls
	for (int i = 0; i < stage_wall_count; i++) {
		CP_Settings_Fill(stage_wall[i].stage_wall_color);
		CP_Graphics_DrawRect(stage_wall[i].stage_wallX, stage_wall[i].stage_wallY, stage_wall[i].stage_wallwidth, stage_wall[i].stage_wallheight);
	}
	//Draw player 
	CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY, player.player_width, player.player_height, player.degree, 0);
	
	
	
	// Fullscreen and exit fullscreen
	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		if (newX == 0 && newY == 0) {
			newX = player.player_posX;
			newY = player.player_posY;
		}
		fullscreen();
		Game_Init();
		newX = 0;
		newY = 0;
	}
	// To get to Main Menu
	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{

}