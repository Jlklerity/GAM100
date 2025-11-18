#pragma once
#include <stdbool.h>
#include "stagewall.h"
#include "player.h"
#include "hazards.h"

typedef struct {
	float x, y;
	float width, height;
	enum TypeofWall type;
} AABB;

typedef struct {
	float x, y;
} Point;

bool checkAABBCollision(AABB objectA, AABB objectB);

AABB Get_Player_HitBox(Player* player);
AABB Get_Orb_HitBox(Orb* orb);
AABB Get_Wall_HitBox(Wall* wall);
Point Calculate_Ray_Endpoint(float start_point_x, float start_point_y, Wall* wall[], int wall_count, Direction dir);
void Resolve_Collision_Wall_Player_Y(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space);
void Resolve_Collision_Wall_Orb_Y(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveY);
void Resolve_Collision_Wall_Player_X(AABB playerHitBox, AABB WallHitBox, Player* player, float breathing_space, float player_moveX);
void Resolve_Collision_Wall_Orb_X(AABB orbHitBox, AABB WallHitBox, Orb* orb, Player* player, float breathing_space, float orb_moveX);
void Resolve_Collision_FloorSensor_Player(AABB playerHitBox, AABB Pressure_sensor, Wall* interactable, Wall* pressure_plate);
void Resolve_Collision_Destroy_Wall_Orb_X(AABB orbHitBox, AABB destroy_wallHitBox, Orb* orb, Wall* destroy_wall, float breathing_space, float orb_moveX);
void Resolve_Collision_Destroy_Wall_Orb_Y(AABB orbHitBox, AABB destroy_wallHitBox, Orb* orb, Wall* destroy_wall, float breathing_space, float orb_moveY);