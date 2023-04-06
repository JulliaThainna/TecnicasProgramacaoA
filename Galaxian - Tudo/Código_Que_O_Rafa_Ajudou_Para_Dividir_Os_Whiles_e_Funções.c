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
#include "INICIA_ALLEGRO_VARIAVEIS/INICIA_ALLEGRO_VARIAVEIS.h"
#include "GALAXIAN_FUNCOES\GALAXIAN_FUNCOES.c"
//#include "GALAXIAN_FUNCOES\MENU PONTOS.c"


#define FPS 60

const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;
enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };



//!!! PASSAR PARA UM UNICO ARQUIVO. PRIMEIRO DECLARA AS FUNÇÕES E DEPOIS DEFINE ELAS!!!


// função que preenche a matriz invisivel
// não é necessário especificar linhas, pois o c "armazena" as linhas uma em sequencia da outra
void inicializar_matriz_invisivel(int y[][9])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<9;j++)
        {
            y[i][j] = 1;
        }
    }
}

// função que verifica a colisão dos invasores e seus tiros com a nave do jogador
int colisao_jogador(int x, int y,int a, int b )
{
    if(x >= a -30 && x < a +50 && y >= b && y <= b+25 )
    {
        return 1;
    }
    return 0;
}

// função que verifica a colisão dos tiros do jogador com os invasores
int colisao_invasor(int x, int y, int a, int b)
{
     if(x >= a - 30 && x < a +30 && y >= b-30 && y < b )
    {
        return 1;
    }
    return 0;

}

// função que altera a direção do movimento dos invasores
int direcao_invasores(int col)
{
    if(col+450 >= LARGURA_TELA)
    {
        return 1;
    }
    if(col == 10)
    {
        return 0;
    }
}



//!!!NÃO PODEMOS COLOCAR EM FUNÇÃO POR ENQUANTO PQ É ARQUIVO DO ALLEGRO!!!
int inicializa_allegro()
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


