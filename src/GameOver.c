#include "cprocessing.h"
#include "utils.h"
#include "stagewall.h"
#include "game.h"
#include "mainmenu.h"
#include "GameOver.h"


static int pause_submenu_state = 0; // 0 = main pause menu, 1 = sound menu
static float volumePercent = 100.0f;
static float GameOverTextX, GameOverTextY;
static float backButtonX, backButtonY;
static float soundButtonX, soundButtonY;
static float resetbarX, resetbarY;

static float mainmenubarX, mainmenubarY;
static float restartbarX, restartbarY;
static float buttonWidth, buttonHeight;

/*
 * ===================================================================
 * GAME OVER MENU (Called by Levels)
 * ===================================================================
 */

int GameOver_screen(void)
{
    textSize = 32.0f;
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
    CP_Settings_TextSize(84.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    // --- GAMEOVER STATE MACHINE ---
    if (pause_submenu_state == 0)
    {
        // --- STATE 0: MAIN PAUSE MENU ---
        GameOverTextX = (float)CP_System_GetWindowWidth() / 2.0f + 10.0f;
        GameOverTextY = (float)CP_System_GetWindowWidth() / 6.0f;
        restartbarX = (float)CP_System_GetWindowWidth() / 2.0f;
        restartbarY = (float)CP_System_GetWindowHeight() / 2.0f;
        mainmenubarX = (float)CP_System_GetWindowWidth() / 2.0f;
        mainmenubarY = (float)CP_System_GetWindowHeight() / 1.4f;

        // Draw buttons
        CP_Image_Draw(mainmenu_ButtonBackground, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);

        // Draw text
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 200));
        CP_Font_DrawText("GAME OVER", GameOverTextX, GameOverTextY);

        CP_Settings_TextSize(textSize);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
        CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);
        CP_Font_DrawText("restart", restartbarX, restartbarY);
      

        // Button press effect
        if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
            if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
            if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
        }

        // Button actions
        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
        {
            if (IsAreaClicked(mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 0; // Reset state before leaving
                return 2;
            }
            if (IsAreaClicked(restartbarX, restartbarY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 0; // Reset state before leaving
                return 3;
            }
             
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
    backButtonY = (float)CP_System_GetWindowHeight() / 2;

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

// --- This is the helper for the PAUSE menu's sound screen ---

// --- PUBLIC FUNCTIONS (Called by Main Menu) ---
void GameOver_Init(void)
{
    mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");

    textSize = 32.0f;
    buttonWidth = 150.0f;
    buttonHeight = 75.0f;

    CP_Settings_TextSize(textSize);
}

void GameOver_Update(void)
{
    if (((CP_Input_KeyDown(KEY_LEFT_ALT)) || (CP_Input_KeyDown(KEY_RIGHT_ALT))) &&
        CP_Input_KeyDown(KEY_ENTER))
    {
        fullscreen();
    }

    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));
    CP_Font_Set(mainmenu_TEXT);
    CP_Settings_RectMode(CP_POSITION_CENTER);

}

void GameOver_Exit(void)
{
    CP_Image_Free(mainmenu_ButtonBackground);
    CP_Image_Free(mainmenu_ButtonWhenPressed);
    CP_Font_Free(mainmenu_TEXT);
}