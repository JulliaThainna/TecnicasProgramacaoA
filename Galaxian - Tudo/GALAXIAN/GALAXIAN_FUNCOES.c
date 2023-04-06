///BIBLIOTECAS PADROES
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

///BIBLIOTECAS DA ALLEGRO
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///TAMANHO DA TELA DO JOGO
const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;

///CHAMA ALGUMAS FUNCOES DA MAIN NECESSARIAS AQUI
void drawMenu();
void drawSecundario();
void drawGameOver();

///STRUCTS

//STRUCT PARA OS INVASORES
typedef struct {
     int inim_col;
     int inim_lin;
     int tiro_lin;
     int tiro_col;
     int dir;    /*DIRECAO DO MOVIMENTO DOS INIMIGOS   0 = direita   1= esquerda*/
     int passo;
}inv;


//STRUCT PARA O INVASOR QUE SE MOVIMENTA
typedef struct {
     int lin;
     int col;
     int tiro_lin;
     int tiro_col;
     int guard_i;
     int guard_j;
     bool repos_inimigo;
}inv_m;


//STRUCT PARA A NAVE DO JOGADOR
typedef struct {
     int x;
     int y;
     int yLaser;
     int xLaser;
     int vidas;
     bool disparo ;
     int pontos;
}player;


///FUNCOES

//FUNCAO QUE PREENCHE A MATRIZ INVISIVEL
void inicializar_matriz_invisivel(int y[][7]) /*Nao e necessario especificar linhas, pois o c "armazena" as linhas uma em sequencia da
                                              /outra*/
{
     int i,j;
     for(i=0;i<5;i++)
     {
          for(j=0;j<7;j++)
          {
               if((i==0 && (j!= 2 && j!= 4 )) || ( i== 1 && (j== 0 || j==6)))
               {
                    y[i][j] = 0;
               }
               else
               {
               y[i][j] = 1;
               }
          }
     }

}


//FUNCAO QUE VERIFICA E ALTERA A DIRECAO DO MOVIMENTO DOS INVASORES
void direcao_invasores(inv *invasores,int *ci)
{
     ///PARA DAR O ASPECTO DOS INIMIGOS SE MOVEREM EM "PASSOS" NA TELA
     (*invasores).passo = 0;
     if(*ci > 20)
     {
          (*invasores).passo = 1;
          *ci = 0;
     }
     if((*invasores).inim_col+450 >= LARGURA_TELA)
     {
          (*invasores).dir = 1;
     }
     if((*invasores).inim_col== 10)
     {
          (*invasores).dir = 0;
     }
     if((*invasores).dir==1)
     {
          (*invasores).inim_col = (*invasores).inim_col - (*invasores).passo*10;
     }
     if((*invasores).dir==0)
     {
          (*invasores).inim_col = (*invasores).inim_col + (*invasores).passo*10;
     }
}


