#include <stdio.h>
#include "CProcessing.h"
#include "mainmenu.h"
#include "utils.h"
 

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
float playerDiameter;

void Game_Init(void)
{
	printf("Game_Init() called\n");
	player1.posX = 100.0f;
	player1.posY = 100.0f;
	player2.posX = 200.0f;
	player2.posY = 100.0f;
	playerDiameter = 60.0f;
	player_no = player_1;
	degrees_1 == 0.0f;
	degrees_2 == 0.0f;
}

void Game_Update(void)
{
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	printf("Current player: %d\n", player_no);
	if (CP_Input_MouseClicked()) {
		printf("------------------------------------\n");
		printf("Click detected at (%.1f, %.1f)\n", mouseX, mouseY);
		printf("Player 1 is at (%.1f, %.1f)\n", player1.posX, player1.posY);
		printf("Player 2 is at (%.1f, %.1f)\n", player2.posX, player2.posY);
		if (IsCircleClicked(player1.posX, player1.posY, playerDiameter, mouseX, mouseY)) {
			player_no = player_1;
			 
		}
		if (IsCircleClicked(player2.posX, player2.posY, playerDiameter, mouseX, mouseY)) {
			printf("Player2: %f  %f\n",player2.posX, player2.posY);
			player_no = player_2;
			 
		}
	}
 
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
  
	}
	else {
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
		
		 
	}
	CP_Graphics_ClearBackground(CP_Color_Create(211, 211, 211, 255));
	if (player_no == player_1) {
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15.0f, player2.posY - 15.0f,
			player2.posX + 25.0f, player2.posY,
			player2.posX - 15.0f, player2.posY + 15.0f, degrees_2);
		//player 1 sprite
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15.0f, player1.posY - 15.0f,
			player1.posX + 25.0f, player1.posY,
			player1.posX - 15.0f, player1.posY + 15.0f, degrees_1);
	}
	else {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15.0f, player1.posY - 15.0f,
			player1.posX + 25.0f, player1.posY,
			player1.posX - 15.0f, player1.posY + 15.0f, degrees_1);

		//player 2 sprite
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15.0f, player2.posY - 15.0f,
			player2.posX + 25.0f, player2.posY,
			player2.posX - 15.0f, player2.posY + 15.0f, degrees_2);
	}

	if (player_no == player_1) {
		if (degrees_2 == 0.0f && player2.posX < (float)CP_System_GetWindowWidth() - 30.0f) {
			player2.posX += 7.0f;
			if (player2.posX >= (float)CP_System_GetWindowWidth() - 30.0f) { 
				degrees_2 = 180.0f;
				player2.posX += 7.0f;
			}
		 }
		else if (degrees_2 == 180.0f && player2.posX > 30.0f) {
			player2.posX -= 7.0f;
			if (player2.posX <= 30.0f) {
				degrees_2 = 0.0f;
				player2.posX -= 7.0f;
			}
		}
		else if (degrees_2 == 270.0f && player2.posY > 30.0f) {
			player2.posY -= 7.0f;
			if (player2.posY <= 30.0f) {
				player2.posY += 7.0f;
				degrees_2 = 90.0f;
			}
		}
		else if (degrees_2 == 90.0f && player2.posY < (float)CP_System_GetWindowHeight() - 30.0f) {
			player2.posY += 7.0f;
			if (player2.posY >= (float)CP_System_GetWindowHeight() - 30.0f) {
				player2.posY -= 7.0f;
				degrees_2 = 270.0f;
			}
		}

		
	}
	if (player_no == player_2) {
		if (degrees_1 == 0.0f && player1.posX < (float)CP_System_GetWindowWidth() - 30.0f) {
			player1.posX += 7.0f;
			if (player1.posX >= (float)CP_System_GetWindowWidth() - 30.0f) {
				degrees_1 = 180.0f;
				player1.posX += 7.0f;
			}
		}
		else if (degrees_1 == 180.0f && player1.posX > 30.0f) {
			player1.posX -= 7.0f;
			if (player1.posX <= 30.0f) {
				degrees_1 = 0.0f;
				player1.posX -= 7.0f;
			}
		}
		else if (degrees_1 == 270.0f && player1.posY > 30.0f) {
			player1.posY -= 7.0f;
			if (player1.posY <= 30.0f) {
				player1.posY += 7.0f;
				degrees_1 = 90.0f;
			}
		}
		else if (degrees_1 == 90.0f && player1.posY < (float)CP_System_GetWindowHeight() - 30.0f) {
			player1.posY += 7.0f;
			if (player1.posY >= (float)CP_System_GetWindowHeight() - 30.0f) {
				player1.posY -= 7.0f;
				degrees_1 = 270.0f;
			}
		}


	}

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}