int main()
{
    inicializa_allegro();

	//Cria uma janela
    JANELA = al_create_display(LARGURA_TELA, ALTURA_TELA);
    //Fila de Eventos na tela
    TelaJogo = al_create_event_queue(); //Sugestão: mudar o nome para filaJogo ou algo do tipo para saber q é uma fila
    //imagens
    LASER = al_load_bitmap("laser.png");
	NAVE = al_load_bitmap("nave.png");
    invasor = al_load_bitmap("invasor.png");
    fundo = al_load_bitmap("fundo.png");
    tiro = al_load_bitmap("projetil.bmp");
    vida = al_load_bitmap("vida.png");
    FundoMenu = al_load_bitmap("fundo_secundario.png");
    //explosao =  al_load_bitmap("explosao.png");


    //fontes
    FonteMenu1 = al_load_font ("FonteMenu1.ttf",9,0);
    FonteGeral_1 = al_load_font ("FonteMenu2.ttf",60,0); //era antes fontemenu 2
    FonteGeral_2 = al_load_font ("FonteMenu1.ttf",20,0); //era antes fontemenu 3
    FonteGO1 = al_load_font ("FonteMenu1.ttf",12,0);
    //FonteGO2 = al_load_font ("FonteMenu2.ttf",60,0);
    //FonteGO3 = al_load_font ("FonteMenu1.ttf",20,0);
    FonteGO4 = al_load_font ("hackerchaos.otf",72,0);
    //FonteMenuPontos = al_load_font ("Sunset Boulevard.otf",35,0);
    //FonteMenu2 = al_load_font ("FonteMenu2.ttf",60,0);
    //FonteMenu3 = al_load_font ("FonteMenu1.ttf",20,0);
    //FonteMenu4 = al_load_font ("FonteMenu1.ttf",20,0);
    //FonteFrase = al_load_font ("Interferencias.otf",25,0);
    FontePontos = al_load_font("FonteMenu1.ttf", 14, 0);
    //audios


    TimerFPS = al_create_timer(1.0 / FPS);

            //!VARIÁVEIS P/ OS INVASORES
            int matriz_invisivel[4][9];
            inicializar_matriz_invisivel(matriz_invisivel);
            // criando uma matriz que servirá apenas para verificar se um invasor está vivo para desenhá-lo ou não na tela
            //- caso vivo, sua posição terá valor 1
            //- caso  morto ou em movimento, sua posição terá valor 0  */

            // coluna e linha iniciais dos inimigos
            int inim_col = 70;
            int inim_lin = 50;

            // coluna e linha iniciais do tiro dos inimigos
            int tiro_lin = ALTURA_TELA;3
            int dir=0;    // DIREÇÃO DO MOVIMENTO DOS INIMIGOS   0 = direita   1= esquerda
            int rand_i; // para sortear a posição(em termos de linha da matriz_invisivel) do inimigo
            int passo = 0;
            int ci = 0;
            int qtd_inimigos= 36;
            int cont;
            int pontos_nave = 0;
            int SCORE;
            int Y = 250;
            int X = 340;
            int ALTURA = 600;
            int LARGURA = 900;
            int OPCAO=0;
            int x = 340, y = 250;

            //variáveis bool
            bool	repos_inimigo = false,
					gameOver = false,
					MOVIMENTO = true,
					menu = true,
					MudarOpcao = true,
					fechar = false,
					jogo = false,
					ComecarJogo = false,
            //!VARIÁVEIS P/ A NAVE DO JOGADOR
					keys[5] = { false,false,false,false,false },
					FecharJanela = false, disparo = false;

           //!VARIÁVEIS P/ O INVASOR QUE SE MOVIMENTA
            invasor_mov.lin = ALTURA_TELA;
            invasor_mov.tiro_lin = ALTURA_TELA;
            int guard_i,guard_j;
            nave.x = 350;
            nave.y = 500;
            nave.yLaser = 497;
            nave.xLaser = nave.x;
            nave.vidas = 3;
            int c = 30;

			//!!!MUDANÇA DE VALOR DE VARIAVEL SEMPRE DEPOIS DE DEFINIÇÃO!!!
			srand(time(NULL));
        //!EVENTOS
        al_register_event_source(TelaJogo, al_get_display_event_source(JANELA)); //registra a janela que vai ser aberta nos eventos
        al_register_event_source(TelaJogo, al_get_keyboard_event_source()); //regristra o teclado nos eventos
        al_register_event_source(TelaJogo, al_get_timer_event_source(TimerFPS)); //registra o FPS nos eventos
        al_start_timer(TimerFPS); //inicia o timer de FPS
		//!!!DEPOIS DO START TIMER NAO PODE TER NENHUM COMANDO ANTES O WHILE!!!


    //!INÍCIO DO JOGO

	 while (!fechar) //fechar == false - ENQUANTO O JOGO ESTIVER ABERTO
	 {
		 while (menu)
		 {
			//Tudo que vai acontecer no menu
			 al_clear_to_color(al_map_rgb(0, 0, 0));
			 //Aqui vai a impressão de todas as imagens e afins
			 //Tudo que for pra printar
			 ALLEGRO_EVENT eventoMenu;
			 al_wait_for_event(TelaJogo, &eventoMenu);
			 //aqui vai tudo que tem de leitura de comandos e dados que o usuario vai digitar
			 if (eventoMenu.type == ALLEGRO_EVENT_KEY_DOWN)
			 {
				 switch (eventoMenu.keyboard.keycode)
				 {
					 //Leitura das teclas apertadas
				 }
			 }
			 if (eventoMenu.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			 {
				 //Caso a pessoa feche o jogo
				 menu = false;
				 fechar = true;
			 }
			 if (eventoMenu.type == ALLEGRO_EVENT_TIMER)
			 {
				 //Atualiza a tela
				 al_flip_display();
			 }
		 }
		 while (jogo)
		 {
			//Tudo o que acontece no jogo
			 al_clear_to_color(al_map_rgb(0, 0, 0));
			 //Aqui vai a impressão de todas as imagens e afins
			 //Tudo que for pra printar
			 ALLEGRO_EVENT eventoJogo;
			 al_wait_for_event(TelaJogo, &eventoJogo);
			 //aqui vai tudo que tem de leitura de comandos e dados que o usuario vai digitar
			 if (eventoJogo.type == ALLEGRO_EVENT_KEY_DOWN)
			 {
				 switch (eventoJogo.keyboard.keycode)
				 {
					 //Leitura das teclas apertadas
				 }
			 }
			 if (eventoJogo.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			 {
				 //Caso a pessoa feche o jogo
				 jogo = false;
				 fechar = true;
			 }
			 if (eventoJogo.type == ALLEGRO_EVENT_TIMER)
			 {
				 //Atualiza a tela
				 al_flip_display();
			 }
		 }
		 while (gameOver)
		 {
			//Tudo o que acontece no game over
			 al_clear_to_color(al_map_rgb(0, 0, 0));
			 //Aqui vai a impressão de todas as imagens e afins
			 //Tudo que for pra printar
			 ALLEGRO_EVENT eventoGameOver;
			 al_wait_for_event(TelaJogo, &eventoGameOver);
			 //aqui vai tudo que tem de leitura de comandos e dados que o usuario vai digitar
			 if (eventoGameOver.type == ALLEGRO_EVENT_KEY_DOWN)
			 {
				 switch (eventoGameOver.keyboard.keycode)
				 {
					 //Leitura das teclas apertadas
				 }
			 }
			 if (eventoGameOver.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			 {
				 //Caso a pessoa feche o jogo
				 gameOver = false;
				 fechar = true;
			 }
			 if (eventoGameOver.type == ALLEGRO_EVENT_TIMER)
			 {
				 //Atualiza a tela
				 al_flip_display();
			 }
		 }
	 }


     al_destroy_display(JANELA);



    return 0;
}










