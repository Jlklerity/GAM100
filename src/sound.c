#include "sound.h"
#include "cprocessing.h"

// Store all sounds in an array
static CP_Sound sfx[sfx_count];
static CP_Sound music[music_count];

// Current volume (as 0–1)
static float sfxVolume = 1.0f;
static float musicVolume = 1.0f;

static const char* sfxFiles[sfx_count] = {
    "./Assets/SFX/test.wav",
    "./Assets/SFX/test.wav",
    "./Assets/SFX/test.wav",
    "./Assets/SFX/test.wav",
    "./Assets/SFX/test.wav",
    "./Assets/SFX/test.wav"
};

static const char* musicFiles[music_count] = {
    "./Assets/SFX/bgm.wav"
};


void Sound_Init(void)
{
    for (int i = 0; i < sfx_count; i++)
        sfx[i] = CP_Sound_Load(sfxFiles[i]);

    for (int i = 0; i < music_count; i++)
        music[i] = CP_Sound_LoadMusic(musicFiles[i]);

    // Apply stored volume
    CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, sfxVolume);
    CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, musicVolume);
}

void Sound_PlaySFX(SFX type)
{
    CP_Sound_PlayAdvanced(sfx[type], 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
}

void Sound_PlayMUSIC(MUSIC type)
{
    CP_Sound_PlayAdvanced(music[type], 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_MUSIC);
}

void Sound_StopMUSIC(MUSIC type)
{
    CP_Sound_StopAll(); 
}

void Sound_StopAll()
{
    CP_Sound_StopAll();
}

void Sound_SetSFXVolume(float volume)
{
    if (volume < 0) volume = 0;
    if (volume > 1) volume = 1;
    sfxVolume = volume;
    CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, volume);
}

void Sound_SetMusicVolume(float v)
{
    if (v < 0) v = 0;
    if (v > 1) v = 1;
    musicVolume = v;
    CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, v);
}

void Sound_Exit()
{
    for (int i = 0; i < sfx_count; i++)
        CP_Sound_Free(&sfx[i]);

    for (int i = 0; i < music_count; i++)
        CP_Sound_Free(&music[i]);
}