//FUNCAO QUE VERIFICA TODAS AS COLISOES DO JOGO
void colisoes(player *nave,inv *invasores, inv_m *invasor_mov, int matriz_invisivel[][7],int *i, int *j)
{
     ///COLISAO COM O INVASOR
     //Colisao do tiro do jogador com o invasor em movimento
     if((*nave).xLaser >= (*invasor_mov).col - 30 && (*nave).xLaser < (*invasor_mov).col+10 && (*nave).yLaser >= (*invasor_mov).lin
        && (*nave).yLaser < (*invasor_mov).lin +30  && (*nave).disparo == true)
     {
          (*invasor_mov).lin = ALTURA_TELA;
          (*nave).pontos = (*nave).pontos +200;
          (*nave).xLaser = (*nave).x;
          (*nave).yLaser = 497;
          (*nave).disparo = false;

     }
     //Colisao do tiro do jogador com o invasor "normal"
     if((*nave).xLaser >= (*invasores).inim_col - 30 && (*nave).xLaser < (*invasores).inim_col+10 &&
        (*nave).yLaser >= (*invasores).inim_lin && (*nave).yLaser < (*invasores).inim_lin +30  && (*nave).disparo == true)
     {
          matriz_invisivel[*i][*j] = 0;
          (*nave).pontos += 30 * ((*invasor_mov).guard_i + 1);
          (*nave).xLaser = (*nave).x;
          (*nave).yLaser = 497;
          (*nave).disparo = false;
     }

     ///COLISAO COM O JOGADOR
     //Verifica se a posicao do TIRO DOS INVASORES parados e igual a da NAVE DO JOGADOR
     if((*invasores).tiro_col >= (*nave).x - 30 && (*invasores).tiro_col < (*nave).x + 50 && (*invasores).tiro_lin >= (*nave).y &&
        (*invasores).tiro_lin < (*nave).y+30)
     {
          (*nave).vidas--;    /*Diminui uma vida*/
          (*invasores).tiro_lin = ALTURA_TELA;

     }
     // verifica se a posicao do TIRO DO INVASOR EM MOVIMENTO e igual a da NAVE DO JOGADOR
     if((*invasor_mov).tiro_col >= (*nave).x - 30 && (*invasor_mov).tiro_col < (*nave).x + 50 && (*invasor_mov).tiro_lin >= (*nave).y
        && (*invasor_mov).tiro_lin < (*nave).y+30)
     {
          (*nave).vidas--; /*Diminui uma vida*/
          (*invasor_mov).tiro_lin = ALTURA_TELA;
     }

     //Verifica se a posicao do INVASOR EM MOVIMENTO e igual a da NAVE DO JOGADOR
     if((*invasor_mov).col >= (*nave).x - 30 && (*invasor_mov).col < (*nave).x + 50 && (*invasor_mov).lin >= (*nave).y &&
        (*invasor_mov).lin < (*nave).y+30)
     {
          (*nave).vidas--; /*Diminui uma vida*/
          (*invasor_mov).lin = ALTURA_TELA;
     }
}


//FUNCAO QUE "REVIVE" OS INVASORES CASO TODOS TENHAM SIDO ELIMINADOS
void reviver_invasores(int matriz_invisivel[][7],inv_m *invasor_mov)
{
     int cont = 0;
     int a,b;
     for(a=0;a<5;a++)
     {
          for(b=0;b<7;b++)
          {
               if(matriz_invisivel[a][b]==0) /*Verifica se todos estao mortos*/
               {
                    cont++;
               }
          }
     }
     if(cont == 35 && (*invasor_mov).lin >= ALTURA_TELA)    /*Se todos estiverem mortos*/
     {
          inicializar_matriz_invisivel(matriz_invisivel);
     }

}


//FUNCAO QUE ALTERA A POSICAO DOS TIROS E DOS PROPRIOS INVASORES EM MOVIMENTO
void movimentos_do_invasor_mov(inv_m *invasor_mov,int matriz_invisivel[][7])
{
     if((*invasor_mov).lin<ALTURA_TELA) /*Caso o invasor ainda nao tenha chegado ao fim da tela*/
     {
          (*invasor_mov).lin = (*invasor_mov).lin+3;
     }
     if((*invasor_mov).lin>ALTURA_TELA) /*Caso o invasor chegue ao fim da tela sem ser destruido*/
     {
          (*invasor_mov).lin = ALTURA_TELA;
          (*invasor_mov).repos_inimigo = true;

     }

     ///REPOSICIONANDO O INVASOR CASO ELE NAO SEJA DESTRUIDO
     if((*invasor_mov).repos_inimigo == true && (*invasor_mov).lin == ALTURA_TELA)
     {
          matriz_invisivel[(*invasor_mov).guard_i][(*invasor_mov).guard_j] = 1; /*A posicao original do invasor recebe 1*/
          (*invasor_mov).repos_inimigo = false;
     }

     //Tiro do invasor em movimento
     if((*invasor_mov).tiro_lin >= ALTURA_TELA && (*invasor_mov).lin <= 300)    /*Se o tiro chegou no final da tela, ele retorna para o
                                                                                invasor*/
     {
          (*invasor_mov).tiro_lin = (*invasor_mov).lin+25;
          (*invasor_mov).tiro_col = (*invasor_mov).tiro_col+25;
     }
     (*invasor_mov).tiro_lin = (*invasor_mov).tiro_lin+5;

}


