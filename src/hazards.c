#include "player.h"
#include "stagewall.h"
#include "hazards.h"
#include "collisionHandling.h"
#include "sound.h"

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

static void laser_hitbox_warning(Laser* laser, Wall* wall[], int wall_count) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 100
	   rectangle should not have any collision with the player and should show up 1 seconds before the laser starts.
	   Might need to use vector for either width and height.*/

	LaserRect rect = calculate_laser_rect(laser, wall, wall_count);

	// need a code that shows this for 1 second before the function laser_hitbox takes over.
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 100));
	if (rect.w > 0 && rect.h > 0) {
		CP_Graphics_DrawRect(rect.x, rect.y, rect.w, rect.h);
	}
}

static void laser_hitbox(Laser* laser, Wall* wall[], int wall_count, Player* player, Orb* orb) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 255
	   if rectangle collides with player, player gets knocked back to the direction player came from and loses one health, player 
	   should not be able to pass through the laser when it is firing, laser last for 3 seconds. Destroys any orb that comes 
	   in contact with it. Might need to use vector for either width and height.*/
	LaserRect rect = calculate_laser_rect(laser, wall, wall_count);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	if (rect.w > 0 && rect.h > 0) {
		CP_Graphics_DrawRect(rect.x, rect.y, rect.w, rect.h);
	}

	AABB playerHitBox = Get_Player_HitBox(player);
	AABB orbHitBox = Get_Orb_HitBox(orb);
	AABB laserHitBox = { rect.x - rect.w / 2.0f,rect.y - rect.h / 2.0f, rect.w,rect.h,NORMAL };
	
	if (checkAABBCollision(playerHitBox, laserHitBox)) {
		Player_Init(player,orb); //reset player position only
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

	switch (laser->state) {
	case LASER_WARNING:
		laser_hitbox_warning(laser, wall, wall_count);

		// Play warning sound only once per warning cycle
		if (!warningPlayed) {
			Sound_PlaySFX(laser_warning); // <<< PLAY WARNING SOUND ONCE <<<
			warningPlayed = 1;
		}

		// After 1 second, switch to firing
		if (laser->timer >= 1.0f) {
			laser->state = LASER_FIRING;
			laser->timer = 0.0f;

			// >>> PLAY LASER ON <<<
			Sound_PlaySFXLoop(laser_on);
		}
		break;

	case LASER_FIRING:
		laser_hitbox(laser, wall, wall_count, player, orbs);

		// Laser lasts 3 seconds
		if (laser->timer >= 2.0f) {
			laser->state = LASER_IDLE;
			laser->timer = 0.0f;
			CP_Sound_StopGroup(CP_SOUND_GROUP_SFX);

			// >>> PLAY LASER OFF <<<
			Sound_PlaySFX(laser_off);
		}
		break;

	case LASER_IDLE:
		// Do nothing
		// After 5 seconds got to LASER_WARNING
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

