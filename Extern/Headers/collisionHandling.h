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