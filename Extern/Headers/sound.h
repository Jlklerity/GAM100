#pragma once
#include "cprocessing.h"

// Enum for all sound identifiers
typedef enum {
    orb_shoot,
    destroy,
    teleport,
    door_open,
    door_close,
    exit,
    sfx_count
} SFX;

typedef enum {
    bgm_level,
    music_count
} MUSIC;

// Initialization and cleanup
void Sound_Init(void);
void Sound_Exit(void);

// Playback control
void Sound_PlaySFX(SFX type);
void Sound_PlayMUSIC(MUSIC type);
void Sound_StopMUSIC(MUSIC type);
void Sound_StopAll(void);
void Sound_SetMusicVolume(float volume);
void Sound_SetSFXVolume(float volume);
