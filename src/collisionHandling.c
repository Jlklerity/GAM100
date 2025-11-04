#include "collisionHandling.h"
#include "stage_wall.h"
#include "player.h"
#include "cprocessing.h"
#include <stdio.h>
#
#define EdgeMargin 32.0f // half the player height and width, used to calculate the clamped value so player doesn't teleport over unintedned platform.
 
 

bool checkAABBCollision(AABB objectA, AABB objectB) { //Main AABB collision logic
	
	bool bothOverlap_X = (objectA.x < objectB.x + objectB.width) && (objectA.x + objectA.width > objectB.x);
	bool bothOverlap_Y = (objectA.y < objectB.y + objectB.height) && (objectA.y + objectA.height > objectB.y);

	return bothOverlap_X && bothOverlap_Y;
}


AABB Get_Wall_HitBox(Wall *wall) {
	AABB box;
	box.x = wall->x - wall->width / 2;
	box.y = wall->y - wall->height / 2;
	box.width = wall->width;
	box.height = wall->height;
	box.type = wall->type;
	return box;
}
AABB Get_Player_HitBox(Player* player) {
	AABB box;
	box.x = player->player_posX - player->player_width / 2;
	box.y = player->player_posY - player->player_height / 2;
	box.width = player->player_width;
	box.height = player->player_height;
	return box;
}

AABB Get_Orb_HitBox(Orb* orb) {
	AABB box;
	box.x = orb->x - orb->diameter / 2;
	box.y = orb->y - orb->diameter / 2;
	box.width = orb->diameter;
	box.height = orb->diameter;
	return box;
}

// Default endpoint is the screen edge


// This variable will hold the X-coordinate of the closest wall we've hit so far.
// We start it at the screen edge.
Point Calculate_Ray_Endpoint(float start_point_x, float start_point_y, Wall* wall[], int wall_count, Direction dir) {
	Point end_point = { start_point_x, start_point_y };
	for (int i = 0; i < wall_count; i++) {
		Wall* w = wall[i];

		// to get the borders of the walls
		float wall_left = w->x - w->width / 2.0f;
		float wall_right = w->x + w->width / 2.0f;
		float wall_top = w->y - w->height / 2.0f;
		float wall_bottom = w->y + w->height / 2.0f;

		switch (dir) {
			/* First term is to check if the wall is alligned with the start point. Second term is to check the wall in front 
			   of the laser, ensuring the wall is ahead of the laser's start point, the third term is when no wall is found 
			   yet, and the fourth term checks if the wall's border is closer than the previously found one. */
			case RIGHT: {
				bool isAligned = (start_point_y >= wall_top && start_point_y <= wall_bottom);
				if (isAligned && wall_left > start_point_x && (end_point.x == start_point_x || wall_left < end_point.x)) {
					end_point.x = wall_left;
				}
				break;
			}
			case LEFT: {
				bool isAligned = (start_point_y >= wall_top && start_point_y <= wall_bottom);
				if (isAligned && wall_right < start_point_x && (end_point.x == start_point_x || wall_right > end_point.x)) {
					end_point.x = wall_right;
				}
				break;
			}
			case DOWN: {
				bool isAligned = (start_point_x >= wall_left && start_point_x <= wall_right);
				if (isAligned && wall_top > start_point_y && (end_point.y == start_point_y || wall_top < end_point.y)) {
					end_point.y = wall_top;
				}
				break;
			}
			case UP: {
				bool isAligned = (start_point_x >= wall_left && start_point_x <= wall_right);
				if (isAligned && wall_bottom < start_point_y && (end_point.y == start_point_y || wall_bottom > end_point.y)) {
					end_point.y = wall_bottom;
				}
				break;
			}
		}
	}
	return end_point;
}



void Resolve_Collision_Wall_Player_Y(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space) {
	// can use for stage wall, platform, door, interactable wall, for interactable wall, please check type of wall before implementing collision.
	//cannot use for orb
	if (checkAABBCollision(playerHitBox, WallHitBox)) {
		if (player->player_velocityY > 0) {
			player->player_posY = WallHitBox.y - (player->player_height / 2.0f) - breathing_space;
			player->player_velocityY = 0.0f;
			player->isGrounded = 1;
		}
		else if (player->player_velocityY < 0) {
			player->player_posY = WallHitBox.y + WallHitBox.height + (player->player_height / 2.0f) + breathing_space;
			player->player_velocityY = 0.0f;
		}
	}
}

static float time_pressure_sensorLastPressed = -10.0f;
void Resolve_Collision_FloorSensor_Player(AABB playerHitBox, AABB pressure_sensorHitBox, Wall* door, Wall* pressure_plate) {

	// Get the actual current time, once per frame.
	float currentTime = CP_System_GetSeconds();

	if (checkAABBCollision(playerHitBox, pressure_sensorHitBox)) {
		pressure_plate->color = CP_Color_Create(255, 0, 0, 255);
		// 2. Open the door
		door->isActivated = 1;
		time_pressure_sensorLastPressed = currentTime;
	}
	else {
		float timeSinceLastPress = currentTime - time_pressure_sensorLastPressed;
		if (timeSinceLastPress >= 5.0f) {
			door->isActivated = 0;
			pressure_plate->color = CP_Color_Create(113, 121, 126, 255);
		}
		
	}
}

