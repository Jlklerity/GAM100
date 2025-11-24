#include "cprocessing.h"
#include "utils.h"
#include "stagewall.h"
#include "player.h"
#include "game.h"
#include "mainmenu.h"
#include "sound.h"
#include "controls.h"

static int pause_submenu_state = 0; // 0 = main pause menu, 1 = sound menu, 2 = controls menu
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
static float controlsButtonX, controlsButtonY;
static void sound_option_pausemenu(void);
static void controls_option_pausemenu(void);
float boxWidth, boxHeight;

/*
 * ===================================================================
 * PAUSE MENU (Called by Levels)
 * ===================================================================
 */

int pause_menu(void)
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
        mainmenubarY = (float)CP_System_GetWindowHeight() / 1.4f;
        soundButtonX = (float)CP_System_GetWindowWidth() / 2.0f;
        soundButtonY = (float)CP_System_GetWindowHeight() / 1.65f;
        controlsButtonX = (float)CP_System_GetWindowWidth() / 2;
        controlsButtonY = (float)CP_System_GetWindowHeight() / 1.2f;

        // Draw buttons
        CP_Image_Draw(mainmenu_ButtonBackground, resumebarX, resumebarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, mainmenubarX, mainmenubarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, restartbarX, restartbarY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, soundButtonX, soundButtonY, buttonWidth, buttonHeight, 255);
        CP_Image_Draw(mainmenu_ButtonBackground, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);

        // Draw text
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 200));
        CP_Font_DrawText("PAUSE", pauseTextX, pauseTextY);

        CP_Settings_TextSize(textSize);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 200));
        CP_Font_DrawText("resume", resumebarX, resumebarY);
        CP_Font_DrawText("main menu", mainmenubarX, mainmenubarY);
        CP_Font_DrawText("restart", restartbarX, restartbarY);
        CP_Font_DrawText("sound", soundButtonX, soundButtonY);
        CP_Font_DrawText("controls", controlsButtonX, controlsButtonY);
        

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
            if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
                CP_Image_Draw(mainmenu_ButtonWhenPressed, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
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
            if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
                pause_submenu_state = 2; // <-- SWITCH TO SOUND SUB-MENU
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

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
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
    else if (pause_submenu_state == 2)
    {
        // --- STATE 1: controls SUB-MENU ---

        // 1. Draw the controls
        controls_option_pausemenu();

        // 2. Draw "Back" button
        backButtonX = (float)CP_System_GetWindowWidth() / 2.0f;
        backButtonY = (float)CP_System_GetWindowHeight() / 1.2f;

        CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
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

// --- This is the helper for the PAUSE menu's controls screen ---
static void controls_option_pausemenu(void) {
    boxWidth = 50.0f;
    boxHeight = 50.0f;
    mouseX = CP_Input_GetMouseX();
    mouseY = CP_Input_GetMouseY();

    // Window is 1600 x 900
    float col1X = 200.0f;   // Movement column farther left
    float col2X = 1000.0f;  // Abilities column farther right
    float startY = 220.0f;
    float spacingY = 80.0f;

    //---------------------------------------------------
    // MAIN HEADING — "CONTROLS"
    //---------------------------------------------------
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(72.0f);
    CP_Font_DrawText("CONTROLS", 1600.0f / 2.0f, 80.0f);

    //---------------------------------------------------
    // SUB HEADERS
    //---------------------------------------------------
    CP_Settings_TextSize(48.0f);

    CP_Font_DrawText("MOVEMENT", col1X + 200.0f, 150.0f);
    CP_Font_DrawText("ABILITIES", col2X + 200.0f, 150.0f);

    //---------------------------------------------------
    // FIRST PASS — DRAW ALL KEYBOXES + CENTERED KEY TEXT
    //---------------------------------------------------
    CP_Settings_TextSize(32.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    // MOVEMENT KEYS -------------------------------------------------------
    CP_Image_Draw(keybox, col1X, startY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("W", col1X, startY);

    CP_Image_Draw(keybox, col1X, startY + spacingY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("S", col1X, startY + spacingY);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 2, boxWidth, boxHeight, 255);
    CP_Font_DrawText("A", col1X, startY + spacingY * 2);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 3, boxWidth, boxHeight, 255);
    CP_Font_DrawText("D", col1X, startY + spacingY * 3);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 4, boxWidth + 100, boxHeight, 255);
    CP_Font_DrawText("SPACE", col1X, startY + spacingY * 4);

    // ABILITIES KEYS ------------------------------------------------------
    CP_Image_Draw(keybox, col2X, startY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("1", col2X, startY);

    CP_Image_Draw(keybox, col2X, startY + spacingY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("2", col2X, startY + spacingY);

    CP_Image_Draw(keybox, col2X, startY + spacingY * 2, boxWidth, boxHeight, 255);
    CP_Font_DrawText("J", col2X, startY + spacingY * 2);


    //---------------------------------------------------
    // SECOND PASS — LEFT-ALIGNED DESCRIPTIONS
    //---------------------------------------------------
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);

    float textOffset = 120.0f;
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

    // MOVEMENT DESCRIPTIONS -----------------------------------------------
    CP_Font_DrawText(" - LOOK UP / ENTER DOORS", col1X + textOffset, startY);
    CP_Font_DrawText(" - LOOK DOWN", col1X + textOffset, startY + spacingY);
    CP_Font_DrawText(" - GO LEFT", col1X + textOffset, startY + spacingY * 2);
    CP_Font_DrawText(" - GO RIGHT", col1X + textOffset, startY + spacingY * 3);
    CP_Font_DrawText(" - JUMP", col1X + textOffset, startY + spacingY * 4);

    // ABILITIES DESCRIPTIONS ----------------------------------------------
    CP_Font_DrawText(" - SELECT TELEPORT ORB", col2X + textOffset, startY);
    CP_Font_DrawText(" - SELECT DESTROY ORB", col2X + textOffset, startY + spacingY);
    CP_Font_DrawText(" - THROW SELECTED ORB", col2X + textOffset, startY + spacingY * 2);
    // Back to CENTER for other UI
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

// --- PUBLIC FUNCTIONS (Called by Main Menu) ---
void option_Init(void)
{
    mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
    keytext = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    keybox = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_glass.png");

    textSize = 32.0f;
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