//FUNCAO QUE "DESENHA" A TELA DO MENU
void drawMenu(ALLEGRO_FONT*FonteMenu2, ALLEGRO_FONT*FonteMenu5, ALLEGRO_BITMAP*fundoMenu, ALLEGRO_BITMAP* LogoMenu,
              const int LARGURA_TELA, const int ALTURA_TELA, int xnave, int x, int y)
{
     al_clear_to_color(al_map_rgb(0,0,0));
     al_draw_bitmap(fundoMenu,0,0,0);
     al_draw_bitmap(LogoMenu, 190, -200, 0);
     al_draw_textf(FonteMenu5, al_map_rgb(0, 204, 255), LARGURA_TELA / 2, 140, ALLEGRO_ALIGN_CENTER,
                   " [This is certainly not an attempt to copy the Galaxian game]");
     al_draw_textf(FonteMenu5, al_map_rgb(0, 204, 255), LARGURA_TELA - 5, ALTURA_TELA - 30, ALLEGRO_ALIGN_RIGHT,
                   "An attempt made by: UEL'S COMPUTEIROS 2019");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 500, ALTURA_TELA - 145, ALLEGRO_ALIGN_RIGHT,
                    " UEL - Universidade Estadual de Londrina");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 644, ALTURA_TELA - 125, ALLEGRO_ALIGN_RIGHT,
                   "Ciencia da Computacao    ");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 605, ALTURA_TELA - 105, ALLEGRO_ALIGN_RIGHT,
                   "Projeto de jogo - Programacao");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 705, ALTURA_TELA - 80, ALLEGRO_ALIGN_RIGHT, "ALUNOS:            ");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 755, ALTURA_TELA - 55, ALLEGRO_ALIGN_RIGHT, "Andre Ferreira");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 755, ALTURA_TELA - 35, ALLEGRO_ALIGN_RIGHT, "Jullia Thainna");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 755, ALTURA_TELA - 15, ALLEGRO_ALIGN_RIGHT, "Tatiane Soares");

     al_draw_textf(FonteMenu2, al_map_rgb(255, 255, 255), xnave, y + 100, ALLEGRO_ALIGN_CENTER, "     G      ");
     al_draw_textf(FonteMenu2, al_map_rgb(255, 255, 255), x, y - 80, ALLEGRO_ALIGN_CENTER, "E  E  E  E  E  E ");
     al_draw_textf(FonteMenu2, al_map_rgb(255, 255, 255), x, y - 30, ALLEGRO_ALIGN_CENTER, "C  C  C  C  C  C ");
     al_draw_textf(FonteMenu2, al_map_rgb(255, 255, 255), x, y+20, ALLEGRO_ALIGN_CENTER, "D  D  D  D  D  D ");
     al_draw_textf(FonteMenu2, al_map_rgb(255, 255, 255), x, y +70, ALLEGRO_ALIGN_CENTER, "J  J  J  J  J  J ");
}


