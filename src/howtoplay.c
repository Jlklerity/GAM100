#include "cprocessing.h"
#include "howtoplay.h"
#include "utils.h"
#include "mainmenu.h" // To return to menu
#include <stdio.h>

// --- VARIABLES ---
static int current_slide = 0;
static int total_slides = 6; // INCREASED to 6 Mechanics

// --- ASSETS ---
static CP_Font font_tutorial;
static CP_Image img_ammo1;  
static CP_Image img_ammo2;
static CP_Image img_throw_orb;      
static CP_Image img_destroy_orb;     
static CP_Image img_destroy_wall;    
static CP_Image img_pressure_plate;  
static CP_Image img_door;           

void HowToPlay_Init(void)
{
    font_tutorial = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");

    // --- LOAD IMAGES ---
    // Make sure these filenames match your assets exactly!
    img_ammo1 = CP_Image_Load("Assets/Tutorial_assets/ammo_teleport.png");  
    img_ammo2 = CP_Image_Load("Assets/Tutorial_assets/ammo_destroy.png");
    img_throw_orb = CP_Image_Load("Assets/Tutorial_assets/throw_orb.png");      
    img_destroy_orb = CP_Image_Load("Assets/Tutorial_assets/switching.png");     
    img_destroy_wall = CP_Image_Load("Assets/Tutorial_assets/destroy_wall.png");    
    img_pressure_plate = CP_Image_Load("Assets/Tutorial_assets/pressure_plate.png");  
    img_door = CP_Image_Load("Assets/Tutorial_assets/door.png");            

    current_slide = 0;
}

