#include "player.h"
#include "stage_wall.h"

static Stage_wall stage_wall[4];
static int stage_wall_count = 0;

void Player_Init(Player *player) {
	Stage_wall_Init(stage_wall, &stage_wall_count);

	const float screen_width = (float)CP_System_GetWindowWidth();
	const float screen_height = (float)CP_System_GetWindowHeight();
	const float player_width = 64.0f;
	const float player_height = 64.0f;
	const float player_highlight = 255.0f;
	const float posX = 100, posY = screen_height - player_height/2 - stage_wall[1].stage_wallheight;
	const int degree = 0; //player facing right

	player->player_speed = 700.0f;
	player->gravity = 9.0f;
	player->direction = PLAYER_RIGHT;
	player->last_direction = PLAYER_RIGHT;
	player->player_posX = posX;
	player->player_posY = posY;
	player->degree = 0;
	player->player_width = player_width;
	player->player_height = player_height;
	player->player_color = CP_Color_Create(255, 0, 0, player_highlight);
}