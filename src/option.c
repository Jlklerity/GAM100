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

static int pause_submenu_state = 0.0f; // 0 = main pause menu, 1 = sound menu
static float volumePercent = 100.0f;
static float pauseTextX, pauseTextY;
static float backButtonX, backButtonY;
static float soundButtonX, soundButtonY;
static float resetbarX, resetbarY;
static float resumebarX, resumebarY;
static float mainmenubarX, mainmenubarY;
static float restartbarX, restartbarY;
static float buttonWidth, buttonHeight;
static float soundBarX, soundBarY;
static float soundBarWidth, soundBarHeight;
static void sound_option_pausemenu(void);

/*
 * ===================================================================
 * PAUSE MENU (Called by Levels)
 * ===================================================================
 */

int pause_menu(void)
{
    float textSize = 32.0f;
    buttonWidth = 200.0f;
    buttonHeight = 75.0f;

    // Draw Translucent Background 
    CP_Settings_Fill(CP_Color_Create(50, 50, 50, 200));
    CP_Graphics_DrawRect((float)CP_System_GetWindowWidth() / 2.0f,
        (float)CP_System_GetWindowHeight() / 2.0f,
        (float)CP_System_GetWindowWidth(),
        (float)CP_System_GetWindowHeight());

    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();
    CP_Font_Set(mainmenu_TEXT); 
    CP_Settings_TextSize(64.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    // --- PAUSE MENU STATE MACHINE ---
    if (pause_submenu_state == 0)
    {
        // --- STATE 0: MAIN PAUSE MENU ---
        pauseTextX = (float)CP_System_GetWindowWidth() / 2.0f+10.0f;
        pauseTextY = (float)CP_System_GetWindowWidth() / 6.0f;
        resumebarX = (float)CP_System_GetWindowWidth() / 2.0f;
        resumebarY = (float)CP_System_GetWindowHeight() / 2.5f;
        restartbarX = (float)CP_System_GetWindowWidth() / 2.0f;
        restartbarY = (float)CP_System_GetWindowHeight() / 2.0f;
        mainmenubarX = (float)CP_System_GetWindowWidth() / 2.0f;
        mainmenubarY = (float)CP_System_GetWindowHeight() / 1.65f;
        soundButtonX = (float)CP_System_GetWindowWidth() / 2.0f;
        soundButtonY = (float)CP_System_GetWindowHeight() / 1.4f;

        // Draw buttons
        CP_Image_Draw(mainmenu_ButtonBackground, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, soundButtonX, soundButtonY, buttonWidth, buttonHeight, 255);

        // Draw text
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 200));
        CP_Font_DrawText("PAUSE", pauseTextX, pauseTextY);

        CP_Settings_TextSize(textSize);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
        CP_Font_DrawText("resume", resumebarX, resumebarY);
        CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);
        CP_Font_DrawText("restart", restartbarX, restartbarY);
        CP_Font_DrawText("sound", soundButtonX, soundButtonY);

        // Button press effect
        if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
            if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
            if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
            if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
            if (IsAreaClicked(soundButtonX, soundButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, soundButtonX, soundButtonY, buttonWidth, buttonHeight, 255);
        }

        // Button actions
        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
        {
            if (IsAreaClicked(resumebarX, resumebarY, buttonWidth, buttonHeight, mouseX, mouseY))
                return 1;
            if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 0; // Reset state before leaving
                return 2;
            }
            if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 0; // Reset state before leaving
                return 3;
            }
            if (IsAreaClicked(soundButtonX, soundButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 1; // <-- SWITCH TO SOUND SUB-MENU
                return 0; // Stay paused
            }
        }
    }
    else if (pause_submenu_state == 1)
    {
        // --- STATE 1: SOUND SUB-MENU ---

        // 1. Draw the sound slider
        sound_option_pausemenu();

        // 2. Draw "Back" button
        backButtonX = (float)CP_System_GetWindowWidth() / 2.0f;
        backButtonY = (float)CP_System_GetWindowHeight() / 2.0f;

        CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
        CP_Font_DrawText("Back", backButtonX, backButtonY);

        // 3. Handle visual press for Back button
        if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) &&
            IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
        {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
        }

        // 4. Handle click for Back button
        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) &&
            IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
        {
            pause_submenu_state = 0; // <-- SWITCH BACK TO MAIN PAUSE MENU
            return 0; // Stay paused
        }
    }

    return 0; // Default: stay paused, do nothing
}

/*
 * ===================================================================
 * OPTIONS SCREEN (Called by Main Menu)
 * ===================================================================
 */
static void back_option_mainmenu(void)
{
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    backButtonX = (float)CP_System_GetWindowWidth() / 2;
    backButtonY = (float)CP_System_GetWindowHeight() / 2 ;

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

// --- This function is now STATIC (private to this file) ---
static void sound_option_mainmenu(void)
{
    // pull updated mouse input
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    // Sound bar — CORNER MODE
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_DrawText("Volume", (float)CP_System_GetWindowWidth() / 2, soundBarY - 30); // Draw label above bar
    CP_Settings_Fill(CP_Color_Create(20, 20, 20, 255));
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
            volumePercent = (mouseX - soundBarX) / soundBarWidth * 100.0f;

            if (volumePercent < 0) volumePercent = 0;
            if (volumePercent > 100) volumePercent = 100;

            float v = volumePercent / 100.0f;
            Sound_SetSFXVolume(v);
            Sound_SetMusicVolume(v);
        }
    }
    // Back to CENTER for other UI
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

// --- This is the helper for the PAUSE menu's sound screen ---
static void sound_option_pausemenu(void) {
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    // Sound bar — CORNER MODE
    CP_Settings_RectMode(CP_POSITION_CORNER);

    // --- Draw 'Volume' label for the slider ---
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(32.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("Volume", (float)CP_System_GetWindowWidth() / 2, soundBarY - 30); // Draw label above bar

    // Outline
    CP_Settings_Fill(CP_Color_Create(20, 20, 20, 255)); // Added background
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
}

// --- PUBLIC FUNCTIONS (Called by Main Menu) ---
void option_Init(void)
{
    mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");

    float textSize = 32.0f;
    buttonWidth = 150.0f;
    buttonHeight = 75.0f;

    CP_Settings_TextSize(textSize);

    // Sound bar relative to window
    soundBarX = (float)CP_System_GetWindowWidth() * 0.1f;
    soundBarY = (float)CP_System_GetWindowHeight() * 0.2f;
    soundBarWidth = (float)CP_System_GetWindowWidth() * 0.8f;
    soundBarHeight = 70.0f;
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

    // Call the STATIC (private) helper functions
    sound_option_mainmenu();
    back_option_mainmenu();
}

void option_Exit(void)
{
    CP_Image_Free(mainmenu_ButtonBackground);
    CP_Image_Free(mainmenu_ButtonWhenPressed);
    CP_Font_Free(mainmenu_TEXT);
}