//FUNCAO QUE "DESENHA" A TELA DO MENU SECUNDARIO
void drawSecundario(ALLEGRO_FONT* FonteFrase, ALLEGRO_FONT* FonteFraseTachado, ALLEGRO_FONT* FontePontos3, ALLEGRO_FONT* FontePontos2,
                     ALLEGRO_BITMAP* fundoMenu, ALLEGRO_BITMAP* invasor1, ALLEGRO_BITMAP* invasor2, ALLEGRO_BITMAP* invasor3,
                     ALLEGRO_FONT* fonteSpace, ALLEGRO_BITMAP* invasor4, const int LARGURA_TELA, const int ALTURA_TELA, int z, int x,
                     int y)
{
     al_clear_to_color(al_map_rgb(0,0,0));
     al_draw_bitmap(fundoMenu,0,0,0);
     al_draw_textf(FonteFrase, al_map_rgb(255, 255, 0),LARGURA_TELA-650,y-150,ALLEGRO_ALIGN_CENTER,"WE ARE");
     al_draw_textf(FonteFraseTachado, al_map_rgb(255, 255, 0),LARGURA_TELA/2-25,y-135,ALLEGRO_ALIGN_CENTER,"COMPUTEIROS ");
     al_draw_textf(FonteFrase, al_map_rgb(255, 255, 0),LARGURA_TELA-270,y-150,ALLEGRO_ALIGN_CENTER,"THE GALAXIANS");
     al_draw_textf(FonteFrase, al_map_rgb(255, 0, 0),LARGURA_TELA/2-330,y-80,ALLEGRO_ALIGN_CENTER,"MISSION... ");
     al_draw_textf(FonteFraseTachado, al_map_rgb(255, 0, 0),LARGURA_TELA-500,y-60,ALLEGRO_ALIGN_CENTER,"  NAO RETER EM PROGRAMACAO");
     al_draw_textf(FonteFrase, al_map_rgb(255, 0, 0),LARGURA_TELA-150,y-80,ALLEGRO_ALIGN_CENTER,"  DESTROY ALIENS ");

     al_draw_text(FontePontos3,al_map_rgb(191, 191, 191),LARGURA_TELA/2-170,ALTURA_TELA-350, ALLEGRO_ALIGN_LEFT,"SCORE ADVANCE TABLE");
     al_draw_textf(FontePontos2,al_map_rgb(255, 255, 255),LARGURA_TELA/2-70,ALTURA_TELA-300,ALLEGRO_ALIGN_LEFT,"   60   pts");
     al_draw_textf(FontePontos2,al_map_rgb(255, 255, 255),LARGURA_TELA/2-70,ALTURA_TELA-260,ALLEGRO_ALIGN_LEFT,"   50   pts");
     al_draw_textf(FontePontos2,al_map_rgb(255, 255, 255),LARGURA_TELA/2-70,ALTURA_TELA-220,ALLEGRO_ALIGN_LEFT,"   40   pts");
     al_draw_textf(FontePontos2,al_map_rgb(255, 255, 255),LARGURA_TELA/2-70,ALTURA_TELA-180,ALLEGRO_ALIGN_LEFT,"   30   pts");
     al_draw_textf(FontePontos2,al_map_rgb(255, 255, 255),LARGURA_TELA/2-140,ALTURA_TELA-130,ALLEGRO_ALIGN_LEFT,"5000 pts + 1 vida");

     al_draw_bitmap(invasor1,LARGURA_TELA/2-100,ALTURA_TELA-265,ALLEGRO_ALIGN_LEFT);
     al_draw_bitmap(invasor2,LARGURA_TELA/2-100,ALTURA_TELA-230,ALLEGRO_ALIGN_LEFT);
     al_draw_bitmap(invasor3,LARGURA_TELA/2-100,ALTURA_TELA-190,ALLEGRO_ALIGN_LEFT);
     al_draw_bitmap(invasor4,LARGURA_TELA/2-103,ALTURA_TELA-310,ALLEGRO_ALIGN_LEFT);

     al_draw_textf(fonteSpace,al_map_rgb(0, 255, 255),LARGURA_TELA/2-150,z+450,ALLEGRO_ALIGN_LEFT,"press SPACE to go to the game");

}


//FUNCAO QUE "DESENHA" A TELA DE GAME OVER
void gameOverDraw(ALLEGRO_FONT *FontePontos2, ALLEGRO_FONT *FonteMenu4, ALLEGRO_BITMAP *fundoMenu, const int LARGURA_TELA, int y,
                  int **lugar, int pontos_nave)
{
     al_clear_to_color(al_map_rgb(0,0,0));
     al_draw_bitmap(fundoMenu,0,0,0);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 40, ALLEGRO_ALIGN_CENTER, "SCORE: %d", pontos_nave);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 80, ALLEGRO_ALIGN_CENTER, "1 Lugar: %d", lugar[0]);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 100, ALLEGRO_ALIGN_CENTER, "2 Lugar: %d", lugar[1]);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 120, ALLEGRO_ALIGN_CENTER, "3 Lugar: %d", lugar[2]);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 140, ALLEGRO_ALIGN_CENTER, "4 Lugar: %d", lugar[3]);
     al_draw_textf(FontePontos2, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y + 160, ALLEGRO_ALIGN_CENTER, "5 Lugar: %d", lugar[4]);

     al_draw_textf(FonteMenu4, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y -200, ALLEGRO_ALIGN_CENTER, "E E E E E E ");
     al_draw_textf(FonteMenu4, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, y, ALLEGRO_ALIGN_CENTER, "J J J J J J ");
}
