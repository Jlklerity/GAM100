#pragma once
#include "cprocessing.h"

enum Orb_Type {
	TELEPORT_ORB, DESTROY_ORB
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
	enum Orb_Type orb_type;
	enum player_facingdirection direction;
	enum player_facingdirection last_direction;
} Player;

typedef struct {
	float x, y;
	float diameter;
	float orb_velocity_x, orb_velocity_Y;
	int direction;
	int isActive;
	enum Orb_Type orb_type;
} Orb;

//extern int orbCount;
//extern int maxOrb;

void Player_Init(Player *player, Orb *orb);
float Player_Update(Player* player, Orb* orb, float deltaTime, float player_moveX, float jump_strength);

//extern Player player;
//
//
//extern int orbCount;
//extern int MaxOrb;
//
//typedef struct {
//	float x, y;
//	float vx, vy;
//	float size;
//	int active;
//	CP_Color orb_color;
//} Orb;
//
//void Orb_Init(Orb* orbs);

