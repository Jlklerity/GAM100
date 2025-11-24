#include <math.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include "player.h"
#include "collisionHandling.h"
#include "stagewall.h"




static int frame_count = 0;   // counts frames for timing
static int animation_speed = 10;


//Destroy orb canvas DOS
static int DOS_x = 0;
static int DOS_y = 0;
static int DOE_x = 32;
static int DOE_y = 32;


//Teleport orb canvas TOS 
static int TOS_x = 0;
static int TOS_y = 0;
static int TOE_x = 32;
static int TOE_y = 32;



int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
    float left_side = area_center_x - area_width / 2.0f;
    float right_side = area_center_x + area_width / 2.0f;
    float top_side = area_center_y - area_height / 2.0f;
    float bottom_side = area_center_y + area_height / 2.0f;
    
    if (click_x >= left_side && click_x <= right_side && click_y >= top_side && click_y <= bottom_side) {
        return 1; 
    }   
    return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
    float radius = diameter / 2.0f;
    float distance_x = click_x - circle_center_x;
    float distance_y = click_y - circle_center_y;
    int is_clicked = (distance_x * distance_x + distance_y * distance_y) <= (radius * radius);
        
    return is_clicked;
}

int IsCircleColliding(float circle1_center_x, float circle1_center_y, float circle2_center_x, float circle2_center_y, float diameter) {
    
    float collided = diameter*2 + 10;
    float distance_x = (fabsf(circle1_center_x - circle2_center_x));
    float distance_y = (fabsf(circle1_center_y - circle2_center_y));
    if (distance_x <= collided && distance_y <= collided) {
        
        return 1;
    }
    else {
        return 0;
    }
    
}

int RGBChange(float StaticValue) {
    float currentTime = CP_System_GetSeconds();
    //float elapsed = currentTime - StaticValue;
    float pulseSpeed = 1.5f; // adjust for speed of pulsing
    float t = (currentTime - StaticValue) * pulseSpeed;
    float greenValue = 115.0f + 75.0f * sinf(t);
    // 115 is midpoint, 75 is amplitude (115±75 = 40 to 190)
    int x = (int)greenValue;
    if (x < 0) x = 0;
    if (x > 255) x = 255;
    return x;
}

void FPSCount(void) {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "frame count: %i", CP_System_GetFrameCount());
    CP_Font_DrawText(buffer, 1580.0f, 20.0f);
}
void Player_Coords(Player* player) {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "player <X:%0.2f Y:%0.2f> ", player->player_posX, player->player_posY);
    CP_Font_DrawText(buffer, 1580.0f, 45.0f);
}
void MousePos(void) {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    mouseX = (float)CP_Input_GetMouseX();
    mouseY = (float)CP_Input_GetMouseY();
    textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "mouse <X:%0.2f Y:%0.2f> ", mouseX, mouseY);
    CP_Font_DrawText(buffer, 1580.0f, 70.0f);
}

void ControlsDisplay(void) {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    textSize = 32.0f;
    CP_Settings_TextSize(textSize);
    
}

void PlayerPov(Player* player) {
    CP_Settings_Stroke(CP_Color_Create(0, 160, 255, 255));
    Point end = Calculate_Ray_Endpoint(player->player_posX, player->player_posY, g_level_collidables, g_level_collidable_count, player->direction);
    switch (player->direction) {
        case (PLAYER_RIGHT):
            //check collision of player's ray right direction with stage wall left
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, end.x, end.y);
            break;
        case (PLAYER_LEFT):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, end.x, end.y);
            break;
        case (PLAYER_UP):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, end.x, end.y);
            break;
        case (PLAYER_DOWN):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, end.x, end.y);
            break;
        }
    CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
}
    
void LevelTimer(float* leveltime, int* GameState, int* GameOverState) {
    int minutes = (int)(*leveltime / 60);
    int seconds = (int)(*leveltime) % 60;
    CP_Settings_TextSize(32.0);
    char time[50] = { 0 };
    sprintf_s(time, 50, "%02d:%02d", minutes, seconds);

    if (*leveltime > 0.0f && *GameState) {
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        CP_Font_DrawText(time, (float)CP_System_GetWindowWidth()/2.0f, 50.0f);
        *leveltime -= CP_System_GetDt();
        if (*leveltime <= 10.0f) {
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
            CP_Font_DrawText(time, (float)CP_System_GetWindowWidth() / 2.0f, 50.0f);
        }
        if (*leveltime < 0.0f) {
            *leveltime = 0.0f;
            *GameOverState = 0;//the game ends and runs the gamover screen
            /*CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);*/
        }
    }
    else {
        if (*leveltime > 10.0f) {
         CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
         CP_Font_DrawText(time, (float)CP_System_GetWindowWidth() / 2.0f, 50.0f);
        }
        else if(*leveltime <= 10.0f){
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
            CP_Font_DrawText(time, (float)CP_System_GetWindowWidth() / 2.0f, 50.0f);
        }
    }
}

void OrbCount(Orb* orb, Player* player) {
    CP_Settings_TextSize(32.0f);
    char buffer[50] = { 0 };
    sprintf_s(buffer, 50, "Ammo: %d", orb->ammo);

    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_DrawText(buffer, 30.0f, 30.0f);

    switch (orb->orb_type) {
    case TELEPORT_ORB:
        /*CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));*/
        CP_Image_DrawSubImage(player->teleport_orb, 85, 75, 50 , 50 , (float)TOS_x, (float)TOS_y, (float)TOE_x, (float)TOE_y, 255);

        break;
    case DESTROY_ORB:
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        CP_Image_DrawSubImage(player->destroy_orb, 85, 75, 50 * 1.5, 50 * 1.5, (float)DOS_x, (float)DOS_y, (float)DOE_x, (float)DOE_y, 255);

        break;
    }
    //CP_Graphics_DrawCircle(90.0f, 90.0f, orb->diameter);
    frame_count++;
    if (frame_count >= animation_speed) {  // every 10 frames change sprite(adjust to speed)
        frame_count = 0;

        DOS_x += 32;
        DOE_x += 32;

        TOS_x += 32;
        TOE_x += 32;


        if (DOS_x >= 32 * 5) { // 5 columns
            DOS_x = 0;
            DOE_x = 32;
        }

        if (TOS_x >= 32 * 4) { // 5 columns
            TOS_x = 0;
            TOE_x = 32;
        }
    }
}

// animating the frames
   // --- animate frames roughly 3 FPS ---
