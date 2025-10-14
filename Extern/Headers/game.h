#pragma once

typedef struct {
	float button_x, button_y;
	float button_width, button_height;
	
} Level_Button;

CP_Font mainmenu_TEXT;
float text_width, text_height;
float mouseX, mouseY;
int textSize;

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);