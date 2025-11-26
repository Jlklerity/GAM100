#include "player.h"
#include "stagewall.h"
#include "hazards.h"
#include "collisionHandling.h"
#include "game.h" 
#include "sound.h"

// --- ANIMATION VARIABLES ---
static int KLS_x = 0;
static int KLS_y = 0;
static int KLE_x = 32;
static int KLE_y = 32;

static int WLS_x = 0;
static int WLS_y = 0;
static int WLE_x = 32;
static int WLE_y = 32;

static int laser_frame_count = 0;
static int animation_speed = 10;




static LaserRect calculate_laser_rect(Laser* laser, Wall* wall[], int wall_count) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 100
	   rectangle should not have any collision with the player and should show up 1 seconds before the laser starts.
	   Might need to use vector for either width and height.*/
	LaserRect rect = { 0 }; // this variable is initiallised and used for drawing the "laser" later on.
	Point end_point = Calculate_Ray_Endpoint(laser->start_point_x, laser->start_point_y, wall, wall_count, laser->dir);

	switch (laser->dir) {
	case RIGHT: {
		rect.w = end_point.x - laser->start_point_x; // the height of the rectangle
		rect.h = laser->width_of_laser; // the width the of rectangle
		rect.x = laser->start_point_x + rect.w / 2.0f; // the midpoint of the rectangle's x axis
		rect.y = laser->start_point_y; // the midpoint of the rectangle's y axis
		break;
	}
	case LEFT: {
		rect.w = laser->start_point_x - end_point.x; // the height of the rectangle
		rect.h = laser->width_of_laser; // the width the of rectangle
		rect.x = laser->start_point_x - rect.w / 2.0f; // the midpoint of the rectangle's x axis
		rect.y = laser->start_point_y; // the midpoint of the rectangle's y axis
		break;
	}
	case DOWN: {
		rect.w = laser->width_of_laser; // the width the of rectangle
		rect.h = end_point.y - laser->start_point_y; // the height of the rectangle
		rect.x = laser->start_point_x; // the midpoint of the rectangle's x axis
		rect.y = laser->start_point_y + rect.h / 2.0f; // the midpoint of the rectangle's y axis
		break;
	}
	case UP: {
		rect.w = laser->width_of_laser; // the width the of rectangle
		rect.h = laser->start_point_y - end_point.y; // the height of the rectangle
		rect.x = laser->start_point_x; // the midpoint of the rectangle's x axis
		rect.y = laser->start_point_y - rect.h / 2.0f; // the midpoint of the rectangle's y axis
		break;
	}
	}
	return rect;
}

// !!! NEW FUNCTION: DRAWING ONLY !!!
void draw_laser(Laser* laser, Wall* wall[], int wall_count) {
	LaserRect rect = calculate_laser_rect(laser, wall, wall_count);

	if (rect.w <= 0 || rect.h <= 0) return;

	switch (laser->state) {
	case LASER_WARNING:
		// Preserving your multiplier * 3
		CP_Image_DrawSubImage(Warning_laser, rect.x, rect.y, rect.w * 2, rect.h, (float)WLS_x, (float)WLS_y, (float)WLE_x, (float)WLE_y, 150);
		break;
	case LASER_FIRING:
	case LASER_CONTINUOUS:
		// Preserving your multiplier (normal width)
		CP_Image_DrawSubImage(kill_laser, rect.x, rect.y, rect.w, rect.h, (float)KLS_x, (float)KLS_y, (float)KLE_x, (float)KLE_y, 255);
		break;
	}
}

// NOTE: This logic was previously in laser_hitbox_warning, but it only drew.
// Since we have draw_laser now, we don't need this function anymore for Logic.
// I kept the function name laser_hitbox for the firing state logic below.

static void laser_hitbox(Laser* laser, Wall* wall[], int wall_count, Player* player, Orb* orb) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 255
	   if rectangle collides with player, player gets knocked back to the direction player came from and loses one health, player
	   should not be able to pass through the laser when it is firing, laser last for 3 seconds. Destroys any orb that comes
	   in contact with it. Might need to use vector for either width and height.*/
	LaserRect rect = calculate_laser_rect(laser, wall, wall_count);

	// --- SPRITE DRAWING LOGIC REMOVED FROM HERE (Moved to draw_laser) ---

	AABB playerHitBox = Get_Player_HitBox(player);
	AABB orbHitBox = Get_Orb_HitBox(orb);
	AABB laserHitBox = { rect.x - rect.w / 2.0f,rect.y - rect.h / 2.0f, rect.w,rect.h,NORMAL };

	if (checkAABBCollision(playerHitBox, laserHitBox)) {
		Player_Init(player, orb); //reset player position only
		// might do things like kockback instead with a health system as reseting 
		// player pos to stsart might be too harsh?
	}

	if (checkAABBCollision(orbHitBox, laserHitBox)) {
		orb->isActive = 0;
	}
}

void update_laser(Laser* laser, float delta_time, Wall* wall[], int wall_count, Player* player, Orb* orbs) {
	static int warningPlayed = 0; // flag to track if warning sound played
	laser->timer += delta_time;

	// --- ANIMATION UPDATE (Runs every frame) ---
	laser_frame_count++;
	if (laser_frame_count >= animation_speed) {
		laser_frame_count = 0;
		KLS_x += 32;
		KLE_x += 32;

		WLS_x += 32; // FIXED: Changed from +0 to +32
		WLE_x += 32; // FIXED: Changed from +0 to +32
	}
	// Reset if we reach the end of the sprite sheet columns (3 columns)
	if (KLS_x >= 32 * 3) {
		KLS_x = 0;
		KLE_x = 32;
	}

	if (WLS_x >= 32 * 3) {
		WLS_x = 0;
		WLE_x = 32;
	}



	switch (laser->state) {
	case LASER_WARNING:
		// No drawing here anymore, drawing happens in draw_laser called from LevelThree.c
		// laser_hitbox_warning(laser, wall, wall_count); <-- Removed drawing call

		// Play warning sound only once per warning cycle
		if (!warningPlayed) {
			Sound_PlaySFX(laser_warning); // <<< PLAY WARNING SOUND ONCE <<<
			warningPlayed = 1;
		}

		// After 1 second, switch to firing
		if (laser->timer >= 1.0f) {
			laser->state = LASER_FIRING;
			laser->timer = 0.0f;

			// Reset warning flag for next cycle
			warningPlayed = 0;

			// >>> PLAY LASER ON <<<
			Sound_PlayLaser(laser_on);
		}
		break;

	case LASER_FIRING:
		laser_hitbox(laser, wall, wall_count, player, orbs); // Only does collisions now
		// Laser lasts 3 seconds
		if (laser->timer >= 2.0f) {
			laser->state = LASER_IDLE; //off
			laser->timer = 0.0f;  // reset timer for firing duration
			CP_Sound_StopGroup(CP_SOUND_GROUP_3);

			// >>> PLAY LASER OFF <<<
			Sound_PlaySFX(laser_off);
		}
		break;

	case LASER_IDLE:
		// Do nothing
		// After 3 seconds go to LASER_WARNING
		if (laser->timer >= 3.0f) {
			laser->state = LASER_WARNING;
			laser->timer = 0.0f;
		}
		break;

	case LASER_CONTINUOUS:
		laser_hitbox(laser, wall, wall_count, player, orbs);
		break;
	}
}
