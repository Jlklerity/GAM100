#include <stdio.h>
#include <string.h>
#include "cprocessing.h"
#include "utils.h"
#include "fullscreen.h"
#include "stage_wall.h"
#include "player.h"
#include "game.h"
#include "mainmenu.h"
#include "sound.h"

// Globals
float mouseX, mouseY;
float volumePercent = 100;

// Buttons
float backButtonX, backButtonY;
float soundButtonX, soundButtonY;
float resetbarX, resetbarY;
float resumebarX, resumebarY;
float mainmenubarX, mainmenubarY;
float restartbarX, restartbarY;
float buttonWidth, buttonHeight;

// Sound bar
float soundBarX, soundBarY;
float soundBarWidth, soundBarHeight;


int pause_menu(void)
{
    float textSize = 32.0f;
    buttonWidth = 200.0f;
    buttonHeight = 100.0f;

    CP_Settings_Fill(CP_Color_Create(50, 50, 50, 200));
    CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f,
        CP_System_GetWindowHeight() / 2.0f,
        CP_System_GetWindowWidth(),
        CP_System_GetWindowHeight());

    resumebarX = CP_System_GetWindowWidth() / 2;
    resumebarY = CP_System_GetWindowHeight() / 2 - 200;

    mainmenubarX = CP_System_GetWindowWidth() / 2;
    mainmenubarY = CP_System_GetWindowHeight() / 2;

    restartbarX = CP_System_GetWindowWidth() / 2;
    restartbarY = CP_System_GetWindowHeight() / 2 + 200;

    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    CP_Font_Set(option_TEXT);
    CP_Settings_TextSize(textSize);

    // Draw buttons
    CP_Image_Draw(mainmenu_ButtonBackground, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    CP_Font_DrawText("resume", resumebarX, resumebarY);
    CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);
    CP_Font_DrawText("restart", restartbarX, restartbarY);

    // Button press effect
    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
    {
        if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
        }
        if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
        }
        if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
        }
    }

    // Button actions
    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
    {
        if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY))
            return 1;

        if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY))
            return 2;

        if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY))
            return 3;
    }

    return 0;
}



void back_option(void)
{
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    backButtonX = CP_System_GetWindowWidth() / 2;
    backButtonY = CP_System_GetWindowHeight() / 2 - 200;

    CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("back", backButtonX, backButtonY);

    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
    }

    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}


void reset_option(void)
{
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    resetbarX = CP_System_GetWindowWidth() / 10;
    resetbarY = CP_System_GetWindowHeight() / 2 + 300;

    CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("reset", resetbarX, resetbarY);

    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        CP_Image_Draw(mainmenu_ButtonWhenPressed, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
    }

    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        g_highest_level_unlocked = 1;
        Save_Progress();
    }
}



void sound_option(void)
{
    soundButtonX = CP_System_GetWindowWidth() / 2;
    soundButtonY = CP_System_GetWindowHeight() / 2 + 100;
    // Always pull updated mouse input
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    // Draw the button background
    CP_Image_Draw(mainmenu_ButtonBackground, soundButtonX, soundButtonY, buttonWidth, buttonHeight, 255);

    // Sound bar — CORNER MODE
    CP_Settings_RectMode(CP_POSITION_CORNER);

    // Outline
    CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
    CP_Graphics_DrawRect(soundBarX, soundBarY, soundBarWidth, soundBarHeight);

    // Fill
    float filledWidth = (volumePercent / 100.0f) * soundBarWidth;
    CP_Settings_Fill(CP_Color_Create(225, 0, 0, 225));
    CP_Graphics_DrawRect(soundBarX, soundBarY, filledWidth, soundBarHeight);

    // Drag logic
    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
    {
        if (mouseX >= soundBarX && mouseX <= soundBarX + soundBarWidth &&
            mouseY >= soundBarY && mouseY <= soundBarY + soundBarHeight)
        {
            volumePercent = (mouseX - soundBarX) / soundBarWidth * 100;

            if (volumePercent < 0) volumePercent = 0;
            if (volumePercent > 100) volumePercent = 100;

            float v = volumePercent / 100.0f;
            Sound_SetSFXVolume(v);
            Sound_SetMusicVolume(v);
        }
    }

    // Back to CENTER for other UI
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // Text label
    CP_Settings_Fill(CP_Color_Create(100, 0, 0, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("sound", soundButtonX, soundButtonY);
}

void back_option_gamemenu(void) {
    float textSize = 32.0f;
    buttonWidth = 150.0f;
    buttonHeight = 75.0f;
    CP_Settings_TextSize(textSize);

    backButtonX = (float)(CP_System_GetWindowWidth() / 10);
    backButtonY = (float)(CP_System_GetWindowHeight() / 10);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("back", backButtonX, backButtonY);

    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
        if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
            CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
            CP_Font_DrawText("back", backButtonX, backButtonY);
        }
    }

    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
        if (IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void reset_option_gamemenu(void) {
    float textSize = 32.0f;
    buttonWidth = 150.0f;
    buttonHeight = 75.0f;
    CP_Settings_TextSize(textSize);

    resetbarX = (float)(CP_System_GetWindowWidth() / 10);
    resetbarY = (float)(CP_System_GetWindowHeight() / 2 + 300);

    CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Image_Draw(mainmenu_ButtonBackground, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("reset", resetbarX, resetbarY);

    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
        if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, resetbarX, resetbarY, buttonWidth, buttonHeight, 255);
            CP_Settings_Fill(CP_Color_Create(0, 0, 0, 150));
            CP_Font_DrawText("reset", resetbarX, resetbarY);
        }
    }

    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
        if (IsAreaClicked(resetbarX, resetbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            g_highest_level_unlocked = 1;
            Save_Progress();
        }
    }
}


void option_Init(void)
{
    mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");

    float textSize = 62.0f;
    buttonWidth = 300.0f;
    buttonHeight = 150.0f;

    CP_Settings_TextSize(textSize);

    // Sound bar relative to window
    soundBarX = CP_System_GetWindowWidth() * 0.1f;
    soundBarY = CP_System_GetWindowHeight() * 0.05f;
    soundBarWidth = CP_System_GetWindowWidth() * 0.8f;
    soundBarHeight = 70;
}



void option_Update(void)
{
    if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) &&
        CP_Input_KeyDown(KEY_ENTER))
    {
        fullscreen();
    }

    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));
    CP_Font_Set(mainmenu_TEXT);
    CP_Settings_RectMode(CP_POSITION_CENTER);

    sound_option();
    back_option();
}



void option_Exit(void)
{
    CP_Image_Free(mainmenu_ButtonBackground);
    CP_Image_Free(mainmenu_ButtonWhenPressed);
    CP_Font_Free(mainmenu_TEXT);
}
