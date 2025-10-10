#include "player.h"
#include <string.h>



void Player_Init(struct Player *player) {
	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const int player_width = 64;
	const int player_height = 64;
	const float player_highlight = 255.0f;
	const float posX = 100, posY = 800;
	const int degree = 0; //player facing right

	player->direction = PLAYER_RIGHT;
	player->last_direction = PLAYER_RIGHT;
	player->player_posX = posX;
	player->player_posY = posY;
	player->degree = 0;
	player->player_width = player_width;
	player->player_height = player_height;
	player->player_color = CP_Color_Create(255, 0, 0, player_highlight);
}