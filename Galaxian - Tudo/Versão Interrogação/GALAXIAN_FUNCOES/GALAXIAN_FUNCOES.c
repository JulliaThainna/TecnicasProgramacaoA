#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//bibliotecas da allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//!STRUCT P/ O INVASOR QUE SE MOVIMENTA
            struct{
            int lin;
            int col;
            int tiro_lin;
            int tiro_col;

            }invasor_mov;

            struct{
            int x;
            int y;
            int yLaser;
            int xLaser;
            int vidas;
            }nave;

            struct{
            int lugar[5];

            }score;

// função que preenche a matriz invisivel
// não é necessário especificar linhas, pois o c "armazena" as linhas uma em sequencia da outra

void inicializar_matriz_invisivel();
int colisao_jogador();
int colisao_invasor();
int direcao_invasores();


