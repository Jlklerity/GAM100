#include <cprocessing.h>
#include "mainmenu.h"


static CP_Font font_credits;
static float timer = 0.0f;
static int current_slide = 0;
static float alpha = 0.0f; 

#define SLIDE_DURATION 4.0f  
#define FADE_SPEED 200.0f  

void Gamecredits_Init(void) {
	font_credits = CP_Font_Load("Assets/Exo2 - Regular.ttf");
	timer = 0.0f;
	current_slide = 0;
	alpha = 0.0f;
}

void Gamecredits_Update(void) {
	float deltaTime = CP_System_GetDt();
	float screenWidth = (float)CP_System_GetWindowWidth();
	float screenHeight = (float)CP_System_GetWindowHeight();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_KeyTriggered(KEY_ESCAPE) || CP_Input_MouseClicked()) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	timer += deltaTime;

	if (timer < 0.5f) {
		alpha += FADE_SPEED * deltaTime; 
	}
	else if (timer > SLIDE_DURATION - 0.5f) {
		alpha -= FADE_SPEED * deltaTime; 
	}
	else {
		alpha = 255.0f; 
	}
	if (alpha < 0) alpha = 0;
	if (alpha > 255) alpha = 255;

	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Font_Set(font_credits);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, (int)alpha));

	switch (current_slide) {

		case 0:
			CP_Settings_TextSize(60.0f);
			CP_Font_DrawText("TEAM DURIAN CATS", screenWidth / 2.0f, screenHeight / 2.0f);
			break;

		case 1:
			CP_Settings_TextSize(50.0f);
			CP_Font_DrawText("THE TEAM", screenWidth / 2.0f, 100.0f);

			CP_Settings_TextSize(30.0f);
			// Replace these with your actual names and roles
			CP_Font_DrawText("JEREMY LIM - Role", screenWidth / 2.0f, 200.0f);
			CP_Font_DrawText("TEO ZIJIE - Role", screenWidth / 2.0f, 250.0f);
			CP_Font_DrawText("CYRUS THAM - Role", screenWidth / 2.0f, 300.0f);
			CP_Font_DrawText("LIM ZI JIE - Role", screenWidth / 2.0f, 350.0f);
			break;

		case 2:
			CP_Settings_TextSize(40.0f);
			CP_Font_DrawText("FACULTY AND ADVISORS", screenWidth / 2.0f, 100.0f);
			CP_Settings_TextSize(25.0f);
			CP_Font_DrawText("Instructor Name", screenWidth / 2.0f, 200.0f);
			CP_Font_DrawText("Instructor Name", screenWidth / 2.0f, 250.0f);
			CP_Font_DrawText("TA Name", screenWidth / 2.0f, 300.0f);
			break;

		case 3:
			CP_Settings_TextSize(35.0f);
			CP_Font_DrawText("Created at DigiPen Institute of Technology Singapore", screenWidth / 2.0f, 100.0f);

			CP_Settings_TextSize(20.0f);
			float start_y = 200.0f;
			float gap = 30.0f;

			// Presidents and Executives list
			CP_Font_DrawText("PRESIDENT: CLAUDE COMAIR", screenWidth / 2.0f, start_y);
			CP_Font_DrawText("EXECUTIVES:", screenWidth / 2.0f, start_y + gap * 2);
			CP_Font_DrawText("JASON CHU", screenWidth / 2.0f, start_y + gap * 3);
			CP_Font_DrawText("SAMIR ABOU SAMRA", screenWidth / 2.0f, start_y + gap * 4);
			CP_Font_DrawText("MICHELE COMAIR", screenWidth / 2.0f, start_y + gap * 5);
			CP_Font_DrawText("ANGELA KUGLER", screenWidth / 2.0f, start_y + gap * 6);
			CP_Font_DrawText("ERIK MOHRMANN", screenWidth / 2.0f, start_y + gap * 7);
			CP_Font_DrawText("BENJAMIN ELLINGER", screenWidth / 2.0f, start_y + gap * 8);
			CP_Font_DrawText("MELVIN GONSALVEZ", screenWidth / 2.0f, start_y + gap * 9);

			// Copyright at bottom
			CP_Settings_TextSize(15.0f);
			CP_Font_DrawText("WWW.DIGIPEN.EDU", screenWidth / 2.0f, screenHeight - 70.0f);
			CP_Font_DrawText("All content \u00A9 2025 DigiPen Institute of Technology Singapore. All Rights Reserved.", screenWidth / 2.0f, screenHeight - 50.0f);
			break;

			case 4:
				CP_Settings_TextSize(40.0f);
				CP_Font_DrawText("TOOLS AND LIBRARIES", screenWidth / 2.0f, 100.0f);

				CP_Settings_TextSize(25.0f);
				CP_Font_DrawText("CProcessing", screenWidth / 2.0f, 200.0f);

				// Mandatory FMOD Credit
				CP_Font_DrawText("FMOD Sound System", screenWidth / 2.0f, 300.0f);
				CP_Font_DrawText("\u00A9 FireLight Technologies Pty Ltd (1998 - 2020)", screenWidth / 2.0f, 330.0f);
				break;

			default:
				// End of credits
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
				break;
	}

	if (timer >= SLIDE_DURATION) {
		current_slide++;
		timer = 0.0f;
		alpha = 0.0f;
	}
}
void Gamecredits_Exit(void) {
	CP_Font_Free(font_credits);
}