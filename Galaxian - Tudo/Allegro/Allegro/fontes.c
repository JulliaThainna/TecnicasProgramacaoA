#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LARGURA 500
#define ALTURA 500

int main (){
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *Fontee = NULL;
    janela = al_create_display(LARGURA,ALTURA);
    Fontee = al_load_font("fontes//fontejogo.ttf",70,0);

    int c = 1;
    while (1){
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_textf (Fontee, al_map_rgb(255,255,255),LARGURA/2,ALTURA/2,ALLEGRO_ALIGN_CENTRE,"%d",c);
        c++;
        al_flip_display();
    }

    return 0;
}

