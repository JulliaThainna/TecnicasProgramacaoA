#ifndef INICIA_ALLEGRO_VARIAVEIS_H_INCLUDED
#define INICIA_ALLEGRO_VARIAVEIS_H_INCLUDED

    ALLEGRO_DISPLAY *JANELA = NULL;
    ALLEGRO_TIMER *TimerFPS = NULL;
    //Fila eventos
	ALLEGRO_EVENT_QUEUE *filaJogo = NULL;
    //imagens
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
     //ALLEGRO_BITMAP *explosao= NULL;
     //fontes
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
     ALLEGRO_FONT *FonteMenuPontos = NULL;
     ALLEGRO_FONT *FonteFraseTachado = NULL;
     ALLEGRO_FONT *Fonte4 = NULL;
     ALLEGRO_FONT *Fonte3 = NULL;
     //audios
	ALLEGRO_AUDIO_STREAM *SomMenu = NULL;
	ALLEGRO_AUDIO_STREAM *MusicaJogo = NULL;
	ALLEGRO_SAMPLE *Laser = NULL;
	//arquivos
	FILE* arquivo;

#endif // INICIA_ALLEGRO_VARIAVEIS_H_INCLUDED
