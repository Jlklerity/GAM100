#include "cprocessing.h"
#include "player.h"
#include "stagewall.h"
#include "collisionHandling.h"
#include "levelone.h"
#include "sound.h"


static float animation_timer;
static int frame_count = 0;   // counts frames for timing
static int idle_count = 0;    // counts idle frames
static int animation_speed = 10;

// --- ORB ANIMATION SETTINGS ---
// CHECK THIS: If your Red Orb is small (like the blue one), change 128 to 32.
static int DOS_x = 0;
static int DOS_y = 0;
static int DOE_x = 32; // Width of one Red Orb frame
static int DOE_y = 32; // Height of one Red Orb frame

static int TOS_x = 0;
static int TOS_y = 0;
static int TOE_x = 32;  // Width of one Blue Orb frame
static int TOE_y = 32;  // Height of one Blue Orb frame

static int facing_left = 0;


void Player_Init(Player* player, Orb* orb) {
    const float screen_height = (float)CP_System_GetWindowHeight();
    const float wall_thickness = 20.0f;
    const float player_width = 64.0f;
    const float player_height = 64.0f;
    const int player_highlight = 255;
    const float posX = 100, posY = screen_height - player_height / 2 - wall_thickness;

    // Reset animation variables
    DOS_x = 0;
    DOS_y = 0;
    DOE_x = 32; // Ensure this matches your sprite width
    DOE_y = 32;

    TOS_x = 0;
    TOS_y = 0;
    TOE_x = 32;
    TOE_y = 32;

    // LOAD IMAGES - CHECK FILENAMES IF ORB IS INVISIBLE
    player->fox_sprite = CP_Image_Load("./Assets/Piskel_sprite_assets/FOX_ANIMATION_ALL_MOVEMENTS_05_JUMP.png");
    player->destroy_orb = CP_Image_Load("./Assets/Piskel_sprite_assets/destroy_orb.png");
    player->teleport_orb = CP_Image_Load("./Assets/Piskel_sprite_assets/teleport_orb_blue.png");

    player->orb_type = TELEPORT_ORB;
    player->player_velocityX = 400.0f;
    player->player_velocityY = 300.0f;
    player->isGrounded = 0;
    player->direction = PLAYER_RIGHT;
    player->last_direction = PLAYER_RIGHT;
    player->player_posX = posX;
    player->player_posY = posY;
    player->degree = 0;
    player->player_width = player_width;
    player->player_height = player_height;
    player->player_color = CP_Color_Create(255, 0, 0, player_highlight);

    orb->isActive = 0;
    orb->orb_velocity_x = 800.0f;
    orb->orb_velocity_Y = 800.0f;
    orb->x = player->player_posX;
    orb->y = player->player_posY;
    orb->diameter = 20.0f;
}

void Player_Update(Player* player, float deltaTime, float* player_moveX, float jump_strength) {
    if (CP_Input_KeyDown(KEY_D)) {
        *player_moveX += player->player_velocityX * deltaTime;
        player->direction = PLAYER_RIGHT;
    }
    if (CP_Input_KeyDown(KEY_A)) {
        *player_moveX -= player->player_velocityX * deltaTime;
        player->direction = PLAYER_LEFT;
    }

    // Vertical aiming
    if (CP_Input_KeyDown(KEY_W)) {
        if (player->direction == PLAYER_LEFT || player->direction == PLAYER_RIGHT) {
            player->last_direction = player->direction;
        }
        player->direction = PLAYER_UP;
    }
    if (CP_Input_KeyReleased(KEY_W)) {
        player->direction = player->last_direction;
    }

    if (CP_Input_KeyDown(KEY_S)) {
        if (player->direction == PLAYER_LEFT || player->direction == PLAYER_RIGHT) {
            player->last_direction = player->direction;
        }
        player->direction = PLAYER_DOWN;
    }

    if (CP_Input_KeyReleased(KEY_S)) {
        player->direction = player->last_direction;
    }

    // Jumping
    if (CP_Input_KeyTriggered(KEY_SPACE) && player->isGrounded) {
        player->player_velocityY = -jump_strength;
        player->isGrounded = 0;
    }
}

