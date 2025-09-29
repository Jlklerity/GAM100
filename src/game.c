#include "CProcessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
#include <stdio.h>
#include "CProcessing.h"
#include "mainmenu.h"

 
void Game_Init(void)
{
	int wallLeftPosX = (int)(CP_System_GetWindowWidth() / 2);
	int wallLeftPosY = (int)(CP_System_GetWindowWidth() / 2);
	int wallRightPosX = (int)(CP_System_GetWindowWidth() / 2);
	int wallRightPosY = (int)(CP_System_GetWindowWidth() / 2);
	int wallTopPosX = (int)(CP_System_GetWindowWidth() / 2);
	int wallTopPosY = (int)(CP_System_GetWindowWidth() / 2);
	int wallBottomPosX = (int)(CP_System_GetWindowWidth() / 2);
	int wallBottomPosY = (int)(CP_System_GetWindowWidth() / 2);
	int wallwidth = 100, wallHeight = 100;
}

void Game_Update(void)
{

	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//Draw Level boundaries



	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}