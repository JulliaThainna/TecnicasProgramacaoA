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

//bibliotecas do jogo
#include  "INICIA_ALLEGRO_VARIAVEIS/INICIA_ALLEGRO_VARIAVEIS.h"
#include  "INICIA_ALLEGRO_VARIAVEIS/VARIAVEIS.h"
#include "GALAXIAN_FUNCOES\FUNCAO_JOGO.c"
#include "GALAXIAN_FUNCOES\GALAXIAN_FUNCOES.c"

#define FPS 60

const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;
enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };


int inicializa_allegro(void)
{
     al_init();

     al_init_image_addon();

     al_install_audio();
     al_init_acodec_addon();
     al_reserve_samples(5);

     al_init_font_addon ();
     al_init_ttf_addon ();

     al_install_keyboard();
}

int gameOver(ALLEGRO_DISPLAY** JANELA, ALLEGRO_FONT* FonteGeral_1,const int ALTURA_TELA, const int LARGURA_TELA, ALLEGRO_FONT* FonteGeral_2, int primeiro,
             int segundo, int terceiro, int quarto, int quinto, int pontos_nave, int y, int x){
          enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
          al_init();
          al_init_image_addon();
          al_install_audio();
          al_init_acodec_addon();
          al_reserve_samples(5);
          al_init_font_addon ();
          al_init_ttf_addon ();
          al_install_keyboard();

          ALLEGRO_BITMAP* fundoMenu = NULL;
          ALLEGRO_FONT* fonteGO1 = NULL;
          ALLEGRO_FONT* fonteGO4 = NULL;
          ALLEGRO_EVENT_QUEUE* gameover_eventos = NULL;
          ALLEGRO_TIMER* timer = NULL;

          fundoMenu = al_load_bitmap("Imagens//fundo_secundario.png");
          fonteGO1 = al_load_font ("Fontes//FonteMenu1.ttf",12,0);
          fonteGO4 = al_load_font ("Fontes//hackerchaos.otf",72,0);
          gameover_eventos = al_create_event_queue();

          int MudarOpcao, OPCAO;
          bool EXIT = false, MOVIMENTO = true, game_over = true, FecharJanela = false;

          al_register_event_source(gameover_eventos, al_get_display_event_source(*JANELA));
          al_register_event_source(gameover_eventos, al_get_keyboard_event_source());
          al_register_event_source(gameover_eventos, al_get_timer_event_source(timer));

          al_start_timer(timer);

          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(fundoMenu,0,0,0);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+90,ALLEGRO_ALIGN_CENTER,"SCORE: %d", pontos_nave);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+120,ALLEGRO_ALIGN_CENTER,"1 Lugar: %d", primeiro);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+140,ALLEGRO_ALIGN_CENTER,"2 Lugar: %d", segundo);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+160,ALLEGRO_ALIGN_CENTER,"3 Lugar: %d", terceiro);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+180,ALLEGRO_ALIGN_CENTER,"4 Lugar: %d", quarto);
          al_draw_textf(fonteGO1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+200,ALLEGRO_ALIGN_CENTER,"5 Lugar: %d", quinto);

          al_draw_textf(FonteGeral_1, al_map_rgb(255,255,255),LARGURA_TELA/2,y-100,ALLEGRO_ALIGN_CENTER,"E E E E E E ");
          al_draw_textf(FonteGeral_1, al_map_rgb(255,255,255),LARGURA_TELA/2,y+50,ALLEGRO_ALIGN_CENTER,"J J J J J J ");

          al_draw_text(FonteGeral_2,al_map_rgb(13, 196, 152),LARGURA_TELA/2-50,ALTURA_TELA-100, ALLEGRO_ALIGN_LEFT,"AGAIN");
          al_draw_text(FonteGeral_2,al_map_rgb(13,196,152),LARGURA_TELA/2-50,ALTURA_TELA-50, ALLEGRO_ALIGN_LEFT,"EXIT");


          ALLEGRO_EVENT GAMEOVER;
          al_wait_for_event(gameover_eventos, &GAMEOVER);


          if (GAMEOVER.type == ALLEGRO_EVENT_KEY_DOWN){
               switch (GAMEOVER.keyboard.keycode){
               case ALLEGRO_KEY_UP:
                    MudarOpcao = 0;
                    if (OPCAO > 0){
                         OPCAO--;
                    }
                    break;
               case ALLEGRO_KEY_DOWN:
                    MudarOpcao = 1;
                    if (OPCAO < 2){
                         OPCAO++;
                    }
                    break;
               case ALLEGRO_KEY_ENTER:
                    if (OPCAO == 0){
                         game_over = false;
                         //EXIT = true;
                    }
                    else {
                         EXIT = true;
                    }
                    break;
               }
          }

          if (OPCAO == 0){
               al_draw_text(FonteGeral_2,al_map_rgb(186, 294, 204),LARGURA_TELA/2-50,ALTURA_TELA-100, ALLEGRO_ALIGN_LEFT,"AGAIN");
               al_draw_text(FonteGeral_2,al_map_rgb(13, 196, 152),LARGURA_TELA/2-50,ALTURA_TELA-50, ALLEGRO_ALIGN_LEFT,"EXIT");
          }
          else if (OPCAO == 1){
               al_draw_text(FonteGeral_2,al_map_rgb(13, 196, 152),LARGURA_TELA/2-50,ALTURA_TELA-100,ALLEGRO_ALIGN_LEFT,"AGAIN");
               al_draw_text(FonteGeral_2,al_map_rgb(186, 294, 204),LARGURA_TELA/2-50,ALTURA_TELA-50, ALLEGRO_ALIGN_LEFT,"EXIT");
          }

          if (GAMEOVER.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
               FecharJanela = true;
               EXIT = true;
          }


          //mecânica de movimento dos aliens na tela do game over
          if (MOVIMENTO == true){
			x = x + 1;
		}
		if (x > LARGURA_TELA){
               x = 500;
               x = x - 400;
		}
          al_draw_textf(fonteGO4, al_map_rgb(255,255,255),x,y-30,ALLEGRO_ALIGN_CENTER,"GAME OVER");


        if (GAMEOVER.type == ALLEGRO_EVENT_TIMER){
               al_flip_display();
          }

}



