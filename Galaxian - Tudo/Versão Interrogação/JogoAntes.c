#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//bibliotecas allegro
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
#define ALTURA 500
#define LARGURA 680

enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
int main() {

	bool keys[5] = { false,false,false,false,false };
	bool FecharJanela = false, tiro = false, acertouInimigo = false;
	int x = 350, y = 450, yLaser = 443, xLaser = x;

	//inicia as funções para usar nas macro
	al_init(); //essencial
	al_init_image_addon(); //imagens

	//audio
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);

	al_install_keyboard();//"instala" o teclado

	//cria as macro
	ALLEGRO_DISPLAY *JANELA = NULL;
	ALLEGRO_TIMER *TimerFPS = NULL;
	ALLEGRO_EVENT_QUEUE *TelaJogo = NULL;
	ALLEGRO_BITMAP *FUNDO = NULL;
	ALLEGRO_BITMAP *LASER = NULL;
	ALLEGRO_BITMAP *NAVE = NULL;
	ALLEGRO_SAMPLE *SomPrincipal = NULL;
	ALLEGRO_SAMPLE *SHOOT = NULL;

	//inicia as variáveis
	JANELA = al_create_display(LARGURA, ALTURA); //cria uma janela
	TelaJogo = al_create_event_queue(); //adiciona a tela do jogo numa fila de eventos
	FUNDO = al_load_bitmap("Imagens//fundo.png"); //carrega o fundo da tela
	LASER = al_load_bitmap("Imagens//laser.png"); //carrega o laser da nave
	NAVE = al_load_bitmap("Imagens//nave.png"); //carrega a imagem da nave
	SomPrincipal = al_load_sample("Sons//MusicaJogo.ogg");
	al_play_sample(SomPrincipal, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	SHOOT = al_load_sample ("Sons//LaserEffect.ogg");
	TimerFPS = al_create_timer(1.0 / FPS); //cria um timer que conta as atualizações por segundo (frames)

	//registra os eventos na fila "TelaJogo"
	al_register_event_source(TelaJogo, al_get_display_event_source(JANELA)); //registra a janela que vai ser aberta nos eventos
	al_register_event_source(TelaJogo, al_get_keyboard_event_source()); //regristra o teclado nos eventos
	al_register_event_source(TelaJogo, al_get_timer_event_source(TimerFPS)); //registra o FPS nos eventos
	al_start_timer(TimerFPS); //inicia o timer de FPS

	//aqui "começa" o jogo
	while (!FecharJanela) { //enquanto a janela não estiver fechada
		al_clear_to_color(al_map_rgb(0, 0, 0)); //limpa a tela a cada atualização
		al_draw_bitmap(FUNDO, 0, 0, 0); //desenha o fundo
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
		//para fechar a janela do jogo
		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			FecharJanela = true;
		}

		//condições de movimentação e limites de tela da nave
		if (x > 0) {
			x -= keys[LEFT] * 8;
		}
		if (x < LARGURA - 57) {
			x += keys[RIGHT] * 8;
		}

		//condições de movimentação e limites de tela do laser
		if (keys[SPACE] == true && tiro == false) {		//Aqui a gente vê se o espaço ta apertado e se ja tem algum laser na tela. Se tiver, ele não solta outro
			tiro = true;
			xLaser = x;
		}
		if (tiro == true) {					//Se ja tiver um laser na tela essa parte verifica se ele ja acertou um inimigo ou saiu da tela.
				if (yLaser > 0) {
					yLaser -= tiro * 20;
					al_play_sample(SHOOT,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}
				else if(yLaser <= 0 || acertouInimigo == true){		//Caso alguma dessas condições sejam satisfeitas, ele seta o tiro como falso. Mais tarde a gente usa isso pra desenhar o laser na mesma posição da nave, ou não.
					tiro = false;
					xLaser = x;
					yLaser = 443;
				}
		}


		if (tiro == true) {		//Se estiver atirando renderiza o laser movimentando pela tela
			al_draw_bitmap(LASER, xLaser + 19, yLaser, 0);
		}
		else {					//Se for falso, desenha o laser atras da nave
			al_draw_bitmap(LASER, x + 19, yLaser, 0);
		}
		al_draw_bitmap(NAVE, x, y, 0); //desenha a nave na tela

		//se estiver acontecendo um evento do tipo "timer"
		if (evento.type == ALLEGRO_EVENT_TIMER) {
			al_flip_display(); //atualiza a tela a cada segundo
		}
	}

	return 0;
}

