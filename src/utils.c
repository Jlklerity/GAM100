#include <math.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "game.h"
#include "player.h"
#include <stdio.h>
#include "levelone.h"

Player player;

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
    float distance_x = abs(circle1_center_x - circle2_center_x);
    float distance_y = abs(circle1_center_y - circle2_center_y);
    if (distance_x <= collided && distance_y <= collided) {
        
        return 1;
    }
    else {
        return 0;
    }
    
}

int RGBChange(float StaticValue) {
    float currentTime = CP_System_GetSeconds();
    float elapsed = currentTime - StaticValue;
    float pulseSpeed = 1.5f; // adjust for speed of pulsing
    float t = (currentTime - StaticValue) * pulseSpeed;
    float greenValue = 115.0f + 75.0f * sinf(t);
    // 115 is midpoint, 75 is amplitude (115±75 = 40 to 190)
    int x = (int)greenValue;
    if (x < 0) x = 0;
    if (x > 255) x = 255;
    return x;
}

void FPSCount() {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    debug_TEXT = CP_Font_Load("Assets/Exo2 - Regular.ttf");
    float textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "frame count: %i", CP_System_GetFrameCount());
    CP_Font_DrawText(buffer, 200, 30);
}
void Player_Coords(Player* player) {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    debug_TEXT = CP_Font_Load("Assets/Exo2 - Regular.ttf");
    float textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "player <X:%0.2f Y:%0.2f> ", player->player_posX, player->player_posY);
    CP_Font_DrawText(buffer, 200, 50);
}
void MousePos() {
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    mouseX = (float)CP_Input_GetMouseX();
    mouseY = (float)CP_Input_GetMouseY();
    debug_TEXT = CP_Font_Load("Assets/Exo2 - Regular.ttf");
    float textSize = 20.0f;
    char buffer[50] = { 0 };
    CP_Settings_TextSize(textSize);
    sprintf_s(buffer, 50, "mouse <X:%0.2f Y:%0.2f> ", mouseX, mouseY);
    CP_Font_DrawText(buffer, 200, 75);
}

void PlayerPov(Player* player) {
    CP_Settings_Stroke(CP_Color_Create(0, 160, 255, 255));
    switch (player->direction) {
        case (PLAYER_RIGHT):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, player->player_posX + 50.0f, player->player_posY);
            break;
        case (PLAYER_LEFT):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, player->player_posX - 50.0f, player->player_posY);
            break;
        case (PLAYER_UP):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, player->player_posX, player->player_posY - 50.0f);
            break;
        case (PLAYER_DOWN):
            CP_Graphics_DrawLine(player->player_posX, player->player_posY, player->player_posX, player->player_posY + 50.0f);
            break;
        }
    CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
}
    
void LevelTimer(float* leveltime, float deltaTime) {
    int minutes = (int)(*leveltime / 60);
    int seconds = (int)(*leveltime) % 60;
    debug_TEXT = CP_Font_Load("Assets/Exo2 - Regular.ttf");
    CP_Settings_TextSize(64.0);
    char time[50] = { 0 };
    sprintf_s(time, 50, "%02d:%02d", minutes, seconds);

    if (*leveltime > 0.0f) {
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        CP_Font_DrawText(time, 200, 200);
        *leveltime -= CP_System_GetDt();
        if (*leveltime <= 10.0f) {
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
            CP_Font_DrawText(time, 200, 200);
        }
        if (*leveltime < 0.0f) {
            *leveltime = 0.0f;
            CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
        }
    }
}

  