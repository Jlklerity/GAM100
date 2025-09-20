#include "CProcessing.h"
#include "mainmenu.h"

struct playerPos {
	float posX, posY;
};
struct playerPos player1;
struct playerPos player2;

enum current_player {
	player_1,
	player_2
};

enum current_player player_no;
float degrees_1 = 0.0f;
float degrees_2 = 0.0f;
float mouseX, mouseY;

void Game_Init(void)
{
	player1.posX = 100.0f;
	player1.posY = 100.0f;
	player2.posX = 200.0f;
	player2.posY = 100.0f;
	
	player_no = player_1;
}

void Game_Update(void)
{
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	if (CP_Input_MouseClicked()) {
						
		if (mouseX >= player1.posX  && mouseX <= player1.posX && 
			mouseY >= player1.posY && mouseY <= player1.posY) {
		
			CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
			
		}
		else if (mouseX >= player2.posX && mouseX <= player2.posX  &&
				mouseY >= player2.posY  && mouseY <= player2.posY) {
			CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
		
		}
	}
	CP_Graphics_ClearBackground(CP_Color_Create(211, 211, 211, 255));
	if (player_no == player_1) {

		if (CP_Input_KeyDown(KEY_W) && player1.posY > 30.0f) {
		player1.posY -= 7.0f;
		degrees_1 = 270.0f;
		}
		else if (CP_Input_KeyDown(KEY_S) && player1.posY < (float)CP_System_GetWindowHeight()-30.0f) {
			player1.posY += 7.0f;
			degrees_1 = 90.0f;
		}
		else if (CP_Input_KeyDown(KEY_A) && player1.posX > 30.0f) {
			player1.posX -= 7.0f;
			degrees_1 = 180.0f;
		}
		else if (CP_Input_KeyDown(KEY_D) && player1.posX < (float)CP_System_GetWindowWidth()-30.0f) {
			player1.posX += 7.0f;
			degrees_1 = 0.0f;
		}
		//Player 1 will render above player 2
		//player 2 sprite
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, 60.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15.0f, player2.posY - 15.0f,
			player2.posX + 25.0f, player2.posY,
			player2.posX - 15.0f, player2.posY + 15.0f, degrees_2);
		//player 1 sprite
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, 60.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15.0f, player1.posY - 15.0f,
			player1.posX + 25.0f, player1.posY,
			player1.posX - 15.0f, player1.posY + 15.0f, degrees_1);
	}
	if (player_no == player_2) {
		if (CP_Input_KeyDown(KEY_W) && player2.posY > 30.0f) {
			player2.posY -= 7.0f;
			degrees_2 = 270.0f;
		}
		else if (CP_Input_KeyDown(KEY_S) && player2.posY < (float)CP_System_GetWindowHeight() - 30.0f) {
			player2.posY += 7.0f;
			degrees_2 = 90.0f;
		}
		else if (CP_Input_KeyDown(KEY_A) && player2.posX > 30.0f) {
			player2.posX -= 7.0f;
			degrees_2 = 180.0f;
		}
		else if (CP_Input_KeyDown(KEY_D) && player2.posX < (float)CP_System_GetWindowWidth() - 30.0f) {
			player2.posX += 7.0f;
			degrees_2 = 0.0f;
		}
		//Player 2 will render above player 1
		//player 1 sprite
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, 60.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15.0f, player1.posY - 15.0f,
			player1.posX + 25.0f, player1.posY,
			player1.posX - 15.0f, player1.posY + 15.0f, degrees_1);
		//player 2 sprite
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, 60.0f);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15.0f, player2.posY - 15.0f,
			player2.posX + 25.0f, player2.posY,
			player2.posX - 15.0f, player2.posY + 15.0f, degrees_2);
	}

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}