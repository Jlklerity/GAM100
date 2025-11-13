#include "sound.h"
#include "cprocessing.h"

CP_Sound sfx_orb_shoot;
CP_Sound sfx_destroy;
CP_Sound sfx_teleport;
CP_Sound sfx_door_open;
CP_Sound sfx_door_close;
CP_Sound sfx_exit;
CP_Sound bgm_level;


void Sound_Init(void)
{
    //make sure to replace with real sounds
    sfx_orb_shoot = CP_Sound_Load("./Assets/SFX/test.wav");
    sfx_destroy = CP_Sound_Load("./Assets/SFX/test.wav");
    sfx_teleport = CP_Sound_Load("./Assets/SFX/test.wav");
    sfx_door_open = CP_Sound_Load("./Assets/SFX/test.wav");
    sfx_door_close = CP_Sound_Load("./Assets/SFX/test.wav");
    sfx_exit = CP_Sound_Load("./Assets/SFX/test.wav");
    bgm_level = CP_Sound_Load("./Assets/SFX/test.wav");
}

void Sound_PlayOrbShoot() 
{
    CP_Sound_Play(sfx_orb_shoot);
}

void Sound_PlayDestroy()
{
    CP_Sound_Play(sfx_destroy);
}
void Sound_PlayTeleport() 
{
    CP_Sound_Play(sfx_teleport);
}

void Sound_PlayDoorOpen()
{
    CP_Sound_Play(sfx_door_open);
}

void Sound_PlayDoorClose()
{
    CP_Sound_Play(sfx_door_close);
}

void Sound_PlayExit()
{
    CP_Sound_Play(sfx_exit);
}

void Sound_PlayBGM(void)
{
   // CP_Sound_PlayAdvanced(bgm_level, 0.6f, TRUE); // 60% volume, looping
}

void Sound_StopBGM(void)
{
    CP_Sound_StopAll();
}

void Sound_Exit(void)
{
    CP_Sound_Free(&sfx_orb_shoot);
    CP_Sound_Free(&sfx_destroy);
    CP_Sound_Free(&sfx_teleport);
    CP_Sound_Free(&sfx_door_open);
    CP_Sound_Free(&sfx_door_close);
    CP_Sound_Free(&bgm_level);
}

