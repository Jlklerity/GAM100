#pragma once

typedef struct {
	float button_x, button_y;
	float button_width, button_height;
	
} Level_Button;

CP_Font debug_TEXT;
CP_Font mainmenu_TEXT;
CP_Image mainmenu_ButtonBackground;
CP_Image mainmenu_ButtonWhenPressed;
CP_Font option_TEXT; //author: Zi Jie (for options menu)

float mouseX, mouseY;
float textSize;
float logoSize;
extern int g_highest_level_unlocked;

void Load_Progress(void);
void Save_Progress(void);

void Game_Init(void);

void Game_Update(void);

void Game_Exit(void);