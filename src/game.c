#include "CProcessing.h"
#include "mainmenu.h"
#include "utils.h"
#include <stdio.h>
 

struct playerPos {
	int posX, posY;
};
struct playerPos player1;
struct playerPos player2;

enum current_player {
	player_1,
	player_2
};

enum current_player player_no;
int degrees_1;
int degrees_2; 
float mouseX, mouseY;
int playerDiameter;
int speed;

void Game_Init(void)
{
	player1.posX = 100;
	player1.posY = 100;
	player2.posX = 200;
	player2.posY = 100;
	playerDiameter = 60;
	player_no = player_1;
	degrees_1 = 0;
	degrees_2 = 0;
	speed = 5;
}

void Game_Update(void)
{
	mouseX = (float)CP_Input_GetMouseX();
	mouseY = (float)CP_Input_GetMouseY();

	 
	if (CP_Input_MouseClicked()) {
		if (IsCircleClicked(player1.posX, player1.posY, playerDiameter, mouseX, mouseY)) {
			player_no = player_1;
		}
		if (IsCircleClicked(player2.posX, player2.posY, playerDiameter, mouseX, mouseY)) {
			player_no = player_2;
			 
		}
	}
 
	if (player_no == player_1) {

		if (CP_Input_KeyDown(KEY_W) && player1.posY > 30) {
		player1.posY -= speed;
		degrees_1 = 270;
		}
		else if (CP_Input_KeyDown(KEY_S) && player1.posY < (float)CP_System_GetWindowHeight()-30) {
			player1.posY += speed;
			degrees_1 = 90;
		}
		else if (CP_Input_KeyDown(KEY_A) && player1.posX > 30) {
			player1.posX -= speed;
			degrees_1 = 180;
		}
		else if (CP_Input_KeyDown(KEY_D) && player1.posX < (float)CP_System_GetWindowWidth()-30) {
			player1.posX += speed;
			degrees_1 = 0;
		}
  
	}
	else {
		if (CP_Input_KeyDown(KEY_W) && player2.posY > 30) {
			player2.posY -= speed;
			degrees_2 = 270;
		}
		else if (CP_Input_KeyDown(KEY_S) && player2.posY < (float)CP_System_GetWindowHeight() - 30) {
			player2.posY += speed;
			degrees_2 = 90;
		}
		else if (CP_Input_KeyDown(KEY_A) && player2.posX > 30) {
			player2.posX -= speed;
			degrees_2 = 180;
		}
		else if (CP_Input_KeyDown(KEY_D) && player2.posX < (float)CP_System_GetWindowWidth() - 30) {
			player2.posX += speed;
			degrees_2 = 0;
		}
		
		 
	}
	CP_Graphics_ClearBackground(CP_Color_Create(211, 211, 211, 255));
	if (player_no == player_1) {
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15, player2.posY - 15.,
			player2.posX + 25, player2.posY,
			player2.posX - 15, player2.posY + 15, degrees_2);
		//player 1 sprite
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15, player1.posY - 15,
			player1.posX + 25, player1.posY,
			player1.posX - 15, player1.posY + 15, degrees_1);
	}
	else {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(player1.posX, player1.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player1.posX - 15, player1.posY - 15,
			player1.posX + 25, player1.posY,
			player1.posX - 15, player1.posY + 15, degrees_1);

		//player 2 sprite
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawCircle(player2.posX, player2.posY, playerDiameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawTriangleAdvanced(player2.posX - 15, player2.posY - 15,
			player2.posX + 25, player2.posY,
			player2.posX - 15, player2.posY + 15, degrees_2);
	}

	if (player_no == player_1) {
		if (degrees_2 == 0 && player2.posX < (float)CP_System_GetWindowWidth() - 30) {
			player2.posX += speed;
			if (player2.posX >= (float)CP_System_GetWindowWidth() - 30) { 
				degrees_2 = 180;
				player2.posX += speed;
			}
		 }
		else if (degrees_2 == 180 && player2.posX > 30) {
			player2.posX -= speed;
			if (player2.posX <= 30
				) {
				degrees_2 = 0;
				player2.posX -= speed;
			}
		}
		else if (degrees_2 == 270 && player2.posY > 30) {
			player2.posY -= speed;
			if (player2.posY <= 30) {
				player2.posY += speed;
				degrees_2 = 90;
			}
		}
		else if (degrees_2 == 90 && player2.posY < (float)CP_System_GetWindowHeight() - 30) {
			player2.posY += speed;
			if (player2.posY >= (float)CP_System_GetWindowHeight() - 30) {
				player2.posY -= speed;
				degrees_2 = 270;
			}
		}

	}
	if (player_no == player_2) {
		if (degrees_1 == 0 && player1.posX < (float)CP_System_GetWindowWidth() - 30) {
			player1.posX += speed;
			if (player1.posX >= (float)CP_System_GetWindowWidth() - 30) {
				degrees_1 = 180;
				player1.posX += speed;
			}
		}
		else if (degrees_1 == 180 && player1.posX > 30) {
			player1.posX -= speed;
			if (player1.posX <= 30) {
				degrees_1 = 0;
				player1.posX -= speed;
			}
		}
		else if (degrees_1 == 270 && player1.posY > 30) {
			player1.posY -= speed;
			if (player1.posY <= 30) {
				player1.posY += speed;
				degrees_1 = 90;
			}
		}
		else if (degrees_1 == 90 && player1.posY < (float)CP_System_GetWindowHeight() - 30) {
			player1.posY += speed;
			if (player1.posY >= (float)CP_System_GetWindowHeight() - 30) {
				player1.posY -= speed;
				degrees_1 = 270;
			}
		}
	}

	if (player_no == player_1) {
		if (IsCircleColliding(player1.posX, player1.posY, player2.posX, player2.posY, playerDiameter)) {
				printf("Both collided (player1: %d,%d  player2: %d,%d\n)",player1.posX, player1.posY,player2.posX,player2.posY);
				if (player1.posX < player2.posX) {
					player2.posX += speed;
					degrees_2 = 0;
				}
				else if (player1.posX > player2.posX) {
					player2.posX -= speed;
					degrees_2 = 180;
				}
				else if (player1.posY > player2.posY) {
					player2.posY -= speed;
					degrees_2 = 270;
				}
				else if (player1.posY < player2.posY) {
					player2.posY += speed;
					degrees_2 = 90;
				}
					
				
			}
	}
	
	if (player1.posX == (float)CP_System_GetWindowWidth()-30) {
		player1.posX = (float)CP_System_GetWindowWidth() - 30;
		printf("player1 touches right wall!\n");
	
	}
	if (player1.posX < 30) {
		player1.posX = 30;
	
	}
	if (player1.posY > (float)CP_System_GetWindowHeight() - 30) {
		player1.posY = (float)CP_System_GetWindowHeight() - 30;
		
	}
	if (player1.posY < 30) {
		player1.posY = 30;
	
	}
	if (player2.posX > (float)CP_System_GetWindowWidth() - 30) {
		player2.posX = (float)CP_System_GetWindowWidth() - 30;
		
	}
	if (player2.posX < 30) {
		player2.posX = 30;
		
	}
	if (player2.posY > (float)CP_System_GetWindowHeight() - 30) {
		player2.posY = (float)CP_System_GetWindowHeight() - 30;
		
	}
	if (player2.posY < 30) {
		player2.posY = 30;
		
	}

	if (CP_Input_KeyDown(KEY_Q)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Game_Exit(void)
{
	
}