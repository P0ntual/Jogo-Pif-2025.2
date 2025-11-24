#include "neve.h"
#include <math.h> 

static Floco flocos[MAX_FLOCOS];
static int screenWidthb = 1280;
static int screenHeightb = 720;

void InitNeve() {
    for (int i = 0; i < MAX_FLOCOS; i++) {
       
        flocos[i].posicao.x = GetRandomValue(0, screenWidthb);
        flocos[i].posicao.y = GetRandomValue(0, screenHeightb);
        
      
        flocos[i].velocidade = GetRandomValue(15, 35) / 10.0f;
        
   
        flocos[i].tamanho = GetRandomValue(10, 30) / 10.0f;
    }
}

void UpdateNeve() {
   
    float vento = sin(GetTime() * 2.0f) * 0.5f;

    for (int i = 0; i < MAX_FLOCOS; i++) {

        flocos[i].posicao.y += flocos[i].velocidade * (flocos[i].tamanho * 0.5f);
        
     
        flocos[i].posicao.x += vento;

 
        if (flocos[i].posicao.y > screenHeightb + 10) {

            flocos[i].posicao.y = GetRandomValue(-50, -10);
            

            flocos[i].posicao.x = GetRandomValue(0, screenWidthb);
        }

        if (flocos[i].posicao.x > screenWidthb) flocos[i].posicao.x = 0;
        if (flocos[i].posicao.x < 0) flocos[i].posicao.x = screenWidthb;
    }
}

void DrawNeve() {
    for (int i = 0; i < MAX_FLOCOS; i++) {
        Color corNeve = (Color){ 255, 255, 255, 200 };
        DrawCircleV(flocos[i].posicao, flocos[i].tamanho, corNeve);
    }
}