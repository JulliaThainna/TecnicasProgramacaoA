#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h> //basico do allegro

#include <allegro5/allegro_primitives.h> //formas do allegro

#include <allegro5/allegro_ttf.h> //para poder importar fontes
#include <allegro5/allegro_font.h> //para poder usar as fontes que foram importadas

#define LARGURA 500 //#define nao cria um espaco de memoria
#define ALTURA 500

int main (){

    al_init ();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *janela = NULL; //TipoDaMacro nomeDaVariavel = valor;
    ALLEGRO_FONT *fonteMenu = NULL; //Cria uma nova fonte
    fonteMenu = al_load_font("fontes//fontejogo.ttf",70,0);
    janela = al_create_display (LARGURA, ALTURA);

    if (!janela){ //(!janela == NULL) || (!janela == false)
        printf ("NAO FOI POSSIVEL CRIAR A JANELA. OCORREU UM ERRO!");
    }

    al_clear_to_color(al_map_rgb(255,112,194)); //limpar o fundo da tela e adicionar a cor escolhida(al_map_rgb é pra definir, tem que pegar os valores das 3 cores para a cor escolhida)
    al_draw_text(fonteMenu, al_map_rgb(0,0,0),LARGURA/2, ALTURA/2,ALLEGRO_ALIGN_CENTRE, "I LOV U <3");
    //al_map_rgb (red,green,blue)
    //al_map_rgba (red,green,blue,alpha (transparente))

    //filled cor inteira
    //sem o filled so a borda

    al_flip_display (); //atualizar tela
    al_rest (4.0); //esperar um tempo "sleep"
    return 0;
}

