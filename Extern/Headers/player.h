#pragma once
#include "cprocessing.h"


enum weapon_type {
	teleport_orb, destroy_orb
};

enum player_facingdirection {
	PLAYER_RIGHT,PLAYER_LEFT,PLAYER_UP,PLAYER_DOWN
};
struct Player {
	float player_posX, player_posY;
	int player_width, player_height;
	CP_Color player_color;
	int gravity;
	int degree;
	int player_speed;
	enum player_facingdirection direction;
	enum player_facingdirection last_direction;
};

void Player_Init(struct Player *player);



