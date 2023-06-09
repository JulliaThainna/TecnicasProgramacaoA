//Bibliotecas padr�es
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
#include  "INICIA_ALLEGRO_VARIAVEIS.h"
#include  "VARIAVEIS.h"
#include "GALAXIAN_FUNCOES.c"


#define FPS 100

const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;

enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };


int main()
{
	inicializar_matriz_invisivel(matriz_invisivel);
	//!VARI�VEIS P/ O INVASOR QUE SE MOVIMENTA
	invasor_mov.lin = ALTURA_TELA;
	invasor_mov.tiro_lin = ALTURA_TELA;
	invasor_mov.col = LARGURA_TELA;
	invasor_mov.tiro_col = LARGURA_TELA;
	nave.x = 350;
	nave.y = 500;
	nave.yLaser = 497;
	nave.xLaser = nave.x;
	nave.vidas = 3;

	al_init();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

     JANELA = al_create_display(LARGURA_TELA, ALTURA_TELA);
	//fila de eventos
	filaJogo = al_create_event_queue();

     //imagens
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
	//fontes
	FonteMenu1 = al_load_font("Fontes//FonteMenu1.ttf", 11, 0);
	FonteMenu2 = al_load_font("Fontes//FonteMenu2.ttf", 60, 0);
	FonteMenu3 = al_load_font("Fontes//FonteMenu1.ttf", 30, 0);
	FonteMenu4 = al_load_font("Fontes//FonteMenu2.ttf", 80, 0);
	FonteMenu5 = al_load_font("Fontes//fonte5.ttf", 14, 0);
	fonteGO1 = al_load_font("Fontes//FonteMenu1.ttf", 12, 0);
	fonteGO4 = al_load_font("Fontes//hackerchaos.otf", 85, 0);
	FontePontos = al_load_font("Fontes//FonteMenu1.ttf", 14, 0);
	FontePontos2 = al_load_font("Fontes//fonte-3.ttf",20,0);
	FontePontos3 = al_load_font("Fontes//fonte-4.ttf",25,0);
	FonteFrase = al_load_font("Fontes//Sunset Boulevard.otf", 50, 0);
	fonteSpace = al_load_font("Fontes//Sunset Boulevard.otf", 30, 0);
	fonteOpcoes = al_load_font("Fontes//Sunset Boulevard.otf", 70, 0);
	FonteFraseTachado = al_load_font("Fontes//fonte riscada 2.ttf", 30, 0);
	//audios
     SomMenu = al_load_audio_stream("Sons//SomMenu.ogg",4,1024);
     MusicaJogo = al_load_audio_stream("Sons//MusicaJogo.ogg",4,1024);
     Laser = al_load_sample("Sons//LaserEffect.ogg");


	TimerFPS = al_create_timer(1.0 / FPS);

	//!FILA DE EVENTOS
	al_register_event_source(filaJogo, al_get_display_event_source(JANELA)); //registra a janela que vai ser aberta nos eventos
	al_register_event_source(filaJogo, al_get_keyboard_event_source()); //regristra o teclado nos eventos
	al_register_event_source(filaJogo, al_get_timer_event_source(TimerFPS)); //registra o FPS nos eventos
	srand(time(NULL));


	arquivo = fopen("score.txt", "r");
	int i;
	for (i = 0; i < 5; i++)
	{
		fscanf(arquivo, "%d\n", &lugar[i]);
	}
	fclose(arquivo);

    al_attach_audio_stream_to_mixer(SomMenu, al_get_default_mixer());
    al_set_audio_stream_playmode(SomMenu, ALLEGRO_PLAYMODE_LOOP);
	al_start_timer(TimerFPS); //inicia o timer de FPS

	while (!fechar)
	{
		while (menu)
		{
			drawMenu(FonteMenu2, FonteMenu5, fundoMenu, LogoMenu, LARGURA_TELA, ALTURA_TELA, xnave, x, y);

			ALLEGRO_EVENT eventoMenu;
			al_wait_for_event(filaJogo, &eventoMenu);
			if (eventoMenu.type == ALLEGRO_EVENT_KEY_DOWN)
                {
				switch (eventoMenu.keyboard.keycode)
                {
				case ALLEGRO_KEY_UP:
					opcao = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					opcao = 1;
					break;
				case ALLEGRO_KEY_ENTER:
					if (opcao == 0)
                    {
						menu = false;
						secundario = true;
					}
					else
                    {
						menu = false;
						fechar = true;
					}
					break;
				}
			}
			if (opcao == 0)
			{
				al_draw_textf(fonteOpcoes, al_map_rgb(186, 294, 204), LARGURA_TELA - 200, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT, ">START");
				al_draw_textf(fonteOpcoes, al_map_rgb(13, 196, 152), LARGURA_TELA - 200, ALTURA_TELA - 100, ALLEGRO_ALIGN_LEFT, " EXIT");
			}
			else
			{
				al_draw_textf(fonteOpcoes, al_map_rgb(13, 196, 152), LARGURA_TELA - 200, ALTURA_TELA - 170, ALLEGRO_ALIGN_LEFT, " START");
				al_draw_textf(fonteOpcoes, al_map_rgb(186, 294, 204), LARGURA_TELA - 200, ALTURA_TELA - 100, ALLEGRO_ALIGN_LEFT, ">EXIT");

			}
			//mec�nica de movimento dos aliens na tela


			if (movimento == true)
			{

			    if(xnave == 350)
                {
                   direction = 0;
			    }

			    if( xnave == LARGURA_TELA-300 )
                {
                   direction = 1;

			    }
				if (direction == 0)
                {
                    xnave++;
                    x++;
				}
				if (direction == 1)
				{
                    xnave--;
                    x--;
				}

			}

			if (eventoMenu.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
				menu= false;
				fechar = true;
			}
			if (eventoMenu.type == ALLEGRO_EVENT_TIMER)
			{
				al_flip_display();
			}

		}
		while (secundario)
		{
            drawSecundario(FonteFrase, FonteFraseTachado, FontePontos3, FontePontos, fundoMenu, invasor1, invasor2, invasor3, invasor4, LARGURA_TELA, ALTURA_TELA, z, x, y);

            ALLEGRO_EVENT eventoSecundario;
			al_wait_for_event(filaJogo, &eventoSecundario);

			if (eventoSecundario.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch(eventoSecundario.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:
					jogo = true;
                    al_set_audio_stream_playing(SomMenu,false);
                    al_attach_audio_stream_to_mixer(MusicaJogo, al_get_default_mixer());
                    al_set_audio_stream_playmode(MusicaJogo, ALLEGRO_PLAYMODE_LOOP);
					secundario = false;
					break;
				}
			}

			if(movimento == true)
            {
                z++;

                if(z > ALTURA_TELA - 480)
                {
                    z = 70;
                }
            }
			if (eventoSecundario.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
				secundario = false;
				fechar = true;
			}


			if (eventoSecundario.type == ALLEGRO_EVENT_TIMER)
            {
				al_flip_display();
			}
		}
		while (jogo)
		{
			//!ANDRE
			al_draw_bitmap(fundo, 0, 0, 0);
			al_draw_textf(FontePontos, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d", pontos_nave);

			//!DESENHANDO VIDA DO JOGADOR
			int i;
			for (i = 0; i < nave.vidas; i++)
			{
				al_draw_bitmap(vida, LARGURA_TELA - 300 + c, -50, 0);
				c = c + 50;
			}
			c = 50;

			ALLEGRO_EVENT eventoJogo; //come�a um eventoJogo, pega um eventoJogo da fila (quando um estiver dispon�vel) e coloca ele na vari�vel eventoJogo.
			al_wait_for_event(filaJogo, &eventoJogo);//remove o primeiro item da fila de eventos e coloca na vari�vel eventoJogo.

			//se alguma tecla estiver pressionada
			if (eventoJogo.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (eventoJogo.keyboard.keycode) { //casos para a movimenta��o da nave (dados do teclado)
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

			//se alguma tecla estiver n�o pressionada
			if (eventoJogo.type == ALLEGRO_EVENT_KEY_UP) {
				switch (eventoJogo.keyboard.keycode) { //para a movimenta��o da nave
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
			if (eventoJogo.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				fechar = true;
				jogo = false;
			}


			//!IMPRIMINDO TIRO DOS INVASORES
			al_draw_bitmap(tiro, tiro_col, tiro_lin, 0);
			tiro_lin = tiro_lin + 6;

			//!INVASOR EM MOVIMENTO

			if (invasor_mov.lin < ALTURA_TELA) {    // caso o invasor ainda n�o tenha chegado ao fim da tela
				invasor_mov.lin = invasor_mov.lin + 3;
			}
			if (invasor_mov.lin > ALTURA_TELA) {  // caso o invasor chegue ao fim da tela sem ser destru�do
				invasor_mov.lin = ALTURA_TELA;
				repos_inimigo = true;
			}

			//VERIFICANDO QUAL BITMAP DE INVASOR SER� DESENHADO


            if (guard_i == 0)
			{
				al_draw_bitmap(invasor4, invasor_mov.col, invasor_mov.lin, 0);// desenhando invasor em movimento
			}

			if (guard_i == 1)
			{
				al_draw_bitmap(invasor2, invasor_mov.col, invasor_mov.lin, 0);// desenhando invasor em movimento
			}
			if (guard_i == 2)
			{
				al_draw_bitmap(invasor1, invasor_mov.col, invasor_mov.lin, 0);// desenhando invasor em movimento
			}

			if (guard_i == 4 || guard_i == 3)
			{
				al_draw_bitmap(invasor3, invasor_mov.col, invasor_mov.lin, 0);// desenhando invasor em movimento
			}

			// tiro do invasor em movimento
			if (invasor_mov.tiro_lin >= ALTURA_TELA && invasor_mov.lin <= 300)// se o tiro chegou no final da tela, ele retorna para o invasor
			{
				invasor_mov.tiro_lin = invasor_mov.lin + 25;
				invasor_mov.tiro_col = invasor_mov.col + 25;
			}
			al_draw_bitmap(tiro, invasor_mov.tiro_col, invasor_mov.tiro_lin, 0); // desenhando tiro do invasor em movimento
			invasor_mov.tiro_lin = invasor_mov.tiro_lin + 5;


			// colis�o do tiro do jogador com o invasor em movimento
			if (colisao_invasor(nave.xLaser, nave.yLaser, invasor_mov.col, invasor_mov.lin) && disparo == true)
			{

				invasor_mov.lin = ALTURA_TELA;
				nave.xLaser = nave.x; // retorna o laser p/ perto da nave
				nave.yLaser = 497;
				qtd_inimigos--;
				pontos_nave = pontos_nave + 200;
				disparo = false;

			}

			//!COLIS�O DOS TIROS E DOS INVASORES COM O JOGADOR

               // verifica se a posi��o do TIRO DOS INVASORES "normais" � igual a da NAVE DO JOGADOR
			if (colisao_jogador(tiro_col, tiro_lin, nave.x, nave.y))
			{
				nave.vidas--; //diminui uma vida
				tiro_lin = ALTURA_TELA;
			}


			// verifica se a posi��o do TIRO DO INVASOR EM MOVIMENTO � igual a da NAVE DO JOGADOR
			if (colisao_jogador(invasor_mov.tiro_col, invasor_mov.tiro_lin, nave.x, nave.y))
			{
				nave.vidas--; //diminui uma vida
				invasor_mov.tiro_lin = ALTURA_TELA;
			}


			// verifica se a posi��o do INVASOR EM MOVIMENTO � igual a da NAVE DO JOGADOR
			if (colisao_jogador(invasor_mov.col, invasor_mov.lin, nave.x, nave.y))
			{
				nave.vidas--; //diminui uma vida
				invasor_mov.lin = ALTURA_TELA;

			}


			//!IMPRIMINDO INVASORES
			inim_lin = 50;
			i = j = 0;

			while (i < 5)
			{
				while (j < 7)
				{

					if (matriz_invisivel[i][j] == 1)// verifica se o inimigo est� vivo
					{

						//!COLIS�O TIRO DO JOGADOR COM O INVASOR
						if (colisao_invasor(nave.xLaser, nave.yLaser, inim_col, inim_lin))
						{
							//al_draw_bitmap(explosao,inim_col,inim_lin,0);//imprimindo explos�o
							matriz_invisivel[i][j] = 0;
							nave.xLaser = nave.x; // retorna o laser p/ perto da nave
							nave.yLaser = 497;
							pontos_nave += 30 * (guard_i + 1);	//pontos_nave = pontos_nave + 30*guard_i
							disparo = false;
						}

						//!RELACIONADO AO TIRO DO INVASOR
						if (tiro_lin >= ALTURA_TELA && (inim_col > nave.x - 50 && inim_col < nave.x - 10) && i != guard_i && j != guard_j) // se o tiro tiver  chegado ao fim da tela e se a col do inimigo for igual � do jogador
						{
							tiro_lin = inim_lin + 25;
							tiro_col = inim_col + 25;
						}


						//!DEFININDO O INVASOR EM MOVIMENTO
						if (invasor_mov.lin == ALTURA_TELA && (inim_col > nave.x && inim_col < nave.x + 50))
							// se for DESTRU�DO ou chegou ao FIM DA TELA e se a coluna for a mesma da nave do jogador
						{
							matriz_invisivel[i][j] = 0;  // faz com que o inimigo n�o seja mais desenhado na sua posi��o original
							invasor_mov.lin = inim_lin;      // determina a posi��o em que ele ser� desenhado
							invasor_mov.col = inim_col;
							invasor_mov.tiro_lin = invasor_mov.lin; //determina a posi��o do tiro
							invasor_mov.tiro_col = invasor_mov.col + 25;
							guard_i = i; //guardam a posi��o original do invasor na matriz
							guard_j = j;

						}
						//reposicionando invasor caso ele N�O SEJA DESTRU�DO
						if (repos_inimigo == true && invasor_mov.lin == ALTURA_TELA)
						{
							matriz_invisivel[guard_i][guard_j] = 1;  //a posi��o original do invasor recebe 1
							repos_inimigo = false;
						}
					}


					//!POSICIONANDO E DESENHANDO INIMIGOS
					if (j == 6)  // aumenta lin e diminui col p/ "quebrar a linha"
					{
						if (matriz_invisivel[i][j] == 1) // verifica se o inimigo est� vivo
						{
							//verificando qual bitmap ser� desenhado
							switch (i) {
							case 0:
								al_draw_bitmap(invasor4, inim_col, inim_lin, 0);
								break;

							case 1:
								al_draw_bitmap(invasor2, inim_col, inim_lin, 0);
								break;

							case 2:
								al_draw_bitmap(invasor1, inim_col, inim_lin, 0);
								break;

							case 3:
								al_draw_bitmap(invasor3, inim_col, inim_lin, 0);
								break;

							case 4:
								al_draw_bitmap(invasor3, inim_col, inim_lin, 0);
								break;

							}
						}
						inim_lin = inim_lin + 50;
						inim_col = inim_col - 420;   // o valor a ser subtra�do � sempre 7*(o n�mero de colunas-1)
					}

					else if (j != 6) // apenas aumenta inim_col p/ dar espa�amento entre os inimigos
					{
						if (matriz_invisivel[i][j] == 1)// verifica se o inimigo est� vivo
						{
							//verificando qual bitmap ser� desenhado
							switch (i) {
							case 0:
								al_draw_bitmap(invasor4, inim_col, inim_lin, 0);
								break;

							case 1:
								al_draw_bitmap(invasor2, inim_col, inim_lin, 0);
								break;

							case 2:
								al_draw_bitmap(invasor1, inim_col, inim_lin, 0);
								break;

							case 3:
								al_draw_bitmap(invasor3, inim_col, inim_lin, 0);
								break;

							case 4:
								al_draw_bitmap(invasor3, inim_col, inim_lin, 0);
								break;

							}

						}
						inim_col = inim_col + 70;
					}
					j++;
				}
				i++;
				j = 0;
			}


			//!ALTERANDO DIRE��O DO MOVIMENTO DOS  INVASORES

				// apenas p/ dar o aspecto dos inimigos se moverem em "passos"
			ci++;
			passo = 0;
			if (ci > 65)  //caso "ci" chegue em 65
			{
				passo = 1;
				ci = 0;
			}

			if (direcao_invasores(inim_col) == 1) {
				dir = 1;
			}

			if (direcao_invasores(inim_col) == 0) {
				dir = 0;
			}

			if (dir == 1) {
				inim_col = inim_col - passo * 10;
			}

			if (dir == 0) {
				inim_col = inim_col + passo * 10;
			}

			//JULLIA
			//!MOVIMENTA��O DO JOGADOR



               //condi��es de movimenta��o e limites de tela da nave
			if (nave.x > 0) {
				nave.x -= keys[LEFT] * 4;
			}
			if (nave.x < LARGURA_TELA - 57) {
				nave.x += keys[RIGHT] * 4;
			}



			//condi��es de movimenta��o e limites de tela do laser
			if (keys[SPACE] == true && disparo == false) {		//Aqui a gente v� se o espa�o ta apertado e se ja tem algum laser na tela. Se tiver, ele n�o solta outro
				disparo = true;
				al_play_sample(Laser,1.0,0.0,1.0, ALLEGRO_PLAYMODE_ONCE,NULL);
				nave.xLaser = nave.x;
			}
			if (disparo == true) {					//Se ja tiver um laser na tela essa parte verifica se ele ja acertou um inimigo ou saiu da tela.
				if (nave.yLaser > 0) {
					nave.yLaser -= disparo * 8;
				}
				else if (nave.yLaser <= 0) {		//Caso alguma dessas condi��es sejam satisfeitas, ele seta o tiro como falso. Mais tarde a gente usa isso pra desenhar o laser na mesma posi��o da nave, ou n�o.
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



		//!CASO TODOS OS INIMIGOS TENHA SIDO ELIMINADOS, ELES REAPARECER�O
			cont = 0;
			int a,b;
			for (a = 0; a < 5; a++)
			{
				for (b = 0; b < 7; b++)
				{
					if (matriz_invisivel[a][b] == 0)        //verifica se todos est�o mortos
					{
						cont++;
					}
				}
			}

			if (cont == 35 && invasor_mov.lin >= ALTURA_TELA) //caso todos estejam mortos
			{
				inicializar_matriz_invisivel(matriz_invisivel);


			}
			//TATIANE
			if (pontos_nave >= 5000 && jaSomou == false)
			{
			    nave.vidas++;
			    jaSomou = true;
			}

			//verifica se o jogador tem vidas, se nao tiver ir� para game_over
			if (nave.vidas <= 0)
			{
			    //verifica se a pontuacao do jogador � maior que uma das 5 primeiras
			    if (pontos_nave >= lugar[4])
			{
				lugar[4] = pontos_nave;
			}
			if (pontos_nave >= lugar[3])
			{
				lugar[4] = lugar[3];
				lugar[3] = pontos_nave;
			}
			if (pontos_nave >= lugar[2])
			{
				lugar[3] = lugar[2];
				lugar[2] = pontos_nave;
			}
			if (pontos_nave >= lugar[1])
			{
				lugar[2] = lugar[1];
				lugar[1] = pontos_nave;
			}
			if (pontos_nave >= lugar[0])
			{
				lugar[1] = lugar[0];
				lugar[0] = pontos_nave;
			}

			arquivo = fopen("score.txt", "w");

               int i;
			for (i = 0; i < 5; i++)
			{
			    //salva as pontuacoes no arquivo de score
				fprintf(arquivo, "%d\n", lugar[i]);
			}
			fclose(arquivo);


				gameOver = true;
				jogo = false;
				nave.vidas = 3;

			}


			if (eventoJogo.type == ALLEGRO_EVENT_TIMER) {
				al_flip_display();
			}

		}
		while (gameOver)
		{
			drawGameOver(FonteMenu2, FonteMenu4, fonteOpcoes, fundoMenu,
                  LARGURA_TELA, ALTURA_TELA, lugar, y);

			ALLEGRO_EVENT eventoGameOver;
			al_wait_for_event(filaJogo, &eventoGameOver);
			if (eventoGameOver.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (eventoGameOver.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					mudarOpcao = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					mudarOpcao = 1;
					break;
				case ALLEGRO_KEY_ENTER:
					if (mudarOpcao == 0)
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
						pontos_nave = 0;
						jaSomou = false;

					}
					else
					{
						fechar = true;
						gameOver = false;
					}
				}
			}


			//mec�nica de movimento do gameover na tela
			if (movimento == true)
			{
				x = x + 1;
			}
			if (x > LARGURA_TELA)
			{
				x = 500;
				x = x - 400;
			}
			al_draw_textf(fonteGO4, al_map_rgb(255, 255, 255), x, y - 100, ALLEGRO_ALIGN_CENTER, "GAME OVER");

			if (eventoGameOver.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
				fechar = true;
				gameOver = false;

            }

			if (eventoGameOver.type == ALLEGRO_EVENT_TIMER) {
				al_flip_display();
			}
		}
	}
	return 0;
}




