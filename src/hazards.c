#include <stdio.h>
#include "player.h"
#include "stage_wall.h"
#include "hazards.h"
#include "collisionHandling.h"


void laser_hitbox_warning(float start_point_x, float start_point_y, float width_of_laser, Wall* wall[], int wall_count, Direction dir) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 100
	   rectangle should not have any collision with the player and should show up 1 seconds before the laser starts.
	   Might need to use vector for either width and height.*/

	Point end_point = Calculate_Ray_Endpoint(start_point_x, start_point_y, &wall, wall_count, dir);

	// this variable is initiallised and used for drawing the "laser" later on.
	float rect_x = start_point_x; // used to get x-coordinates of the rectangle to draw (midpoint)
	float rect_y = start_point_y; // used to get y-coordinates of the rectangle to draw (midpoint)
	float rect_w = 0; // the width the of rectangle
	float rect_h = 0; // the height of the rectangle

	switch (dir) {
		case RIGHT: {
			float length = end_point.x - start_point_x;
			rect_w = length;
			rect_h = width_of_laser;
			rect_x = start_point_x + rect_w / 2.0f; // the midpoint of the rectangle
			rect_y = start_point_y;
			break;
		}
		case LEFT: {
			float length = start_point_x - end_point.x;
			rect_w = length;
			rect_h = width_of_laser;
			rect_x = start_point_x - rect_w / 2.0f;
			rect_y = start_point_y;
			break;
		}
		case DOWN: {
			float length = end_point.y - start_point_y;
			rect_w = width_of_laser;
			rect_h = length;
			rect_x = start_point_x;
			rect_y = start_point_y + rect_h / 2.0f;
			break;
		}
		case UP: {
			float length = start_point_y - end_point.y;
			rect_w = width_of_laser;
			rect_h = length;
			rect_x = start_point_x;
			rect_y = start_point_y - rect_h / 2.0f;
			break;
		}
	}
	// need a code that shows this for 1 second before the function laser_hitbox takes over.
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 100));
	if (rect_w > 0 && rect_h > 0) {
		CP_Graphics_DrawRect(rect_x, rect_y, rect_w, rect_h);
	}
}

void laser_hitbox(float start_point_x, float start_point_y, float width_of_laser, Wall* wall, int wall_count, Player* player, Orb* orb, Direction dir) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 255
	   if rectangle collides with player, player gets knocked back to the direction player came from and loses one health, player 
	   should not be able to pass through the laser when it is firing, laser last for 3 seconds. Destroys any orb that comes 
	   in contact with it. Might need to use vector for either width and height.*/
	Point end_point = Calculate_Ray_Endpoint(start_point_x, start_point_y, &wall, wall_count, dir);

	// this variable is initiallised and used for drawing the "laser" later on.
	float rect_x = start_point_x; // used to get x-coordinates of the rectangle to draw (midpoint)
	float rect_y = start_point_y; // used to get y-coordinates of the rectangle to draw (midpoint)
	float rect_w = 0; // the width the of rectangle
	float rect_h = 0; // the height of the rectangle

	switch (dir) {
		case RIGHT: {
			float length = end_point.x - start_point_x;
			rect_w = length;
			rect_h = width_of_laser;
			rect_x = start_point_x + rect_w / 2.0f; // the midpoint of the rectangle
			rect_y = start_point_y;
			break;
		}
		case LEFT: {
			float length = start_point_x - end_point.x;
			rect_w = length;
			rect_h = width_of_laser;
			rect_x = start_point_x - rect_w / 2.0f;
			rect_y = start_point_y;
			break;
		}
		case DOWN: {
			float length = end_point.y - start_point_y;
			rect_w = width_of_laser;
			rect_h = length;
			rect_x = start_point_x;
			rect_y = start_point_y + rect_h / 2.0f;
			break;
		}
		case UP: {
			float length = start_point_y - end_point.y;
			rect_w = width_of_laser;
			rect_h = length;
			rect_x = start_point_x;
			rect_y = start_point_y - rect_h / 2.0f;
			break;
		}
	}
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	if (rect_w > 0 && rect_h > 0) {
		CP_Graphics_DrawRect(rect_x, rect_y, rect_w, rect_h);
	}

	AABB playerHitBox = Get_Player_HitBox(&player);
	AABB orbHitBox = Get_Orb_HitBox(&orb);
	AABB laserHitBox = { rect_x,rect_y, rect_w,rect_h,STAGEWALL };
	
	if (checkAABBCollision(playerHitBox, laserHitBox)) {
		//player takes damage
		//player gets reset to starting position
	}

	if (checkAABBCollision(orbHitBox, laserHitBox)) {
		orb->isActive = 0;
	}
}


void pitfall(float pitfall_x, float pitfall_y, float width_of_pitfall, float depth_of_pitfall, Wall* wall, Player* player) {
	/* checks where the player first comes above the pitfall and marks the direction of the player. If player falls into depth
	   player should be teleported to left or right of pitfall depending whereplayer comes from, player will lose 1 health. */
}
