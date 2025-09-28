#include "startscreen.h"

void displayStartScreen(void)
{
	//first function called once on startup of game, this shows the IGT logo on the screen. Comment by Teo Zijie.
	CP_Engine_SetNextGameStateForced(start_screen_init, start_screen_update, start_screen_exit);
	CP_Image_Draw(logo1, (float)CP_System_GetWindowWidth() / 2.0f, (float)CP_System_GetWindowHeight() / 2.0f, CP_Image_GetWidth(logo1) / 1.0, CP_Image_GetHeight(logo1) / 1.0, 255);
	//You can add more visual elements here, like a simple progress bar. Comment by Teo Zijie.
}

void start_screen_update(void)
{
	float currentElapsedTime = CP_System_GetSeconds();
	if (currentElapsedTime < 5.0f)
	{
		displayStartScreen();
	}
	else
	{
		CP_Engine_SetNextGameState(main_menu_init, main_menu_update, main_menu_exit);
	}
	//setting buttons needed to press for game to enable fullscreen. Comment by Teo Zijie. Completed by Teo Zijie.
	if ((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT)) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
		//set int fullscreen_state = 0;
	}
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
}

void start_screen_exit(void)
{
	CP_Image_Free(logo);
}