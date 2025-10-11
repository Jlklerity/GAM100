#include "stage_wall.h"
#include <string.h>

void Stage_wall_Init(Stage_wall stage_wall[4], int* stage_wall_count) {
	
	*stage_wall_count = 0;

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float stage_wall_thickness = 20.0f;
	const float stage_wall_highlight = 255.0f;

	float top_wall_coords[8] = { 0.0f, 0.0f, screen_width, 0.0f, screen_width, stage_wall_thickness, 0.0f, stage_wall_thickness };
	memcpy(stage_wall[*stage_wall_count].stage_wall_coords, top_wall_coords, sizeof(top_wall_coords));
	stage_wall[*stage_wall_count].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	(*stage_wall_count)++;

	float bottom_wall_coords[8] = { 0.0f, screen_height - stage_wall_thickness, screen_width, screen_height - stage_wall_thickness,
									screen_width, screen_height, 0.0f, screen_height };
	memcpy(stage_wall[*stage_wall_count].stage_wall_coords, bottom_wall_coords, sizeof(bottom_wall_coords));
	stage_wall[*stage_wall_count].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	(*stage_wall_count)++;

	float left_wall_coords[8] = { 0.0f, 0.0f, stage_wall_thickness, 0.0f, stage_wall_thickness, screen_height, 0.0f, screen_height };
	memcpy(stage_wall[*stage_wall_count].stage_wall_coords, left_wall_coords, sizeof(left_wall_coords));
	stage_wall[*stage_wall_count].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	(*stage_wall_count)++;

	float right_wall_coords[8] = { screen_width - stage_wall_thickness, 0.0f, screen_width, 0.0f, screen_width, screen_height,
									screen_width - stage_wall_thickness, screen_height };
	memcpy(stage_wall[*stage_wall_count].stage_wall_coords, right_wall_coords, sizeof(right_wall_coords));
	stage_wall[*stage_wall_count].stage_wall_color = CP_Color_Create(255, 255, 255, stage_wall_highlight);
	(*stage_wall_count)++;
}
