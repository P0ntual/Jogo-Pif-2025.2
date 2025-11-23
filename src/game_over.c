#include "game_over.h"
#include <stdio.h>

static Font fonteGameOver;

void InitGameOver() {
    
    fonteGameOver = LoadFontEx("assets/fonts/polarsnoww.ttf", 100, 0, 0);
    SetTextureFilter(fonteGameOver.texture, TEXTURE_FILTER_BILINEAR);
}

void UnloadGameOver() {
    UnloadFont(fonteGameOver);
}

void DrawGameOver() {
    
    ClearBackground(BLUE);

    float centroX = GetScreenWidth() / 2.0f;
    float centroY = GetScreenHeight() / 2.0f;

   
    const char* textoTitulo = "GAME OVER";
    float tamTitulo = 120.0f;
    Vector2 dimTitulo = MeasureTextEx(fonteGameOver, textoTitulo, tamTitulo, 2.0f);
    
    DrawTextEx(fonteGameOver, textoTitulo, 
              (Vector2){centroX - dimTitulo.x/2, centroY - 150}, 
              tamTitulo, 2.0f, WHITE);

    
    const char* textoSub = "Voce caiu no abismo!";
    float tamSub = 40.0f;
    Vector2 dimSub = MeasureTextEx(fonteGameOver, textoSub, tamSub, 2.0f);

    DrawTextEx(fonteGameOver, textoSub, 
              (Vector2){centroX - dimSub.x/2, centroY}, 
              tamSub, 2.0f, WHITE);

    
    const char* textoR = "[R] Tentar Novamente";
    const char* textoEnter = "[ENTER] Voltar ao Menu";
    float tamInstr = 30.0f;
    
    Vector2 dimR = MeasureTextEx(fonteGameOver, textoR, tamInstr, 2.0f);
    Vector2 dimEnter = MeasureTextEx(fonteGameOver, textoEnter, tamInstr, 2.0f);

    DrawTextEx(fonteGameOver, textoR, 
              (Vector2){centroX - dimR.x/2, centroY + 100}, 
              tamInstr, 2.0f, WHITE);
              
    DrawTextEx(fonteGameOver, textoEnter, 
              (Vector2){centroX - dimEnter.x/2, centroY + 150}, 
              tamInstr, 2.0f, WHITE);
}

int UpdateGameOver() {
    if (IsKeyPressed(KEY_R)) {
        return 1; 
    }
    if (IsKeyPressed(KEY_ENTER)) {
        return 2; 
    }
    return 0; 
}