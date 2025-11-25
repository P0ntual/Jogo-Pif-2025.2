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
    float ultimoXInicio = ultimoX - 125.0f; // X inicial da primeira plataforma (centro - metade da largura)
    float ultimoXFim = ultimoX + 125.0f; // X final da primeira plataforma

    for (int i = 0; i < numPlataformas; i++) {
        
        
        float distanciaY = GetRandomValue(130, 210); 
        float novoY = ultimoY - distanciaY;

        
        float largura = 250.0f; 
        // Largura efetiva da plataforma (80% da largura da imagem, considerando pixels vazios nas bordas)
        float larguraEfetiva = largura * 0.8f; // 200 pixels
        
        // Define separação mínima para evitar alinhamento (20 pixels ou 1.5% da tela)
        float separacaoMinima = screenWidth * 0.015f;
        if (separacaoMinima < 20.0f) {
            separacaoMinima = 20.0f;
        }
        
        // Define separação máxima para garantir alcançabilidade (50% da largura efetiva ou 100 pixels, o que for menor)
        // Isso garante que não fique muito difícil (pixel perfect)
        float separacaoMaxima = larguraEfetiva * 0.5f; // 50% de 200 = 100 pixels
        if (separacaoMaxima > 100.0f) {
            separacaoMaxima = 100.0f;
        }
        
        // Calcula o centro e as bordas efetivas da plataforma anterior
        float ultimoCentroEfetivo = ultimoXInicio + larguraEfetiva / 2.0f;
        float ultimoInicioEfetivo = ultimoCentroEfetivo - larguraEfetiva / 2.0f;
        float ultimoFimEfetivo = ultimoCentroEfetivo + larguraEfetiva / 2.0f;
        
        // Calcula as áreas proibidas (onde não pode começar - zona muito próxima)
        // Usa a largura efetiva para cálculos mais precisos
        float zonaProibidaEsquerda = ultimoFimEfetivo + separacaoMinima;
        float zonaProibidaDireita = ultimoInicioEfetivo - separacaoMinima - larguraEfetiva;
        
        // Calcula as zonas muito distantes (além do alcance de pulo)
        float zonaMuitoDistanteEsquerda = ultimoFimEfetivo + separacaoMaxima;
        float zonaMuitoDistanteDireita = ultimoInicioEfetivo - separacaoMaxima - larguraEfetiva;
        
        // Define os limites da tela
        float xLimiteEsquerda = 50.0f;
        float xLimiteDireita = screenWidth - largura - 50.0f;
        
        // Cria duas zonas possíveis: à esquerda ou à direita da plataforma anterior
        float novoX;
        
        // Escolhe aleatoriamente se vai para a esquerda ou direita
        int escolha = GetRandomValue(0, 1);
        
        if (escolha == 0) {
            // Tenta colocar à direita da plataforma anterior
            float xMinDireita = zonaProibidaEsquerda;
            float xMaxDireita = (zonaMuitoDistanteEsquerda < xLimiteDireita) ? 
                               zonaMuitoDistanteEsquerda : xLimiteDireita;
            
            if (xMinDireita < xMaxDireita) {
                // Tem espaço válido à direita (entre mínimo e máximo)
                float novoCentroX = GetRandomValue((int)xMinDireita, (int)xMaxDireita);
                novoX = novoCentroX - larguraEfetiva / 2.0f;
            } else {
                // Não tem espaço à direita, coloca à esquerda
                float xMaxEsquerda = zonaProibidaDireita;
                float xMinEsquerda = (zonaMuitoDistanteDireita > xLimiteEsquerda) ? 
                                     zonaMuitoDistanteDireita : xLimiteEsquerda;
                
                if (xMaxEsquerda > xMinEsquerda) {
                    float novoCentroX = GetRandomValue((int)xMinEsquerda, (int)xMaxEsquerda);
                    novoX = novoCentroX - larguraEfetiva / 2.0f;
                } else {
                    // Se não tem espaço válido, usa uma posição segura no centro
                    novoX = (xLimiteEsquerda + xLimiteDireita) / 2.0f - largura / 2.0f;
                }
            }
        } else {
            // Tenta colocar à esquerda da plataforma anterior
            float xMaxEsquerda = zonaProibidaDireita;
            float xMinEsquerda = (zonaMuitoDistanteDireita > xLimiteEsquerda) ? 
                                 zonaMuitoDistanteDireita : xLimiteEsquerda;
            
            if (xMaxEsquerda > xMinEsquerda) {
                // Tem espaço válido à esquerda (entre mínimo e máximo)
                float novoCentroX = GetRandomValue((int)xMinEsquerda, (int)xMaxEsquerda);
                novoX = novoCentroX - larguraEfetiva / 2.0f;
            } else {
                // Não tem espaço à esquerda, coloca à direita
                float xMinDireita = zonaProibidaEsquerda;
                float xMaxDireita = (zonaMuitoDistanteEsquerda < xLimiteDireita) ? 
                                   zonaMuitoDistanteEsquerda : xLimiteDireita;
                
                if (xMinDireita < xMaxDireita) {
                    float novoCentroX = GetRandomValue((int)xMinDireita, (int)xMaxDireita);
                    novoX = novoCentroX - larguraEfetiva / 2.0f;
                } else {
                    // Se não tem espaço válido, usa uma posição segura no centro
                    novoX = (xLimiteEsquerda + xLimiteDireita) / 2.0f - largura / 2.0f;
                }
            }
        }
        
        // Garantias finais de limites
        if (novoX < xLimiteEsquerda) {
            novoX = xLimiteEsquerda;
        }
        if (novoX + largura > xLimiteDireita + largura) {
            novoX = xLimiteDireita;
        }
        
        // Validação final: garante que a distância entre bordas efetivas não exceda o máximo
        float novoCentroX = novoX + (largura / 2);
        float novoInicioEfetivo = novoCentroX - larguraEfetiva / 2.0f;
        float novoFimEfetivo = novoCentroX + larguraEfetiva / 2.0f;
        
        // Calcula distância entre as bordas efetivas
        float distanciaEntreBordas;
        if (novoInicioEfetivo > ultimoFimEfetivo) {
            // Nova plataforma está à direita
            distanciaEntreBordas = novoInicioEfetivo - ultimoFimEfetivo;
        } else if (novoFimEfetivo < ultimoInicioEfetivo) {
            // Nova plataforma está à esquerda
            distanciaEntreBordas = ultimoInicioEfetivo - novoFimEfetivo;
        } else {
            // Há sobreposição (ok, permite)
            distanciaEntreBordas = 0.0f;
        }
        
        // Se a distância exceder o máximo, ajusta para o máximo permitido
        if (distanciaEntreBordas > separacaoMaxima) {
            // Ajusta para manter exatamente a separação máxima
            if (novoInicioEfetivo > ultimoFimEfetivo) {
                // Está à direita - move para mais perto
                novoInicioEfetivo = ultimoFimEfetivo + separacaoMaxima;
                novoCentroX = novoInicioEfetivo + larguraEfetiva / 2.0f;
                novoX = novoCentroX - largura / 2.0f;
            } else if (novoFimEfetivo < ultimoInicioEfetivo) {
                // Está à esquerda - move para mais perto
                novoFimEfetivo = ultimoInicioEfetivo - separacaoMaxima;
                novoCentroX = novoFimEfetivo - larguraEfetiva / 2.0f;
                novoX = novoCentroX - largura / 2.0f;
            }
            
            // Revalida limites após ajuste
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
        // Guarda o X inicial e final considerando a posição real da imagem (não apenas a parte efetiva)
        ultimoXInicio = novoX; // Guarda o X inicial para a próxima iteração
        ultimoXFim = novoX + largura; // Guarda o X final para a próxima iteração
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