#include "collisionHandling.h"
#include "player.h"
#include <stdio.h>

 
bool checkAABBCollision(AABB objectA, AABB objectB) {
	
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

void Resolve_Collision_Wall_Orb_Y(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveY) {
	if (checkAABBCollision(orbHitBox, WallHitBox)) {
		if (orb->orb_type == TELEPORT_ORB && WallHitBox.type == BLUE_TELEPORT) {
			if (orb_moveY > 0) {
				player->player_posY = WallHitBox.y - (player->player_height / 2.0f) - breathing_space;
				player->player_posX = orb->x;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
			else if (orb_moveY < 0) {
				printf("Teleporting...");
				float Wall_Bottom = WallHitBox.y + WallHitBox.height;
				player->player_posY = Wall_Bottom + (player->player_height / 2.0f) + breathing_space;
				player->player_posX = orb->x;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
		}
		else {
			orb->isActive = 0;
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

void Resolve_Collision_Wall_Orb_X(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveX) {
	// can use for stage wall, platform, door, interactable wall, for interactable wall, please check type of wall before implementing collision.
	// can only use for orb
	if (checkAABBCollision(orbHitBox, WallHitBox)) {
		if (orb->orb_type == TELEPORT_ORB && WallHitBox.type == BLUE_TELEPORT) {
			if (orb_moveX > 0) {
				player->player_posX = WallHitBox.x - (player->player_width / 2.0f) - breathing_space;
				player->player_posY = orb->y;
				player->player_velocityY = 0.0f;
				orb->isActive = 0;
			}
			else if (orb_moveX < 0) {
				float Wall_Right_Edge = WallHitBox.x + WallHitBox.width;
				player->player_posX = Wall_Right_Edge + (player->player_width / 2.0f) + breathing_space;
				player->player_posY = orb->y;
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

