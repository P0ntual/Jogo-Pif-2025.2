#include "personagem.h"

#define G_FORCA 0.8f  
#define FORCA_PULO 18.0f

void InitPersonagem(Personagem *p)
{
    p->posicao = (Vector2){ 200, 360 }; 
    p->velocidade = 5.0f;
    p->gravidade = 0.0f; 
    p->raio = 20.0f;
    p->color = MAROON;
}

void UpdatePersonagem(Personagem *p)
{
    int alturaTela = GetScreenHeight();
    
    
    if (IsKeyDown(KEY_RIGHT)) p->posicao.x += p->velocidade;
    if (IsKeyDown(KEY_LEFT))  p->posicao.x -= p->velocidade;

   
    if (IsKeyPressed(KEY_SPACE)&& p->gravidade == 0) {
        p->gravidade = -18.0f; 
    }

   
    p->posicao.y += p->gravidade;
    p->gravidade += 0.8f;        
}

void DrawPersonagem(Personagem p)
{
    DrawCircleV(p.posicao, p.raio, p.color);
}