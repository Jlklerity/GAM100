#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
 

static struct Stage_wall stage_wall[4];
static int stage_wall_count = 0;


void Game_Init(void)
{
	Stage_wall_Init(stage_wall, &stage_wall_count);
}
void Game_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//Draw stage walls
	for (int i = 0; i < stage_wall_count; i++) {
		CP_Settings_Fill(stage_wall[i].stage_wall_color);
		CP_Graphics_DrawQuad(stage_wall[i].stage_wall_coords[0], stage_wall[i].stage_wall_coords[1],
							stage_wall[i].stage_wall_coords[2], stage_wall[i].stage_wall_coords[3],
							stage_wall[i].stage_wall_coords[4], stage_wall[i].stage_wall_coords[5],
							stage_wall[i].stage_wall_coords[6], stage_wall[i].stage_wall_coords[7]);
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