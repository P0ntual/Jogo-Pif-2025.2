#include "raylib.h"
#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 
#include "personagem.h"
#include "tela_inicial.h"
#include "game_over.h"
#include "paredes.h"
#include "cenario.h"
#include "audio.h"
#include "neve.h" 

typedef enum GameScreen { MENU, GAMEPLAY, GAMEOVER } GameScreen;

int main(void)
{
    SetRandomSeed(time(0));

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Meu Jogo Vertical");
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Permite redimensionar a janela
    
    
    InitAudio();
    InitTelaInicial();
    InitGameOver();
    InitCenario();
    InitPersonagemAssets();
    InitParedesAssets();
    InitNeve(); 
    
    Font fonteInterface = LoadFontEx("assets/fonts/fonteinterface.ttf", 70, 0, 0);

    SetTargetFPS(60);

    // Cria um RenderTexture para renderizar o jogo em resolução fixa
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    
    Personagem player;
    InitPersonagem(&player); 

    ParedeNode* listaParedes = InicializarParedes(screenWidth, screenHeight);

    
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    float velocidadeCamera = 1.0f;

    GameScreen currentScreen = MENU;

    while (!WindowShouldClose())
    {
        UpdateAudio();

        switch(currentScreen) 
        {
            case MENU:
                if (UpdateTelaInicial() == 1) {
                    currentScreen = GAMEPLAY;
                    
                    
                    InitPersonagem(&player);
                    camera.target = (Vector2){ 0, 0 };
                    velocidadeCamera = 1.0f;
                    InitNeve();
                    
                    LiberarParedes(listaParedes);
                    listaParedes = InicializarParedes(screenWidth, screenHeight);
                }
                break;

            case GAMEPLAY:
                UpdatePersonagem(&player);
                VerificarColisaoParedes(listaParedes, &player);
                UpdateNeve(); 
                
              
                camera.target.y -= velocidadeCamera;
                velocidadeCamera += 0.001f; 

                
                if (player.posicao.y > camera.target.y + screenHeight + 50) {
                    currentScreen = GAMEOVER;
                }
                break;
            
            case GAMEOVER:
                int acao = UpdateGameOver();
                if (acao == 1) { 
                    currentScreen = GAMEPLAY;
                    
                    
                    InitPersonagem(&player);
                    camera.target = (Vector2){ 0, 0 };
                    velocidadeCamera = 1.0f;
                    InitNeve(); 
                    
                    listaParedes = ResetarParedes(listaParedes, screenWidth, screenHeight);
                }
                else if (acao == 2) { 
                     currentScreen = MENU;
                }
                break;
        }

        // Obtém o tamanho atual da janela
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();
        
        // Calcula a escala mantendo proporções
        float scaleX = (float)currentWidth / (float)screenWidth;
        float scaleY = (float)currentHeight / (float)screenHeight;
        float scale = (scaleX < scaleY) ? scaleX : scaleY; // Usa o menor para manter proporções
        
        // Calcula o offset para centralizar
        int offsetX = (currentWidth - (int)(screenWidth * scale)) / 2;
        int offsetY = (currentHeight - (int)(screenHeight * scale)) / 2;

        // Renderiza para o RenderTexture
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            
            switch(currentScreen) 
            {
                case MENU:
                    DrawTelaInicial();
                    break;

                case GAMEPLAY:
                    ClearBackground(RAYWHITE);
                    
                    DrawCenario(); 
                    DrawNeve();
                    
                    BeginMode2D(camera);
                        DrawParedes(listaParedes); 
                        DrawPersonagem(player);
                    EndMode2D();
                    
                    
                    float alturaAtual = (360.0f - player.posicao.y) / 10.0f;
                    if (alturaAtual < 0) alturaAtual = 0;

                    const char* textoPontuacao = TextFormat("ALTURA: %.0f m", alturaAtual);
                    
                    float tamanhoFonte = 40.0f; 
                    float padding = 20.0f; 
                    
                    Vector2 tamanhoTexto = { 0 };
                    
                    if (fonteInterface.texture.id > 0) {
                        tamanhoTexto = MeasureTextEx(fonteInterface, textoPontuacao, tamanhoFonte, 2.0f);
                    } else {
                        tamanhoTexto.x = 300;
                        tamanhoTexto.y = 40;
                    }

                    float larguraCaixa = tamanhoTexto.x + (padding * 2);
                    float alturaCaixa = 80.0f;

                    // Posição no canto inferior direito
                    float posX = screenWidth - larguraCaixa;
                    float posY = screenHeight - alturaCaixa;
                    
                    DrawRectangle((int)posX, (int)posY, (int)larguraCaixa, (int)alturaCaixa, (Color){ 20, 20, 20, 230 });
                    
                    // Bordas do container no canto inferior direito
                    DrawLineEx((Vector2){posX, posY + alturaCaixa}, (Vector2){posX + larguraCaixa, posY + alturaCaixa}, 4.0f, WHITE);
                    DrawLineEx((Vector2){posX + larguraCaixa, posY}, (Vector2){posX + larguraCaixa, posY + alturaCaixa}, 4.0f, WHITE);
                    DrawLineEx((Vector2){posX, posY}, (Vector2){posX, posY + alturaCaixa}, 4.0f, WHITE);
                    DrawLineEx((Vector2){posX, posY}, (Vector2){posX + larguraCaixa, posY}, 4.0f, WHITE);

                   
                    Vector2 posicaoTexto = { posX + padding, posY + (alturaCaixa - tamanhoTexto.y) / 2.0f };

                    if (fonteInterface.texture.id > 0) {
                         DrawTextEx(fonteInterface, textoPontuacao, (Vector2){posicaoTexto.x+2, posicaoTexto.y+2}, tamanhoFonte, 2.0f, BLACK);
                         DrawTextEx(fonteInterface, textoPontuacao, posicaoTexto, tamanhoFonte, 2.0f, WHITE);
                    } else {
                        DrawText(textoPontuacao, (int)padding, 20, 40, WHITE);
                    }
                    break;

                case GAMEOVER:
                    DrawGameOver();
                    break;
            }
        EndTextureMode();

        // Renderiza o RenderTexture escalado na tela
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Desenha o RenderTexture escalado e centralizado
            Rectangle source = { 0, 0, (float)target.texture.width, -(float)target.texture.height };
            Rectangle dest = { (float)offsetX, (float)offsetY, (float)screenWidth * scale, (float)screenHeight * scale };
            Vector2 origin = { 0, 0 };
            DrawTexturePro(target.texture, source, dest, origin, 0.0f, WHITE);
        EndDrawing();
    }

    
    UnloadTelaInicial();
    UnloadGameOver();
    UnloadCenario();
    UnloadAudio();
    
   
    UnloadPersonagemRunningAssets(&player); 
    UnloadPersonagemAssets(); 
    
    UnloadParedesAssets();
    UnloadFont(fonteInterface);
    
    LiberarParedes(listaParedes);
    
    // Libera o RenderTexture
    UnloadRenderTexture(target);

    CloseWindow();
    return 0;
}