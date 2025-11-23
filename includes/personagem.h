#ifndef PERSONAGEM_H_
#define PERSONAGEM_H_

#include "raylib.h"


typedef struct Personagem{
    Vector2 posicao;
    float velocidade;
    float gravidade;
    float raio;
    Color color; 
} Personagem;


void InitPersonagem(Personagem* p);
void UpdatePersonagem(Personagem* p);
void DrawPersonagem(Personagem p);

#endif 
