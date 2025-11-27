#ifndef RANKING_H
#define RANKING_H
#include "raylib.h"
#define MAX_SCORES 10
#define MAX_NAME_LENGTH 20
#define RANKING_FILE "ranking.json"

typedef struct {
    char nome[MAX_NAME_LENGTH];
    float pontuacao;
} Score;

typedef struct {
    Score scores[MAX_SCORES];
    int count;
} Ranking;

void InitRanking();
void UnloadRanking();
void CarregarRanking(Ranking* ranking);
void SalvarRanking(Ranking* ranking);
void AdicionarScore(Ranking* ranking, const char* nome, float pontuacao);
void DesenharRanking(Ranking* ranking, Font fonte, float x, float y, float tamanhoFonte);

#endif

