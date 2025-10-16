#pragma once
#include <stdbool.h>
#include "stage_wall.h"
#include "player.h"

typedef struct {
	float x, y;
	float width, height;
} AABB;

bool checkAABBCollision(AABB objectA, AABB objectB);
//void platformCollider(AABB platformCheck, AABB playerCheck, LevelPlatform plat, Player player);
AABB Get_Player_HitBox(Player* player);
AABB Get_Orb_HitBox(Orb* orb);
AABB Get_Stage_Wall_HitBox(Stage_wall* stagewall);
AABB Get_Level_Platform_HitBox(LevelPlatform* levelplatform);
AABB Get_Door_HitBox(Door* door);
AABB Get_Pressure_Plate_Hitbox(PressurePlate* PressurePlate);
AABB Get_Interactable_Wall_HitBox(InteractableWall* InteractableWall);
AABB Get_Exit_Door_HitBox(ExitDoor* ExitDoor);
