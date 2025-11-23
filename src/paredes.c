#include "paredes.h"
#include <stdlib.h> 
#include <stdio.h>
#include <math.h> 

void AdicionarParede(ParedeNode** head, Rectangle rect) {
    ParedeNode* novoNo = (ParedeNode*)malloc(sizeof(ParedeNode));
    novoNo->retangulo = rect;
    novoNo->proximo = *head;
    *head = novoNo;
}

ParedeNode* InicializarParedes(int screenWidth, int screenHeight) {
    ParedeNode* lista = NULL; 
    
    
    int espessura = 100;
    
   
    int alturaNivel = 10000; 

    
    AdicionarParede(&lista, (Rectangle){ -espessura, -alturaNivel, espessura, alturaNivel + screenHeight });
    
    AdicionarParede(&lista, (Rectangle){ screenWidth, -alturaNivel, espessura, alturaNivel + screenHeight });

    
    AdicionarParede(&lista, (Rectangle){ 0, 650, screenWidth, 40 });

    
    int numPlataformas = 100; 
    float yAtual = 500;       
    
    for (int i = 0; i < numPlataformas; i++) {
        
        
        float largura = GetRandomValue(150, 400);
        
        
        float x = GetRandomValue(50, screenWidth - largura - 50);
        
        
        float altura = 30;

        
        AdicionarParede(&lista, (Rectangle){ x, yAtual, largura, altura });

       
        yAtual -= GetRandomValue(130, 180);
    }

    return lista;
}


void VerificarColisaoParedes(ParedeNode* head, Personagem* p) {
    ParedeNode* atual = head;
    while (atual != NULL) {
        Rectangle r = atual->retangulo;
        Rectangle playerRect = { p->posicao.x - p->raio, p->posicao.y - p->raio, p->raio * 2, p->raio * 2 };

        if (CheckCollisionRecs(playerRect, r)) {
            Rectangle interseccao = GetCollisionRec(playerRect, r);
            if (interseccao.width > interseccao.height) {
                if (p->posicao.y < r.y + (r.height/2)) {
                    p->posicao.y = r.y - p->raio;
                    if (p->gravidade > 0) p->gravidade = 0;
                } else {
                    p->posicao.y = r.y + r.height + p->raio;
                    if (p->gravidade < 0) p->gravidade = 0;
                }
            } else {
                if (p->posicao.x < r.x) p->posicao.x = r.x - p->raio;
                else p->posicao.x = r.x + r.width + p->raio;
            }
        }
        atual = atual->proximo; 
    }
}

void DrawParedes(ParedeNode* head) {
    ParedeNode* atual = head;
    while (atual != NULL) {
        DrawRectangleRec(atual->retangulo, DARKGRAY);
        DrawRectangleLinesEx(atual->retangulo, 2, LIGHTGRAY);
        atual = atual->proximo;
    }
}

void LiberarParedes(ParedeNode* head) {
    ParedeNode* atual = head;
    while (atual != NULL) {
        ParedeNode* temp = atual;
        atual = atual->proximo;
        free(temp); 
    }
}