#ifndef RECORDS_H
#define RECORDS_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
#endif

#include "ships.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nome[5];
    int vitorias;
    int pontos; 
} Registro;

int ler_regs(Registro **regs);
int atualiza_regs(Registro **regs, int cads, Nave *nave, char nick[]);
void escrever_regs(Registro **regs, FILE *file, Nave *p1, Nave *p2, int cads, int modo);
void ordena_regs(Registro **regs, int cads);

#endif