#pragma once

typedef struct {
	float button_x, button_y;
	float button_width, button_height;
	
} Level_Button;

CP_Font mainmenu_TEXT;
CP_Image mainmenu_ButtonBackground;
CP_Image mainmenu_ButtonWhenPressed;
float mouseX, mouseY;
int textSize;

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);