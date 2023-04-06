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

enum KEYS {UP, DOWN, ENTER, SPACE};
int main (){
     bool keys [4] = {false, false,false,false},
          Exit = false;
     int x=340, y=250, Opcao=0;

     al_init();

     al_init_image_addon();

     al_init_font_addon ();
     al_init_ttf_addon ();

     al_install_keyboard();

     ALLEGRO_DISPLAY *JANELA = NULL;
     ALLEGRO_TIMER *TimerFPS = NULL;
     ALLEGRO_EVENT_QUEUE *TELAPONTOS = NULL;
     ALLEGRO_BITMAP *FundoMenu = NULL;
     ALLEGRO_BITMAP *Invasor1 = NULL;
     ALLEGRO_BITMAP *Invasor2 = NULL;
     ALLEGRO_BITMAP *Invasor3 = NULL;
     ALLEGRO_BITMAP *Invasor4 = NULL;
     ALLEGRO_FONT *FonteMenu1 = NULL;
     ALLEGRO_FONT *FonteMenu2 = NULL;
     ALLEGRO_FONT *FonteMenu3 = NULL;
     ALLEGRO_FONT *Fonte4 = NULL;
     ALLEGRO_FONT *Fonte3 = NULL;
     ALLEGRO_FONT *FonteFrase = NULL;

     JANELA = al_create_display(LARGURA,ALTURA);
     TELAPONTOS = al_create_event_queue();
     FundoMenu = al_load_bitmap("Imagens//FundoMenu.png");
     Invasor1 = al_load_bitmap("Imagens//Invasor1.png");
     Invasor2 = al_load_bitmap("Imagens//Invasor2.png");
     Invasor3 = al_load_bitmap("Imagens//Invasor3.png");
     Invasor4 = al_load_bitmap("Imagens//Invasor4.png");
     FonteMenu1 = al_load_font ("Fontes//Sunset-Boulevard.otf",35,0);
     FonteMenu2 = al_load_font ("Fontes//FonteMenu2.ttf",60,0);
     FonteMenu3 = al_load_font ("Fontes//FonteMenu1.ttf",15,0);
     Fonte4 = al_load_font ("Fontes//fonte-4.ttf",20,0);
     Fonte3 = al_load_font ("Fontes//fonte-3.ttf",20,0);
     FonteFrase = al_load_font ("Fontes//fonte-riscada-2.ttf",20,0);

     TimerFPS = al_create_timer(1.0/FPS);

     al_register_event_source(TELAPONTOS, al_get_display_event_source(JANELA));
     al_register_event_source(TELAPONTOS, al_get_keyboard_event_source());
     al_register_event_source(TELAPONTOS, al_get_timer_event_source(TimerFPS));
     al_start_timer(TimerFPS);

     while (!Exit){
          al_clear_to_color(al_map_rgb(0,0,0));
          al_draw_bitmap(FundoMenu,0,0,0);
          ALLEGRO_EVENT evento;
          al_wait_for_event(TELAPONTOS,&evento);

          al_draw_textf(FonteMenu2, al_map_rgb(255,255,255),x+10,y-200,ALLEGRO_ALIGN_CENTER,"E E E E E E E E E E");
          al_draw_textf(FonteMenu1, al_map_rgb(255, 255, 0),LARGURA/2-135,y-150,ALLEGRO_ALIGN_CENTER,"WE ARE");
          al_draw_textf(FonteFrase, al_map_rgb(255, 255, 0),LARGURA/2-15,y-135,ALLEGRO_ALIGN_CENTER,"COMPUTEIROS ");
          al_draw_textf(FonteMenu1, al_map_rgb(255, 255, 0),LARGURA/2+130,y-150,ALLEGRO_ALIGN_CENTER,"THE GALAXIANS");
          al_draw_textf(FonteMenu1, al_map_rgb(255, 0, 0),LARGURA-560,y-100,ALLEGRO_ALIGN_CENTER,"MISSION: ");
          al_draw_textf(FonteFrase, al_map_rgb(230, 46, 0),LARGURA-380,y-90,ALLEGRO_ALIGN_CENTER," NAO RETER EM PROGRAMACAO");
          al_draw_textf(FonteMenu1, al_map_rgb(255, 0, 0),LARGURA-150,y-100,ALLEGRO_ALIGN_CENTER,"  DESTROY ALIENS ");

          al_draw_text(Fonte4,al_map_rgb(191, 191, 191),LARGURA/2-140,ALTURA-270, ALLEGRO_ALIGN_LEFT,"SCORE ADVANCE TABLE");
          al_draw_textf(Fonte3,al_map_rgb(255, 255, 255),LARGURA/2-70,ALTURA-232,ALLEGRO_ALIGN_LEFT,"   60   pts");
          al_draw_textf(Fonte3,al_map_rgb(255, 255, 255),LARGURA/2-70,ALTURA-200,ALLEGRO_ALIGN_LEFT,"   50   pts");
          al_draw_textf(Fonte3,al_map_rgb(255, 255, 255),LARGURA/2-70,ALTURA-170,ALLEGRO_ALIGN_LEFT,"   40   pts");
          al_draw_textf(Fonte3,al_map_rgb(255, 255, 255),LARGURA/2-70,ALTURA-140,ALLEGRO_ALIGN_LEFT,"   30   pts");
          al_draw_textf(Fonte3,al_map_rgb(255, 255, 255),LARGURA/2-140,ALTURA-100,ALLEGRO_ALIGN_LEFT,"5000 pts + 1 vida");

          al_draw_bitmap(Invasor1,LARGURA/2-100,ALTURA-147,ALLEGRO_ALIGN_LEFT);
          al_draw_bitmap(Invasor2,LARGURA/2-100,ALTURA-180,ALLEGRO_ALIGN_LEFT);
          al_draw_bitmap(Invasor3,LARGURA/2-100,ALTURA-210,ALLEGRO_ALIGN_LEFT);
          al_draw_bitmap(Invasor4,LARGURA/2-103,ALTURA-245,ALLEGRO_ALIGN_LEFT);

          if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
               switch (evento.keyboard.keycode) {
                    case ALLEGRO_KEY_SPACE:
                         keys[SPACE] = true;
                         Opcao = 1;
				break;
			}
		}
          if (Opcao == 0){
               al_draw_textf(FonteMenu3,al_map_rgb(0, 255, 255),LARGURA-530,ALTURA-40,ALLEGRO_ALIGN_LEFT,"press SPACE to go to menu");
          }
          else {
               al_draw_textf(FonteMenu3,al_map_rgb(13, 196, 152),LARGURA-530,ALTURA-40,ALLEGRO_ALIGN_LEFT,"press SPACE to go to menu");
          }

          if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
               //FecharJanela = true;
               Exit = true;
          }

          if (evento.type == ALLEGRO_EVENT_TIMER){
               al_flip_display();
          }
     }
     return 0;
}

