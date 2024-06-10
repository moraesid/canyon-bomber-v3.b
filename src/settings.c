#include "globals.h"
#include "records.h"
#include <stdio.h>
#include <stdlib.h>

#include "settings.h"


int load_settings(void)
{
    FILE *file;
    // carrega configuracoes
    file = fopen(configs_arq, "r");
    if (!file)
    {
       //fprintf(stderr, "ERRO 1: arquivo de configurações não encontrado!\n"); 
       fclose(file);
       return 0;
    }
    else if (file)
    {
        fscanf(file, "%d %d %d %d", &xcon_1_save, &xcon_2_save, &xcon_3_save, &xcon_4_save);
        fscanf(file, "%f %f %f", &GAIN_SFX, &GAIN_TRACK_PLAY_GAME, &GAIN_TRACK_MENUS);
        fscanf(file, "%f %f %f", &x1_vol, &x2_vol, &x3_vol);
        fclose(file);
    }
    return 1;
}

void save_settings(void)
{
    FILE *file;
    file = fopen(configs_arq, "w");
    fprintf(file, "%d %d %d %d", xcon_1_save, xcon_2_save, xcon_3_save, xcon_4_save);
    fprintf(file, "\n%f %f %f", GAIN_SFX, GAIN_TRACK_PLAY_GAME, GAIN_TRACK_MENUS);
    fprintf(file, "\n%f %f %f", x1_vol, x2_vol, x3_vol);
    fclose(file); 
}

void save_history(Nave *nave_1, Nave *nave_2)
{
    Registro *regs[MAX_REGS];
    int num_cads = ler_regs(regs);
   
    if (!num_cads)
    {
        file = fopen(historico_arq, "w");
        fprintf(file, "%d\n", 2);
        fprintf(file, "%s,%d,%d\n", nick_1, nave_1->win, nave_1->pontos);
        fprintf(file, "%s,%d,%d", nick_2, nave_2->win, nave_2->pontos);
        fclose(file);
    }
    else
    { 
        int var_1 = atualiza_regs(regs, num_cads, nave_1, nick_1);
        int var_2 = atualiza_regs(regs, num_cads, nave_2, nick_2);
        ordena_regs(regs, num_cads);
        
        if (var_1 && var_2)
            escrever_regs(regs, file, nave_1, nave_2, num_cads, 3);
        else if (var_1 && !var_2)
            escrever_regs(regs, file, nave_1, nave_2, num_cads, 1);
        else if (!var_1 && var_2)
            escrever_regs(regs, file, nave_1, nave_2, num_cads, 2);
        else if (!var_1 && !var_2)
            escrever_regs(regs, file, nave_1, nave_2, num_cads, 0);  
    }
    return;
}
