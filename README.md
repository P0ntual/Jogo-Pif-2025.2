# Jogo-Pif-2025.2
Jogo de pif do segundo semestre.

Tutorial de como instalar o raylib: 
1. Instalar as Dependências
Primeiro, instale as ferramentas de compilação (build-essential), o git (para baixar o código) e todas as bibliotecas gráficas e de áudio que o Raylib precisa:
No bash digite
sudo apt update
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

2. Baixar o Código-Fonte
Use o git para baixar (clonar) a última versão do Raylib do GitHub para uma nova pasta chamada raylib:
No bash digite
git clone https://github.com/raysan5/raylib.git raylib

3. Compilar o Raylib
Agora, vamos entrar na pasta do código-fonte e compilar o projeto.

Entre na pasta src do Raylib:
No bash digite
cd raylib/src
Execute o comando make para compilar para a plataforma Desktop:
No bash digite
make PLATFORM=PLATFORM_DESKTOP

4. Instalar os Arquivos no Sistema
Após a compilação, instale os arquivos da biblioteca e os cabeçalhos (.h) em um local padrão do sistema para que o compilador (gcc) possa encontrá-los:
No bash digite
sudo make install

5. Atualizar o Cache de Bibliotecas
Execute este comando final para que o Linux reconheça a nova biblioteca que você acabou de instalar:
No bash digite
sudo ldconfig

Tudo pronto para rodar o jogo!
