# FLY 

FLY é um jogo de plataforma vertical desenvolvido em **C** utilizando a biblioteca **Raylib**. 

![Status](https://img.shields.io/badge/Status-Em_Desenvolvimento-yellow)
![Language](https://img.shields.io/badge/C-Linux%2FWSL-blue)

## Pré-requisitos

Este jogo foi desenvolvido para rodar em ambiente **Linux** ou **WSL (Windows Subsystem for Linux)**.

**Nota:** Possua a **Raylib** já instalada em seu sistema.

### Instalação das Dependências de Sistema:

Para garantir que o som e a janela funcionem corretamente (especialmente no WSL), instale as bibliotecas de suporte abaixo.

# 1. Atualize o sistema:
sudo apt update

# 2. Instale ferramentas de compilação e Git:
sudo apt install build-essential git

# 3. Instale drivers de áudio e dependências gráficas:
sudo apt install libasound2-dev libx11-dev libgl1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev pulseaudio libpulse-dev

# Dica: Se estiver no Ubuntu 24.04 ou superior, adicione também:
sudo apt install libasound2t64

### Clonagem de Repositório: 

# 1. Clonagem:
git clone [https://github.com/P0ntual/Jogo-Pif-2025.2.git](https://github.com/P0ntual/Jogo-Pif-2025.2.git)
cd Jogo-Pif-2025.2

# 2. Compilação:
gcc src/main.c src/personagem.c src/tela_inicial.c src/game_over.c src/paredes.c src/cenario.c src/audio.c src/neve.c src/ranking.c -o output/meujogo -I includes -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# 3. Execução: 
./output/meujogo

# NOTA: 
caso a pasta output nao apareça, você deve realizar o seguinte codigo no terminal: mkdir output 

## Créditos dos Assets
Fonte: Polar Snow (Assets/Fonts)

Música: "First Snow" por Lolurio (Itch.io)

Fundo: Winter Background (Itch.io/CraftPix)

Biblioteca: Raylib

Integrantes: Hugo Gomes, Eloi pontual e Teteu Diniz

# Vídeo Do Jogo: 
https://www.youtube.com/watch?v=OErtT2dlsC0
