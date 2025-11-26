#include "paredes.h"
#include "raylib.h"
#include "personagem.h" 
#include <stdlib.h> 
#include <stdio.h>
#include <math.h> 


static Texture2D texturaPlataforma;



void InitParedesAssets() {
    
    texturaPlataforma = LoadTexture("assets/images/plataforma.png");
}

void UnloadParedesAssets() {
    UnloadTexture(texturaPlataforma);
}



void AdicionarParede(ParedeNode** head, Rectangle rect) {
    ParedeNode* novoNo = (ParedeNode*)malloc(sizeof(ParedeNode));
    novoNo->retangulo = rect;
    novoNo->proximo = *head;
    *head = novoNo;
}

ParedeNode* InicializarParedes(int screenWidth, int screenHeight) {
    ParedeNode* lista = NULL; 
    
    int espessura = 100;
    int alturaNivel = 10000; 
     
    AdicionarParede(&lista, (Rectangle){ -espessura, -alturaNivel, espessura, alturaNivel + screenHeight });
    AdicionarParede(&lista, (Rectangle){ screenWidth, -alturaNivel, espessura, alturaNivel + screenHeight });
    
    
    AdicionarParede(&lista, (Rectangle){ 0, 650, screenWidth, 40 });

    int numPlataformas = 100; 
    
    float ultimoY = 650;
    float ultimoX = screenWidth / 2.0f; 
    float ultimoXInicio = ultimoX - 125.0f; 
    float ultimoXFim = ultimoX + 125.0f;

    for (int i = 0; i < numPlataformas; i++) {
        
        
        float distanciaY = GetRandomValue(130, 210); 
        float novoY = ultimoY - distanciaY;

        
        float largura = 250.0f; 
        float larguraEfetiva = largura * 0.8f; 
        
        float separacaoMinima = screenWidth * 0.015f;
        if (separacaoMinima < 20.0f) {
            separacaoMinima = 20.0f;
        }
        
        float separacaoMaxima = larguraEfetiva * 0.5f;
        if (separacaoMaxima > 100.0f) {
            separacaoMaxima = 100.0f;
        }
        
        float ultimoCentroEfetivo = ultimoXInicio + larguraEfetiva / 2.0f;
        float ultimoInicioEfetivo = ultimoCentroEfetivo - larguraEfetiva / 2.0f;
        float ultimoFimEfetivo = ultimoCentroEfetivo + larguraEfetiva / 2.0f;
        
        float zonaProibidaEsquerda = ultimoFimEfetivo + separacaoMinima;
        float zonaProibidaDireita = ultimoInicioEfetivo - separacaoMinima - larguraEfetiva;
        
        float zonaMuitoDistanteEsquerda = ultimoFimEfetivo + separacaoMaxima;
        float zonaMuitoDistanteDireita = ultimoInicioEfetivo - separacaoMaxima - larguraEfetiva;
        
        float xLimiteEsquerda = 50.0f;
        float xLimiteDireita = screenWidth - largura - 50.0f;
        
        float novoX;
        
        int escolha = GetRandomValue(0, 1);
        
        if (escolha == 0) {
            float xMinDireita = zonaProibidaEsquerda;
            float xMaxDireita = (zonaMuitoDistanteEsquerda < xLimiteDireita) ? 
                               zonaMuitoDistanteEsquerda : xLimiteDireita;
            
            if (xMinDireita < xMaxDireita) {
                float novoCentroX = GetRandomValue((int)xMinDireita, (int)xMaxDireita);
                novoX = novoCentroX - larguraEfetiva / 2.0f;
            } else {
                float xMaxEsquerda = zonaProibidaDireita;
                float xMinEsquerda = (zonaMuitoDistanteDireita > xLimiteEsquerda) ? 
                                     zonaMuitoDistanteDireita : xLimiteEsquerda;
                
                if (xMaxEsquerda > xMinEsquerda) {
                    float novoCentroX = GetRandomValue((int)xMinEsquerda, (int)xMaxEsquerda);
                    novoX = novoCentroX - larguraEfetiva / 2.0f;
                } else {
                    novoX = (xLimiteEsquerda + xLimiteDireita) / 2.0f - largura / 2.0f;
                }
            }
        } else {
            float xMaxEsquerda = zonaProibidaDireita;
            float xMinEsquerda = (zonaMuitoDistanteDireita > xLimiteEsquerda) ? 
                                 zonaMuitoDistanteDireita : xLimiteEsquerda;
            
            if (xMaxEsquerda > xMinEsquerda) {
                float novoCentroX = GetRandomValue((int)xMinEsquerda, (int)xMaxEsquerda);
                novoX = novoCentroX - larguraEfetiva / 2.0f;
            } else {
                float xMinDireita = zonaProibidaEsquerda;
                float xMaxDireita = (zonaMuitoDistanteEsquerda < xLimiteDireita) ? 
                                   zonaMuitoDistanteEsquerda : xLimiteDireita;
                
                if (xMinDireita < xMaxDireita) {
                    float novoCentroX = GetRandomValue((int)xMinDireita, (int)xMaxDireita);
                    novoX = novoCentroX - larguraEfetiva / 2.0f;
                } else {
                    novoX = (xLimiteEsquerda + xLimiteDireita) / 2.0f - largura / 2.0f;
                }
            }
        }
        
        if (novoX < xLimiteEsquerda) {
            novoX = xLimiteEsquerda;
        }
        if (novoX + largura > xLimiteDireita + largura) {
            novoX = xLimiteDireita;
        }
        
        float novoCentroX = novoX + (largura / 2);
        float novoInicioEfetivo = novoCentroX - larguraEfetiva / 2.0f;
        float novoFimEfetivo = novoCentroX + larguraEfetiva / 2.0f;
        
        float distanciaEntreBordas;
        if (novoInicioEfetivo > ultimoFimEfetivo) {
            distanciaEntreBordas = novoInicioEfetivo - ultimoFimEfetivo;
        } else if (novoFimEfetivo < ultimoInicioEfetivo) {
            distanciaEntreBordas = ultimoInicioEfetivo - novoFimEfetivo;
        } else {
            distanciaEntreBordas = 0.0f;
        }
        
        if (distanciaEntreBordas > separacaoMaxima) {
            if (novoInicioEfetivo > ultimoFimEfetivo) {
                novoInicioEfetivo = ultimoFimEfetivo + separacaoMaxima;
                novoCentroX = novoInicioEfetivo + larguraEfetiva / 2.0f;
                novoX = novoCentroX - largura / 2.0f;
            } else if (novoFimEfetivo < ultimoInicioEfetivo) {
                novoFimEfetivo = ultimoInicioEfetivo - separacaoMaxima;
                novoCentroX = novoFimEfetivo - larguraEfetiva / 2.0f;
                novoX = novoCentroX - largura / 2.0f;
            }
            
            if (novoX < xLimiteEsquerda) {
                novoX = xLimiteEsquerda;
                novoCentroX = novoX + (largura / 2);
            }
            if (novoX + largura > xLimiteDireita + largura) {
                novoX = xLimiteDireita;
                novoCentroX = novoX + (largura / 2);
            }
        }

        AdicionarParede(&lista, (Rectangle){ novoX, novoY, largura, 30 });

        ultimoY = novoY;
        ultimoX = novoCentroX;
        ultimoXInicio = novoX; 
        ultimoXFim = novoX + largura;
    }

    return lista;
}

