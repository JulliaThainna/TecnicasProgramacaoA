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


void inicializa_allegro();
void inicializar_matriz_invisivel();
int colisao_jogador();
int colisao_invasor();
int direcao_invasores();
void drawMenu();
void drawSecundario();
void drawGameOver();

void inicializar_matriz_invisivel(int y[][7]){
     int i,j;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 7; j++){
			if ((i == 0 && (j != 2 && j != 4)) || (i == 1 && (j == 0 || j == 6))){
				y[i][j] = 0;
			}
			else{
				y[i][j] = 1;
			}
		}
	}
}
//Verifica se a posicao do laser que o inimigo disparou coincide com a posicao da nave.
//Caso sim, retorna um. Caso a colisao seja falsa, retorna 0
// função que preenche a matriz invisivel
// não é necessário especificar linhas, pois o c "armazena" as linhas uma em sequencia da outra



// função que verifica a colisão dos invasores e seus tiros com a nave do jogador
int colisao_jogador(int x, int y, int a, int b){
	if (x >= a - 30 && x < a + 50 && y >= b && y <= b + 25){
		return 1;
	}
	return 0;
}


//Faz a mesma coisa que a funcao de cima so que pra nave dos inimigos (tiro jogador). Ja que o tamanho das naves e diferente
// função que verifica a colisão dos tiros do jogador com os invasores
int colisao_invasor(int x, int y, int a, int b){
	if (x >= a - 30 && x < a + 30 && y >= b - 30 && y < b){
		return 1;
	}
	return 0;

}

// função que altera a direção do movimento dos invasores
int direcao_invasores(int col){
	if (col + 450 >= 900){
		return 1;
	}
	if (col == 10){
		return 0;
	}
	return -1;
}
void drawMenu(ALLEGRO_FONT*FonteMenu2, ALLEGRO_FONT*FonteMenu5, ALLEGRO_BITMAP*fundoMenu, ALLEGRO_BITMAP* LogoMenu, const int LARGURA_TELA,
              const int ALTURA_TELA, int xnave, int x, int y){
     al_clear_to_color(al_map_rgb(0,0,0));
     al_draw_bitmap(fundoMenu,0,0,0);
     al_draw_bitmap(LogoMenu, 190, -200, 0);
     al_draw_textf(FonteMenu5, al_map_rgb(0, 204, 255), LARGURA_TELA / 2, 140, ALLEGRO_ALIGN_CENTER, " [This is certainly not an attempt to copy the Galaxian game]");
     al_draw_textf(FonteMenu5, al_map_rgb(0, 204, 255), LARGURA_TELA - 5, ALTURA_TELA - 30, ALLEGRO_ALIGN_RIGHT, "An attempt made by: UEL'S COMPUTEIROS 2019");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 500, ALTURA_TELA - 145, ALLEGRO_ALIGN_RIGHT, " UEL - Universidade Estadual de Londrina");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 644, ALTURA_TELA - 125, ALLEGRO_ALIGN_RIGHT, "Ciencia da Computacao    ");
     al_draw_textf(FonteMenu5, al_map_rgb(255, 255, 255), LARGURA_TELA - 605, ALTURA_TELA - 105, ALLEGRO_ALIGN_RIGHT, "Projeto de jogo - Programacao");
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

void drawSecundario(ALLEGRO_FONT* FonteFrase, ALLEGRO_FONT* FonteFraseTachado, ALLEGRO_FONT* FontePontos3, ALLEGRO_FONT* FontePontos2,
                     ALLEGRO_BITMAP* fundoMenu, ALLEGRO_BITMAP* invasor1, ALLEGRO_BITMAP* invasor2, ALLEGRO_BITMAP* invasor3,
                     ALLEGRO_BITMAP* invasor4, const int LARGURA_TELA, const int ALTURA_TELA, int z, int x, int y){
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

     al_draw_textf(fonteSpace,al_map_rgb(0, 255, 255),LARGURA/2-150,z+450,ALLEGRO_ALIGN_LEFT,"press SPACE to go to the game");

}

void drawGameOver(ALLEGRO_FONT* FonteMenu2, ALLEGRO_FONT*FonteMenu4, ALLEGRO_FONT* fonteOpcoes, ALLEGRO_BITMAP* fundoMenu,
                  const int LARGURA_TELA, const int ALTURA_TELA, int lugar[5], int y ){
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

     al_draw_text(fonteOpcoes, al_map_rgb(13 + 173 * mudarOpcao, 196 + 98 * mudarOpcao, 152 + 52 * mudarOpcao), LARGURA_TELA/ 2 - 60, ALTURA_TELA - 90, ALLEGRO_ALIGN_LEFT, " EXIT  ");
     al_draw_text(fonteOpcoes, al_map_rgb(186 - 173 * mudarOpcao, 294 - 98 * mudarOpcao, 204 - 52 * mudarOpcao), LARGURA_TELA/ 2 - 70, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT, " AGAIN ");

}

	struct tipoInvasor_mov{
          int lin;
		int col;
		int tiro_lin;
		int tiro_col;
	}invasor_mov;
	struct tipoNave{
		int x;
		int y;
		int yLaser;
		int xLaser;
		int vidas;
	}nave;