void Resolve_Collision_Wall_Player_X(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space, float player_moveX) {
	// can use for stage wall, platform, door, interactable wall, for interactable wall, please check type of wall before implementing collision.
	// cannot use for orb
	if (checkAABBCollision(playerHitBox, WallHitBox)) {
		if (player_moveX > 0) {
			player->player_posX = WallHitBox.x - (player->player_width / 2.0f) - breathing_space;
		}
		else if (player_moveX < 0) {
			float Wall_Right_Edge = WallHitBox.x + WallHitBox.width;
			player->player_posX = Wall_Right_Edge + (player->player_width / 2.0f) + breathing_space;
		}
	}
}

void Resolve_Collision_Wall_Orb_Y(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveY) {
	// add clamp so player will not glitch out of wall.
	float WallLeft = WallHitBox.x;
	float WallRight = WallHitBox.x + WallHitBox.width;

	float SafeLeft = WallLeft + EdgeMargin;
	float SafeRight = WallRight - EdgeMargin;

	float clampedX = orb->x;
	if (clampedX < SafeLeft) clampedX = SafeLeft;
	if (clampedX > SafeRight) clampedX = SafeRight;

	if (checkAABBCollision(orbHitBox, WallHitBox)) {
		if (orb->orb_type == TELEPORT_ORB && WallHitBox.type == BLUE_TELEPORT) {
			if (orb_moveY > 0) {
				player->player_posY = WallHitBox.y - (player->player_height / 2.0f) - breathing_space;
				player->player_posX = clampedX;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
			else if (orb_moveY < 0) {
				float Wall_Bottom = WallHitBox.y + WallHitBox.height;
				player->player_posY = Wall_Bottom + (player->player_height / 2.0f) + breathing_space;
				player->player_posX = clampedX;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
		}
		else {
			orb->isActive = 0;
		}
	}
}

void Resolve_Collision_Wall_Orb_X(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveX) {
	// can use for stage wall, platform, door, interactable wall, for interactable wall, please check type of wall before implementing collision.
	// can only use for orb
	// add clamp so player will not glitch out of wall.
	float WallTop = WallHitBox.y;
	float WallBottom = WallHitBox.y + WallHitBox.height;

	float SafeTop = WallTop + EdgeMargin;
	float SafeBottom = WallBottom - EdgeMargin;

	float clampedY = orb->y;
	if (clampedY < SafeTop) clampedY = SafeTop;
	if (clampedY > SafeBottom) clampedY = SafeBottom;

	if (checkAABBCollision(orbHitBox, WallHitBox)) {
		if (orb->orb_type == TELEPORT_ORB && WallHitBox.type == BLUE_TELEPORT) {
			if (orb_moveX > 0) {
				player->player_posX = WallHitBox.x - (player->player_width / 2.0f) - breathing_space;
				player->player_posY = clampedY;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
	
			else if (orb_moveX < 0) {
				float Wall_Right_Edge = WallHitBox.x + WallHitBox.width;
				player->player_posX = Wall_Right_Edge + (player->player_width / 2.0f) + breathing_space;
				player->player_posY = clampedY;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
		}
		else {
			//play orb shatter anim
			orb->isActive = 0;
		}
	}
}


void Resolve_Collision_Destroy_Wall_Orb_X(AABB orbHitBox, AABB destroy_wallHitBox, Orb* orb, Wall* destroy_wall, float breathing_space, float orb_moveX) {
	if (checkAABBCollision(orbHitBox, destroy_wallHitBox)) {
		if (orb->orb_type == DESTROY_ORB && destroy_wallHitBox.type == RED_DESTROY) {
			if (orb_moveX > 0) {
				destroy_wall->isActivated = 1;
				orb->x = orb->x + breathing_space;
				orb->isActive = 0;
			}
			if (orb_moveX < 0) {
				destroy_wall->isActivated = 1;
				orb->x = orb->x - breathing_space;
				orb->isActive = 0;
			}
		}
		else {
			orb->isActive = 0;
			orb->x = 0;
		}
	}
	else {
		destroy_wall->isActivated = 0;
		destroy_wall->color = CP_Color_Create(255, 0, 0, 255);
	}
}

void Resolve_Collision_Destroy_Wall_Orb_Y(AABB orbHitBox, AABB destroy_wallHitBox, Orb* orb, Wall* destroy_wall, float breathing_space, float orb_moveY) {
	if (checkAABBCollision(orbHitBox, destroy_wallHitBox)) {
		if (orb->orb_type == DESTROY_ORB && destroy_wallHitBox.type == RED_DESTROY) {
			if (orb_moveY > 0) {
				destroy_wall->isActivated = 1;
				orb->y = orb->y - breathing_space;
				orb->isActive = 0;
			}
			if (orb_moveY < 0) {
				destroy_wall->isActivated = 1;
				orb->y = orb->y + breathing_space;
				orb->isActive = 0;
			}
		}
		else {
			orb->isActive = 0;
			orb->x = 0;
		}
	}
	else {
		destroy_wall->isActivated = 0;
		destroy_wall->color = CP_Color_Create(255, 0, 0, 255);
	}
}
