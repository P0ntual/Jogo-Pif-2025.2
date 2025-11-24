#include "audio.h"
#include "raylib.h"

static Music musicaFundo;

void InitAudio() {
    
    SetAudioStreamBufferSizeDefault(16384);

    InitAudioDevice();

    musicaFundo = LoadMusicStream("assets/sounds/musica.ogg");
    
  
    SetMusicVolume(musicaFundo, 0.5f);
    PlayMusicStream(musicaFundo);
}

void UpdateAudio() {
    
    UpdateMusicStream(musicaFundo);
}

void UnloadAudio() {

    StopMusicStream(musicaFundo);
    UnloadMusicStream(musicaFundo);
    CloseAudioDevice(); 
}