void Orb_Update(Player* player, Orb* orb, float* orb_moveX, float* orb_moveY, float deltaTime) {

    // Timer for the "Above Head" indicator
    static float indicator_timer = 0.0f;

    if (indicator_timer > 0.0f) {
        indicator_timer -= deltaTime;
    }

    if (orb->isActive == 0) {
        if (CP_Input_KeyTriggered(KEY_1)) {
            player->orb_type = TELEPORT_ORB;
            orb->orb_type = TELEPORT_ORB;
            indicator_timer = 2.0f;
        }
        if (CP_Input_KeyTriggered(KEY_2)) {
            player->orb_type = DESTROY_ORB;
            orb->orb_type = DESTROY_ORB;
            indicator_timer = 2.0f;

            // RESET ANIMATION FRAMES
            // This fixes the bug where the sprite might be stuck "off screen"
            DOS_x = 0;
            DOE_x = 32; // Use 32 if sprite is small
        }
    }

    // Ammo regen
    static float ammo_timer = 0.0f;
    ammo_timer += deltaTime;
    if (ammo_timer > 10.0f) {
        if (orb->ammo < orb->max_ammo) {
            orb->ammo++;
        }
        ammo_timer = 0.0f;
    }

    // Shooting logic
    if (orb->isActive == 0) {
        if (CP_Input_KeyTriggered(KEY_J)) {
            if (orb->ammo > 0) {
                orb->isActive = 1;
                orb->x = player->player_posX;
                orb->y = player->player_posY;
                orb->direction = player->direction;
                orb->ammo--;
                Sound_PlaySFX(orb_shoot);
            }
        }
    }

    // --- ANIMATION LOGIC ---
    frame_count++;
    if (frame_count >= animation_speed) {
        frame_count = 0;

        // Animate Destroy Orb
        DOS_x += 32; // Change to 32 if sprite is small
        DOE_x += 32; // Change to 32 if sprite is small

        // Animate Teleport Orb
        TOS_x += 32;
        TOE_x += 32;

        if (DOS_x >= 32 * 5) { // Assuming 5 frames
            DOS_x = 0;
            DOE_x = 32; // Change to 32 if sprite is small
        }

        if (TOS_x >= 32 * 4) { // Assuming 4 frames
            TOS_x = 0;
            TOE_x = 32;
        }
    }

    // --- PROJECTILE MOVEMENT & DRAWING (When Active) ---
    if (orb->isActive == 1) {
        switch (orb->direction) {
        case PLAYER_RIGHT: *orb_moveX += orb->orb_velocity_x * deltaTime; break;
        case PLAYER_LEFT:  *orb_moveX -= orb->orb_velocity_x * deltaTime; break;
        case PLAYER_UP:    *orb_moveY -= orb->orb_velocity_Y * deltaTime; break;
        case PLAYER_DOWN:  *orb_moveY += orb->orb_velocity_Y * deltaTime; break;
        }

        switch (player->orb_type) {
        case TELEPORT_ORB:
            CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));
            CP_Image_DrawSubImage(player->teleport_orb, orb->x, orb->y, 50 , 50 , (float)TOS_x, (float)TOS_y, (float)TOE_x, (float)TOE_y, 255);
            break;
        case DESTROY_ORB:
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
            CP_Image_DrawSubImage(player->destroy_orb, orb->x, orb->y, 75 , 75 , (float)DOS_x, (float)DOS_y, (float)DOE_x, (float)DOE_y, 255);
            break;
        default:
            CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
            break;
        }
    }

    // --- INDICATOR DRAWING (Above Head) ---
    if (indicator_timer > 0.0f) {
        switch (player->orb_type) {
        case TELEPORT_ORB:
            CP_Image_DrawSubImage(player->teleport_orb, player->player_posX, player->player_posY - 100.0f, 50.0f, 50.0f, (float)TOS_x, (float)TOS_y, (float)TOE_x, (float)TOE_y, 255);
            break;
        case DESTROY_ORB:
            CP_Image_DrawSubImage(player->destroy_orb, player->player_posX, player->player_posY - 100.0f, 75.0f, 75.0f, (float)DOS_x, (float)DOS_y, (float)DOE_x, (float)DOE_y, 255);
            break;
        }
    }
}