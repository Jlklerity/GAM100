#include "fullscreen.h"

static int fullscreen_state = 0;

void fullscreen(void)
{
	//fullscreen function
	if (fullscreen_state == 0)
	{
		CP_System_FullscreenAdvanced(1600, 900);
		fullscreen_state = 1;
	}
	//end fullscreen
	else if (fullscreen_state == 1)
	{
		CP_System_SetWindowSize(1600, 900);
		fullscreen_state = 0;
	}
}