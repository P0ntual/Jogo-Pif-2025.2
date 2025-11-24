#include "audio.h"

static Music musicaFundo;

void InitAudio() {
    InitAudioDevice();

    musicaFundo = LoadMusicStream("assets/sounds/musica.ogg");

    SetMusicVolume(musicaFundo, 0.5f);

    PlayMusicStream(musicaFundo);
}

void UpdateAudio() {
  
    UpdateMusicStream(musicaFundo);
}

void UnloadAudio() {
    UnloadMusicStream(musicaFundo);
    CloseAudioDevice(); 
}