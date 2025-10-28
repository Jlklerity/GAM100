#include <stdio.h>
#include "player.h"
#include "stage_wall.h"
#include "hazards.h"
#include "collisionHandling.h"


void laser_hitbox_warning(float start_point_x, float start_point_y, float width_of_laser, float height_of_laser) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 100
	   rectangle should not have any collision with the player and should show up 1 seconds before the laser starts.
	   Might need to use vector for either width and height.*/
}

void laser_hitbox(float start_point_x, float start_point_y, float width_of_laser, float height_of_laser, Player* player) {
	/* draw a rectangle that starts from the laser and ends at any wall encountered, the alpha value of this is 255
	   if rectangle collides with player, player gets knocked back to the direction player came from and loses one health, player 
	   should not be able to pass through the laser when it is firing, laser last for 3 seconds. Destroys any orb that comes 
	   in contact with it. Might need to use vector for either width and height.*/
}


void pitfall(float pitfall_x, float pitfall_y, float width_of_pitfall, float depth_of_pitfall, Player* player) {
	/* checks where the player first comes above the pitfall and marks the direction of the player. If player falls into depth
	   player should be teleported to left or right of pitfall depending whereplayer comes from, player will lose 1 health. */
}
