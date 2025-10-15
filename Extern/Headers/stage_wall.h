#pragma once
#include "cprocessing.h"

typedef struct {
	float stage_wallX, stage_wallY;
	float stage_wallwidth, stage_wallheight;
	CP_Color stage_wall_color;
} Stage_wall;

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
} LevelPlatform;

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
	int stateIsOpen;//0 is closed, 1 is open
} Door;

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
	int IsSteppedOn;//0 is not stepped on, 1 is stepped on
} PressurePlate;

enum TypeofWall {
	NORMAL, BLUE_TELEPORT, RED_DESTROY
};

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
	enum TypeofWall; //if  0, normal wall - blocks character movement destroys all orb.
	// If 1, Color = blue, only teleport orb can hit, will destroy teleport orb, destroy orb will go past this  and player can walk pass this
	// If 2, Color = red, only destroy orb can hit, will destroy destroy orb, teleport orb will go past this and player cannot walk pass this
} InteratableWall;

typedef struct {
	float x, y;
	float width, height;
	CP_Color color;
} ExitDoor;

extern Stage_wall stage_wall[4];
extern LevelPlatform level_platform;
extern ExitDoor exit_door;
extern int stage_wall_count;

void Stage_wall_Init(Stage_wall stage_wall[4], int *stage_wall_count);