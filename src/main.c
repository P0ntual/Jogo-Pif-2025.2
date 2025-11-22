#include "raylib.h"
#include "personagem.h"
#include "tela_inicial.h" 


typedef enum GameScreen { MENU, GAMEPLAY } GameScreen;

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Meu Jogo - Full HD");
    SetTargetFPS(60);

    
    Personagem player;
    InitPersonagem(&player);

    
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
                    DrawPersonagem(player);
                    break;
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}