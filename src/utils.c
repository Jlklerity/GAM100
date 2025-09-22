#include <math.h>
#include "cprocessing.h"
#include "game.h"

 

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
    float left_side = area_center_x - area_width / 2.0f;
    float right_side = area_center_x + area_width / 2.0f;
    float top_side = area_center_y - area_height / 2.0f;
    float bottom_side = area_center_y + area_height / 2.0f;
    
    if (click_x >= left_side && click_x <= right_side && click_y >= top_side && click_y <= bottom_side) {
        return 1; 
    }   
    return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
    float radius = diameter / 2.0f;
    
    float distance_x = click_x - circle_center_x;
    float distance_y = click_y - circle_center_y;
     

    int is_clicked = (distance_x * distance_x + distance_y * distance_y) <= (radius * radius);
        
    return is_clicked;
}

int IsCircleColliding(float circle1_center_x, float circle1_center_y, float circle2_center_x, float circle2_center_y, float diameter) {
    
    float collided = diameter*2 + 10;
    float distance_x = abs(circle1_center_x - circle2_center_x);
    float distance_y = abs(circle1_center_y - circle2_center_y);
    if (distance_x <= collided && distance_y <= collided) {
        
        return 1;
    }
    else {
        return 0;
    }
    
}