void VerificarColisaoParedes(ParedeNode* head, Personagem* p) {
    ParedeNode* atual = head;

    while (atual != NULL) {
        Rectangle r = atual->retangulo;
        Rectangle playerRect = { p->posicao.x - p->raio, p->posicao.y - p->raio, p->raio * 2, p->raio * 2 };

        if (CheckCollisionRecs(playerRect, r)) {
            Rectangle interseccao = GetCollisionRec(playerRect, r);

            if (interseccao.width > interseccao.height) {
                if (p->posicao.y < r.y + (r.height/2)) {
                    p->posicao.y = r.y - p->raio;
                    if (p->gravidade > 0) p->gravidade = 0;
                } else {
                    p->posicao.y = r.y + r.height + p->raio;
                    if (p->gravidade < 0) p->gravidade = 0;
                }
            } else {
                if (p->posicao.x < r.x) p->posicao.x = r.x - p->raio;
                else p->posicao.x = r.x + r.width + p->raio;
            }
        }
        atual = atual->proximo; 
    }
}

void DrawParedes(ParedeNode* head) {
    ParedeNode* atual = head;

    
    int imagemOk = (texturaPlataforma.id > 0 && texturaPlataforma.width > 0);

    while (atual != NULL) {
        
        if (imagemOk) {
           
            Rectangle source = { 0.0f, 0.0f, (float)texturaPlataforma.width, (float)texturaPlataforma.height };
            Rectangle dest = atual->retangulo;
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(texturaPlataforma, source, dest, origin, 0.0f, WHITE);
        } else {
           
            DrawRectangleRec(atual->retangulo, RED);
            DrawRectangleLinesEx(atual->retangulo, 2, YELLOW);
        }
        
        atual = atual->proximo;
    }
}

void LiberarParedes(ParedeNode* head) {
    ParedeNode* atual = head;
    while (atual != NULL) {
        ParedeNode* temp = atual;
        atual = atual->proximo;
        free(temp); 
    }
}


ParedeNode* ResetarParedes(ParedeNode* listaAntiga, int screenWidth, int screenHeight) {
    
    LiberarParedes(listaAntiga);
    
    
    return InicializarParedes(screenWidth, screenHeight);
}