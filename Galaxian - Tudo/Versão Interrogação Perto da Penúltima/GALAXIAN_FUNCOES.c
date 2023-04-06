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


void inicializar_matriz_invisivel();
int colisao_jogador();
int colisao_invasor();
int direcao_invasores();
void inicializa_allegro();

void inicializa_allegro()
{
	al_init();

	al_init_image_addon();

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(5);

	al_init_font_addon();
	al_init_ttf_addon();

	al_install_keyboard();
}


void inicializar_matriz_invisivel(int y[][7])
{
     int i,j;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if ((i == 0 && (j != 2 && j != 4)) || (i == 1 && (j == 0 || j == 6)))
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
//Verifica se a posicao do laser que o inimigo disparou coincide com a posicao da nave.
//Caso sim, retorna um. Caso a colisao seja falsa, retorna 0
// função que preenche a matriz invisivel
// não é necessário especificar linhas, pois o c "armazena" as linhas uma em sequencia da outra



// função que verifica a colisão dos invasores e seus tiros com a nave do jogador
int colisao_jogador(int x, int y, int a, int b)
{
	if (x >= a - 30 && x < a + 50 && y >= b && y <= b + 25)
	{
		return 1;
	}
	return 0;
}


//Faz a mesma coisa que a funcao de cima so que pra nave dos inimigos (tiro jogador). Ja que o tamanho das naves e diferente
// função que verifica a colisão dos tiros do jogador com os invasores
int colisao_invasor(int x, int y, int a, int b)
{
	if (x >= a - 30 && x < a + 30 && y >= b - 30 && y < b)
	{
		return 1;
	}
	return 0;

}

// função que altera a direção do movimento dos invasores
int direcao_invasores(int col)
{
	if (col + 450 >= 900)
	{
		return 1;
	}
	if (col == 10)
	{
		return 0;
	}
	return -1;
}
