#pragma once
#include <stdbool.h>

typedef struct {
	float x, y;
	float width, height;
} AABB;

bool checkAABBCollision(AABB objectA, AABB objectB);