#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include "fullscreen.h"

CP_Font mainmenu_TEXT;
CP_Image mainmenu_ButtonBackground;
CP_Image mainmenu_ButtonWhenPressed;
int textSize;
float mouseX, mouseY;
float playButtonX, playButtonY; 
float exitButtonX, exitButtonY; 
float buttonWidth, buttonHeight;


void Main_Menu_Init(void)
{
	mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
	mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	textSize = 72;
	buttonWidth = 300.0f;
	buttonHeight = 150.0f;
	CP_Settings_TextSize(textSize);
	 
}

void Main_Menu_Update(void)
{
	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
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
	/*CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(playButtonX, playButtonY, buttonWidth, buttonHeight);*/
	CP_Image_Draw(mainmenu_ButtonBackground, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);

	//box of exit button
	/*CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(exitButtonX, exitButtonY, buttonWidth, buttonHeight);*/
	CP_Image_Draw(mainmenu_ButtonBackground, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
	CP_Settings_Fill(CP_Color_Create(0,0,0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Play", playButtonX, playButtonY);
	CP_Font_DrawText("Exit", exitButtonX, exitButtonY);
	

	
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
			if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
				CP_Image_Draw(mainmenu_ButtonWhenPressed, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
				CP_Font_DrawText("Play", playButtonX, playButtonY);
			}
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
			if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
				CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
			}
		}
	
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
			if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
				CP_Image_Draw(mainmenu_ButtonWhenPressed, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
				CP_Font_DrawText("Exit", exitButtonX, exitButtonY);
			}
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
			if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
				CP_Engine_Terminate();
			}
		}
	
}
	 

void Main_Menu_Exit(void)
{
	 
}
