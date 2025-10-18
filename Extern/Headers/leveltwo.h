#pragma once
#include "cprocessing.h"
#include "player.h"
#include "stage_wall.h"
#include "game.h"
#include "collisionHandling.h"
enum GameState
{
	RUNNING, PAUSED, OVER
}State;

void LevelTwo_Init(void);

void LevelTwo_Update(void);

void LevelTwo_Exit(void);