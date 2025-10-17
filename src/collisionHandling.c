#include "collisionHandling.h"



bool checkAABBCollision(AABB objectA, AABB objectB) {
	
	bool bothOverlap_X = (objectA.x < objectB.x + objectB.width) && (objectA.x + objectA.width > objectB.x);

	bool bothOverlap_Y = (objectA.y < objectB.y + objectB.height) && (objectA.y + objectA.height > objectB.y);

	return bothOverlap_X && bothOverlap_Y;
}

AABB Get_Player_HitBox(Player* player) {
	AABB box;
	box.x = player->player_posX - player->player_width / 2;
	box.y = player->player_posY - player->player_height / 2;
	box.width = player->player_width;
	box.height = player->player_height;
	return box;
}

//float player_moveX = 0.0f; //solve this variable thingie
//void platformCollider(AABB platformCheck, AABB playerCheck, LevelPlatform plat, Player player) {
//	float platformTopLeftX = level_platform.x - (level_platform.width / 2.0f);
//	float platformTopLeftY = level_platform.y - (level_platform.height / 2.0f);
//	float platformwidth = plat.width;
//	float platformheight = plat.height;
//
//	platformCheck.x = platformTopLeftX;
//	platformCheck.y = platformTopLeftY;
//	platformCheck.width = platformwidth;
//	platformCheck.height = platformheight;
//
//	float PlayerTopLeftX = player.player_posX - (player.player_width / 2.0f);
//	float PlayerTopLeftY = player.player_posY - (player.player_height / 2.0f);
//	float PlayerWidth = player.player_width;
//	float PlayerHeight = player.player_height;
//
//	playerCheck.x = PlayerTopLeftX;
//	playerCheck.y = PlayerTopLeftY;
//	playerCheck.width = PlayerWidth;
//	playerCheck.height = PlayerHeight;
//
//	if (checkAABBCollision(playerCheck, platformCheck)) {
//		const float breathing_space = 0.1f;
//		if (player.player_velocityY > 0) {
//			float platform_top_edge = platformCheck.y;
//			player.player_posY = platform_top_edge - (player.player_height / 2.0f) - breathing_space;
//			player.player_velocityY = 0.0f;
//			player.isGrounded = 1;
//		}
//		else if (player.player_velocityY < 0) {
//			float platform_bottom_edge = platformCheck.y;
//			player.player_posY = platform_bottom_edge + (player.player_height / 2.0f) + breathing_space;
//			player.player_velocityY = 0.0f;
//		}
//	}
//	if (checkAABBCollision(playerCheck, platformCheck)) {
//		const float breathing_space = 0.1f;
//		if (player_moveX > 0) { //idk how to solve this part
//			float platform_left_edge = platformCheck.x;
//			player.player_posX = platform_left_edge - (player.player_width / 2.0f) - breathing_space;
//		}
//		else if (player_moveX < 0) { //idk how to solve this part
//			printf("contact with platform!");
//			float platform_right_edge = platformCheck.x + (platformCheck.width);
//			// if you want to i guess printf("%0.2f\n", platform_right_edge);
//			player.player_posX = platform_right_edge + (player.player_width / 2.0f) + breathing_space;
//		}
//
//	}