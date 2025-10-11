#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
 
static struct Player player;
static struct Stage_wall stage_wall[4];
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
		CP_Graphics_DrawQuad(stage_wall[i].stage_wall_coords[0], stage_wall[i].stage_wall_coords[1],
							stage_wall[i].stage_wall_coords[2], stage_wall[i].stage_wall_coords[3],
							stage_wall[i].stage_wall_coords[4], stage_wall[i].stage_wall_coords[5],
							stage_wall[i].stage_wall_coords[6], stage_wall[i].stage_wall_coords[7]);

	}

	//Draw player 
	CP_Graphics_DrawRectAdvanced(player.player_posX, player.player_posY, player.player_width, player.player_height, player.degree, 0);

	//Player movement

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

	//player facing direction
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
	

	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		if (fullscreen_state == 0) {
			fullscreen();
			fullscreen_state = 1;
		}
		else {
			CP_System_FullscreenAdvanced(1600, 900);
			fullscreen_state = 0;
		}
	}

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}