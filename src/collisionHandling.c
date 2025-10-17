#include "collisionHandling.h"
#include "player.h"

 
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

AABB Get_Level2_Platform_HitBox(LevelPlatform* levelplatform) {
	AABB box;
	box.x = levelplatform->x - levelplatform->width / 2;
	box.y = levelplatform->y - levelplatform->height / 2;
	box.width = levelplatform->width;
	box.height = levelplatform->height;
	return box;
}

AABB Get_Door_HitBox(Door* door) {
	AABB box;
	box.x = door->x - door->width / 2;
	box.y = door->y - door->height / 2;
	box.width = door->width;
	box.height = door->height;
	return box;
}

AABB Get_Pressure_Plate_Hitbox(PressurePlate* pressure_plate) {
	AABB box;
	box.x = pressure_plate->x - pressure_plate->width / 2;
	box.y = pressure_plate->y - pressure_plate->height / 2;
	box.width = pressure_plate->width;
	box.height = pressure_plate->height;
	return box;
}

AABB Get_Interactable_Wall_HitBox(InteractableWall* interactable_wall) {
	AABB box;
	box.x = interactable_wall->x - interactable_wall->width / 2;
	box.y = interactable_wall->y - interactable_wall->height / 2;
	box.width = interactable_wall->width;
	box.height = interactable_wall->height;
	return box;
}

AABB Get_Exit_Door_HitBox(ExitDoor* level2_exit_door) {
	AABB box;
	box;
	box.x = level2_exit_door->x - level2_exit_door->width / 2;
	box.y = level2_exit_door->y - level2_exit_door->height / 2;
	box.width = level2_exit_door->width;
	box.height = level2_exit_door->height;
	return box;
}