#include "personagem.h"
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>


#define G_FORCA 0.8f
#define FORCA_PULO 18.0f


static Texture2D spritePersonagem;
static Texture2D spritePulo;

void InitPersonagemAssets() {
    spritePersonagem = LoadTexture("assets/images/personagem.png");
    SetTextureFilter(spritePersonagem, TEXTURE_FILTER_POINT);
    
    spritePulo = LoadTexture("assets/images/Jump.png");
    SetTextureFilter(spritePulo, TEXTURE_FILTER_POINT);
}

void UnloadPersonagemAssets() {
    UnloadTexture(spritePersonagem);
    UnloadTexture(spritePulo);
}

void LoadPersonagemRunningAssets(Personagem *p) {
    char nomeArquivo[64];
    for (int i = 0; i < NUM_SPRITES_CORRIDA; i++) {
        // Formata o nome do arquivo, ex: "assets/images/p1r.png"
        sprintf(nomeArquivo, "assets/images/p%dr.png", i + 1);

        p->spritesCorrida[i] = LoadTexture(nomeArquivo);
        SetTextureFilter(p->spritesCorrida[i], TEXTURE_FILTER_POINT);
    }
}

void UnloadPersonagemRunningAssets(Personagem *p) {
    for (int i = 0; i < NUM_SPRITES_CORRIDA; i++) {
        UnloadTexture(p->spritesCorrida[i]);
    }
}

void InitPersonagem(Personagem *p)
{
    p->posicao = (Vector2){ 200, 360 };
    p->velocidade = 6.5f;
    p->gravidade = 0.0f;
    p->raio = 15.0f; 
    p->color = WHITE;
    
    p->direcao = 1.0f; 
    
    LoadPersonagemRunningAssets(p); 
    p->frameAtual = 0;
    p->timerAnimacao = 0.0f;
    p->estaCorrendo = false;
}

void UpdatePersonagem(Personagem *p)
{
    bool moveuHorizontalmente = false; 

    if (IsKeyDown(KEY_RIGHT)) {
        p->posicao.x += p->velocidade;
        p->direcao = 1.0f;
        moveuHorizontalmente = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        p->posicao.x -= p->velocidade;
        p->direcao = -1.0f;
        moveuHorizontalmente = true;
    }
    
    if (moveuHorizontalmente) {
        p->estaCorrendo = true;
        p->timerAnimacao += GetFrameTime(); 
        
        if (p->timerAnimacao >= VELOCIDADE_ANIMACAO) {
            p->frameAtual++;
            if (p->frameAtual >= NUM_SPRITES_CORRIDA) {
                p->frameAtual = 0;
            }
            p->timerAnimacao = 0.0f; 
        }
    } else {
        p->estaCorrendo = false;
        p->frameAtual = 0;
    }
    
    if (IsKeyPressed(KEY_SPACE) && p->gravidade >= 0 && p->gravidade <= G_FORCA * 2.0f) {
        p->gravidade = -FORCA_PULO;
    }

    p->posicao.y += p->gravidade;
    p->gravidade += G_FORCA;
}

void DrawPersonagem(Personagem p)
{
    Texture2D spriteParaDesenhar;
    
    // Verifica se está pulando (gravidade negativa significa subindo)
    bool estaPulando = p.gravidade < -1.0f;
    
    if (estaPulando) {
        // Usa o sprite de pulo quando está pulando
        spriteParaDesenhar = spritePulo;
    } else if (p.estaCorrendo) {
        // Usa os sprites de corrida quando está correndo
        spriteParaDesenhar = p.spritesCorrida[p.frameAtual];
    } else {
        // Sprite parado
        spriteParaDesenhar = spritePersonagem;
    }
    
    if (spriteParaDesenhar.id <= 0) {
        DrawCircleV(p.posicao, p.raio, RED);
        return;
    }
    
   
    Rectangle source = { 
        0.0f, 
        0.0f, 
        (float)spriteParaDesenhar.width, 
        (float)spriteParaDesenhar.height 
    };

    // Define uma altura de destino fixa para manter consistência visual
    // Baseado no sprite parado que tem 44 pixels de altura
    float escalaVisual = 5.5f; 
    float alturaDestinoFixa = p.raio * escalaVisual;
    
    // Calcula a escala baseada na altura do sprite atual
    // Isso mantém todos os sprites com a mesma altura visual
    float escala = alturaDestinoFixa / (float)spriteParaDesenhar.height;
    
    // Calcula as dimensões de destino mantendo a proporção do sprite
    float destWidth = (float)spriteParaDesenhar.width * escala;
    float destHeight = alturaDestinoFixa;
    
    // Ajusta o source para flip horizontal quando direcao < 0
    if (p.direcao < 0.0f) {
        source.width = -source.width;
    }
    
   
    Rectangle dest = {
        p.posicao.x - (destWidth / 2.0f), 
        p.posicao.y - (destHeight / 2.0f), 
        destWidth,
        destHeight
    };

    Vector2 origin = { 0.0f, 0.0f };

  
    DrawTexturePro(spriteParaDesenhar, source, dest, origin, 0.0f, p.color);
}