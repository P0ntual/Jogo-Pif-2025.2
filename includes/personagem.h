#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "raylib.h"
#include <stdbool.h> 


#define NUM_SPRITES_CORRIDA 7
#define VELOCIDADE_ANIMACAO 0.08f 

typedef struct Personagem {
    
    Vector2 posicao;
    float velocidade;
    float gravidade;
    float raio;
    Color color;
    float direcao; 
    Texture2D spritesCorrida[NUM_SPRITES_CORRIDA];
    int frameAtual;        
    float timerAnimacao;   
    bool estaCorrendo;     
    
} Personagem;


void InitPersonagemAssets();
void UnloadPersonagemAssets();


void LoadPersonagemRunningAssets(Personagem *p);
void UnloadPersonagemRunningAssets(Personagem *p);

void InitPersonagem(Personagem *p);
void UpdatePersonagem(Personagem *p);
void DrawPersonagem(Personagem p);

#endif