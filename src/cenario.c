#include "cenario.h"

static Texture2D texturaFundo;

void InitCenario() {
    texturaFundo = LoadTexture("assets/images/5.png");
}

void UnloadCenario() {
    UnloadTexture(texturaFundo);
}

void DrawCenario() {
    
    Rectangle fonte = { 0, 0, texturaFundo.width, texturaFundo.height };
    
    Rectangle destino = { 0, 0, GetScreenWidth(), GetScreenHeight() };
    
    Vector2 origem = { 0, 0 };
    
    DrawTexturePro(texturaFundo, fonte, destino, origem, 0.0f, WHITE);
}