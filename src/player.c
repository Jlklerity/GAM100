#include "cprocessing.h"
#include "player.h"
#include "stage_wall.h"
#include "collisionHandling.h"
#include "levelone.h"
#include "sound.h"

void Player_Init(Player *player, Orb *orb) {
	//const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
    const float wall_thickness = 20.0f;
	const float player_width = 64.0f;
	const float player_height = 64.0f;
	const int player_highlight = 255;
	const float posX = 100, posY = screen_height - player_height/2 - wall_thickness;
	//const int degree = 0; //player facing right
	/*orbCount = 0;
	maxOrb = 5;*/

    player->fox_sprite = CP_Image_Load("./Assets/Piskel_sprite_assets/FOX_ANIMATION_ALL_MOVEMENTS_05_JUMP.png"); //fox sprite drawing


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

void Player_Update(Player* player, float deltaTime, float *player_moveX, float jump_strength) {
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

void Orb_Update(Player* player, Orb* orb, float *orb_moveX, float *orb_moveY, float deltaTime) {
    if (orb->isActive == 0) {
        if (CP_Input_KeyTriggered(KEY_1)) {
            player->orb_type = TELEPORT_ORB;
            orb->orb_type = TELEPORT_ORB;
        }
        if (CP_Input_KeyTriggered(KEY_2)) {
            player->orb_type = DESTROY_ORB;
            orb->orb_type = DESTROY_ORB;
        }
    }
    static float ammo_timer = 0.0f;
    ammo_timer += deltaTime;
    if (ammo_timer > 10.0f) { // every 10 seconds
        if (orb->ammo < orb->max_ammo) {
            orb->ammo++;
        }
        ammo_timer = 0.0f;
    }
    //Checking if orb is active in the air
    if (orb->isActive == 0) {
        if (CP_Input_KeyTriggered(KEY_J)) {
            if (orb->ammo > 0) {
                orb->isActive = 1;
                orb->x = player->player_posX;
                orb->y = player->player_posY;
                orb->direction = player->direction;
                orb->ammo--;  // decrease ammo when shooting
                Sound_PlaySFX(orb_shoot);
            }
        }
    }

    if (orb->isActive == 1) {
        switch (orb->direction) {
        case PLAYER_RIGHT:
            player->degree = 0; //for sprite looking direction
            *orb_moveX += orb->orb_velocity_x * deltaTime;
            break;
        case PLAYER_LEFT:
            player->degree = 180;
            *orb_moveX -= orb->orb_velocity_x * deltaTime;
        case PLAYER_UP:
            *orb_moveY -= orb->orb_velocity_Y * deltaTime;
        case PLAYER_DOWN:
            *orb_moveY += orb->orb_velocity_Y * deltaTime;
        }
        //Change orb type
        switch (player->orb_type) {
        case TELEPORT_ORB:
            CP_Settings_Fill(CP_Color_Create(0, 190, 255, 255));
            break;
        case DESTROY_ORB:
            CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
            break;
        default:
            CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
            break;
        }
        CP_Graphics_DrawCircle(orb->x, orb->y, orb->diameter);
    }

}
 