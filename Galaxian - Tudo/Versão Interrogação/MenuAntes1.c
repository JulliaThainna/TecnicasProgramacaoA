#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <allegro5/allegro.h>

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include <allegro5/allegro_image.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#define FPS 60
#define LARGURA 680
#define ALTURA 500

enum KEYS {UP, DOWN, ENTER};
int main (){
     bool keys [3] = {false, false,false};
     bool Exit = false;
     bool Game = false;
     bool FecharJanela = false;
     bool Movimento = true;
     bool JogoMenu = true;
     bool MudarOpcao;
     int Opcao=0;

     int x = 340, y = 250, xnave = 340;

     al_init();

     al_init_image_addon();

     al_install_audio();
     al_init_acodec_addon();
     al_reserve_samples(5);

     al_init_font_addon ();
     al_init_ttf_addon ();

     al_install_keyboard();

     ALLEGRO_DISPLAY *JANELA = NULL;
     ALLEGRO_TIMER *TimerFPS = NULL;
     ALLEGRO_EVENT_QUEUE *MENU = NULL;
     ALLEGRO_BITMAP *FundoMenu = NULL;
     ALLEGRO_BITMAP *LogoMenu = NULL;
     ALLEGRO_SAMPLE *SomMenu = NULL;
     ALLEGRO_FONT *FonteMenu1 = NULL;
     ALLEGRO_FONT *FonteMenu2 = NULL;
     ALLEGRO_FONT *FonteMenu3 = NULL;

     JANELA = al_create_display(LARGURA,ALTURA);
     MENU = al_create_event_queue();
     FundoMenu = al_load_bitmap("Imagens//FundoMenu.png");
     LogoMenu = al_load_bitmap("Imagens//Logo.png");
     SomMenu = al_load_sample("Sons//SomMenu.ogg");
     al_play_sample (SomMenu,1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
     FonteMenu1 = al_load_font ("Fontes//FonteMenu1.ttf",9,0);
     FonteMenu2 = al_load_font ("Fontes//FonteMenu2.ttf",60,0);
     FonteMenu3 = al_load_font ("Fontes//FonteMenu1.ttf",20,0);

     TimerFPS = al_create_timer(1.0/FPS);

     al_register_event_source(MENU, al_get_display_event_source(JANELA));
     al_register_event_source(MENU, al_get_keyboard_event_source());
     al_register_event_source(MENU, al_get_timer_event_source(TimerFPS));
     al_start_timer(TimerFPS);

     while (JogoMenu==true){
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(FundoMenu,0,0,0);
          al_draw_bitmap(LogoMenu,90,-200,0);
          ALLEGRO_EVENT evento;
          al_wait_for_event(MENU,&evento);

          al_draw_textf(FonteMenu1,al_map_rgb(0, 204, 255),LARGURA/2,133,ALLEGRO_ALIGN_CENTER," [This is certainly not an attempt to copy the Galaxian game]");
          al_draw_textf(FonteMenu1,al_map_rgb(0, 204, 255),LARGURA-5,ALTURA-10,ALLEGRO_ALIGN_RIGHT,"An attempt made by: UEL'S COMPUTEIROS 2019");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-327,ALTURA-90,ALLEGRO_ALIGN_RIGHT,"UEL - Universidade Estadual de Londrina");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-453,ALTURA-80,ALLEGRO_ALIGN_RIGHT,"Ciencia da Computacao    ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-417,ALTURA-70,ALLEGRO_ALIGN_RIGHT,"Projeto de jogo - Programacao");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-508,ALTURA-50,ALLEGRO_ALIGN_RIGHT,"ALUNOS:            ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-554,ALTURA-10,ALLEGRO_ALIGN_RIGHT,"Andre Ferreira");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-554,ALTURA-30,ALLEGRO_ALIGN_RIGHT,"Jullia Thainna");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA-554,ALTURA-20,ALLEGRO_ALIGN_RIGHT,"Tatiane Soares");

          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),LARGURA/2,y+90,ALLEGRO_ALIGN_CENTER,"    |      ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),380,y+30,ALLEGRO_ALIGN_CENTER,"    |      ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),270,y-10,ALLEGRO_ALIGN_CENTER,"    |      ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),350,y-30,ALLEGRO_ALIGN_CENTER,"    |      ");
          al_draw_textf(FonteMenu1, al_map_rgb(255,255,255),280,y-70,ALLEGRO_ALIGN_CENTER,"    |      ");
          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),x,y-100,ALLEGRO_ALIGN_CENTER,"E E E E E E ");
          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),x,y-50,ALLEGRO_ALIGN_CENTER,"C C C C C C ");
          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),x,y,ALLEGRO_ALIGN_CENTER,"D D D D D D ");
          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),x,y+50,ALLEGRO_ALIGN_CENTER,"J J J J J J ");
          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),xnave,y+95,ALLEGRO_ALIGN_CENTER,"     G      ");

          al_draw_textf(FonteMenu3,al_map_rgb(0, 196, 152),LARGURA-160,ALTURA-150, ALLEGRO_ALIGN_LEFT," START");
          al_draw_textf(FonteMenu3,al_map_rgb(0,196,152),LARGURA-160,ALTURA-100, ALLEGRO_ALIGN_LEFT," EXIT");

          if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
               switch (evento.keyboard.keycode){
               case ALLEGRO_KEY_UP:
                    Opcao = 0;
                    break;
               case ALLEGRO_KEY_DOWN:
                    Opcao = 1;
                    break;
               case ALLEGRO_KEY_ENTER:
                    if (Opcao == 0){
                         JogoMenu = false;
                         Game = true;
                    }
                    else {
                         JogoMenu = false;
                         Exit = true;
                    }
                    break;
               }
          }


          if (Opcao == 0){
               al_draw_textf(FonteMenu3,al_map_rgb(186, 294, 204),LARGURA-160,ALTURA-150, ALLEGRO_ALIGN_LEFT,">START");
               al_draw_textf(FonteMenu3,al_map_rgb(13, 196, 152),LARGURA-160,ALTURA-100, ALLEGRO_ALIGN_LEFT," EXIT");
          }
          else {
               al_draw_textf(FonteMenu3,al_map_rgb(13, 196, 152),LARGURA-160,ALTURA-150, ALLEGRO_ALIGN_LEFT," START");
               al_draw_textf(FonteMenu3,al_map_rgb(186, 294, 204),LARGURA-160,ALTURA-100, ALLEGRO_ALIGN_LEFT,">EXIT");
          }


          if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
               JogoMenu = false;
               Exit = true;
          }

          //mecânica de movimento dos aliens na tela
          if (Movimento == true) {
               x ++;
               xnave ++;
          }
          if ((x > LARGURA-300) || (xnave > LARGURA-300)){
               x = 260;
               xnave = x;
          }

          if (evento.type == ALLEGRO_EVENT_TIMER){
               al_flip_display();
          }
     }

     return 0;
}
