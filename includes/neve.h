#ifndef NEVE_H_
#define NEVE_H_

#include "raylib.h"
#define MAX_FLOCOS 50

typedef struct Floco {
    Vector2 posicao;  
    float velocidade; 
    float tamanho;    
} Floco;

void InitNeve();   
void UpdateNeve(); 
void DrawNeve(); 

#endif