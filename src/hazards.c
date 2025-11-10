#include <stdio.h>
#include "player.h"
#include "stage_wall.h"
#include "hazards.h"
#include "collisionHandling.h"

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

void laser_hitbox_warning(Laser* laser, Wall* wall[], int wall_count) {
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

void laser_hitbox(Laser* laser, Wall* wall[], int wall_count, Player* player, Orb* orb) {
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
	AABB laserHitBox = { rect.x,rect.y, rect.w,rect.h,LASER };
	
	if (checkAABBCollision(playerHitBox, laserHitBox)) {
		Player_Init(player,orb); //reset player position only
		// might do things like kockback instead with a health system as reseting 
		// player pos to stsart might be too harsh?
	}

	if (checkAABBCollision(orbHitBox, laserHitBox)) {
		orb->isActive = 0;
	}
}


void pitfall(float pitfall_x, float pitfall_y, float width_of_pitfall, float depth_of_pitfall, Wall* wall, Player* player) {
	/* checks where the player first comes above the pitfall and marks the direction of the player. If player falls into depth
	   player should be teleported to left or right of pitfall depending whereplayer comes from, player will lose 1 health. */
}
