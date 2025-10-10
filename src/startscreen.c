//#include <stdio.h>
#include "cprocessing.h"
#include "fullscreen.h"
#include "mainmenu.h"


CP_Image logo;
int transition_alpha = 255;
static int GameIsRunning = 0;
//find out we need to initialize the vales of init,update, and exit for other game states. Comment by Teo Zijie. Completed by Teo Zijie.

void start_screen_init(void)
{
	float width = CP_System_GetWindowWidth();
	float height = CP_System_GetWindowHeight();

	CP_System_SetWindowSize(1600, 900);
	logo = CP_Image_Load("./Assets/DigiPen_Singapore_allrightsreserved.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	 
}

void displayStartScreen(void)
{
	float width = CP_System_GetWindowWidth();
	float height = CP_System_GetWindowHeight();
	float image_width = CP_Image_GetWidth(logo);
	float image_height = CP_Image_GetHeight(logo);
	//first function called once on startup of game, this shows the IGT logo on the screen. Comment by Teo Zijie.
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	
	CP_Image_Draw(logo, width / 2.0f, height / 2.0f, image_width, image_height, transition_alpha);
	/*CP_Image_Draw(logo, CP_System_GetWindowWidth() / 2.0, CP_System_GetWindowHeight() / 2.0, CP_Image_GetWidth(logo) / 1.0, CP_Image_GetHeight(logo) / 1.0, 255);*/
	// You can add more visual elements here, like a simple progress bar. Comment by Teo Zijie.
}
void start_screen_update(void)
{
	//Changes the alpha of CP_Image_Draw logo to fade in and out based on the current elapsed time
	float currentElapsedTime = CP_System_GetSeconds();
	if (currentElapsedTime < 2.0f) {  
		transition_alpha = (int)(currentElapsedTime / 2.0f * 255);
	}
	else if (currentElapsedTime < 4.0f) {  
		transition_alpha = 255;
	}
	else if (currentElapsedTime < 5.0f) {  
		transition_alpha = (int)((5.0f - currentElapsedTime) * 255);
	}
	
	if (GameIsRunning == 0) {
		if (currentElapsedTime < 5.0f && !(CP_Input_KeyDown(KEY_SPACE))) 
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
}

void start_screen_exit(void)
{
	CP_Image_Free(logo);
}