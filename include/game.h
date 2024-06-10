#ifndef GAME_H
#define GAME_H

#include "animations.h"
#include "ships.h"
#include "scenario.h"


void run_game(Nave *nave_1, Nave *nave_2, Nave *inimigo_1, Nave *inimigo_2, Explosao explosoes[][COLUNAS], Tile grid[][COLUNAS], Estrelas planos[][MAX_ESTRELAS]);
void end_game(Nave *nave_1, Nave *nave_2);

#endif