#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "utils.h"
#include "stagewall.h"
#include "player.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "game.h"
#include "option.h"
Level_Button button[5];
int g_highest_level_unlocked = 1; //default to level1 being accessible


//fox animation sprite canvas
static int start_x = 0;
static int start_y = 64;
static int end_x = 64;
static int end_y = 128;

static float animation_timer;
static int frame_count = 0;   // counts frames for timing
static int idle_count = 0;    // counts idle frames
static int animation_speed = 10;


CP_Image fox_sprite;

void Load_Progress(void) {
	FILE* file_input = fopen("Assets/Levels/SaveData.txt", "r");
	if (!file_input) {
		Save_Progress();
		return;
	}
	fscanf_s(file_input, "%d", &g_highest_level_unlocked);
	fclose(file_input);

}

void Save_Progress(void) {
	FILE* file_output = fopen("Assets/Levels/SaveData.txt", "w");
	if (!file_output) {
		printf("Could not save progress!");
		return;
	}
	fprintf(file_output, "%d", g_highest_level_unlocked);
	fclose(file_output);
}


void Game_Init(void)
{
	option_Init();
	const float screen_width = (float)CP_System_GetWindowWidth();
	mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
	mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	Level_select = CP_Image_Load("./Assets/Piskel_sprite_assets/level_select.png");
	fox_sprite = CP_Image_Load("./Assets/Piskel_sprite_assets/FOX_ANIMATION_ALL_MOVEMENTS_05_JUMP.png");


	button[0] = (Level_Button){ screen_width/4.0f, 200.0f, 150.0f, 100.0f};
	button[1] = (Level_Button){ screen_width/2.0f, 200.0f, 150.0f, 100.0f};
	button[2] = (Level_Button){ screen_width/1.4f, 200.0f, 150.0f, 100.0f};
	button[3] = (Level_Button){ screen_width/3.0f, 700.0f, 150.0f, 100.0f};
	button[4] = (Level_Button){ screen_width/1.5f, 700.0f, 150.0f, 100.0f};
	textSize = 60.0f;
	CP_Settings_TextSize(textSize);
}
void Game_Update(void)
{
	Load_Progress();
	float deltaTime = CP_System_GetDt();
	const float max_deltaTime = 0.02f; // cap deltaTime to be lower than 0.02f prevents collision tunneling
	if (deltaTime > max_deltaTime) {
		deltaTime = max_deltaTime;
	}
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	CP_Font_Set(mainmenu_TEXT);
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));
	CP_Image_Draw( Level_select, (float)CP_System_GetWindowWidth()/2.0f, (float)CP_System_GetWindowHeight() / 2.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(),225);


	for (int i = 0; i < 5; i++) {
		int level_num = i + 1;
		if (level_num <= g_highest_level_unlocked) {
			CP_Image_Draw(mainmenu_ButtonBackground, button[i].button_x, button[i].button_y, button[i].button_width, button[i].button_height, 255);
		}
		else {
			CP_Image_Draw(mainmenu_ButtonBackground, button[i].button_x, button[i].button_y, button[i].button_width, button[i].button_height, 100);
		}
	}

	if (g_highest_level_unlocked >= 3) {
		//drawing fox sprite
		CP_Image_DrawSubImage(fox_sprite, 700, 430, 200, 200, (float)start_x, (float)start_y, (float)end_x, (float)end_y, 255);

		// animating the frames
		  // --- animate frames roughly 3 FPS ---
		frame_count++;
		if (frame_count >= animation_speed) {  // every 10 frames change sprite(adjust to speed)
			frame_count = 0;

			start_x += 64;
			end_x += 64;

			if (start_x >= 64 * 4) { // 4 columns
				start_x = 0;
				end_x = 64;
			}
		}
	
	}

	

	for (int i = 0; i < 5; i++) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(62.0f);
		char level_text[2];
		int level_num = i + 1;
		sprintf_s(level_text, 2, "%d", level_num);
		CP_Font_DrawText(level_text, button[i].button_x, button[i].button_y);
	}

	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		for (int i = 0; i < 5; i++) {
			if (IsAreaClicked(button[i].button_x, button[i].button_y, button[i].button_width, button[i].button_height, mouseX, mouseY)) {
				int level_num = i + 1;
					CP_Image_Draw(mainmenu_ButtonWhenPressed, button[i].button_x, button[i].button_y, button[i].button_width, button[i].button_height, 255);
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
					char level_text[2];
					sprintf_s(level_text, 2, "%d", level_num);
					CP_Font_DrawText(level_text, button[i].button_x, button[i].button_y);
				
			}
		}
	}

	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(button[0].button_x, button[0].button_y, button[0].button_width, button[0].button_height, mouseX, mouseY)) {
			CP_Engine_SetNextGameState(LevelOne_Init, LevelOne_Update, LevelOne_Exit);
		}
		if (IsAreaClicked(button[1].button_x, button[1].button_y, button[1].button_width, button[1].button_height, mouseX, mouseY) && g_highest_level_unlocked >= 2) {
			CP_Engine_SetNextGameState(LevelTwo_Init, LevelTwo_Update, LevelTwo_Exit);
		}
		if (IsAreaClicked(button[2].button_x, button[2].button_y, button[2].button_width, button[2].button_height, mouseX, mouseY) && g_highest_level_unlocked >= 3) {
			CP_Engine_SetNextGameState(LevelThree_Init, LevelThree_Update, LevelThree_Exit);
		}
	}
	// --- NEW "Back" Button ---
	float back_x = 150.0f;
	float back_y = 800.0f;
	float back_w = 200.0f;
	float back_h = 100.0f;

	CP_Settings_TextSize(48.0f);
	if (IsAreaClicked(back_x, back_y, back_w, back_h, mouseX, mouseY)) {
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, back_x, back_y, back_w, back_h, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
		}
		else {
			CP_Image_Draw(mainmenu_ButtonBackground, back_x, back_y, back_w, back_h, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
	else {
		CP_Image_Draw(mainmenu_ButtonBackground, back_x, back_y, back_w, back_h, 255);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Back", back_x, back_y);


	// --- NEW "Reset Progress" Button ---
	float reset_x = 1450.0f;
	float reset_y = 800.0f;
	float reset_w = 200.0f;
	float reset_h = 100.0f;

	CP_Settings_TextSize(32.0f);
	if (IsAreaClicked(reset_x, reset_y, reset_w, reset_h, mouseX, mouseY)) {
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
			CP_Image_Draw(mainmenu_ButtonWhenPressed, reset_x, reset_y, reset_w, reset_h, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
		}
		else {
			CP_Image_Draw(mainmenu_ButtonBackground, reset_x, reset_y, reset_w, reset_h, 255);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		}
		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
			g_highest_level_unlocked = 1;
			Save_Progress();
		}
	}
	else {
		CP_Image_Draw(mainmenu_ButtonBackground, reset_x, reset_y, reset_w, reset_h, 255);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("Reset All", reset_x, reset_y);

}

void Game_Exit(void)
{
	CP_Image_Free(fox_sprite);
	CP_Image_Free(mainmenu_ButtonBackground);
	CP_Image_Free(mainmenu_ButtonWhenPressed);
	option_Exit();
	CP_Font_Free(mainmenu_TEXT);
	CP_Image_Free(Level_select);
}