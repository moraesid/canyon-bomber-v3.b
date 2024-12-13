#include "records.h"


int ler_regs(Registro **regs)
{
    FILE *file = fopen(historico_arq, "r");
    int cads = 0;
    Registro *add = malloc(sizeof(Registro));
    char buffer[MAX_STRING];
    
    if (!file) 
    {
        return 0;
    }
    else
    {
        fscanf(file, "%d\n", &cads);
        for (int i=0; i<cads; i++)
        {
            fgets(buffer, MAX_STRING, file);
            strcpy(add->nome, strtok(buffer, ","));
            add->vitorias = atoi(strtok(NULL, ","));
            add->pontos = atoi(strtok(NULL, ","));
            regs[i] = add;
            add = malloc(sizeof(Registro));
        }
        fclose(file);
    }
    return cads;
}

int atualiza_regs(Registro **regs, int cads, Nave *nave, char nick[])
{
    for (int i=0; i<cads; i++)
    {
        if (!strcmp(regs[i]->nome, nick))
        {
            regs[i]->pontos += nave->pontos;
            regs[i]->vitorias += nave->win;
            return 1;
        }
    }
    return 0;
}

void escrever_regs(Registro **regs, FILE *file, Nave *p1, Nave *p2, int cads, int modo)
{   
    int up_cads = 0;   
    switch (modo)
    {
        case 0: // Jogadores 1 e 2 nao registrados
        {    
            Registro *add_1 = malloc(sizeof(Registro));
            Registro *add_2 = malloc(sizeof(Registro));
            strcpy(add_1->nome, nick_1);
            add_1->pontos = p1->pontos;
            add_1->vitorias = p1->win;
            strcpy(add_2->nome, nick_2);
            add_2->pontos = p2->pontos;
            add_2->vitorias = p2->win;            
            if (cads <= MAX_REGS - 2)
            {
                regs[cads] = add_1;
                regs[cads+1] = add_2;
            }
            else if (cads == MAX_REGS)
            {
                regs[cads-2] = add_1;
                regs[cads-1] = add_2;
            }    
            up_cads = cads + 2;
            break;
        }
        case 1: // Jogador 1 registrado
            Registro *add_2 = malloc(sizeof(Registro));            
            strcpy(add_2->nome, nick_2);
            add_2->pontos = p2->pontos;
            add_2->vitorias = p2->win;              
            if (cads <= MAX_REGS - 1)
                regs[cads] = add_2;          
            else if (cads == MAX_REGS)
                regs[cads-1] = add_2;           
            up_cads = cads + 1;
            break;
        case 2: // Jogador 2 registrado
            Registro *add_1 = malloc(sizeof(Registro));            
            strcpy(add_1->nome, nick_1);
            add_1->pontos = p1->pontos;
            add_1->vitorias = p1->win;             
            if (cads <= MAX_REGS - 1)
                regs[cads] = add_1;          
            else if (cads == MAX_REGS)
                regs[cads-1] = add_1;            
            up_cads = cads + 1;
            break;       
        case 3: // Os 2 jogadores registrados
            up_cads = cads;           
            break;
    }    
    file = fopen(historico_arq, "w");
    fprintf(file, "%d\n", up_cads);
    for (int i=0; i<up_cads; i++)
        fprintf(file, "%s,%d,%d\n", regs[i]->nome, regs[i]->vitorias, regs[i]->pontos);
    fclose(file);
}


void ordena_regs(Registro **regs, int cads)
{
    Registro *aux;
    for (int i=0; i<cads; i++)
    {
        for (int j=i+1; j<cads; j++)
        {
            if (regs[i]->vitorias < regs[j]->vitorias)
            {
                aux = regs[j];
                regs[j] = regs[i];
                regs[i] = aux;
            }
        }
    }
}
