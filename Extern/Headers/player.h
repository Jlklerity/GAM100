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

	//drawing of sprites 
	CP_Image fox_sprite;
	CP_Image destroy_orb;
	CP_Image teleport_orb;

} Player;

typedef struct {
	float x, y;
	float diameter;
	float orb_velocity_x, orb_velocity_Y;
	int direction;
	int isActive;
	int ammo;
	int max_ammo;
	enum Orb_Type orb_type;
} Orb;



void Player_Init(Player *player, Orb *orb);
void Player_Update(Player* player, float deltaTime, float *player_moveX, float jump_strength);
void Orb_Update(Player* player, Orb* orb, float *orb_moveX, float *orb_moveY, float deltaTime);


