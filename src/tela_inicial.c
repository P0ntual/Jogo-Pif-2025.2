#include "tela_inicial.h"

static Font fonteDoJogo;

static float btnLargura = 400.0f;
static float btnAltura = 100.0f;

void InitTelaInicial() {
    fonteDoJogo = LoadFontEx("assets/fonts/polarsnoww.ttf", 100, 0, 0);
    SetTextureFilter(fonteDoJogo.texture, TEXTURE_FILTER_BILINEAR);
}

void UnloadTelaInicial() {
    UnloadFont(fonteDoJogo);
}

void DrawTelaInicial() {
    ClearBackground(DARKBLUE);

    float centroX = GetScreenWidth() / 2.0f;
    float centroY = GetScreenHeight() / 2.0f;

    Rectangle btnBounds = { 
        centroX - (btnLargura / 2), 
        centroY + 50, 
        btnLargura, 
        btnAltura 
    };

    Vector2 mousePoint = GetMousePosition();

    Color corBotao = BLUE;
    
    if (CheckCollisionPointRec(mousePoint, btnBounds)) {
        corBotao = SKYBLUE; 
    }

    DrawRectangleRounded(btnBounds, 0.2f, 10, corBotao); 
    
    
    DrawRectangleRoundedLines(btnBounds, 0.2f, 10, WHITE); 

    const char* textoTitulo = "FLY";
    float tamTitulo = 150.0f;
    Vector2 dimTitulo = MeasureTextEx(fonteDoJogo, textoTitulo, tamTitulo, 2.0f);
    DrawTextEx(fonteDoJogo, textoTitulo, (Vector2){centroX - dimTitulo.x/2, centroY - 150}, tamTitulo, 2.0f, WHITE);

    const char* textoBotao = "PLAY";
    float tamBotao = 50.0f;
    Vector2 dimBotao = MeasureTextEx(fonteDoJogo, textoBotao, tamBotao, 2.0f);
    
    float textoX = btnBounds.x + (btnBounds.width - dimBotao.x) / 2;
    float textoY = btnBounds.y + (btnBounds.height - dimBotao.y) / 2;
    
    DrawTextEx(fonteDoJogo, textoBotao, (Vector2){textoX, textoY}, tamBotao, 2.0f, WHITE);
}

int UpdateTelaInicial() {
    float centroX = GetScreenWidth() / 2.0f;
    float centroY = GetScreenHeight() / 2.0f;
    
    Rectangle btnBounds = { 
        centroX - (btnLargura / 2), 
        centroY + 50, 
        btnLargura, 
        btnAltura 
    };

    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, btnBounds)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return 1; 
        }
    }

    return 0;
}