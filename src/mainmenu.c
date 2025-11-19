#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include "fullscreen.h"
#include "option.h"
#include "controls.h"

float mouseX, mouseY;
float logoX, logoY;
float playButtonX, playButtonY;
float exitButtonX, exitButtonY;
float buttonWidth, buttonHeight;
float optionButtonX, optionButtonY;
float controlsButtonX, controlsButtonY;

void Main_Menu_Init(void)
{
	mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	CP_Font_Set(mainmenu_TEXT);
	mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
	mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	textSize = 32.0f;
	logoSize = 75.0f;
	buttonWidth = 200.0f;
	buttonHeight = 75.0f;
	logoX = (float)(CP_System_GetWindowWidth() / 2);
	logoY = (float)(CP_System_GetWindowWidth() / 8.1f);
	playButtonX = (float)(CP_System_GetWindowWidth() / 2);
	playButtonY = (float)(CP_System_GetWindowHeight() / 3);
	exitButtonX = (float)(CP_System_GetWindowWidth() / 2);
	exitButtonY = (float)(CP_System_GetWindowHeight() / 1.2);

	optionButtonX = (float)(CP_System_GetWindowWidth() / 2);
	optionButtonY = (float)(CP_System_GetWindowHeight() / 2);

	controlsButtonX = (float)(CP_System_GetWindowWidth() / 2);
	controlsButtonY = (float)(CP_System_GetWindowHeight() / 1.5);
}

void Main_Menu_Update(void)
{
	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
	}

	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//box of play button
	CP_Image_Draw(mainmenu_ButtonBackground, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
	//box of exit button
	CP_Image_Draw(mainmenu_ButtonBackground, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
	//box of option button
	CP_Image_Draw(mainmenu_ButtonBackground, optionButtonX, optionButtonY, buttonWidth, buttonHeight, 255);
	//box of controls button
	CP_Image_Draw(mainmenu_ButtonBackground, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);


	//Draw logo
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(logoSize);
	CP_Font_DrawText("TELESCAPE", logoX, logoY);

	//Draw button text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(textSize);
	CP_Font_DrawText("Play", playButtonX, playButtonY);
	CP_Font_DrawText("Quit", exitButtonX, exitButtonY);
	CP_Font_DrawText("Option", optionButtonX, optionButtonY);
	CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("Play", playButtonX, playButtonY);
		}
		if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("Quit", exitButtonX, exitButtonY);
		}

		if (IsAreaClicked(optionButtonX, optionButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, optionButtonX, optionButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("option", optionButtonX, optionButtonY);
		}

		if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
		}
		if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_Terminate();
		}
		if (IsAreaClicked(optionButtonX, optionButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(option_Init, option_Update, option_Exit);
		}
		if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(controls_Init, controls_Update, controls_Exit);
		}
	}
}

void Main_Menu_Exit(void)
{
	CP_Image_Free(mainmenu_ButtonBackground);
	CP_Image_Free(mainmenu_ButtonWhenPressed);
	CP_Font_Free(mainmenu_TEXT);
}
