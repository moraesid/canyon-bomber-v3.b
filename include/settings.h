#ifndef SETTINGS_H
#define SETTINGS_H

#include "ships.h"


int load_settings(void);
void save_settings(void);
void save_history(Nave *nave_1, Nave *nave_2);

#endif