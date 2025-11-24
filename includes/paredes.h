#ifndef PAREDES_H
#define PAREDES_H

#include "raylib.h"
struct Personagem; 

typedef struct ParedeNode {
    Rectangle retangulo;
    struct ParedeNode* proximo;
} ParedeNode;

void InitParedesAssets();
void UnloadParedesAssets();

ParedeNode* InicializarParedes(int screenWidth, int screenHeight);
void DrawParedes(ParedeNode* head);
void VerificarColisaoParedes(ParedeNode* head, struct Personagem* p);
void LiberarParedes(ParedeNode* head);


ParedeNode* ResetarParedes(ParedeNode* listaAntiga, int screenWidth, int screenHeight);

#endif