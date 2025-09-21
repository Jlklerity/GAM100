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
        printf("Checking circle at (%f, %f), click at (%f, %f), radius = %f\n",
        circle_center_x, circle_center_y, click_x, click_y, radius);
    if (is_clicked) {
        printf("Click registered on circle at (%f, %f)\n", circle_center_x, circle_center_y);
    }
    return is_clicked;
    
}



