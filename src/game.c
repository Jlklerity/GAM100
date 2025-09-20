#include "CProcessing.h"
#include "mainmenu.h"

struct playerPos {
	float posX, posY;
};
struct playerPos player1;
struct playerPos player2;
float degrees = 0.0f;

void Game_Init(void)
{
	player1.posX = 100.0f;
	player1.posY = 100.0f;
	player2.posX = 100.0f;
	player2.posY = 100.0f;
}

void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(211, 211, 211, 255));
	if (CP_Input_KeyDown(KEY_W) && player1.posY > 30.0f) {
		player1.posY -= 7.0f;
		degrees = 270.0f;
	}
	else if (CP_Input_KeyDown(KEY_S) && player1.posY < (float)CP_System_GetWindowHeight()-30.0f) {
		player1.posY += 7.0f;
		degrees = 90.0f;
	}
	else if (CP_Input_KeyDown(KEY_A) && player1.posX > 30.0f) {
		player1.posX -= 7.0f;
		degrees = 180.0f;
	}
	else if (CP_Input_KeyDown(KEY_D) && player1.posX < (float)CP_System_GetWindowWidth()-30.0f) {
		player1.posX += 7.0f;
		degrees = 0.0f;
	}
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(player1.posX, player1.posY, 60.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangleAdvanced(player1.posX-15.0f, player1.posY-15.0f,
									player1.posX+25.0f, player1.posY,
									player1.posX-15.0f, player1.posY+15.0f, degrees);

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}