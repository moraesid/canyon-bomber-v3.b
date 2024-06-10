#ifndef STATS_H
#define STATS_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
#endif

#include "ships.h"
#include "globals.h"
#include <string.h>


int nickname(ALLEGRO_EVENT ev_menu, char nick[]);
void desenha_atributos_nave(Nave *nave1, Nave *nave2, ALLEGRO_FONT *font1, ALLEGRO_FONT *font2);

#endif