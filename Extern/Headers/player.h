#pragma once
#include "cprocessing.h"


enum weapon_type {
	teleport_orb, destroy_orb
};

enum player_facingdirection {
	PLAYER_RIGHT,PLAYER_LEFT,PLAYER_UP,PLAYER_DOWN
};
typedef struct {
	float player_posX, player_posY;
	float player_width, player_height;
	CP_Color player_color;
	int degree;
	float player_velocityX;
	float player_velocityY;
	int isGrounded;
	enum player_facingdirection direction;
	enum player_facingdirection last_direction;
} Player;

extern float newX;
extern float newY;

void Player_Init(struct Player *player);



