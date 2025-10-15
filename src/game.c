#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "levelfive.h"
#include "game.h"
 
Level_Button button[5];

void Game_Init(void)
{
	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	mainmenu_TEXT = CP_Font_Load("Assets/Exo2-Regular.ttf");

	button[0] = (Level_Button){ screen_width/4.0f, 200.0f, 150.0f, 100.0f};
	button[1] = (Level_Button){ screen_width/2.0f, 200.0f, 150.0f, 100.0f};
	button[2] = (Level_Button){ screen_width/1.4f, 200.0f, 150.0f, 100.0f};
	button[3] = (Level_Button){ screen_width/3.0f, 700.0f, 150.0f, 100.0f};
	button[4] = (Level_Button){ screen_width/1.5f, 700.0f, 150.0f, 100.0f};
	text_width = 70.0f, text_height = 70.0f, textSize = 60.0f;
	CP_Settings_TextSize(textSize);
}
void Game_Update(void)
{

	float deltaTime = CP_System_GetDt();
	const float max_deltaTime = 0.02f; // cap deltaTime to be lower than 0.02f prevents collision tunneling
	if (deltaTime > max_deltaTime) {
		deltaTime = max_deltaTime;
	}
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Font_Set(mainmenu_TEXT);
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	for (int i = 0; i < 5; i++) {
		CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
		CP_Graphics_DrawRect(button[i].button_x, button[i].button_y, button[i].button_width, button[i].button_height);
	}

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("1", button[0].button_x, button[0].button_y);
	CP_Font_DrawText("2", button[1].button_x, button[1].button_y);
	CP_Font_DrawText("3", button[2].button_x, button[2].button_y);
	CP_Font_DrawText("4", button[3].button_x, button[3].button_y);
	CP_Font_DrawText("5", button[4].button_x, button[4].button_y);

	if (CP_Input_MouseClicked()) {

		if (IsAreaClicked(button[0].button_x, button[0].button_y, button[0].button_width, button[0].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelOne_Init, LevelOne_Update, LevelOne_Exit);
		}
		if (IsAreaClicked(button[1].button_x, button[1].button_y, button[1].button_width, button[1].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelTwo_Init, LevelTwo_Update, LevelTwo_Exit);
		}
		if (IsAreaClicked(button[2].button_x, button[2].button_y, button[2].button_width, button[2].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelThree_Init, LevelThree_Update, LevelThree_Exit);
		}
		if (IsAreaClicked(button[3].button_x, button[3].button_y, button[3].button_width, button[3].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelFour_Init, LevelFour_Update, LevelFour_Exit);
		}
		if (IsAreaClicked(button[4].button_x, button[4].button_y, button[4].button_width, button[4].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelFive_Init, LevelFive_Update, LevelFive_Exit);
		}
	}

	// Fullscreen and exit fullscreen
	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
	}
	// To get to Main Menu
	if (CP_Input_KeyTriggered(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{

}