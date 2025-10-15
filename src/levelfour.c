#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"

static Player player;

void LevelFour_Init(void) {
    Stage_wall_Init(stage_wall, &stage_wall_count);
    Player_Init(&player);
}

void LevelFour_Update(void) {
    float deltaTime = CP_System_GetDt();
    const float max_deltaTime = 0.02f; // cap deltaTime to be lower than 0.02f prevents collision tunneling
    if (deltaTime > max_deltaTime) {
        deltaTime = max_deltaTime;
    }
    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    if (CP_Input_KeyDown(KEY_S)) {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }
}

void LevelFour_Exit(void) {

}