int main()
{
    inicializa_allegro();


    JANELA = al_create_display(LARGURA_TELA, ALTURA_TELA);

    //eventos
    TelaJogo = al_create_event_queue();

     //imagens
     LASER = al_load_bitmap("Imagens//laser.png");
     NAVE = al_load_bitmap("Imagens//nave.png");
     invasor = al_load_bitmap("Imagens//invasor.png");
     fundo = al_load_bitmap("Imagens//fundo.png");
     tiro = al_load_bitmap("Imagens//projetil.bmp");
     vida = al_load_bitmap("Imagens//vida.png");
     FundoMenu = al_load_bitmap("Imagens//fundo_secundario.png");
     //explosao =  al_load_bitmap("explosao.png");

     //fontes
     FonteMenu1 = al_load_font ("Fontes//FonteMenu1.ttf",9,0);
     FonteGeral_1 = al_load_font ("Fontes//FonteMenu2.ttf",60,0); //era antes fontemenu 2
     FonteGeral_2 = al_load_font ("Fontes//FonteMenu1.ttf",20,0); //era antes fontemenu 3
     FonteGO1 = al_load_font ("Fontes//FonteMenu1.ttf",12,0);
     //FonteGO2 = al_load_font ("FonteMenu2.ttf",60,0);
     //FonteGO3 = al_load_font ("FonteMenu1.ttf",20,0);
     FonteGO4 = al_load_font ("Fontes//hackerchaos.otf",72,0);
     //FonteMenuPontos = al_load_font ("Sunset Boulevard.otf",35,0);
     //FonteMenu2 = al_load_font ("FonteMenu2.ttf",60,0);
     //FonteMenu3 = al_load_font ("FonteMenu1.ttf",20,0);
     //FonteMenu4 = al_load_font ("FonteMenu1.ttf",20,0);
     //FonteFrase = al_load_font ("Interferencias.otf",25,0);
     FontePontos = al_load_font("Fontes//FonteMenu1.ttf", 14, 0);

     //audios
     SomPrincipal = al_load_sample("Sons//MusicaJogo.ogg");
     al_play_sample(SomPrincipal, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	SHOOT = al_load_sample ("Sons//LaserEffect.ogg");

     TimerFPS = al_create_timer(1.0 / FPS);


        //!EVENTOS
        al_register_event_source(TelaJogo, al_get_display_event_source(JANELA)); //registra a janela que vai ser aberta nos eventos
        al_register_event_source(TelaJogo, al_get_keyboard_event_source()); //regristra o teclado nos eventos
        al_register_event_source(TelaJogo, al_get_timer_event_source(TimerFPS)); //registra o FPS nos eventos
        al_start_timer(TimerFPS); //inicia o timer de FPS

        srand(time(NULL));

        inicializar_matriz_invisivel(matriz_invisivel);
        //!VARIÁVEIS P/ O INVASOR QUE SE MOVIMENTA
            invasor_mov.lin = ALTURA_TELA;
            invasor_mov.tiro_lin = ALTURA_TELA;
            nave.x = 350;
            nave.y = 500;
            nave.yLaser = 497;
            nave.xLaser = nave.x;
            nave.vidas = 3;
            FILE* arquivo;
			arquivo = fopen("score.txt", "r");
			int i;
            for (i = 0; i < 5; i++)
			{
				fscanf(arquivo, "%d\n", &score.lugar[i]);
			}
			fclose(arquivo);



    //!INÍCIO DO JOGO
    //if(game_over == false)
   // {
    while(!game_over)
    {
        /*while (!ComecarJogo)
        {
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(FundoMenu,0,0,0);
          ALLEGRO_EVENT menupontos;


          al_wait_for_event(TELAPONTOS,&menupontos);

          drawfrases(Fonte3, Fonte4, FonteFrase, FonteGeral_3, FonteMenuPontos,
          LARGURA, ALTURA, X, Y);

        }*/




        al_draw_bitmap(fundo,0,0,0);
        al_draw_textf(FontePontos, al_map_rgb(255,255,255),LARGURA_TELA/2,20,ALLEGRO_ALIGN_CENTER,"SCORE: %d", pontos_nave);
        int i=0,j=0;

        //!DESENHANDO VIDA DO JOGADOR
            for(i=0;i<nave.vidas;i++)
            {
                al_draw_bitmap(vida,LARGURA_TELA-300+c,-50,0);
                c = c+50;
            }
            c = 50;


        //!IMPRIMINDO TIRO DOS INVASORES
            al_draw_bitmap(tiro,tiro_col,tiro_lin,0);
            tiro_lin = tiro_lin+6;

        //!INVASOR EM MOVIMENTO

            if(invasor_mov.lin<ALTURA_TELA){    // caso o invasor ainda não tenha chegado ao fim da tela
                invasor_mov.lin = invasor_mov.lin+3;
            }
             if(invasor_mov.lin>ALTURA_TELA){  // caso o invasor chegue ao fim da tela sem ser destruído
                invasor_mov.lin = ALTURA_TELA;
                repos_inimigo = true;
             }

            al_draw_bitmap(invasor,invasor_mov.col,invasor_mov.lin,0);// desenhando invasor em movimento

            // tiro do invasor em movimento
            if(invasor_mov.tiro_lin >= ALTURA_TELA && invasor_mov.lin <= 300 )// se o tiro chegou no final da tela, ele retorna para o invasor
            {
                invasor_mov.tiro_lin = invasor_mov.lin+25;
                invasor_mov.tiro_col = invasor_mov.col+25;
            }
            al_draw_bitmap(tiro,invasor_mov.tiro_col,invasor_mov.tiro_lin,0); // desenhando tiro do invasor em movimento
            invasor_mov.tiro_lin = invasor_mov.tiro_lin+5;


            // colisão do tiro do jogador com o invasor em movimento
            if(colisao_invasor(nave.xLaser, nave.yLaser, invasor_mov.col,invasor_mov.lin) && disparo == true)
                {

                    invasor_mov.lin = ALTURA_TELA;
                    nave.xLaser = nave.x; // retorna o laser p/ perto da nave
                    nave.yLaser = 497;
                    qtd_inimigos--;
                    pontos_nave = pontos_nave +100;
                    disparo = false;

                }

        //!COLISÃO DOS TIROS E DOS INVASORES COM O JOGADOR

            // verifica se a posição do TIRO DOS INVASORES "normais" é igual a da NAVE DO JOGADOR
                    if(colisao_jogador(tiro_col , tiro_lin , nave.x , nave.y))
                        {
                            nave.vidas--; //diminui uma vida
                            tiro_lin = ALTURA_TELA;
                        }


            // verifica se a posição do TIRO DO INVASOR EM MOVIMENTO é igual a da NAVE DO JOGADOR
                    if(colisao_jogador(invasor_mov.tiro_col, invasor_mov.tiro_lin, nave.x, nave.y))
                        {
                            nave.vidas--; //diminui uma vida
                            invasor_mov.tiro_lin = ALTURA_TELA;
                        }


            // verifica se a posição do INVASOR EM MOVIMENTO é igual a da NAVE DO JOGADOR
                    if( colisao_jogador(invasor_mov.col, invasor_mov.lin, nave.x, nave.y) )
                        {
                            nave.vidas--; //diminui uma vida
                            invasor_mov.lin= ALTURA_TELA;

                        }


        //!IMPRIMINDO INVASORES
            inim_lin = 50;
            i = j = 0;

            while(i<4)
            {
                  while(j<9)
                  {

                        if(matriz_invisivel[i][j] == 1)// verifica se o inimigo está vivo
                        {

                                //!COLISÃO TIRO DO JOGADOR COM O INVASOR
                                    if(colisao_invasor(nave.xLaser, nave.yLaser, inim_col, inim_lin))
                                    {
                                        //al_draw_bitmap(explosao,inim_col,inim_lin,0);//imprimindo explosão
                                        matriz_invisivel[i][j] = 0;
                                        nave.xLaser = nave.x; // retorna o laser p/ perto da nave
                                        nave.yLaser = 497;
                                        pontos_nave = pontos_nave + 30;
                                        disparo = false;
                                    }

                                //!RELACIONADO AO TIRO DO INVASOR
                                    if(tiro_lin >= ALTURA_TELA && ( inim_col > nave.x-50 && inim_col < nave.x-10 )  && i != guard_i && j != guard_j ) // se o tiro tiver  chegado ao fim da tela e se a col do inimigo for igual à do jogador
                                    {
                                        tiro_lin = inim_lin+25;
                                        tiro_col = inim_col+25;
                                    }


                                //!DEFININDO O INVASOR EM MOVIMENTO
                                    if(invasor_mov.lin == ALTURA_TELA && (inim_col > nave.x && inim_col < nave.x + 50) )
                                        // se for DESTRUÍDO ou chegou ao FIM DA TELA e se a coluna for a mesma da nave do jogador
                                    {
                                        matriz_invisivel[i][j] = 0;  // faz com que o inimigo não seja mais desenhado na sua posição original
                                        invasor_mov.lin = inim_lin;      // determina a posição em que ele será desenhado
                                        invasor_mov.col = inim_col;
                                        invasor_mov.tiro_lin = invasor_mov.lin; //determina a posição do tiro
                                        invasor_mov.tiro_col = invasor_mov.col+25;
                                        guard_i = i; //guardam a posição original do invasor na matriz
                                        guard_j = j;

                                    }
                                     //reposicionando invasor caso ele NÃO SEJA DESTRUÍDO
                                        if(repos_inimigo == true && invasor_mov.lin == ALTURA_TELA )
                                        {
                                            matriz_invisivel[guard_i][guard_j] = 1;  //a posição original do invasor recebe 1
                                            repos_inimigo = false;
                                        }
                        }


                                //!POSICIONANDO E DESENHANDO INIMIGOS
                                    if( j==8 )  // aumenta lin e diminui col p/ "quebrar a linha"
                                    {
                                        if(matriz_invisivel[i][j] == 1) // verifica se o inimigo está vivo
                                        {
                                            al_draw_bitmap(invasor,inim_col,inim_lin,0);
                                        }
                                        inim_lin = inim_lin+50;
                                        inim_col = inim_col - 400;   // o valor a ser subtraído é sempre 5*(o número de colunas-1)
                                    }

                                    else if( j!=8 ) // apenas aumenta inim_col p/ dar espaçamento entre os inimigos
                                    {
                                        if(matriz_invisivel[i][j] == 1)// verifica se o inimigo está vivo
                                        {
                                            al_draw_bitmap(invasor,inim_col,inim_lin,0);
                                        }
                                        inim_col = inim_col+50;
                                    }

                    j++;
                 }
                i++;
                j=0;
            }


    //!ALTERANDO DIREÇÃO DO MOVIMENTO DOS  INVASORES

        // apenas p/ dar o aspecto dos inimigos se moverem em "passos"
            ci++;
            passo = 0;
            if (ci > 65)  //caso "ci" chegue em 65
            {
                passo = 1;
                ci = 0;
            }

        if(direcao_invasores(inim_col) == 1){
            dir = 1;}

         if(direcao_invasores(inim_col) == 0){
            dir = 0;}

         if(dir==1){
            inim_col = inim_col - passo*10;}

         if(dir==0){
            inim_col = inim_col + passo*10;}


    //!MOVIMENTAÇÃO DO JOGADOR

        ALLEGRO_EVENT evento; //começa um evento, pega um evento da fila (quando um estiver disponível) e coloca ele na variável evento.
		al_wait_for_event(TelaJogo, &evento);//remove o primeiro item da fila de eventos e coloca na variável evento.

		//se alguma tecla estiver pressionada
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (evento.keyboard.keycode) { //casos para a movimentação da nave (dados do teclado)
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			}
		}

		//se alguma tecla estiver não pressionada
		if (evento.type == ALLEGRO_EVENT_KEY_UP) {
			switch (evento.keyboard.keycode) { //para a movimentação da nave
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		//para conseguir fechar a janela do jogo
		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			FecharJanela = true;
		}

		//condições de movimentação e limites de tela da nave
		if (nave.x > 0) {
			nave.x -= keys[LEFT]*4 ;
		}
		if (nave.x < LARGURA_TELA -57 ) {
			nave.x += keys[RIGHT]*4;
		}



		//condições de movimentação e limites de tela do laser
		if (keys[SPACE] == true && disparo == false ) {		//Aqui a gente vê se o espaço ta apertado e se ja tem algum laser na tela. Se tiver, ele não solta outro
			disparo = true;
			nave.xLaser = nave.x;
		}
		if (disparo == true) {					//Se ja tiver um laser na tela essa parte verifica se ele ja acertou um inimigo ou saiu da tela.
				if (nave.yLaser > 0) {
					nave.yLaser -= disparo * 8;
				}
				else if(nave.yLaser <= 0 ){		//Caso alguma dessas condições sejam satisfeitas, ele seta o tiro como falso. Mais tarde a gente usa isso pra desenhar o laser na mesma posição da nave, ou não.
					disparo = false;
					nave.xLaser = nave.x;
					nave.yLaser = 493;
				}
		}

		if (disparo == true) {		//Se estiver atirando renderiza o laser movimentando pela tela
			al_draw_bitmap(LASER, nave.xLaser + 19, nave.yLaser, 0);
		}
		else {					//Se for falso, desenha o laser atras da nave
			al_draw_bitmap(LASER, nave.x + 19, nave.yLaser, 0);
		}
		al_draw_bitmap(NAVE, nave.x, nave.y, 0); //desenha a nave na tela



    //!CASO TODOS OS INIMIGOS TENHA SIDO ELIMINADOS, ELES REAPARECERÃO
		cont = 0;
		int a,b;
		for(a=0;a<4;a++)
        {
            for(b=0;b<9;b++)
            {
                if(matriz_invisivel[a][b]==0)        //verifica se todos estão mortos
                {
                    cont++;
                }
            }
        }

        if(cont == 36 && invasor_mov.lin >= ALTURA_TELA) //caso todos estejam mortos
        {
             int a,b;
            for(a=0;a<4;a++)
            {
                for(b=0;b<9;b++)
                {
                    if(matriz_invisivel[a][b]==0)
                    {
                        matriz_invisivel[a][b]=1; //serão adicionados novamente
                    }
                }
            }

        }

        if(pontos_nave>=5000)
        {
            nave.vidas++;
        }




        //verifica se o jogador tem vidas, se nao tiver irá para game_over
        if(nave.vidas<=0)
        {
            game_over = true;
        }


        al_flip_display();


    }

    SCORE = pontos_nave;

        if(SCORE>=score.lugar[4])
        {
             score.lugar[4] = SCORE;
        }
        if(SCORE>=score.lugar[3])
         {
			 score.lugar[4] = score.lugar[3];
             score.lugar[3] = SCORE;
         }
        if (SCORE >= score.lugar[2])
		{
			 score.lugar[3] = score.lugar[2];
			 score.lugar[2] = SCORE;
		}
        if(SCORE>=score.lugar[1])
		{
			score.lugar[2] = score.lugar[1];
			score.lugar[1] = SCORE;
		}
        if (SCORE >= score.lugar[0])
		{
			score.lugar[1] = score.lugar[0];
			score.lugar[0] = SCORE;
		}

        int primeiro = score.lugar[0];
        int segundo = score.lugar[1];
        int terceiro = score.lugar[2];
        int quarto = score.lugar[3];
        int quinto = score.lugar[4];

	arquivo = fopen("score.txt", "w");
	int i;
	for (i = 0; i < 5; i++)
	{
		fprintf(arquivo, "%d\n", score.lugar[i]);
	}
	fclose(arquivo);
     if(game_over==true)
    {
        while (!EXIT)
        {
        gameOver( &JANELA, FonteGeral_1, ALTURA_TELA, LARGURA_TELA, FonteGeral_2, primeiro,
        segundo, terceiro, quarto, quinto, pontos_nave, y, x);
        }
    }


     al_destroy_display(JANELA);



    return 0;
}









