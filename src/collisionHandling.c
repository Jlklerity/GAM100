#include "collisionHandling.h"
#include "player.h";

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

AABB Get_Orb_HitBox(Orb* orb) {
	AABB box;
	box.x = orb->x - orb->diameter / 2;
	box.y = orb->y - orb->diameter / 2;
	box.width = orb->diameter;
	box.height = orb->diameter;
	return box;
}

AABB Get_Stage_Wall_HitBox(Stage_wall* stagewall) {
	AABB box;
	box.x = stagewall->stage_wallX - stagewall->stage_wallwidth / 2;
	box.y = stagewall->stage_wallY - stagewall->stage_wallheight / 2;
	box.width = stagewall->stage_wallwidth;
	box.height = stagewall->stage_wallheight;
	return box;
}

AABB Get_Level_Platform_HitBox(LevelPlatform* levelplatform) {
	AABB box;
	box.x = levelplatform->x - levelplatform->width / 2;
	box.y = levelplatform->y - levelplatform->height / 2;
	box.width = levelplatform->width;
	box.height = levelplatform->height;
	return box;
}

AABB Get_Door_HitBox(Door* door) {
	AABB box;
	box.x = door->x - door->width/2;
	box.y = door->y - door->height / 2;
	box.width = door->width;
	box.height = door->height;
	return box;
}

AABB Get_Pressure_Plate_Hitbox(PressurePlate* Pressure_Plate) {
	AABB box;
	box.x = Pressure_Plate->x - Pressure_Plate->width / 2;
	box.y = Pressure_Plate->y - Pressure_Plate->height / 2;
	box.width = Pressure_Plate->width;
	box.height = Pressure_Plate->height;
	return box;
}

AABB Get_Interactable_Wall_HitBox(InteractableWall* Interactable_Wall) {
	AABB box;
	box.x = Interactable_Wall->x - Interactable_Wall->width / 2;
	box.y = Interactable_Wall->y - Interactable_Wall->height / 2;
	box.width = Interactable_Wall->width;
	box.height = Interactable_Wall->height;
	return box;
}

AABB Get_Exit_Door_HitBox(ExitDoor* Exit_Door) {
	AABB box;
	box.x = Exit_Door->x - Exit_Door->width / 2;
	box.y = Exit_Door->y - Exit_Door->height / 2;
	box.width = Exit_Door->width;
	box.height = Exit_Door->height;
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