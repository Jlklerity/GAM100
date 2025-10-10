#pragma once
#include "cprocessing.h"


enum weapon_type {
	teleport_orb, destroy_orb
};

enum player_direction {
	PLAYER_UP,PLAYER_DOWN,PLAYER_LEFT,PLAYER_RIGHT
};
struct Player {
	float player_posX, player_posY;
	int player_width, player_height;
	CP_Color player_color;
	float gravity;
	int degree;
};

void Player_Init(struct Player *player);

