#ifndef TELA_GAMEOVER_H_
#define TELA_GAMEOVER_H_
#include "raylib.h"
#include "ranking.h"

void InitGameOver();
void UnloadGameOver();
void DrawGameOver(float pontuacao, Ranking* ranking);

int UpdateGameOver(char* nomeJogador, int* nomeFoiSalvo); 
void DrawNomeInput(char* nomeJogador, float pontuacao);

#endif