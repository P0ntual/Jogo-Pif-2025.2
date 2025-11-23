#include "raylib.h"
#include "personagem.h"
#include "tela_inicial.h"
#include "paredes.h"


typedef enum GameScreen { MENU, GAMEPLAY, GAMEOVER } GameScreen;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Meu Jogo - Game Over");
    
    InitTelaInicial();
    SetTargetFPS(60);

    Personagem player;
    InitPersonagem(&player); 

    ParedeNode* listaParedes = InicializarParedes(screenWidth, screenHeight);

    GameScreen currentScreen = MENU;

    while (!WindowShouldClose())
    {
        
        switch(currentScreen) 
        {
            case MENU:
                if (UpdateTelaInicial() == 1) {
                    currentScreen = GAMEPLAY;
                }
                break;

            case GAMEPLAY:
                UpdatePersonagem(&player);
                VerificarColisaoParedes(listaParedes, &player);

                
                if (player.posicao.y > screenHeight + 50) {
                    currentScreen = GAMEOVER;
                }
                break;
            
            case GAMEOVER:
                
                if (IsKeyPressed(KEY_R)) {
                    InitPersonagem(&player); 
                    currentScreen = GAMEPLAY;
                }
                
                if (IsKeyPressed(KEY_ENTER)) {
                    InitPersonagem(&player);
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
                    DrawParedes(listaParedes); 
                    DrawPersonagem(player);
                    break;

                case GAMEOVER:
                    
                    ClearBackground(MAROON);
                    DrawText("GAME OVER", 400, 200, 80, WHITE);
                    DrawText("Pressione 'R' para tentar de novo", 380, 400, 30, LIGHTGRAY);
                    DrawText("Pressione 'ENTER' para o Menu", 420, 450, 20, GRAY);
                    break;
            }

        EndDrawing();
    }

    UnloadTelaInicial();
    LiberarParedes(listaParedes); 

    CloseWindow();
    return 0;
}