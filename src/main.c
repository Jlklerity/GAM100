#include "cprocessing.h"
#include "mainmenu.h"
#include "startscreen.h"


int main(void)
{
	CP_Engine_SetNextGameState(start_screen_init, start_screen_update, start_screen_exit);
	CP_Engine_Run(0);
	return 0;
}
