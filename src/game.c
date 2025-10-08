#include <stdio.h>
#include "CProcessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"



static float Stage_Wall[8];


void Game_Init(void)
{
	float stage_coords[8] = {
		0.0f, 0.0f,
		100.0f, 0.0f,
		100.0f, 100.0f,
		0.0f, 100.0f
};

	for (int i = 0; i < 8; ++i) {
		Stage_Wall[i] = stage_coords[i];
	}
}
void Game_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//Draw Level boundaries
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawQuad(Stage_Wall[0], Stage_Wall[1], Stage_Wall[2], Stage_Wall[3],
						Stage_Wall[4], Stage_Wall[5], Stage_Wall[6], Stage_Wall[7]);




	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}