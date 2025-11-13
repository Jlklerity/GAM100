#pragma once
#include "player.h"
#include "cprocessing.h"

extern CP_Sound sfx_orb_shoot;
extern CP_Sound sfx_destroy;
extern CP_Sound sfx_teleport;
extern CP_Sound sfx_door_open;
extern CP_Sound sfx_door_close;
extern CP_Sound sfx_exit;
extern CP_Sound bgm_level;

// Initializes all game sounds
void Sound_Init();

// Plays one-shot sound effects
void Sound_PlayOrbShoot();
void Sound_PlayDestroy();
void Sound_PlayTeleport();
void Sound_PlayDoorOpen();
void Sound_PlayDoorClose();
void Sound_PlayExit();

// Background music control
void Sound_PlayBGM();
void Sound_StopBGM();

// Frees loaded sound assets
void Sound_Exit();
