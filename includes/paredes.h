#ifndef PAREDES_H_
#define PAREDES_H_

#include "raylib.h"
#include "personagem.h"

typedef struct ParedeNode {
    Rectangle retangulo;      
    struct ParedeNode* proximo; 
} ParedeNode;

ParedeNode* InicializarParedes(int screenWidth, int screenHeight);
void AdicionarParede(ParedeNode** head, Rectangle rect);
void VerificarColisaoParedes(ParedeNode* head, Personagem* p);


void DrawParedes(ParedeNode* head); 

void LiberarParedes(ParedeNode* head); 

#endif