#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include "fullscreen.h"

CP_Font mainmenu_TEXT;
int textSize;

float mouseX, mouseY;
float playButtonX, playButtonY; 
float exitButtonX, exitButtonY; 
float buttonWidth, buttonHeight;
float TextWidth, TextHeight;


void Main_Menu_Init(void)
{
	mainmenu_TEXT = CP_Font_Load("Assets/Exo2-Regular.ttf");
	textSize = 80;
	buttonWidth = 300.0f;
	buttonHeight = 150.0f;
	TextWidth = 100, TextHeight = 100;

	CP_Settings_TextSize(textSize);
	 
}

void Main_Menu_Update(void)
{
	
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
	
	playButtonX = (float)(CP_System_GetWindowWidth() / 2);
	playButtonY = (float)(CP_System_GetWindowHeight() / 2 - 200);
	exitButtonX = (float)(CP_System_GetWindowWidth() / 2);
	exitButtonY = (float)(CP_System_GetWindowHeight() / 2 + 200);
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Font_Set(mainmenu_TEXT);
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//box of play button
	CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(playButtonX, playButtonY, buttonWidth, buttonHeight);

	//box of exit button
	CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(exitButtonX, exitButtonY, buttonWidth, buttonHeight);

	CP_Settings_Fill(CP_Color_Create(0,0,0, 255));
	CP_Font_DrawText("Play", playButtonX - 60, playButtonY + 25);
	CP_Font_DrawText("Exit", exitButtonX - 60, exitButtonY + 25);
	

	if (CP_Input_MouseClicked()) {

		if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
		}
		if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_Terminate();
		}
	}
	 
}

void Main_Menu_Exit(void)
{
	 
}
