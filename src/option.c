#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
#include "game.h"
#include "mainmenu.h"
#include "sound.h"

float mouseX, mouseY;
float volumePercent = 100;
float backButtonX, backButtonY;
float soundbarX, soundbarY;
float buttonWidth, buttonHeight;
float soundBarX, soundBarY;
float soundBarWidth, soundBarHeight;


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

	backButtonX = (float)(CP_System_GetWindowWidth() / 2);
	backButtonY = (float)(CP_System_GetWindowHeight() / 2 - 200);

	soundbarX = (float)(CP_System_GetWindowWidth() / 2);
	soundbarY = (float)(CP_System_GetWindowHeight() / 2 + 100);

	CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));


	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Font_Set(option_TEXT);
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//box of back button
	/*CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(backButtonX, backButtonY, buttonWidth, buttonHeight);*/
	CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
	CP_Image_Draw(mainmenu_ButtonBackground, soundbarX, soundbarY, buttonWidth, buttonHeight, 255);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("back", backButtonX, backButtonY);



	CP_Settings_RectMode(CP_POSITION_CORNER);
	//soundbar meter
	CP_Graphics_DrawRect(100, 50, 1400, 70); //rect of the volume meter
	CP_Settings_Fill(CP_Color_Create(225, 255, 0, 225)); //color of volume

            if (volumePercent < 0) volumePercent = 0;
            if (volumePercent > 100) volumePercent = 100;

            // 0-100 -> 0-1
            float volume = volumePercent / 100.0f;

            Sound_SetSFXVolume(volume);
            Sound_SetMusicVolume(volume);
        }
    }

	// sound bottun ui
	CP_Settings_Fill(CP_Color_Create(100, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("sound", soundbarX, soundbarY);


	//back button
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

void option_Exit(void) {
    CP_Image_Free(mainmenu_ButtonBackground);
    CP_Image_Free(mainmenu_ButtonWhenPressed);
    CP_Font_Free(mainmenu_TEXT);
}
