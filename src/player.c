#include "player.h"
#include "stage_wall.h"
#include "collisionHandling.h"

void Player_Init(Player *player, Orb *orb) {
	Stage_wall_Init(stage_wall, &stage_wall_count);

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float player_width = 64.0f;
	const float player_height = 64.0f;
	const float player_highlight = 255.0f;
	const float posX = 100, posY = screen_height - player_height/2 - stage_wall[1].height;
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
}

float Player_Update(Player* player, Orb* orb, float deltaTime, float player_moveX, float jump_strength) {
	if (CP_Input_KeyDown(KEY_D)) {
		player_moveX += player->player_velocityX * deltaTime;
		player->direction = PLAYER_RIGHT;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		player_moveX -= player->player_velocityX * deltaTime;
		player->direction = PLAYER_LEFT;
	}

	// Vertical aiming
	if (CP_Input_KeyDown(KEY_W)) {
		if (player->direction == PLAYER_LEFT || player->direction == PLAYER_RIGHT) {
			player->last_direction = player->direction;
		}
		player->direction = PLAYER_UP;
	}
	if (CP_Input_KeyReleased(KEY_W)) {
		player->direction = player->last_direction;
	}

	if (CP_Input_KeyDown(KEY_S)) {
		if (player->direction == PLAYER_LEFT || player->direction == PLAYER_RIGHT) {
			player->last_direction = player->direction;
		}
		player->direction = PLAYER_DOWN;
	}
	if (CP_Input_KeyReleased(KEY_S)) {
		player->direction = player->last_direction;
	}

	// Jumping
	if (CP_Input_KeyTriggered(KEY_SPACE) && player->isGrounded) {
		printf("jumpped!");
		player->player_velocityY = -jump_strength;
		player->isGrounded = 0;
	}
	return player_moveX;
}

