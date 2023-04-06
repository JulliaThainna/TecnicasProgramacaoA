#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> //pra poder usar imagens


int main() {
    int posx = 0, posy = 0;
    int acao = 0;

    bool fechar = false;

    al_init();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_TIMER *timerFPS = NULL; //contador, em um determinado tempo ele dispara um evento
    ALLEGRO_EVENT_QUEUE *filaMenu = NULL; //lista de eventos
    ALLEGRO_BITMAP *nave = NULL;

    janela = al_create_display(500, 500);
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
            case ALLEGRO_KEY_UP:
                printf("Apertei a tecla pra cima");
                acao = 0;
                break;
            case ALLEGRO_KEY_LEFT:
                printf("Apertei a tecla pra esquerda ");
                acao = 1;
                break;
            case ALLEGRO_KEY_DOWN:
                printf("Apertei a tecla pra baixo");
                acao = 2;
                break;
            case ALLEGRO_KEY_RIGHT:
                printf("Apertei a tecla pra direita");
                acao = 3;
                break;
            }

        }

        else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //pra fechar a janela
            fechar = true;
        }

        if (acao == 0)
        {
            posy -= 10;
        }
        else if(acao == 1)
        {
            posx -= 10;
        }
        else if (acao == 2)
        {
            posy += 10;
        }
        else if (acao == 3)
        {
            posx += 10;
        }

        al_draw_bitmap(nave, posx, posy, 0);
        if (evento.type == ALLEGRO_EVENT_TIMER) { //atualizar a tela a cada evento que acontece
            al_flip_display();
        }

    }

    return 0;
}

