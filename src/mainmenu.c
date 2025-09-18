#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include <stdio.h>

CP_Font mainmenu_TEXT;
int textSize;
float width = 100;
float height = 100;
float mouseX, mouseY;
float playButtonX, playButtonY; 
float exitButtonX, exitButtonY; 
float buttonWidth, buttonHeight;
char debug_text[100];

void Main_Menu_Init(void)
{
	mainmenu_TEXT = CP_Font_Load("Assets/Exo2-Regular.ttf");
	textSize = 80;
	buttonWidth = 300.0f;
	buttonHeight = 150.0f;
	CP_Settings_TextSize(textSize);
	 
}

void Main_Menu_Update(void)
{
	playButtonX = (float)(CP_System_GetWindowWidth() / 2 - 40);
	playButtonY = (float)(CP_System_GetWindowHeight() / 2 - 210);
	exitButtonX = (float)(CP_System_GetWindowWidth() / 2 - 40);
	exitButtonY = (float)(CP_System_GetWindowHeight() / 2 + 190);
	float mouseX = (float)CP_Input_GetMouseX();
	float mouseY = (float)CP_Input_GetMouseY();
	sprintf_s(debug_text, 100, "Mouse: %.1f, %.1f", mouseX, mouseY);
	CP_Font_Set(mainmenu_TEXT);
	CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

	//box of play button
	CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(playButtonX, playButtonY, buttonWidth, buttonHeight);

	//box of exit button
	CP_Settings_Fill(CP_Color_Create(255, 128, 128, 255));
	CP_Graphics_DrawRect(exitButtonX, exitButtonY, buttonWidth, buttonHeight);

	CP_Settings_Fill(CP_Color_Create(0,0,0, 255));
	CP_Font_DrawText("Play", (float)CP_System_GetWindowWidth()/2 -100, (float)CP_System_GetWindowHeight()/2 -200);
	CP_Font_DrawText("Exit", (float)CP_System_GetWindowWidth()/2-100, (float)CP_System_GetWindowHeight()/2 +200);	
	
	if (CP_Input_MouseClicked()) {
		
		if (mouseX >= playButtonX && mouseX <= playButtonX + buttonWidth && mouseY
			>= playButtonY && mouseY <= playButtonY + buttonHeight) {
			CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
		}
		else if (mouseX >= exitButtonX && mouseX <= exitButtonX + buttonWidth &&
			mouseY >= exitButtonY && mouseY <= exitButtonY + buttonHeight) {
			CP_Engine_Terminate();
		}
	}
}

void Main_Menu_Exit(void)
{
	 
}
