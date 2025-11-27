#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include "option.h"
#include "controls.h"
#include "creditscreen.h"
#include "howtoplay.h"

CP_Image menu_background;
float mouseX, mouseY;
static float logoX, logoY;
static float playButtonX, playButtonY;
static float exitButtonX, exitButtonY;
static float buttonWidth, buttonHeight;
static float optionButtonX, optionButtonY;
static float howtoPlayButtonX, howtoPlayButtonY;
static float controlsButtonX, controlsButtonY;
static float creditsButtonX, creditsButtonY;
static float btn_gap;
static float start_y;
static float center_x;

void Main_Menu_Init(void)
{
	mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	CP_Font_Set(mainmenu_TEXT);
	mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
	mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	menu_background = CP_Image_Load("./Assets/Piskel_sprite_assets/mainmenu.png");
	title = CP_Image_Load("./Assets/Piskel_sprite_assets/title.png");
	textSize = 32.0f;
	logoSize = 75.0f;
	buttonWidth = 200.0f;
	buttonHeight = 75.0f;
	btn_gap = 100.0f;
	center_x = CP_System_GetWindowWidth() / 2.0f;
	start_y = (CP_System_GetWindowHeight() / 2.0f) - (2.5f * btn_gap);
	
	logoX = center_x;
	logoY = start_y - 150.0f; // Logo is above the buttons

	playButtonX = center_x;
	playButtonY = start_y;

	optionButtonX = center_x;
	optionButtonY = start_y + btn_gap;

	howtoPlayButtonX = center_x;
	howtoPlayButtonY = start_y + (btn_gap * 2);

	controlsButtonX = center_x;
	controlsButtonY = start_y + (btn_gap * 3);

	creditsButtonX = center_x;
	creditsButtonY = start_y + (btn_gap * 4);

	exitButtonX = center_x;
	exitButtonY = start_y + (btn_gap * 5);
}

void Main_Menu_Update(void)
{

	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255)); //background color
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(menu_background, 0, 0, 1600 * 1.1f, 800 * 1.2f, 225); //background drawing mainmenu
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	
	//box of play button
	CP_Image_Draw(mainmenu_ButtonBackground, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
	//box of exit button
	CP_Image_Draw(mainmenu_ButtonBackground, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
	//box of option button
	CP_Image_Draw(mainmenu_ButtonBackground, optionButtonX, optionButtonY, buttonWidth, buttonHeight, 255);
	//box of howtoplay button
	CP_Image_Draw(mainmenu_ButtonBackground, howtoPlayButtonX, howtoPlayButtonY, buttonWidth+50.0f, buttonHeight, 255);
	//box of controls button
	CP_Image_Draw(mainmenu_ButtonBackground, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
	//box of credits button 
	CP_Image_Draw(mainmenu_ButtonBackground, creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, 255);

	//Draw logo
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(logoSize);
	//CP_Font_DrawText("TELESCAPE", logoX, logoY);

	CP_Image_Draw(title, 800, 50 , 250*2 , 40*2  , 225); //title image 

	//Draw button text
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(textSize);
	CP_Font_DrawText("Play", playButtonX, playButtonY);
	CP_Font_DrawText("Quit", exitButtonX, exitButtonY);
	CP_Font_DrawText("Option", optionButtonX, optionButtonY);
	CP_Font_DrawText("How To Play", howtoPlayButtonX, howtoPlayButtonY);
	CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);
	CP_Font_DrawText("Credits", creditsButtonX, creditsButtonY);


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
		if (IsAreaClicked(howtoPlayButtonX, howtoPlayButtonY, buttonWidth + 50.0f, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, howtoPlayButtonX, howtoPlayButtonY, buttonWidth + 50.0f, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("How To Play", howtoPlayButtonX, howtoPlayButtonY);
		}

		if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);
		}
		if (IsAreaClicked(creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("Credits", creditsButtonX, creditsButtonY);
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
		if (IsAreaClicked(howtoPlayButtonX, howtoPlayButtonY, buttonWidth + 50.0f, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(HowToPlay_Init, HowToPlay_Update, HowToPlay_Exit);
		}
		if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(controls_Init, controls_Update, controls_Exit);
		}
		if (IsAreaClicked(creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(Gamecredits_Init, Gamecredits_Update, Gamecredits_Exit);
		}
	}
}

void Main_Menu_Exit(void)
{
	CP_Image_Free(mainmenu_ButtonBackground);
	CP_Image_Free(mainmenu_ButtonWhenPressed);
	CP_Font_Free(mainmenu_TEXT);
	CP_Image_Free(menu_background);
	CP_Image_Free(keybox);
	CP_Font_Free(keytext);
}
