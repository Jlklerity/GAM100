#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "stage_wall.h"
#include "player.h"
#include "collisionHandling.h"
#include "game.h"

static Player player;
static Orb orb;

void LevelThree_Init(void) {
    Stage_wall_Init();
    Player_Init(&player, &orb);
}

void LevelThree_Update(void) {
    float deltaTime = CP_System_GetDt();
    const float max_deltaTime = 0.02f; // cap deltaTime to be lower than 0.02f prevents collision tunneling
    if (deltaTime > max_deltaTime) {
        deltaTime = max_deltaTime;
    }
    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    if (CP_Input_KeyTriggered(KEY_Q)) {
        CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
    }
}

void LevelThree_Exit(void) {

}