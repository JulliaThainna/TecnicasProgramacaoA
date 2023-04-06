#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main (){
    al_init ();
    ALLEGRO_DISPLAY *display = NULL;
    display=al_create_display (500,516);
    al_clear_to_color(al_map_rgb(100,0,0));
    al_flip_display ();
    al_rest (3);
    return 0;
}
