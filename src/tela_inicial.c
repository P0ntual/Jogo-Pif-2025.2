#include "tela_inicial.h"

void DrawTelaInicial() {
    ClearBackground(DARKBLUE);

    
    const char* textoTitulo = "FLY";
    const char* textoSubtitulo = "Pressione ENTER para iniciar";
    
    int tamanhoTitulo = 150; 
    int tamanhoSub = 30;

    
    int larguraTitulo = MeasureText(textoTitulo, tamanhoTitulo);
    int larguraSub = MeasureText(textoSubtitulo, tamanhoSub);

    
    int posXTitulo = (GetScreenWidth() - larguraTitulo) / 2;
    int posXSub = (GetScreenWidth() - larguraSub) / 2;

    
    int centroY = GetScreenHeight() / 2;

    
    DrawText(textoTitulo, posXTitulo, centroY - 100, tamanhoTitulo, WHITE);
    DrawText(textoSubtitulo, posXSub, centroY + 50, tamanhoSub, YELLOW);
}

int UpdateTelaInicial() {
    if (IsKeyPressed(KEY_ENTER)) {
        return 1;
    }
    return 0;
}