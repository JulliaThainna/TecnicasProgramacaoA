#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //pra poder usar imagens

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
int main (){
    al_init ();
    al_init_image_addon();
    al_init_acodec_addon(); //instala o codec do audio
    al_install_audio(); //instala o audio do jogo
    al_reserve_samples(5); //cria 5 canais de audio

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_BITMAP *ibagem = NULL; //para "criar" uma imagem "vazia" "moldura"
    ALLEGRO_BITMAP *ibagem2 = NULL;
    ALLEGRO_BITMAP *ibagem3 = NULL;
    ALLEGRO_SAMPLE *som = NULL; //para "criar" um sample "vazio"

    janela = al_create_display(500,500);

    ibagem = al_load_bitmap("heart.png"); //carrega a imagem "variavel" criada
    ibagem2 = al_load_bitmap ("eye.png");
    ibagem3 = al_load_bitmap ("planets.png");

    som = al_load_audio_stream("aestheristico.ogg",4,1024);  //caminho da musica, 4 aletario 'flag', 1024 atualizoes por segundo
    al_attach_audio_stream_to_mixer(som,al_get_default_mixer());
    //som2 = al_load_sample("sounds\\tick_menu.ogg")
    //al_play_sample(som2,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL); //allegro_playmode_loop //som pequeno

    al_clear_to_color(al_map_rgb(255,112,194));

    al_draw_bitmap(ibagem,-800,0,0); //dx,dy,flags, sempre ser no tamanho da tela
    al_draw_bitmap(ibagem2,0,0,0);
    al_draw_bitmap (ibagem3,0,0,0);

    al_flip_display();
    al_rest(40.0);

    return 0;
}
