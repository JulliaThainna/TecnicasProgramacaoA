#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //pra poder usar imagens


#define FPS 60
#define ALTURA 650
#define LARGURA 800

enum KEYS {UP, DOWN, LEFT, RIGHT};

int main() {
     int posx = 250, posy = 250;
     int acao = 0;
     bool keys[4] = { false, false, false ,false };
     bool fechar = false;

     al_init();
     al_install_keyboard();
     al_init_image_addon();

     ALLEGRO_DISPLAY *janela = NULL;
     ALLEGRO_TIMER *timerFPS = NULL; //contador, em um determinado tempo ele dispara um evento
     ALLEGRO_EVENT_QUEUE *filaMenu = NULL; //lista de eventos
     ALLEGRO_BITMAP *nave = NULL;

     janela = al_create_display(LARGURA, ALTURA);
     filaMenu = al_create_event_queue();
     nave = al_load_bitmap("nave.png");
     timerFPS = al_create_timer(1.0 / 60); //quantas atualizações ele vai ter por segundo

     al_register_event_source(filaMenu, al_get_keyboard_event_source()); //pegar o que ta no teclado, registrar um evento
     al_register_event_source(filaMenu, al_get_display_event_source(janela)); //ele considera um comando externo então tem que trazer esse comando para "dentro" do projeto
     al_register_event_source(filaMenu, al_get_timer_event_source(timerFPS));

     al_start_timer(timerFPS); //ele começa a contar, jogo começa, é bom nao ter outra linha entre while e al_start_times porque tem uma desincronização do timer com o FPS

     while (!fechar) { //equivalente fechar == false

          al_clear_to_color(al_map_rgb(0, 0, 0));
          ALLEGRO_EVENT evento; //salva o evento que esta acontecendo no momento
          al_wait_for_event(filaMenu, &evento); // poe o evento que esta acontecendo na fila
          if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

               switch (evento.keyboard.keycode) {
               case ALLEGRO_KEY_W:
                    printf("\nApertei a tecla pra cima");
                    keys[UP] = true;
                    break;
               case ALLEGRO_KEY_A:
                    printf("\nApertei a tecla pra esquerda ");
                    keys[LEFT] = true;
                    break;
               case ALLEGRO_KEY_S:
                    printf("\nApertei a tecla pra baixo");
                    keys[DOWN] = true;
                    break;
               case ALLEGRO_KEY_D:
                    printf("\nApertei a tecla pra direita");
                    keys[RIGHT] = true;
                    break;
               }

          }
          if (evento.type == ALLEGRO_EVENT_KEY_UP){
               switch (evento.keyboard.keycode) {
               case ALLEGRO_KEY_W:
                    printf("\nSoltei a tecla pra cima");
                    keys[UP] = false;
                    break;
               case ALLEGRO_KEY_A:
                    printf("\nSoltei a tecla pra esquerda ");
                    keys[LEFT] = false;
                    break;
               case ALLEGRO_KEY_S:
                    printf("\nSoltei a tecla pra baixo");
                    keys[DOWN] = false;
                    break;
               case ALLEGRO_KEY_D:
                    printf("\nSoltei a tecla pra direita");
                    keys[RIGHT] = false;
                    break;
               }
          }

          else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //pra fechar a janela
               fechar = true;
          }

          if (posy > 0){
               posy -= keys[UP] * 10;
          }
          if (posy < ALTURA-20){
               posy += keys[DOWN] * 10;
          }
          if (posx > 0){
               posx -= keys[LEFT] * 10;
          }
          if (posx < LARGURA-20){
               posx += keys[RIGHT] * 10;
          }


          al_draw_bitmap(nave, posx, posy, 0);
          if (evento.type == ALLEGRO_EVENT_TIMER) { //atualizar a tela a cada evento que acontece
               al_flip_display();
          }

     }
     return 0;
}

