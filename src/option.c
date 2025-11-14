#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
#include "game.h"
#include "mainmenu.h"

//this is your own latest copy in 
float mouseX, mouseY;
float volume;
float backButtonX, backButtonY;
float soundbarX, soundbarY;
float resetbarX, resetbarY;
float resumebarX, resumebarY;
float mainmenubarX, mainmenubarY;
float restartbarX, restartbarY;
float buttonWidth, buttonHeight;

int pause_menu(void) {
	float textSize = 32.0f;
	buttonWidth = 200.0f;
	buttonHeight = 100.0f;
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 200));
	CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2.0f, (float)CP_System_GetWindowHeight() / 2.0f,
		(float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());

	resumebarX = (float)(CP_System_GetWindowWidth() / 2);
	resumebarY = (float)(CP_System_GetWindowHeight() / 2 - 200);

	mainmenubarX = (float)(CP_System_GetWindowWidth() / 2);
	mainmenubarY = (float)(CP_System_GetWindowHeight() / 2);

	restartbarX = (float)(CP_System_GetWindowWidth() / 2);
	restartbarY = (float)(CP_System_GetWindowHeight() / 2 + 200);

	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Font_Set(option_TEXT);
	CP_Settings_TextSize(textSize);
	CP_Image_Draw(mainmenu_ButtonBackground, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
	CP_Image_Draw(mainmenu_ButtonBackground, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
	CP_Image_Draw(mainmenu_ButtonBackground, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);


	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("resume", resumebarX, resumebarY);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("restart", restartbarX, restartbarY);

	// --- Handle Button Presses (Visual Feedback) ---
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
 			CP_Font_DrawText("resume", resumebarX, resumebarY);
		}
 		if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);
		}
		if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("restart", restartbarX, restartbarY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			return 1; // Signal 1: Resume Game
		}
		if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			return 2; // Signal 2: Go to Main Menu
		}
		if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			return 3; // Signal 3: restart level
		}
	}
	return 0;
}
void back_option(void) {
	backButtonX = (float)(CP_System_GetWindowWidth() / 2);
	backButtonY = (float)(CP_System_GetWindowHeight() / 2 - 200);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("back", backButtonX, backButtonY);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("back", backButtonX, backButtonY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}
void reset_option(void) {
	CP_Settings_TextSize(textSize);
	resetbarX = (float)(CP_System_GetWindowWidth() / 10);
	resetbarY = (float)(CP_System_GetWindowHeight() / 2 + 300);

	CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("reset", resetbarX, resetbarY);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("reset", resetbarX, resetbarY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			g_highest_level_unlocked = 1;
			Save_Progress();
		}
	}

}
void sound_option(void) {
	soundbarX = (float)(CP_System_GetWindowWidth() / 2);
	soundbarY = (float)(CP_System_GetWindowHeight() / 2 + 100);

	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Image_Draw(mainmenu_ButtonBackground, soundbarX, soundbarY, buttonWidth, buttonHeight, 255);

	CP_Settings_RectMode(CP_POSITION_CORNER);

	//soundbar meter
	CP_Graphics_DrawRect(100, 50, 1400, 70); //rect of the volume meter
	CP_Settings_Fill(CP_Color_Create(225, 255, 0, 225)); //color of volume


	CP_Graphics_DrawRect(100, 50, volume / 100 * 1400, 70); //vol bar
	if (CP_Input_KeyDown(KEY_LEFT)) {
		volume -= 1;
	}
	if (volume <= 0)
		volume = 0;


	CP_Graphics_DrawRect(100, 50, volume / 100 * 1400, 70); //vol level
	if (CP_Input_KeyDown(KEY_RIGHT)) {
		volume += 1;
	}
	if (volume >= 100)
		volume = 100;

	CP_Settings_Fill(CP_Color_Create(100, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("sound", soundbarX, soundbarY);
}
void back_option_gamemenu(void) {
	float textSize = 32.0f;
	buttonWidth = 150.0f;
	buttonHeight = 75.0f;
	CP_Settings_TextSize(textSize);
	backButtonX = (float)(CP_System_GetWindowWidth() / 10);
	backButtonY = (float)(CP_System_GetWindowHeight() / 10);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("back", backButtonX, backButtonY);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("back", backButtonX, backButtonY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}
void reset_option_gamemenu(void) {
	float textSize = 32.0f;
	buttonWidth = 150.0f;
	buttonHeight = 75.0f;
	CP_Settings_TextSize(textSize);
	resetbarX = (float)(CP_System_GetWindowWidth() / 10);
	resetbarY = (float)(CP_System_GetWindowHeight() / 2 + 300);

	CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("reset", resetbarX, resetbarY);

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
			CP_Font_DrawText("reset", resetbarX, resetbarY);
		}
	}
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
			g_highest_level_unlocked = 1;
			Save_Progress();
		}
	}

}

void option_Init(void) {
	mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
	mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	float textSize = 62.0f;
	buttonWidth = 300.0f;
	buttonHeight = 150.0f;
	CP_Settings_TextSize(textSize);
}


void option_Update(void) {

	if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) && (CP_Input_KeyDown(KEY_ENTER)))
	{
		fullscreen();
	}
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));
	CP_Font_Set(mainmenu_TEXT);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	sound_option(); 
	back_option();
}

void option_Exit(void) {
	CP_Image_Free(mainmenu_ButtonBackground);
	CP_Image_Free(mainmenu_ButtonWhenPressed);
	CP_Font_Free(mainmenu_TEXT);
}