#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "mainmenu.h"

float boxWidth, boxHeight;
CP_Image keybox;
CP_Font keytext;

void controls_Init(void) {
	keytext = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
	keybox = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_glass.png");
	CP_Font_Set(keytext);
	boxWidth = 50.0f;
	boxHeight = 50.0f;
}

void controls_Update(void) {
    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    float col1X = 150.0f;   // Movement keys column
    float col2X = 550.0f;   // Orb/ability keys column
    float startY = 180.0f;
    float spacingY = 80.0f;

    // -----------------------------------
    // HEADING
    // -----------------------------------
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(64.0f);
    CP_Font_DrawText("CONTROLS", CP_System_GetWindowWidth() / 2.0f, 80.0f);

    CP_Settings_TextSize(32.0f);

    // -----------------------------------
    // FIRST PASS — DRAW KEYBOX + CENTERED KEYS
    // -----------------------------------
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));

    // Movement Keys ---------------------------------
    CP_Image_Draw(keybox, col1X, startY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("W", col1X, startY);

    CP_Image_Draw(keybox, col1X, startY + spacingY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("S", col1X, startY + spacingY);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 2, boxWidth, boxHeight, 255);
    CP_Font_DrawText("A", col1X, startY + spacingY * 2);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 3, boxWidth, boxHeight, 255);
    CP_Font_DrawText("D", col1X, startY + spacingY * 3);

    CP_Image_Draw(keybox, col1X, startY + spacingY * 4, boxWidth, boxHeight, 255);
    CP_Font_DrawText("SPACE", col1X, startY + spacingY * 4);


    // Orb / Ability Keys ------------------------------
    CP_Image_Draw(keybox, col2X, startY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("1", col2X, startY);

    CP_Image_Draw(keybox, col2X, startY + spacingY, boxWidth, boxHeight, 255);
    CP_Font_DrawText("2", col2X, startY + spacingY);

    CP_Image_Draw(keybox, col2X, startY + spacingY * 2, boxWidth, boxHeight, 255);
    CP_Font_DrawText("J", col2X, startY + spacingY * 2);

    // -----------------------------------
    // SECOND PASS — DRAW LEFT-ALIGNED DESCRIPTIONS
    // -----------------------------------
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
    float textOffset = 100.0f;

    // Movement descriptions
    CP_Font_DrawText(" - LOOK UP / ENTER DOORS", col1X + textOffset, startY);
    CP_Font_DrawText(" - LOOK DOWN", col1X + textOffset, startY + spacingY);
    CP_Font_DrawText(" - GO LEFT", col1X + textOffset, startY + spacingY * 2);
    CP_Font_DrawText(" - GO RIGHT", col1X + textOffset, startY + spacingY * 3);
    CP_Font_DrawText(" - JUMP", col1X + textOffset, startY + spacingY * 4);

    // Orb/Ability descriptions
    CP_Font_DrawText(" - TELEPORT ORB", col2X + textOffset, startY);
    CP_Font_DrawText(" - DESTROY ORB", col2X + textOffset, startY + spacingY);
    CP_Font_DrawText(" - THROW SELECTED ORB", col2X + textOffset, startY + spacingY * 2);
}


void controls_Exit(void) {
	CP_Image_Free(keybox);
	CP_Font_Free(keytext);
}