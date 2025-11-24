#include "personagem.h"
#include "raylib.h"
#include <stdio.h>

#define G_FORCA 0.8f
#define FORCA_PULO 18.0f

static Texture2D spritePersonagem;

void InitPersonagemAssets() {
    spritePersonagem = LoadTexture("assets/images/personagem.png");
    SetTextureFilter(spritePersonagem, TEXTURE_FILTER_POINT);
}

void UnloadPersonagemAssets() {
    UnloadTexture(spritePersonagem);
}

void InitPersonagem(Personagem *p)
{
    p->posicao = (Vector2){ 200, 360 };
    p->velocidade = 5.0f;
    p->gravidade = 0.0f;
    p->raio = 20.0f; 
    p->color = WHITE;
    
    
    p->direcao = 1.0f; 
}

void UpdatePersonagem(Personagem *p)
{
    
    if (IsKeyDown(KEY_RIGHT)) {
        p->posicao.x += p->velocidade;
        p->direcao = 1.0f; 
    }
    if (IsKeyDown(KEY_LEFT)) {
        p->posicao.x -= p->velocidade;
        p->direcao = -1.0f; 
    }

    if (IsKeyPressed(KEY_SPACE) && p->gravidade >= 0 && p->gravidade <= 1.0f) {
        p->gravidade = -FORCA_PULO;
    }

    p->posicao.y += p->gravidade;
    p->gravidade += G_FORCA;
}

void DrawPersonagem(Personagem p)
{
    if (spritePersonagem.id <= 0) {
        DrawCircleV(p.posicao, p.raio, RED);
        return;
    }
    Rectangle source = { 
        0.0f, 
        0.0f, 
        (float)spritePersonagem.width * p.direcao, 
        (float)spritePersonagem.height 
    };

    float escalaVisual = 5.5f; 

    float destWidth = p.raio * escalaVisual; 
    float destHeight = p.raio * escalaVisual;
   
    Rectangle dest = {
        p.posicao.x - (destWidth / 2.0f), 
        p.posicao.y - (destHeight / 2.0f), 
        destWidth,
        destHeight
    };

    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(spritePersonagem, source, dest, origin, 0.0f, p.color);
}