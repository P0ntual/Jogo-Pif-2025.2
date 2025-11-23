#include "raylib.h"
#include "personagem.h"
#include "tela_inicial.h"
#include "game_over.h" 
#include "paredes.h"

typedef enum GameScreen { MENU, GAMEPLAY, GAMEOVER } GameScreen;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "FLY");
    
    InitTelaInicial();
    InitGameOver(); 
    
    SetTargetFPS(60);

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
        switch(currentScreen) 
        {
            case MENU:
                if (UpdateTelaInicial() == 1) {
                   
                    currentScreen = GAMEPLAY;
                    InitPersonagem(&player);
                    
                    
                    camera.target = (Vector2){ 0, 0 };
                    velocidadeCamera = 1.0f;
                    
                    
                }
                break;

            case GAMEPLAY:
                UpdatePersonagem(&player);
                VerificarColisaoParedes(listaParedes, &player);

                
                camera.target.y -= velocidadeCamera;
                velocidadeCamera += 0.0005f; 

                
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
                }
                else if (acao == 2) { 
                    currentScreen = MENU;
                }
                break;
        }

        BeginDrawing();
            
            switch(currentScreen) 
            {
                case MENU:
                    DrawTelaInicial();
                    break;

                case GAMEPLAY:
                    ClearBackground(RAYWHITE);
                    BeginMode2D(camera);
                        DrawParedes(listaParedes); 
                        DrawPersonagem(player);
                    EndMode2D();
                    
                    
                    DrawText(TextFormat("Altura: %.0f", -player.posicao.y), 10, 10, 20, BLACK);
                    break;

                case GAMEOVER:
                    
                    DrawGameOver();
                    break;
            }

        EndDrawing();
    }

    UnloadTelaInicial();
    UnloadGameOver(); 
    LiberarParedes(listaParedes); 

    CloseWindow();
    return 0;
}