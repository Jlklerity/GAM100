#include <math.h>
#include <stdio.h>
#include "cprocessing.h"
#include "game.h"
#include "player.h"
#include "collisionHandling.h"
#include "stagewall.h"
#include "sound.h"
int soundplayed = 0;


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

void ControlsDisplay(Player* player, Orb* orb) {
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    textSize = 32.0f;
    CP_Settings_TextSize(textSize);
    for (int i = 0; i < MAX_LEVEL_OBJECTS; i++) {
        if (g_level_destroy_wall[i] != NULL && g_level_destroy_wall[i]->isActivated == 0) {
            if (player->orb_type == TELEPORT_ORB) {
                CP_Settings_Fill(g_level_destroy_wall[i]->color);
                CP_Font_DrawText("select red orb", player->player_posX, player->player_posY - 100);
            }
            if (player->orb_type == DESTROY_ORB) {
                CP_Settings_Fill(g_level_destroy_wall[i]->color);
                CP_Font_DrawText("Destroy This", g_level_destroy_wall[i]->x - 300, g_level_destroy_wall[i]->y);
            }
        }
        else if (g_level_pressure_plate[i] != NULL && g_level_door[i]->isActivated == 0) {
            CP_Settings_Fill(g_level_pressure_plate[i]->color);
            CP_Font_DrawText("Step Here", g_level_pressure_plate[i]->x, g_level_pressure_plate[i]->y - 100);
        }
        else if (g_level_teleport_wall[i] != NULL && orb->isActive == 0) {
            if (player->orb_type == DESTROY_ORB) {
                CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));
                CP_Font_DrawText("select blue orb", player->player_posX, player->player_posY - 100);
            }
            if (player->orb_type == TELEPORT_ORB) {
                CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));
                CP_Font_DrawText("Teleport Here", g_level_teleport_wall[i]->x - 300, g_level_teleport_wall[i]->y);
            }
        }
        else {
            CP_Settings_TextSize(24.0f);
            CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
            CP_Font_DrawText("EXIT HERE", g_level_exit_door->x, g_level_exit_door->y - 90);
        }
    }
    

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
    
void LevelTimer(float* leveltime, int* GameState) {
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    int minutes = (int)(*leveltime / 60);
    int seconds = (int)(*leveltime) % 60;
    CP_Settings_TextSize(32.0);

    char time[50] = { 0 };
    sprintf_s(time, 50, "%02d:%02d", minutes, seconds);

    if (*leveltime > 0.0f && *GameState) {

        float prevtime = *leveltime;

        // ---------- TEXT COLOR ----------
        if (*leveltime <= 11.0f)
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   // RED under 10
        else
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255)); // WHITE above 10

        CP_Font_DrawText(time, (float)CP_System_GetWindowWidth() / 2.0f, 60.0f);

        // countdown
        *leveltime -= CP_System_GetDt();

        // ---------- Alarm: play once ----------
        if (prevtime > 11.0f && *leveltime <= 11.0f && soundplayed == 0) {
            Sound_PlaySFX(alarm);
            soundplayed = 1;
        }

        // ---------- time ran out ----------
        if (*leveltime < 0.0f) {
            *leveltime = 0.0f;
            CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
        }
    }
    else {
        // ---------- Paused display ----------
        if (*leveltime <= 11.0f) {
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        }
        else
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

        CP_Font_DrawText(time, (float)CP_System_GetWindowWidth() / 2.0f, 60.0f);
    }
}


void OrbCount(Orb* orb) {
    CP_Settings_TextSize(32.0f);
    char buffer[50] = { 0 };
    sprintf_s(buffer, 50, "Ammo: %d", orb->ammo);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_DrawText(buffer, 120.0f, 60.0f);

    switch (orb->orb_type) {
    case TELEPORT_ORB:
        CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));
        break;
    case DESTROY_ORB:
        CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
        break;
    }
    CP_Graphics_DrawCircle(120.0f, 90.0f, orb->diameter);
}

