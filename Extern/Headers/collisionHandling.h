#pragma once
#include <stdbool.h>
#include "stage_wall.h"
#include "player.h"


typedef struct {
	float x, y;
	float width, height;
	enum TypeofWall type;
} AABB;


bool checkAABBCollision(AABB objectA, AABB objectB);

AABB Get_Player_HitBox(Player* player);
AABB Get_Orb_HitBox(Orb* orb);
AABB Get_Wall_HitBox(Wall* wall);
void Resolve_Collision_Wall_Player_Y(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space);
void Resolve_Collision_Wall_Orb_Y(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveY);
void Resolve_Collision_Wall_Player_X(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space, float player_moveX);
void Resolve_Collision_Wall_Orb_X(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveX);
void Resolve_Collision_FloorSensor_Player(AABB playerHitBox, AABB Pressure_sensor, Player* player, Wall* door, Wall* pressure_plate);