#include <stdio.h>
#include <string.h>
#include "CProcessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
 
 
struct Stage_wall {
	float stage_wall_coords[8];
	CP_Color stage_wall_color;
};

static struct Stage_wall stage_wall[4];
static int stage_wall_count = 0;

void Game_Init(void)
{
	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float stage_wall_thickness = 20.0f;
	const float stage_wall_highlight = 255.0f;

	float top_wall_coords[8] = { 0.0f, 0.0f, screen_width, 0.0f, screen_width, stage_wall_thickness, 0.0f, stage_wall_thickness };
	memcpy(stage_wall[0].stage_wall_coords, top_wall_coords, sizeof(top_wall_coords));
	stage_wall[0].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	stage_wall_count++;

	float bottom_wall_coords[8] = { 0.0f, screen_height - stage_wall_thickness, screen_width, screen_height - stage_wall_thickness,
									screen_width, screen_height, 0.0f, screen_height };
	memcpy(stage_wall[1].stage_wall_coords, bottom_wall_coords, sizeof(bottom_wall_coords));
	stage_wall[1].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	stage_wall_count++;

	float left_wall_coords[8] = { 0.0f, 0.0f, stage_wall_thickness, 0.0f, stage_wall_thickness, screen_height, 0.0f, screen_height };
	memcpy(stage_wall[2].stage_wall_coords, left_wall_coords, sizeof(left_wall_coords));
	stage_wall[2].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	stage_wall_count++;

	float right_wall_coords[8] = { screen_width - stage_wall_thickness, 0.0f, screen_width, 0.0f, screen_width, screen_height,
									screen_width - stage_wall_thickness, screen_height };
	memcpy(stage_wall[3].stage_wall_coords, right_wall_coords, sizeof(right_wall_coords));
	stage_wall[3].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	stage_wall_count++;
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




	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}