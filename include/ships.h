#ifndef SHIPS_H
#define SHIPS_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
#endif

#include "globals.h"
#include "animations.h"
#include <stdlib.h>


typedef struct 
{
    float x, y;
    int ativo;
    int hit;
    float vel_y;
    float acel_y;
    int quadroW;
    int quadroH;
    int quadroAtual;
    int quadroMax;
    int quadroDelay;
    int quadroCont;
    ALLEGRO_BITMAP *img;
} Tiro;

typedef struct 
{
    float x, y;
    int ativo;
    float vel;
} Tirof;

typedef struct 
{
    int id;
    int ativo;
    int fase;
    float x, y;
    float vel;
    int posY;
    int vidas;
    int pontos;
    int quadroH;
    int quadroW;
    int quadroMax;
    int quadroAtual;
    int quadroCont;
    int quadroDelay;
    int win;
    int defesa;
    int escudo;
    int atingido;
    int tempoInvalido;
    int contTempo;
    Tiro tiro;
    Tirof tirof;
    Explosao exp;
    ALLEGRO_COLOR cor;
    ALLEGRO_COLOR cor_t;
    ALLEGRO_BITMAP *imgAtual;
    ALLEGRO_BITMAP *imgD;
    ALLEGRO_BITMAP *imgE;
    ALLEGRO_BITMAP *sprites[6];
} Nave;

void init_nave(Nave *nave, ALLEGRO_BITMAP *img_tiro, int dim_w, int dim_h, int max_q, int id_nave);
void init_sprites_nave(Nave *nave);
void desenha_nave(Nave *nave);
void atualiza_nave(Nave *nave_1);   
void verifica_fase(Nave *nave, Nave *inimigo);
void init_nave_i(Nave *nave, ALLEGRO_BITMAP *img_nave_d, ALLEGRO_BITMAP *img_nave_e, int dim_w, int dim_h, int max_q, int id_nave);
void atualiza_nave_i(Nave *nave_1, Nave *nave_2);
void desenha_nave_i(Nave *nave);
void seleciona_sprites_naves(Nave *nave_1, Nave *nave_2);
void seleciona_posy_naves(Nave *nave_1, Nave *nave_2);

#endif