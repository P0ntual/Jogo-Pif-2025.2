#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static Font fonteRanking;

void InitRanking() {
    fonteRanking = LoadFontEx("assets/fonts/fonteinterface.ttf", 40, 0, 0);
    SetTextureFilter(fonteRanking.texture, TEXTURE_FILTER_BILINEAR);
}

void UnloadRanking() {
    UnloadFont(fonteRanking);
}

void CarregarRanking(Ranking* ranking) {
    ranking->count = 0;
    
    FILE* file = fopen(RANKING_FILE, "r");
    if (!file) {
        
        return;
    }
    
    
    char buffer[4096];
    int len = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[len] = '\0';
    fclose(file);
    
    
    char* scoresStart = strstr(buffer, "\"scores\"");
    if (!scoresStart) {
        return;
    }
    
    char* arrayStart = strchr(scoresStart, '[');
    if (!arrayStart) {
        return;
    }
    
    char* pos = arrayStart + 1;
    
    while (ranking->count < MAX_SCORES) {
        
        char* objStart = strchr(pos, '{');
        if (!objStart) break;
        
        
        char* nomeStart = strstr(objStart, "\"nome\"");
        if (!nomeStart) break;
        
        
        char* nomeValue = strchr(nomeStart, ':');
        if (!nomeValue) break;
        nomeValue++; 
        
        
        while (*nomeValue == ' ' || *nomeValue == '"') nomeValue++;
        
        
        int nomeLen = 0;
        while (*nomeValue != '"' && nomeLen < MAX_NAME_LENGTH - 1) {
            ranking->scores[ranking->count].nome[nomeLen++] = *nomeValue++;
        }
        ranking->scores[ranking->count].nome[nomeLen] = '\0';
        
        
        char* pontStart = strstr(nomeValue, "\"pontuacao\"");
        if (!pontStart) break;
        
        
        char* pontValue = strchr(pontStart, ':');
        if (!pontValue) break;
        pontValue++; 
        
        
        while (*pontValue == ' ') pontValue++;
        
        
        ranking->scores[ranking->count].pontuacao = atof(pontValue);
        
        ranking->count++;
        
        
        pos = strchr(objStart, '}');
        if (!pos) break;
        pos++;
        
        
        if (*pos == ']' || strchr(pos, '{') == NULL) break;
    }
}

void SalvarRanking(Ranking* ranking) {
    FILE* file = fopen(RANKING_FILE, "w");
    if (!file) {
        return;
    }
    
    fprintf(file, "{\n  \"scores\": [\n");
    
    for (int i = 0; i < ranking->count; i++) {
        fprintf(file, "    {\"nome\": \"%s\", \"pontuacao\": %.2f}", 
                ranking->scores[i].nome, ranking->scores[i].pontuacao);
        
        if (i < ranking->count - 1) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    
    fprintf(file, "  ]\n}\n");
    fclose(file);
}

void AdicionarScore(Ranking* ranking, const char* nome, float pontuacao) {
    int nomeExiste = -1;
    for (int i = 0; i < ranking->count; i++) {
        if (strcmp(ranking->scores[i].nome, nome) == 0) {
            nomeExiste = i;
            break;
        }
    }
    
    if (nomeExiste >= 0) {
        if (pontuacao > ranking->scores[nomeExiste].pontuacao) {
            ranking->scores[nomeExiste].pontuacao = pontuacao;
        } else {
            return;
        }
    } else {
        if (ranking->count < MAX_SCORES) {
            strncpy(ranking->scores[ranking->count].nome, nome, MAX_NAME_LENGTH - 1);
            ranking->scores[ranking->count].nome[MAX_NAME_LENGTH - 1] = '\0';
            ranking->scores[ranking->count].pontuacao = pontuacao;
            ranking->count++;
        } else {
            float menorPontuacao = ranking->scores[ranking->count - 1].pontuacao;
            if (pontuacao > menorPontuacao) {
                strncpy(ranking->scores[ranking->count - 1].nome, nome, MAX_NAME_LENGTH - 1);
                ranking->scores[ranking->count - 1].nome[MAX_NAME_LENGTH - 1] = '\0';
                ranking->scores[ranking->count - 1].pontuacao = pontuacao;
            } else {
                return;
            }
        }
    }
    
    for (int i = 0; i < ranking->count - 1; i++) {
        for (int j = i + 1; j < ranking->count; j++) {
            if (ranking->scores[i].pontuacao < ranking->scores[j].pontuacao) {
                Score temp = ranking->scores[i];
                ranking->scores[i] = ranking->scores[j];
                ranking->scores[j] = temp;
            }
        }
    }
    
    SalvarRanking(ranking);
}

void DesenharRanking(Ranking* ranking, Font fonte, float x, float y, float tamanhoFonte) {
    if (ranking->count == 0) {
        const char* texto = "Nenhum recorde ainda!";
        Vector2 dim = MeasureTextEx(fonte, texto, tamanhoFonte, 1.0f);
        DrawTextEx(fonte, texto, (Vector2){x, y}, tamanhoFonte, 1.0f, WHITE);
        return;
    }
    
    const char* titulo = "RANKING";
    Vector2 dimTitulo = MeasureTextEx(fonte, titulo, tamanhoFonte * 1.2f, 1.0f);
    DrawTextEx(fonte, titulo, (Vector2){x, y}, tamanhoFonte * 1.2f, 1.0f, YELLOW);
    
    float linhaY = y + dimTitulo.y + 20.0f;
    float espacamento = tamanhoFonte + 10.0f;
    
    int maxMostrar = (ranking->count < 5) ? ranking->count : 5; 
    
    for (int i = 0; i < maxMostrar; i++) {
        char linha[100];
        snprintf(linha, sizeof(linha), "%d. %s - %.0f m", 
                 i + 1, ranking->scores[i].nome, ranking->scores[i].pontuacao);
        
        DrawTextEx(fonte, linha, (Vector2){x, linhaY}, tamanhoFonte, 1.0f, WHITE);
        linhaY += espacamento;
    }
}

