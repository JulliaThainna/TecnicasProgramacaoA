///BIBLIOTECAS PADROES
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

///BIBLIOTECAS ALLEGROS
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///BIBLIOTECAS DOS JOGO
#include "GALAXIAN_FUNCOES.c"

///FPS DO JOGO
#define FPS 100

enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};

int main()
{
     ///"INSTALANDO" OS ITENS IMPORTADOS DA ALLEGRO
	al_init();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	///DECLARACAO DAS MACRO
     ALLEGRO_DISPLAY *JANELA = NULL;
     ALLEGRO_TIMER *TimerFPS = NULL;
     //Fila de eventos
     ALLEGRO_EVENT_QUEUE *filaJogo = NULL;
     //Imagens
     ALLEGRO_BITMAP *NAVE = NULL;
     ALLEGRO_BITMAP *LASER = NULL;
     ALLEGRO_BITMAP *invasor1 = NULL;
     ALLEGRO_BITMAP *invasor2 = NULL;
     ALLEGRO_BITMAP *invasor3 = NULL;
     ALLEGRO_BITMAP *invasor4 = NULL;
     ALLEGRO_BITMAP *fundo = NULL;
     ALLEGRO_BITMAP *tiro = NULL;
     ALLEGRO_BITMAP *vida = NULL;
     ALLEGRO_BITMAP *fundoMenu = NULL;
     ALLEGRO_BITMAP *FundoMenuPontos = NULL;
     ALLEGRO_BITMAP *LogoMenu = NULL;
     //Fontes
     ALLEGRO_FONT *FonteFrase = NULL;
     ALLEGRO_FONT *fonteSpace = NULL;
     ALLEGRO_FONT *fonteOpcoes = NULL;
     ALLEGRO_FONT *FontePontos = NULL;
     ALLEGRO_FONT *FontePontos2 = NULL;
     ALLEGRO_FONT *FontePontos3 = NULL;
     ALLEGRO_FONT *FonteMenu1 = NULL;
     ALLEGRO_FONT *FonteMenu2 = NULL;
     ALLEGRO_FONT *FonteMenu3 = NULL;
     ALLEGRO_FONT *FonteMenu4 = NULL;
     ALLEGRO_FONT *FonteMenu5 = NULL;
     ALLEGRO_FONT *fonteGO1 = NULL;
     ALLEGRO_FONT *fonteGO4 = NULL;
     ALLEGRO_FONT *FonteFraseTachado = NULL;
     ALLEGRO_FONT *Fonte3 = NULL;
     //Audios
     ALLEGRO_AUDIO_STREAM *SomMenu = NULL;
     ALLEGRO_AUDIO_STREAM *MusicaJogo = NULL;
     ALLEGRO_SAMPLE *Laser = NULL;
	//Arquivos
	FILE* arquivo;

	///CARREGAMENTO DAS MACRO
	JANELA = al_create_display(LARGURA_TELA, ALTURA_TELA);
	//Fila de eventos
	filaJogo = al_create_event_queue();
	//Imagens
     LASER = al_load_bitmap("Imagens//laser.png");
	NAVE = al_load_bitmap("Imagens//nave.png");
	invasor1 = al_load_bitmap("Imagens//invasor1.png");
	invasor2 = al_load_bitmap("Imagens//invasor2.png");
	invasor3 = al_load_bitmap("Imagens//invasor3.png");
	invasor4 = al_load_bitmap("Imagens//invasor4.png");
	fundo = al_load_bitmap("Imagens//fundo.png");
	tiro = al_load_bitmap("Imagens//projetil.bmp");
	vida = al_load_bitmap("Imagens//vida.png");
	fundoMenu = al_load_bitmap("Imagens//fundo_secundario.png");
     LogoMenu = al_load_bitmap("Imagens//logoteste.png");
	//Fontes
	FonteMenu2 = al_load_font("Fontes//FonteMenu2.ttf", 60, 0);
	FonteMenu4 = al_load_font("Fontes//FonteMenu2.ttf", 80, 0);
	FonteMenu5 = al_load_font("Fontes//fonte5.ttf", 14, 0);
	fonteGO4 = al_load_font("Fontes//hackerchaos.otf", 85, 0);
	FontePontos = al_load_font("Fontes//FonteMenu1.ttf", 14, 0);
	FontePontos2 = al_load_font("Fontes//fonte-3.ttf",20,0);
	FontePontos3 = al_load_font("Fontes//fonte-4.ttf",25,0);
	FonteFrase = al_load_font("Fontes//Sunset Boulevard.otf", 50, 0);
	fonteSpace = al_load_font("Fontes//Sunset Boulevard.otf", 30, 0);
	fonteOpcoes = al_load_font("Fontes//Sunset Boulevard.otf", 70, 0);
	FonteFraseTachado = al_load_font("Fontes//fonte riscada 2.ttf", 30, 0);
	//Audios
     SomMenu = al_load_audio_stream("Sons//SomMenu.ogg",4,1024);
     MusicaJogo = al_load_audio_stream("Sons//MusicaJogo.ogg",4,1024);
     Laser = al_load_sample("Sons//LaserEffect.ogg");

     ///VARIAVEIS E CHAMADAS DA STRUCT
     //Variaveis para os invasores parados
     int matriz_invisivel[5][7];
     inicializar_matriz_invisivel(matriz_invisivel);
     /*criando uma matriz que servira apenas para verificar se um invasor está vivo para desenhá-lo ou nao na tela
          - caso vivo, sua posicao tera valor 1
          - caso  morto ou em movimento, sua posicao tera valor 0*/

     //Coluna e linha iniciais dos inimigos
     inv invasores;
     invasores.inim_col = 200;
     invasores.inim_lin = 50;
     invasores.tiro_lin = ALTURA_TELA;
     invasores.tiro_col;
     invasores.dir = 0;  /*Direcao do movimento dos inimigos -> 0 = direita   1= esquerda*/
     invasores.passo = 0;
     int ci = 0,
     qtd_inimigos = 36;

     //Variaveis para os invasores em movimento
     inv_m invasor_mov;
     invasor_mov.lin = ALTURA_TELA;
     invasor_mov.tiro_lin = ALTURA_TELA;
     invasor_mov.repos_inimigo = false;

     //Variaveis para a nave do jogador
     player nave;
     nave.x = 350;
     nave.y = 500;
     nave.yLaser = 497;
     nave.xLaser = nave.x;
     nave.vidas = 3;
     nave.disparo = false;
     nave.pontos = 0;

     int pontos_nave = 0, opcao = 0, lugar [5], c = 30, direction = 0, x = 340, y = 250, z = 250, xnave = 340, i = 0, j = 0;

     //Variaveis booleanas (multiplas utilidades)
     bool keys[5] = {false,false,false,false,false}, secundario = false, movimento = true, jaSomou = false, menu = true,
     gameOver = false, mudarOpcao = false, fechar = false, jogo = false, ComecarJogo = false, disparo = false;

     ///DECLARA A QUANTIDADE DE FRAMES POR SEGUNDO
	TimerFPS = al_create_timer(1.0 / FPS);

	///FILA DE EVENTOS
	al_register_event_source(filaJogo, al_get_display_event_source(JANELA)); /*registra a janela que vai ser aberta nos eventos*/
	al_register_event_source(filaJogo, al_get_keyboard_event_source()); /*regristra o teclado nos eventos*/
	al_register_event_source(filaJogo, al_get_timer_event_source(TimerFPS)); /*registra o FPS nos eventos*/

	///PARA ABRIR O ARQUIVO DE PONTUACAO E SEMPRE LER AS PONTUACOES ANTERIORES
	arquivo = fopen("score.txt", "r");
	int a;
	for(a = 0; a < 5; a++)
	{
		fscanf(arquivo, "%d\n", &lugar[a]);
	}
	fclose(arquivo);

	///DEFINE OS SONS E O FPS
     al_attach_audio_stream_to_mixer(SomMenu, al_get_default_mixer());
     al_set_audio_stream_playmode(SomMenu, ALLEGRO_PLAYMODE_LOOP);
	al_start_timer(TimerFPS);     /*Inicia o timer de FPS*/


	///O JOGO INTEIRO ESTA DENTRO DESSE WHILE(!fechar) E E DIVIDIDO EM 4 PARTES (menu, menu secundario, jogo e game over)
	while(!fechar)
	{
	     ///While do MENU
          while(menu)
		{
               drawMenu(FonteMenu2, FonteMenu5, fundoMenu, LogoMenu, LARGURA_TELA, ALTURA_TELA, xnave, x, y); /*Funcao para "desenhar" o
                                                                                                              menu*/
               //Aqui comeca um novo evento
			ALLEGRO_EVENT eventoMenu;
			al_wait_for_event(filaJogo, &eventoMenu);

			///CONDICOES PARA A ESCOLHA DO "START/EXIT"
			if(eventoMenu.type == ALLEGRO_EVENT_KEY_DOWN)    /*Se uma tecla estiver pressionada*/
                {
				switch(eventoMenu.keyboard.keycode)    /*Escolhe o teclado*/
                    {
				case ALLEGRO_KEY_UP:
					opcao = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					opcao = 1;
					break;
				case ALLEGRO_KEY_ENTER:  /*Se o enter for pressionado*/
					if(opcao == 0)     /*Se a opcao for == 0, entao o menu e fechado e o secundario aberto*/
                         {
						menu = false;
						secundario = true;
					}
					else /*Se a opcao for == 1, entao o menu o menu e fechado e o while(!fechar) se torna verdadeiro*/
                         {
						menu = false;
						fechar = true;
					}
					break;
                    }
			}

			///CONDICOES PARA MUDAR O REALCE DO "START/EXIT"
			if(opcao == 0)
			{
				al_draw_text(fonteOpcoes, al_map_rgb(186, 294, 204), LARGURA_TELA - 200, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT,
                                ">START");
				al_draw_text(fonteOpcoes, al_map_rgb(13, 196, 152), LARGURA_TELA - 200, ALTURA_TELA - 100, ALLEGRO_ALIGN_LEFT,
                                " EXIT");
			}
			else
			{
				al_draw_text(fonteOpcoes, al_map_rgb(13, 196, 152), LARGURA_TELA - 200, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT,
                                 " START");
				al_draw_text(fonteOpcoes, al_map_rgb(186, 294, 204), LARGURA_TELA - 200, ALTURA_TELA - 100, ALLEGRO_ALIGN_LEFT,
                                 ">EXIT");
			}

			///MECÂNICA DE MOVIMENTO DOS INVASORES NA TELA DO MENU (Lembrando que tanto no menu quanto no game over, eles nao sao
               ///bitmaps e sim fontes!)
			if(movimento == true)
			{
                    if(xnave == 350)
                    {
                         direction = 0;
                    }
                    if(xnave == LARGURA_TELA-300)
                    {
                         direction = 1;
                    }
				if(direction == 0)
                    {
                         xnave++;
                         x++;
				}
				if(direction == 1)
				{
                         xnave--;
                         x--;
				}

			}

			///CONDICAO PARA O JOGO SER FECHADO
			if(eventoMenu.type == ALLEGRO_EVENT_DISPLAY_CLOSE)    /*Caso for clicado o "X" na janela, o menu se torna falso e o
                                                                      while (!fechar) verdadeiro*/
               {
				menu = false;
				fechar = true;
			}

			///ATUALIZA A TELA A CADA FRAME
			if(eventoMenu.type == ALLEGRO_EVENT_TIMER)
			{
				al_flip_display();
			}
		}


          ///While do MENU SECUNDARIO
		while(secundario)
		{
               drawSecundario(FonteFrase, FonteFraseTachado, FontePontos3, FontePontos2, fundoMenu, invasor1, invasor2, invasor3,
               fonteSpace, invasor4, LARGURA_TELA, ALTURA_TELA, z, x, y);   /*Funcao para "desenhar" o menu secundario*/

               ALLEGRO_EVENT eventoSecundario;    /*Aqui comeca um novo evento*/
			al_wait_for_event(filaJogo, &eventoSecundario);

               ///CONDICOES PARA QUANDO A TECLA FOR ESPACO FOR PRESSIONADA, ONDE HA MUDANCAS NAS JANELAS ABERTAS E SONS
			if(eventoSecundario.type == ALLEGRO_EVENT_KEY_DOWN)   /*Se alguma tecla for pressionada*/
			{
				switch(eventoSecundario.keyboard.keycode)    /*Escolher o teclado*/
				{
                         case ALLEGRO_KEY_SPACE:       /*Caso esteja seja a tecla espaco o jogo abre, o menu secundario
                                                       fecha, e o som do menu para, comecando a tocar o som do jogo*/
                              jogo = true;
                              al_set_audio_stream_playing(SomMenu,false);
                              al_attach_audio_stream_to_mixer(MusicaJogo, al_get_default_mixer());
                              al_set_audio_stream_playmode(MusicaJogo, ALLEGRO_PLAYMODE_LOOP);
                              secundario = false;
                              break;
				}
			}

			///FAZ A MOVIMENTACAO DO "PRESS SPACE TO START"
			if(movimento == true)
               {
                    z++;
                    if(z > ALTURA_TELA - 480)
                    {
                         z = 70;
                    }
               }

               ///CONDICAO PARA O JOGO SER FECHADO
			if(eventoSecundario.type == ALLEGRO_EVENT_DISPLAY_CLOSE)    /*Caso for clicado o "X" na janela, o menu se torna falso e o
                                                                           while (!fechar) verdadeiro*/
               {
				secundario = false;
				fechar = true;
			}

               ///ATUALIZA A TELA A CADA FRAME
			if(eventoSecundario.type == ALLEGRO_EVENT_TIMER)
               {
				al_flip_display();
			}
		}


		///While do JOGO
		while(jogo)
		{

          ///ANDRE
          ///INIMIGOS (INVASORES)

               pontos_nave = nave.pontos;    /*Pontuacao do jogador*/

			al_draw_bitmap(fundo, 0, 0, 0);
			al_draw_textf(FontePontos, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d",
                             pontos_nave);   /*Imprime a pontuacao do jogador na tela do jogo*/

			//Imprime a vida do jogador
			for(i = 0; i < nave.vidas; i++)
			{
				al_draw_bitmap(vida, LARGURA_TELA - 300 + c, -50, 0);
				c = c + 50;
			}
			c = 50;

               //Imprime os tiros do invasor parado
               al_draw_bitmap(tiro,invasores.tiro_col,invasores.tiro_lin,0);
               invasores.tiro_lin = invasores.tiro_lin+6;

               movimentos_do_invasor_mov(&invasor_mov,matriz_invisivel);   /*Funcao do invasor em movimento*/

               ///DESENHANDO

               //Imprime o tiro do invasor em movimento
               al_draw_bitmap(tiro,invasor_mov.tiro_col,invasor_mov.tiro_lin,0);

               //Imprime o invasor
               switch(invasor_mov.guard_i) /*Definindo qual bitmap sera desenhado*/
               {
                    case 0:
                         al_draw_bitmap(invasor4,invasor_mov.col,invasor_mov.lin,0); /*Desenhando invasor em movimento*/
                         break;
                    case 1:
                         al_draw_bitmap(invasor2,invasor_mov.col,invasor_mov.lin,0); /*Desenhando invasor em movimento*/
                         break;
                    case 2:
                         al_draw_bitmap(invasor1,invasor_mov.col,invasor_mov.lin,0); /*Desenhando invasor em movimento*/
                         break;
                    case 3:
                         al_draw_bitmap(invasor3,invasor_mov.col,invasor_mov.lin,0); /*Desenhando invasor em movimento*/
                         break;
                    case 4:
                         al_draw_bitmap(invasor3,invasor_mov.col,invasor_mov.lin,0); /*Desenhando invasor em movimento*/
                         break;
               }

               //Colisoes
               colisoes(&nave,&invasores,&invasor_mov,matriz_invisivel,&i,&j);  /*Funcao que verifica a colisao*/

			//Imprimindo os invasores
			invasores.inim_lin = 50;
			i = j = 0;

			while(i < 5)
			{
                    while(j < 7)
				{
                         if(matriz_invisivel[i][j] == 1)    /*Verifica se o inimigo esta vivo*/
                         {
                              colisoes(&nave,&invasores,&invasor_mov,matriz_invisivel,&i,&j);  /*Funcao da colisao*/

                              //Relacionando o tiro do invasor com a colisao
                              if(invasores.tiro_lin >= ALTURA_TELA && (invasores.inim_col > nave.x-50 && invasores.inim_col < nave.x-10)
                                 && i != invasor_mov.guard_i && j != invasor_mov.guard_j) /*Se o tiro tiver  chegado ao fim da tela e
                                                                                          se a col do inimigo for igual a do jogador*/
                              {
                                   invasores.tiro_lin = invasores.inim_lin+25;
                                   invasores.tiro_col = invasores.inim_col+25;
                              }

                              //Definindo o invasor em movimento
                              if(invasor_mov.lin == ALTURA_TELA)
                                    {
                                        //Desenha o invasor caso ele ultrapassar a tela ou o "apaga" se ele morrer
                                        if(invasores.inim_col > nave.x && invasores.inim_col <= nave.x + 50)  /*Se for DESTRUIDO ou
                                                                                                              chegou ao FIM DA TELA e
                                                                                                              se a coluna for a mesma
                                                                                                              da nave do jogador*/
                                        {
                                             //Faz com que o invasor nao seja mais desenhado na sua posicao original
                                             matriz_invisivel[i][j] = 0;

                                             //Determina a posicao em que ele sera desenhado
                                             invasor_mov.lin = invasores.inim_lin;
                                             invasor_mov.col = invasores.inim_col;

                                             //Determina a posicao do tiro
                                             invasor_mov.tiro_lin = invasor_mov.lin;
                                             invasor_mov.tiro_col = invasor_mov.col+25;

                                             //Guarda a posicao original do invasor na matriz
                                             invasor_mov.guard_i = i;
                                             invasor_mov.guard_j = j;

                                        }

                                    }

                              }

                              ///POSICIONANDO E DESENHANDO INVASORES(INIMIGOS)
                              if(j == 6)     /*Aumenta lin e diminui col para "quebrar a linha"*/
                              {
                                   if(matriz_invisivel[i][j] == 1)    /*Verifica se o inimigo esta vivo*/
                                   {
                                        //Verifica qual bitmap sera desenhado (por causa dos tipos dos invasores)
                                        switch (i)
                                        {
                                             case 0:
                                                  al_draw_bitmap(invasor4,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 1:
                                                  al_draw_bitmap(invasor2,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 2:
                                                  al_draw_bitmap(invasor1,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 3:
                                                  al_draw_bitmap(invasor3,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 4:
                                                  al_draw_bitmap(invasor3,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                        }

                                   }
                                   invasores.inim_lin = invasores.inim_lin+50;
                                   invasores.inim_col = invasores.inim_col - 420;    /*O valor a ser subtraido e sempre
                                                                                     7vezes(o numero de colunas-1)*/
                              }

                              else if(j != 6) /*Apenas aumenta inim_col para dar espacamento entre os inimigos*/
                              {
                                   if(matriz_invisivel[i][j] == 1)    /*Verifica se o inimigo esta vivo */
                                   {
                                        //Verificando qual bitmap sera desenhado
                                        switch(i)
                                        {
                                             case 0:
                                                  al_draw_bitmap(invasor4,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 1:
                                                  al_draw_bitmap(invasor2,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 2:
                                                  al_draw_bitmap(invasor1,invasores.inim_col,invasores.inim_lin,0);
                                                  break;
                                             case 3:
                                                  al_draw_bitmap(invasor3,invasores.inim_col,invasores.inim_lin,0);
                                             case 4:
                                                  al_draw_bitmap(invasor3,invasores.inim_col,invasores.inim_lin,0);

                                        }
                                   }
                                   invasores.inim_col = invasores.inim_col+70;
                              }
                              j++;
                         }
                         i++;
                         j = 0;
                    }


                    ///ALTERANDO DIRECAO DO MOVIMENTO DOS INVASORES
                    ci++;
                    direcao_invasores(&invasores,&ci);

                    ///CASO TODOS OS INIMIGOS TENHA SIDO ELIMINADOS, ELES REAPARECERAO
                    reviver_invasores(matriz_invisivel,&invasor_mov);


               ///JULLIA
               ///MOVIMENTACAO DO JOGADOR

                    ALLEGRO_EVENT eventoJogo;     /*Comeca um eventoJogo, pega um eventoJogo da fila (quando um estiver disponivel)
                                                  e coloca ele na variavel eventoJogo*/
                    al_wait_for_event(filaJogo, &eventoJogo);    /*Remove o primeiro item da fila de eventos e coloca na variavel
                                                                 eventoJogo*/

                    if(eventoJogo.type == ALLEGRO_EVENT_KEY_DOWN) {  /*Se alguma tecla estiver pressionada*/
                         switch(eventoJogo.keyboard.keycode) {  /*Casos para a movimentacao da nave (dados do teclado)*/
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

                    if(eventoJogo.type == ALLEGRO_EVENT_KEY_UP) {    /*Se alguma tecla nao estiver pressionada*/
                         switch(eventoJogo.keyboard.keycode) {       /*Casos para a movimentacao da nave (dados do teclado)*/
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
                    ///Para conseguir fechar a janela do jogo
                    if(eventoJogo.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                         fechar = true;
                         jogo = false;
                    }

                    ///Condicoes de movimentacao e limites de tela da nave
                    if(nave.x > 0) {
                         nave.x -= keys[LEFT] * 4;     /*Linha de comando equivalente a: nave.x = nave.x - (keys left * 4)*/
                    }
                    if(nave.x < LARGURA_TELA - 57) {
                         nave.x += keys[RIGHT] * 4;
                    }

                    ///Condicoes de movimentacaoo e limites de tela do laser
                    if(keys[SPACE] == true && nave.disparo == false) { /*Aqui ve se a tecla espaco esta pressionada e se ja ha
                                                                        algum laser na tela. Se houver, ele nao solta outro*/
                         nave.disparo = true;
                         al_play_sample(Laser,1.0,0.0,1.0, ALLEGRO_PLAYMODE_ONCE,NULL);
                         nave.xLaser = nave.x;
                    }
                    if(nave.disparo == true) {   /*Se ja houver um laser na tela, essa parte verifica se ele ja acertou um inimigo ou
                                                  saiu da tela*/
                         if(nave.yLaser > 0) {
                              nave.yLaser -= nave.disparo * 8;
                         }
                         else if(nave.yLaser <= 0) {	/*Caso alguma dessas condicoes sejam satisfeitas, ele seta o tiro como falso,
                                                       mais tarde usa-se isso pra desenhar o laser na mesma posicao da nave, ou nao*/
                              nave.disparo = false;
                              nave.xLaser = nave.x;
                              nave.yLaser = 493;
                         }
                    }

                    if(nave.disparo == true) {   /*Se estiver atirando renderiza o laser movimentando pela tela*/
                         al_draw_bitmap(LASER, nave.xLaser + 19, nave.yLaser, 0);
                    }
                    else {    /*Se for falso, desenha o laser atras da nave*/
                         al_draw_bitmap(LASER, nave.x + 19, nave.yLaser, 0);
                    }
                    al_draw_bitmap(NAVE, nave.x, nave.y, 0);     /*Desenha a nave na tela*/


               ///TATIANE
               ///SCORE E GAME OVER
                    //Para verificar se a pontuacao chegou a 5000, se sim, o jogador ganha uma vida a mais
                    if(pontos_nave >= 5000 && jaSomou == false)
                    {
                        nave.vidas++;
                        jaSomou = true;
                    }

                    ///CONDICOES PARA VERIFICAR A VIDA E A PONTUACAO DO JOGADOR
                    if(nave.vidas <= 0)     /*Verifica se o jogador tem vidas, se nao tiver ira para game_over*/
                    {
                        if(pontos_nave >= lugar[4])   /*Verifica se a pontuacao do jogador e maior que uma das 5 primeiras*/
                         {
                              lugar[4] = pontos_nave;
                         }
                         if(pontos_nave >= lugar[3])
                         {
                              lugar[4] = lugar[3];
                              lugar[3] = pontos_nave;
                         }
                         if(pontos_nave >= lugar[2])
                         {
                              lugar[3] = lugar[2];
                              lugar[2] = pontos_nave;
                         }
                         if(pontos_nave >= lugar[1])
                         {
                              lugar[2] = lugar[1];
                              lugar[1] = pontos_nave;
                         }
                         if(pontos_nave >= lugar[0])
                         {
                              lugar[1] = lugar[0];
                              lugar[0] = pontos_nave;
                         }
                         //Abre o arquivo de pontos
                         arquivo = fopen("score.txt", "w");

                         for(i = 0; i < 5; i++)  /*Salva as pontuacoes no arquivo de score*/
                         {
                              fprintf(arquivo, "%d\n", lugar[i]);
                         }

                         //Apos fechar o arquivo de pontuacoes, aparece a tela de game over e o jogo fecha
                         fclose(arquivo);
                         gameOver = true;
                         jogo = false;
                    }

                    ///ATUALIZA A TELA A CADA FRAME
                    if(eventoJogo.type == ALLEGRO_EVENT_TIMER) {
                         al_flip_display();
                    }

               }


          ///While do GAME OVER
		while(gameOver)
		{
               gameOverDraw(FontePontos2, FonteMenu4, fundoMenu, LARGURA_TELA, y, lugar, pontos_nave);   /*Funcao que "desenha" a tela
                                                                                                         de game over*/
               //Aqui começa um novo evento
			ALLEGRO_EVENT eventoGameOver;
			al_wait_for_event(filaJogo, &eventoGameOver);

			if(eventoGameOver.type == ALLEGRO_EVENT_KEY_DOWN) /*Se uma tecla estiver pressionada*/
			{
                    switch(eventoGameOver.keyboard.keycode) /*Escolhe um evento do teclado*/
				{
                    //Condicoes para o realce do "AGAIN/EXIT"
				case ALLEGRO_KEY_UP:
					mudarOpcao = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					mudarOpcao = 1;
					break;
				case ALLEGRO_KEY_ENTER: /*Se a tecla enter estiver pressionada, e mudarOpcao for == 0, entao, o jogo volta, o game
                                            over fecha e todas as variaveis do jogo sao resetadas como da primeira vez*/
					if(mudarOpcao == 0)
					{
						jogo = true;
						gameOver = false;
						invasor_mov.lin = ALTURA_TELA;
						invasor_mov.tiro_lin = ALTURA_TELA;
						invasor_mov.col = LARGURA_TELA;
						invasor_mov.tiro_col = LARGURA_TELA;
						nave.x = 350;
						nave.y = 500;
						nave.yLaser = 497;
						nave.xLaser = nave.x;
						nave.vidas = 3;
						inicializar_matriz_invisivel(matriz_invisivel);
						nave.pontos = 0;
						jaSomou = false;

					}
					else /*Se a tecla enter estiver pressionada mas mudarOpcao for == 1 entao o jogo é fechado*/
					{
						fechar = true;
						gameOver = false;
					}
				}
			}
               ///IMPRIME "EXIT/AGAIN" NA TELA (REALCANDO JUNTO)
               al_draw_text(fonteOpcoes, al_map_rgb(13 + 173 * mudarOpcao, 196 + 98 * mudarOpcao, 152 + 52 * mudarOpcao),
                            LARGURA_TELA/ 2 - 60, ALTURA_TELA - 90, ALLEGRO_ALIGN_LEFT, " EXIT  ");
			al_draw_text(fonteOpcoes, al_map_rgb(186 - 173 * mudarOpcao, 294 - 98 * mudarOpcao, 204 - 52 * mudarOpcao),
                            LARGURA_TELA/ 2 - 70, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT, " AGAIN ");


			///MECANICA DE MOVIMENTO DO "GAME OVER" NA TELA
			if(movimento == true)
			{
				x = x + 1;
			}
			if(x > LARGURA_TELA)
			{
				x = 500;
				x = x - 400;
			}
			al_draw_textf(fonteGO4, al_map_rgb(255, 255, 255), x, y - 100, ALLEGRO_ALIGN_CENTER, "GAME OVER"); /*Imprime "GAME OVER
                                                                                                                   na tela*/

               ///CONDICAO PARA FECHAR O JOGO
			if(eventoGameOver.type == ALLEGRO_EVENT_DISPLAY_CLOSE)  /*Caso for clicado o "X" na janela, o menu se torna falso e o
                                                                       while (!fechar) verdadeiro*/
               {
                    fechar = true;
				gameOver = false;
               }

               ///ATUALIZA A TELA A CADA FRAME
			if(eventoGameOver.type == ALLEGRO_EVENT_TIMER) {
				al_flip_display();
			}
		}
	}
	return 0;
}
