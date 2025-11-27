#include "cprocessing.h"
#include "game.h"
#include "utils.h"
#include "option.h"
#include "controls.h"
#include "creditscreen.h"
#include "howtoplay.h"

CP_Image menu_background;
float mouseX, mouseY;

// Title
static float titleX, titleY;
static float titleW, titleH;

// Button positions
static float buttonWidth, buttonHeight;
static float playButtonX, playButtonY;
static float optionButtonX, optionButtonY;
static float howtoPlayButtonX, howtoPlayButtonY;
static float controlsButtonX, controlsButtonY;
static float creditsButtonX, creditsButtonY;
static float exitButtonX, exitButtonY;

static float btn_gap;
static float left_margin;
static float start_y;

CP_Image title;

void Main_Menu_Init(void)
{
    mainmenu_TEXT = CP_Font_Load("Assets/kenney_ui-pack-space-expansion/Font/Kenney Future Narrow.ttf");
    CP_Font_Set(mainmenu_TEXT);
    mainmenu_ButtonBackground = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/button_rectangle_depth.png");
    mainmenu_ButtonWhenPressed = CP_Image_Load("Assets/kenney_ui-pack-space-expansion/PNG/Extra/Double/panel_rectangle_screws.png");
    menu_background = CP_Image_Load("./Assets/Piskel_sprite_assets/mainmenu.png");
    title = CP_Image_Load("./Assets/Piskel_sprite_assets/TELESCAPE.png");

    textSize = 36.0f;

    // Portal-2 style left-side alignment
    left_margin = CP_System_GetWindowWidth() * 0.18f; // left side menu
    start_y = CP_System_GetWindowHeight() * 0.35f;

    // Button sizes
    buttonWidth = 300.0f;
    buttonHeight = 75.0f;
    btn_gap = 95.0f;

    // Title (top-left corner area)
    titleX = CP_System_GetWindowWidth() * 0.18f;
    titleY = CP_System_GetWindowHeight() * 0.18f;
    titleW = 500.0f;
    titleH = 100.0f;

    // Button positions (stack downwards)
    playButtonX = left_margin;
    playButtonY = start_y;

    optionButtonX = left_margin;
    optionButtonY = playButtonY + btn_gap;

    howtoPlayButtonX = left_margin;
    howtoPlayButtonY = optionButtonY + btn_gap;

    controlsButtonX = left_margin;
    controlsButtonY = howtoPlayButtonY + btn_gap;

    creditsButtonX = left_margin;
    creditsButtonY = controlsButtonY + btn_gap;

    exitButtonX = left_margin;
    exitButtonY = creditsButtonY + btn_gap;
}

void Main_Menu_Update(void)
{
    mouseX = (float)CP_Input_GetMouseX();
    mouseY = (float)CP_Input_GetMouseY();

    CP_Graphics_ClearBackground(CP_Color_Create(85, 85, 85, 255));

    // Background fullscreen
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(menu_background, 0, 0,
        (float)CP_System_GetWindowWidth(),
        (float)CP_System_GetWindowHeight(),
        255);

    CP_Settings_ImageMode(CP_POSITION_CENTER);

    // title
    CP_Image_Draw(title, titleX, titleY, titleW, titleH, 255);

    // Draw buttons
    CP_Image_Draw(mainmenu_ButtonBackground, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, optionButtonX, optionButtonY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, howtoPlayButtonX, howtoPlayButtonY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, 255);
    CP_Image_Draw(mainmenu_ButtonBackground, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);

    // Text settings
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(textSize);

    // Draw button labels (left-aligned style)
    CP_Font_DrawText("Play", playButtonX, playButtonY);
    CP_Font_DrawText("Options", optionButtonX, optionButtonY);
    CP_Font_DrawText("How To Play", howtoPlayButtonX, howtoPlayButtonY);
    CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);
    CP_Font_DrawText("Credits", creditsButtonX, creditsButtonY);
    CP_Font_DrawText("Quit", exitButtonX, exitButtonY);


    // Highlight when clicking
    if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
    {
        if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, playButtonX, playButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("Play", playButtonX, playButtonY);
        }
        if (IsAreaClicked(optionButtonX, optionButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, optionButtonX, optionButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("Options", optionButtonX, optionButtonY);
        }
        if (IsAreaClicked(howtoPlayButtonX, howtoPlayButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, howtoPlayButtonX, howtoPlayButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("How To Play", howtoPlayButtonX, howtoPlayButtonY);
        }
        if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("Controls", controlsButtonX, controlsButtonY);
        }
        if (IsAreaClicked(creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("Credits", creditsButtonX, creditsButtonY);
        }
        if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY)) {
            CP_Image_Draw(mainmenu_ButtonWhenPressed, exitButtonX, exitButtonY, buttonWidth, buttonHeight, 255);
            CP_Font_DrawText("Quit", exitButtonX, exitButtonY);
        }
    }

    // Click release actions
    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
    {
        if (IsAreaClicked(playButtonX, playButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);

        if (IsAreaClicked(optionButtonX, optionButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_SetNextGameState(option_Init, option_Update, option_Exit);

        if (IsAreaClicked(howtoPlayButtonX, howtoPlayButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_SetNextGameState(HowToPlay_Init, HowToPlay_Update, HowToPlay_Exit);

        if (IsAreaClicked(controlsButtonX, controlsButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_SetNextGameState(controls_Init, controls_Update, controls_Exit);

        if (IsAreaClicked(creditsButtonX, creditsButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_SetNextGameState(Gamecredits_Init, Gamecredits_Update, Gamecredits_Exit);

        if (IsAreaClicked(exitButtonX, exitButtonY, buttonWidth, buttonHeight, mouseX, mouseY))
            CP_Engine_Terminate();
    }
}

void Main_Menu_Exit(void)
{
    CP_Image_Free(mainmenu_ButtonBackground);
    CP_Image_Free(mainmenu_ButtonWhenPressed);
    CP_Font_Free(mainmenu_TEXT);
    CP_Image_Free(menu_background);
    CP_Image_Free(title);
    CP_Image_Free(keybox);
    CP_Font_Free(keytext);
}