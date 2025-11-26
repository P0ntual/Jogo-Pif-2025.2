#include "game_over.h"
#include "ranking.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static Font fonteInterface;

static Font fonteGameOver;
static Texture2D imagemFundoGameOver;

static void ProcessarInputNome(char* nomeJogador, int maxLen) {
    int key = GetCharPressed();
    
    while (key > 0) {
        // Verifica se o caractere é válido e se há espaço
        if ((key >= 32) && (key <= 125) && (strlen(nomeJogador) < maxLen - 1)) {
            int len = strlen(nomeJogador);
            // Converte para maiúscula antes de adicionar
            nomeJogador[len] = (char)toupper(key);
            nomeJogador[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    
    // Backspace
    if (IsKeyPressed(KEY_BACKSPACE)) {
        int len = strlen(nomeJogador);
        if (len > 0) {
            nomeJogador[len - 1] = '\0';
        }
    }
}

void InitGameOver() {
    
    fonteGameOver = LoadFontEx("assets/fonts/polarsnoww.ttf", 100, 0, 0);
    SetTextureFilter(fonteGameOver.texture, TEXTURE_FILTER_BILINEAR);
    
    fonteInterface = LoadFontEx("assets/fonts/fonteinterface.ttf", 40, 0, 0);
    SetTextureFilter(fonteInterface.texture, TEXTURE_FILTER_BILINEAR);
    
    imagemFundoGameOver = LoadTexture("assets/images/6.png");
    SetTextureFilter(imagemFundoGameOver, TEXTURE_FILTER_BILINEAR);
}

void UnloadGameOver() {
    UnloadFont(fonteGameOver);
    UnloadFont(fonteInterface);
    UnloadTexture(imagemFundoGameOver);
}

void DrawNomeInput(char* nomeJogador, float pontuacao) {
    // Overlay escuro
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 200});
    
    float centroX = GetScreenWidth() / 2.0f;
    float centroY = GetScreenHeight() / 2.0f;
    
    // Caixa do input
    float boxWidth = 500.0f;
    float boxHeight = 300.0f;
    Rectangle box = {centroX - boxWidth/2, centroY - boxHeight/2, boxWidth, boxHeight};
    
    DrawRectangleRec(box, (Color){30, 30, 30, 255});
    DrawRectangleLinesEx(box, 4.0f, WHITE);
    
    // Título
    const char* titulo = "Digite seu nome:";
    float tamTitulo = 40.0f;
    Vector2 dimTitulo = MeasureTextEx(fonteGameOver, titulo, tamTitulo, 1.0f);
    DrawTextEx(fonteGameOver, titulo, 
              (Vector2){centroX - dimTitulo.x/2, centroY - boxHeight/2 + 40}, 
              tamTitulo, 1.0f, WHITE);
    
    // Pontuação
    char textoPontuacao[100];
    snprintf(textoPontuacao, sizeof(textoPontuacao), "Pontuacao: %.0f m", pontuacao);
    float tamPontuacao = 30.0f;
    Vector2 dimPontuacao = MeasureTextEx(fonteGameOver, textoPontuacao, tamPontuacao, 1.0f);
    DrawTextEx(fonteGameOver, textoPontuacao, 
              (Vector2){centroX - dimPontuacao.x/2, centroY - boxHeight/2 + 90}, 
              tamPontuacao, 1.0f, YELLOW);
    
    // Input box
    float inputWidth = 400.0f;
    float inputHeight = 50.0f;
    Rectangle inputBox = {centroX - inputWidth/2, centroY - 20, inputWidth, inputHeight};
    
    DrawRectangleRec(inputBox, BLACK);
    DrawRectangleLinesEx(inputBox, 2.0f, WHITE);
    
    // Texto do input
    float tamInput = 35.0f;
    char displayNome[21];
    snprintf(displayNome, sizeof(displayNome), "%s_", nomeJogador);
    Vector2 dimInput = MeasureTextEx(fonteGameOver, displayNome, tamInput, 1.0f);
    DrawTextEx(fonteGameOver, displayNome, 
              (Vector2){centroX - dimInput.x/2, centroY - 10}, 
              tamInput, 1.0f, WHITE);
    
    // Instruções
    const char* instrucao = "[ENTER] para confirmar";
    float tamInstrucao = 25.0f;
    Vector2 dimInstrucao = MeasureTextEx(fonteGameOver, instrucao, tamInstrucao, 1.0f);
    DrawTextEx(fonteGameOver, instrucao, 
              (Vector2){centroX - dimInstrucao.x/2, centroY + 60}, 
              tamInstrucao, 1.0f, GRAY);
}

void DrawGameOver(float pontuacao, Ranking* ranking) {
    
    // Desenha a imagem de fundo
    if (imagemFundoGameOver.id > 0) {
        Rectangle source = { 0.0f, 0.0f, (float)imagemFundoGameOver.width, (float)imagemFundoGameOver.height };
        Rectangle dest = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(imagemFundoGameOver, source, dest, origin, 0.0f, WHITE);
    } else {
        ClearBackground(BLUE);
    }

    float centroX = GetScreenWidth() / 2.0f;
    float centroY = GetScreenHeight() / 2.0f;

   
    const char* textoTitulo = "GAME OVER";
    float tamTitulo = 120.0f;
    Vector2 dimTitulo = MeasureTextEx(fonteGameOver, textoTitulo, tamTitulo, 2.0f);
    
    DrawTextEx(fonteGameOver, textoTitulo, 
              (Vector2){centroX - dimTitulo.x/2, 50}, 
              tamTitulo, 2.0f, WHITE);

    // Mostra pontuação
    char textoPontuacao[100];
    snprintf(textoPontuacao, sizeof(textoPontuacao), "Pontuacao: %.0f m", pontuacao);
    float tamPontuacao = 40.0f;
    Vector2 dimPontuacao = MeasureTextEx(fonteGameOver, textoPontuacao, tamPontuacao, 2.0f);
    
    DrawTextEx(fonteGameOver, textoPontuacao, 
              (Vector2){centroX - dimPontuacao.x/2, 180}, 
              tamPontuacao, 2.0f, YELLOW);

    // Renderiza o ranking à esquerda
    DesenharRanking(ranking, fonteInterface, 50.0f, 250.0f, 30.0f);

    // Botões na parte inferior (mais altos na tela)
    float btnLargura = 400.0f;
    float btnAltura = 60.0f;
    float btnEspacamento = 20.0f;
    float btnY = GetScreenHeight() - 200.0f; // Ajustado para ficar mais alto na tela
    
    Vector2 mousePoint = GetMousePosition();
    
    // Botão "Tentar Novamente"
    Rectangle btnTentar = { centroX - btnLargura/2, btnY, btnLargura, btnAltura };
    bool btnTentarHover = CheckCollisionPointRec(mousePoint, btnTentar);
    Color corBtnTentar = btnTentarHover ? (Color){100, 100, 255, 255} : (Color){50, 50, 200, 255};
    
    DrawRectangleRounded(btnTentar, 0.3f, 10, corBtnTentar);
    DrawRectangleRoundedLines(btnTentar, 0.3f, 10, WHITE);
    
    const char* textoR = "Tentar Novamente";
    float tamInstr = 35.0f;
    Vector2 dimR = MeasureTextEx(fonteGameOver, textoR, tamInstr, 1.0f);
    DrawTextEx(fonteGameOver, textoR, 
              (Vector2){centroX - dimR.x/2, btnY + (btnAltura - dimR.y)/2}, 
              tamInstr, 1.0f, WHITE);
    
    // Botão "Voltar ao Menu"
    Rectangle btnMenu = { centroX - btnLargura/2, btnY + btnAltura + btnEspacamento, btnLargura, btnAltura };
    bool btnMenuHover = CheckCollisionPointRec(mousePoint, btnMenu);
    Color corBtnMenu = btnMenuHover ? (Color){100, 100, 255, 255} : (Color){50, 50, 200, 255};
    
    DrawRectangleRounded(btnMenu, 0.3f, 10, corBtnMenu);
    DrawRectangleRoundedLines(btnMenu, 0.3f, 10, WHITE);
    
    const char* textoEnter = "Voltar ao Menu";
    Vector2 dimEnter = MeasureTextEx(fonteGameOver, textoEnter, tamInstr, 1.0f);
    DrawTextEx(fonteGameOver, textoEnter, 
              (Vector2){centroX - dimEnter.x/2, btnY + btnAltura + btnEspacamento + (btnAltura - dimEnter.y)/2}, 
              tamInstr, 1.0f, WHITE);
}

int UpdateGameOver(char* nomeJogador, int* nomeFoiSalvo) {
    if (!*nomeFoiSalvo) {
        // Processa entrada de texto
        ProcessarInputNome(nomeJogador, MAX_NAME_LENGTH);
        
        // Enter confirma o nome
        if (IsKeyPressed(KEY_ENTER) && strlen(nomeJogador) > 0) {
            *nomeFoiSalvo = 1;
            return 0; // Ainda não sai, só salva
        }
    } else {
        // Nome já foi salvo, permite navegação normal
        float centroX = GetScreenWidth() / 2.0f;
        float btnLargura = 400.0f;
        float btnAltura = 60.0f;
        float btnEspacamento = 20.0f;
        float btnY = GetScreenHeight() - 150.0f;
        
        Vector2 mousePoint = GetMousePosition();
        
        // Botão "Tentar Novamente"
        Rectangle btnTentar = { centroX - btnLargura/2, btnY, btnLargura, btnAltura };
        
        // Botão "Voltar ao Menu"
        Rectangle btnMenu = { centroX - btnLargura/2, btnY + btnAltura + btnEspacamento, btnLargura, btnAltura };
        
        // Verifica cliques nos botões ou teclas
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePoint, btnTentar)) {
                return 1;
            }
            if (CheckCollisionPointRec(mousePoint, btnMenu)) {
                return 2;
            }
        }
        
        // Mantém suporte para teclas
        if (IsKeyPressed(KEY_R)) {
            return 1; 
        }
        if (IsKeyPressed(KEY_ENTER)) {
            return 2; 
        }
    }
    return 0; 
}