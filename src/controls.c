#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "mainmenu.h"
#include "controls.h"

float backButtonX, backButtonY;
float buttonWidth, buttonHeight;
float boxWidth, boxHeight;

void controls_Init(void) {
	keytext = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	keybox = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_glass.png");
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
	CP_Font_Set(keytext);
	boxWidth = 50.0f;
	boxHeight = 50.0f;
    buttonWidth = 200.0f;
    buttonHeight = 75.0f;
    backButtonX = (float)(CP_System_GetWindowWidth() / 2);
    backButtonY = (float)(CP_System_GetWindowHeight() / 1.2f);
}

void controls_Update(void) {
    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

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

    CP_Font_DrawText("MOVEMENT", col1X+200.0f, 150.0f);
    CP_Font_DrawText("ABILITIES", col2X+200.0f, 150.0f);

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


    CP_Image_Draw(mainmenu_ButtonBackground, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("back", backButtonX, backButtonY);

    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        CP_Image_Draw(mainmenu_ButtonWhenPressed, backButtonX, backButtonY, buttonWidth, buttonHeight, 255);
         CP_Font_DrawText("back", backButtonX, backButtonY);
    }

    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT) &&
        IsAreaClicked(backButtonX, backButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}



void controls_Exit(void) {
	CP_Image_Free(keybox);
	CP_Font_Free(keytext);
}