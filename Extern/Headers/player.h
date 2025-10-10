#pragma once
#include "cprocessing.h"

enum weapon_type {
	teleport_orb, destroy_orb
};

enum player_direction {
	PLAYER_UP,PLAYER_DOWN,PLAYER_LEFT,PLAYER_RIGHT
};
struct Player{
	float player_coords[8];
	CP_Color player_color;
	float gravity;
	int degree
};

void player_Movement(void);

