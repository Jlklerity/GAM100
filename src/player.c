#include "player.h"
#include "stage_wall.h"
#include "collisionHandling.h"

float newX = 0;
float newY = 0;

void Player_Init(Player *player, Orb *orb) {
	Stage_wall_Init(stage_wall, &stage_wall_count);

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float player_width = 64.0f;
	const float player_height = 64.0f;
	const float player_highlight = 255.0f;
	const float posX = 100, posY = screen_height - player_height/2 - stage_wall[1].stage_wallheight;
	const int degree = 0; //player facing right
	/*orbCount = 0;
	maxOrb = 5;*/

	player->orb_type = TELEPORT_ORB;
	player->player_velocityX = 400.0f;
	player->player_velocityY = 300.0f;
	player->isGrounded = 0;
	player->direction = PLAYER_RIGHT;
	player->last_direction = PLAYER_RIGHT;
	player->player_posX = posX;
	player->player_posY = posY;
	player->degree = 0;
	player->player_width = player_width;
	player->player_height = player_height;
	player->player_color = CP_Color_Create(255, 0, 0, player_highlight);

	orb->isActive = 0;
	orb->orb_velocity_x = 800.0f;
	orb->orb_velocity_Y = 800.0f;
	orb->x = player->player_posX;
	orb->y = player->player_posY;
	orb->diameter = 20.0f;

	/*AABB playerHitBoxY = {
		player->player_posX - (player->player_width / 2.0f),
		player->player_posY - (player->player_height / 2.0f),
		player->player_width,
		player->player_height
	};*/

}

//orbCount = 0;
//MaxOrb = 5;
//void Orb_Init(Orb* orbs) {
//
//	orbs->size = 10.0f;
//	
// 
//}