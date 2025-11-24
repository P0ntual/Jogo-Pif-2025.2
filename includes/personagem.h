#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "raylib.h"

typedef struct Personagem {
    Vector2 posicao;
    float velocidade;
    float gravidade;
    float raio;
    Color color;
    float direcao; 
} Personagem;
void InitPersonagemAssets();
void UnloadPersonagemAssets();

void InitPersonagem(Personagem *p);
void UpdatePersonagem(Personagem *p);
void DrawPersonagem(Personagem p);

#endif