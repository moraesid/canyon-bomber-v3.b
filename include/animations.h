#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
#endif

#include "globals.h"


typedef struct
{
    int x;
    int y;
    int ativo;
    int maxQ;
    int atualQ;
    int contQ;
    int delayQ;
    int wQ;
    int hQ;
    int numCol;
    int dir;    
    ALLEGRO_BITMAP *imagem;
} Explosao;

void init_exp(Explosao exp[][COLUNAS], ALLEGRO_BITMAP *IMGexp);
void desenha_exp(Explosao exp[][COLUNAS]);
void inicia_exp(Explosao exp[][COLUNAS], int x, int y);
void atualiza_exp(Explosao exp[][COLUNAS]);
int fadein_f(int velocidade, ALLEGRO_BITMAP *imagem, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);
int fadeout_f(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue);
void fadeout_with_audio_less(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_AUDIO_STREAM *audio_stream);
void fadeout_with_audio_plus(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_AUDIO_STREAM *audio_stream);
void carregando_f(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue);

#endif