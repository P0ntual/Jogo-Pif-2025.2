#include "personagem.h" 

void InitPersonagem(Personagem *p)
{
    p->posicao = (Vector2){ 400, 225 }; 
    p->velocidade = 5.0f;               
    p->raio = 20.0f;                    
    p->color = MAROON;
}
void UpdatePersonagem(Personagem *p)
{
    if (IsKeyDown(KEY_RIGHT)) p->posicao.x += p->velocidade; 
    if (IsKeyDown(KEY_LEFT))  p->posicao.x -= p->velocidade; 
    if (IsKeyDown(KEY_UP))    p->posicao.y -= p->velocidade; 
    if (IsKeyDown(KEY_DOWN))  p->posicao.y += p->velocidade; 
}
void DrawPersonagem(Personagem p)
{
    DrawCircleV(p.posicao, p.raio, p.color); 
}
