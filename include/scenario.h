#ifndef SCENARIO_H
#define SCENARIO_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
#endif

#include "globals.h"
#include "ships.h"
#include "animations.h"


typedef struct
{
    int x;
    int y;
    float vel;
} Estrelas;

typedef struct
{
    int investigado;
    int pontuacao;
} Tile;

void init_planos(Estrelas planos[][MAX_ESTRELAS]);
void atualiza_planos(Estrelas planos[][MAX_ESTRELAS]);
void desenha_planos(Estrelas planos[][MAX_ESTRELAS]);
void init_grid(Tile g[][COLUNAS]);
void desenha_grid(ALLEGRO_BITMAP *img, Tile g[][COLUNAS]);
void atualiza_grid(Tile grid[][COLUNAS], Nave *nave, ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_tile, Explosao exp[][COLUNAS]);
int verifica_grid(Tile g[][COLUNAS]);
void falhou(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS]);
void completou(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS], int nave_win, char nick[]);
void incompleto(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS], char nick[]);
void verifica_colisao_1(Explosao exp[][COLUNAS], ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_colision , Nave *nave, Nave *inimigo);
void verifica_colisao_2(Explosao exp[][COLUNAS], ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_colision , Nave *nave, Nave *inimigo);
void contagem_regressiva_f(ALLEGRO_EVENT_QUEUE *event_queue);

#endif