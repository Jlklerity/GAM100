//#include <stdio.h>
#include "cprocessing.h"
#include "fullscreen.h"
#include "mainmenu.h"


CP_Image logo;
 
static int GameIsRunning = 0;
//find out we need to initialize the vales of init,update, and exit for other game states. Comment by Teo Zijie. Completed by Teo Zijie.

void start_screen_init(void)
{
	CP_System_SetWindowSize(1600, 900);
	//CP_System_Fullscreen();
	logo = CP_Image_Load("./Assets/DigiPen_Singapore_WEB_WHITE.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

void displayStartScreen(void)
{
	//first function called once on startup of game, this shows the IGT logo on the screen. Comment by Teo Zijie.
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	CP_Image_Draw(logo, CP_System_GetWindowWidth() / 2.0, CP_System_GetWindowHeight() / 2.0, CP_Image_GetWidth(logo) / 1.0, CP_Image_GetHeight(logo) / 1.0, 255);
	// You can add more visual elements here, like a simple progress bar. Comment by Teo Zijie.
}
void start_screen_update(void)
{
	float currentElapsedTime = CP_System_GetSeconds();
	if (GameIsRunning == 0) {
		if (currentElapsedTime < 5.0f)
			{
				displayStartScreen();
			}
			else
			{
				GameIsRunning = 1;
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
	}
	
	//setting buttons needed to press for game to enable fullscreen. Comment by Teo Zijie. Completed by Teo Zijie.
	if ((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT)) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
	}
}

void start_screen_exit(void)
{
	CP_Image_Free(logo);
}