void HowToPlay_Update(void)
{
    // 1. Background
    CP_Graphics_ClearBackground(CP_Color_Create(50, 50, 50, 255));

    float width = (float)CP_System_GetWindowWidth();
    float height = (float)CP_System_GetWindowHeight();
    float center_x = width / 2.0f;

    // 2. Draw Title
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Font_Set(font_tutorial);
    CP_Settings_TextSize(60.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("HOW TO PLAY", center_x, 80.0f);

    // Image Dimensions
    float img_y = height / 2.0f - 50.0f;
    float text_y = height - 180.0f;
    float img_w = 600.0f;
    float img_h = 350.0f;

    CP_Settings_RectMode(CP_POSITION_CENTER);

    // 3. Display Content based on 'current_slide'
    CP_Settings_TextSize(40.0f);

    switch (current_slide) {

    case 0: // NEW: AMMO & ORB TYPE
        if (img_ammo1 != NULL) {
            // This image is small (just UI), so maybe draw it smaller or zoomed
            CP_Image_Draw(img_ammo1, center_x - 300.0f, img_y, 400.0f, 300.0f, 255);
            CP_Image_Draw(img_ammo2, center_x + 300.0f, img_y, 400.0f, 300.0f, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 1: AMMO & ORBS", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Top Left shows your AMMO and current ORB TYPE.", center_x, text_y);
        CP_Font_DrawText("Blue Dot = Teleport Orb. Red Dot = Destroy Orb.", center_x, text_y + 30.0f);
        CP_Font_DrawText("Ammo regenerates automatically over time.", center_x, text_y + 60.0f);
        break;

    case 1: // THROW ORB
        if (img_throw_orb != NULL) {
            CP_Image_Draw(img_throw_orb, center_x, img_y, img_w, img_h - 50, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 2: THROW ORB", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Press 'J' to throw your orb.", center_x, text_y);
        CP_Font_DrawText("The orb follows your movement direction.", center_x, text_y + 30.0f);
        CP_Font_DrawText("Press '1' to switch to Teleport Orb.", center_x, text_y + 60.0f);
        break;

    case 2: // DESTROY ORB
        if (img_destroy_orb != NULL) {
            CP_Image_Draw(img_destroy_orb, center_x, img_y, img_w, img_h - 50, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 3: DESTROY ORB", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Press '2' to switch to Destroy Orb.", center_x, text_y);
        CP_Font_DrawText("This orb is red and dangerous!", center_x, text_y + 30.0f);
        CP_Font_DrawText("Use it to break obstacles.", center_x, text_y + 60.0f);
        break;

    case 3: // DESTROY WALL
        if (img_destroy_wall != NULL) {
            // Vertical wall image might need different dimensions
            CP_Image_Draw(img_destroy_wall, center_x, img_y, 400.0f, 400.0f, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 4: DESTROY WALL", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Use the Destroy Orb on RED WALLS.", center_x, text_y);
        CP_Font_DrawText("The wall will break, clearing your path.", center_x, text_y + 30.0f);
        break;

    case 4: // TIME SENSITIVE PRESSURE SENSOR
        if (img_pressure_plate != NULL) {
            CP_Image_Draw(img_pressure_plate, center_x, img_y, 270.0f, 490.0f, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 5: PRESSURE PLATES", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Stand on plates to activate doors or platforms.", center_x, text_y);
        CP_Font_DrawText("Some plates are TIME SENSITIVE (5 seconds).", center_x, text_y + 30.0f);
        CP_Font_DrawText("You must hurry before they reset!", center_x, text_y + 60.0f);
        break;

    case 5: // DOOR OPENING
        if (img_door != NULL) {
            // Door image is vertical
            CP_Image_Draw(img_door, center_x, img_y, 270.0f, 490.0f, 255);
        }
        CP_Settings_TextSize(40.0f);
        CP_Font_DrawText("MECHANIC 6: DOORS", center_x, text_y - 50.0f);
        CP_Settings_TextSize(30.0f);
        CP_Font_DrawText("Pressure plates open specific doors.", center_x, text_y);
        CP_Font_DrawText("Find the right plate to proceed.", center_x, text_y + 30.0f);
        CP_Font_DrawText("Reach the EXIT DOOR to finish the level.", center_x, text_y + 60.0f);
        break;
    }

    // 4. Navigation Buttons (Next / Back / Exit)
    float btn_y = height - 100.0f;
    float btn_w = 150.0f;
    float btn_h = 60.0f;
    float mouseX = CP_Input_GetMouseX();
    float mouseY = CP_Input_GetMouseY();

    // "NEXT" Button (Only if not on last slide)
    if (current_slide < total_slides - 1) {
        float next_x = width - 200.0f;
        CP_Settings_Fill(CP_Color_Create(100, 100, 255, 255));
        CP_Graphics_DrawRect(next_x, btn_y, btn_w, btn_h);
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        CP_Font_DrawText("NEXT >", next_x, btn_y);

        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
            if (IsAreaClicked(next_x, btn_y, btn_w, btn_h, mouseX, mouseY)) {
                current_slide++;
            }
        }
    }
    else {
        // "FINISH" Button (On last slide)
        float next_x = width - 200.0f;
        CP_Settings_Fill(CP_Color_Create(100, 255, 100, 255)); // Green
        CP_Graphics_DrawRect(next_x, btn_y, btn_w, btn_h);
        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
        CP_Font_DrawText("FINISH", next_x, btn_y);

        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
            if (IsAreaClicked(next_x, btn_y, btn_w, btn_h, mouseX, mouseY)) {
                CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            }
        }
    }

    // "PREVIOUS" Button (Only if not on first slide)
    if (current_slide > 0) {
        float prev_x = 200.0f;
        CP_Settings_Fill(CP_Color_Create(255, 100, 100, 255));
        CP_Graphics_DrawRect(prev_x, btn_y, btn_w, btn_h);
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
        CP_Font_DrawText("< BACK", prev_x, btn_y);

        if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
            if (IsAreaClicked(prev_x, btn_y, btn_w, btn_h, mouseX, mouseY)) {
                current_slide--;
            }
        }
    }

    // "EXIT" Button (Always available)
    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void HowToPlay_Exit(void)
{
    CP_Font_Free(font_tutorial);
    CP_Image_Free(img_ammo1);
    CP_Image_Free(img_ammo2);
    CP_Image_Free(img_throw_orb);
    CP_Image_Free(img_destroy_orb);
    CP_Image_Free(img_destroy_wall);
    CP_Image_Free(img_pressure_plate);
    CP_Image_Free(img_door);
}