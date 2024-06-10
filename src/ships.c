#include "ships.h"


void init_nave(Nave *nave, ALLEGRO_BITMAP *img_tiro, int dim_w, int dim_h, int max_q, int id_nave)
{ 
    nave->id = id_nave;
    if (id_nave == 100)
    {
        nave->x = -w_xwing;
        nave->y = posy_inicial_1;
        nave->posY = 1;
        nave->cor = al_map_rgba_f(0,0,0.25,0.3);
        nave->cor_t = al_map_rgb(0,0,255);
    }
    else if (id_nave == 200)
    {
        nave->x = SCREEN_W + 5;
        nave->y = posy_inicial_2;
        nave->posY = 2;
        nave->cor = al_map_rgba_f(0.25,0,0,0.3);
        nave->cor_t = al_map_rgb(255,0,0);
    }
    
    init_sprites_nave(nave);

    nave->ativo = 1;
    nave->fase = 0;
    nave->imgAtual = NULL;
    nave->imgD = nave->sprites[0];
    nave->imgE = nave->sprites[1];
    nave->win = 0;
    nave->vel = 3;
    nave->vidas = 3;
    nave->defesa = 150;
    nave->escudo = 0;
    nave->atingido = 0;
    nave->tempoInvalido = 0;
    nave->contTempo = 0;
    nave->pontos = 0;
    nave->quadroAtual = 0;
    nave->quadroCont = 0;
    nave->quadroMax = max_q;
    nave->quadroDelay = 0.25;
    nave->quadroH = dim_h;
    nave->quadroW = dim_w;
    nave->tiro.x = 0;
    nave->tiro.y = 0; 
    nave->tiro.img = img_tiro;
    nave->tiro.quadroH = 30;
    nave->tiro.quadroW = 20;
    nave->tiro.quadroAtual = 0;
    nave->tiro.quadroCont = 0;
    nave->tiro.quadroDelay = 1;
    nave->tiro.quadroMax = 3;
    nave->tiro.ativo = 0;
    nave->tiro.hit = 0;
    nave->tiro.vel_y = 0;
    nave->tiro.acel_y = 0.05;
    nave->tirof.ativo = 0;
    nave->tirof.x = 0;
    nave->tirof.y = 0;
    nave->tirof.vel = 10;
}

void init_sprites_nave(Nave *nave)
{
    switch (nave->id)
    {
        case 100:
            nave->sprites[0] = xwingS1_100;
            nave->sprites[1] = xwingS2_100;
            nave->sprites[2] = xwingS1_101;
            nave->sprites[3] = xwingS2_101;
            nave->sprites[4] = xwingS1_102;
            nave->sprites[5] = xwingS2_102;
            break;
        case 200:
            nave->sprites[0] = viperS1_200;
            nave->sprites[1] = viperS2_200;
            nave->sprites[2] = viperS1_201;
            nave->sprites[3] = viperS2_201;
            nave->sprites[4] = viperS1_202;
            nave->sprites[5] = viperS2_202;
            break;
    }
}

void seleciona_sprites_naves(Nave *nave_1, Nave *nave_2)
{
    if (nave_1->x > SCREEN_W + 5 && nave_1->vel > 0)
    {
        nave_1->quadroAtual = 0;
        nave_1->quadroCont = 0;
        nave_2->quadroAtual = 0;
        nave_2->quadroCont = 0;
        
        int pseudo_aleatorio = rand () % 5;
        if (pseudo_aleatorio % 2) pseudo_aleatorio++;

        nave_1->imgD = nave_1->sprites[pseudo_aleatorio];
        nave_1->imgE = nave_1->sprites[pseudo_aleatorio + 1];
        nave_2->imgD = nave_2->sprites[pseudo_aleatorio];
        nave_2->imgE = nave_2->sprites[pseudo_aleatorio + 1];

        switch (pseudo_aleatorio)
        {
            case 0:
                nave_1->vel = 3;
                nave_2->vel = -3;
                break;
            case 2:
                nave_1->vel = 3.5;
                nave_2->vel = -3.5;
                break;
            case 4:
                nave_1->vel = 4;
                nave_2->vel = -4;
                break;
            default:
                nave_1->vel = 3;
                nave_2->vel = -3;
                break;
        }
    }
    else if (nave_1->x < -w_xwing && nave_1->vel < 0)
    {
        nave_1->quadroAtual = 0;
        nave_1->quadroCont = 0;
        nave_2->quadroAtual = 0;
        nave_2->quadroCont = 0;
        
        int pseudo_aleatorio = rand () % 5;
        if (pseudo_aleatorio % 2) pseudo_aleatorio++;

        nave_1->imgD = nave_1->sprites[pseudo_aleatorio];
        nave_1->imgE = nave_1->sprites[pseudo_aleatorio + 1];
        nave_2->imgD = nave_2->sprites[pseudo_aleatorio];
        nave_2->imgE = nave_2->sprites[pseudo_aleatorio + 1];

        switch (pseudo_aleatorio)
        {
            case 0:
                nave_1->vel = -3;
                nave_2->vel = 3;
                break;
            case 2:
                nave_1->vel = -3.5;
                nave_2->vel = 3.5;
                break;
            case 4:
                nave_1->vel = -4;
                nave_2->vel = 4;
                break;
            default:
                nave_1->vel = -3;
                nave_2->vel = 3;
                break;
        }
    }
}

void desenha_nave(Nave *nave)
{
    if (nave->ativo)
    {
        if (nave->tempoInvalido < 5 || !nave->atingido) 
            al_draw_bitmap_region(nave->imgAtual, nave->quadroAtual * nave->quadroW, 0, nave->quadroW, nave->quadroH, nave->x, nave->y, 0);
        if (nave->tiro.ativo) 
            al_draw_bitmap_region(nave->tiro.img, nave->tiro.quadroAtual * nave->tiro.quadroW, 0, nave->tiro.quadroW, nave->tiro.quadroH, nave->tiro.x, nave->tiro.y, 0);
        if (nave->tirof.ativo)
            al_draw_filled_rectangle(nave->tirof.x, nave->tirof.y - 1, nave->tirof.x + 50, nave->tirof.y + 1, nave->cor_t);
        if (nave->escudo) 
            al_draw_filled_ellipse(nave->x + nave->quadroW / 2, nave->y + nave->quadroH / 2, nave->quadroW / 2 + 10, nave->quadroH * 0.7, nave->cor);
    }
}

void seleciona_posy_naves(Nave *nave_1, Nave *nave_2)
{
    if (nave_1->x > SCREEN_W + 5 && nave_1->vel > 0)
    {
        srand(time(NULL));
        if (rand() % 2)
        {
            float aux = nave_1->y;
            nave_1->y = nave_2->y;
            nave_2->y = aux;
        }
    }
    else if (nave_1->x < -w_xwing && nave_1->vel < 0)
    {
        srand(time(NULL));
        if (rand() % 2)
        {
            float aux = nave_1->y;
            nave_1->y = nave_2->y;
            nave_2->y = aux;
        }
    }
}

void atualiza_nave(Nave *nave_1)
{
    if (nave_1->ativo)
    {
        if (++(nave_1->quadroCont) >= nave_1->quadroDelay)
        {
            if (++(nave_1->quadroAtual) >= nave_1->quadroMax)
                nave_1->quadroAtual = 0;
            nave_1->quadroCont = 0;
        }   
        if (nave_1->tiro.ativo)
        {
            if (++(nave_1->tiro.quadroCont) >= nave_1->tiro.quadroDelay) 
            {
                if (++(nave_1->tiro.quadroAtual) >= nave_1->tiro.quadroMax)
                    nave_1->tiro.quadroAtual = 0;
                nave_1->tiro.quadroCont = 0;
            }
        }
        if (nave_1->pontos >= 100 && nave_1->pontos <= 300) nave_1->fase = 1;
        else if (nave_1->pontos >= 300 && nave_1->pontos <= 500) nave_1->fase = 2;
        else if (nave_1->pontos >= 500 && nave_1->pontos <= 700) nave_1->fase = 3;
        else if (nave_1->pontos >= 700 && nave_1->pontos <= 1000) nave_1->fase = 4;
        else if (nave_1->pontos >= 1000 && nave_1->pontos <= 1700) nave_1->fase = 5;
        
        // Efeito de "piscar" a Nave-Jogador caso atingida
        if (nave_1->atingido)
        {
            if (nave_1->tempoInvalido > 10) nave_1->tempoInvalido = 0;
            nave_1->tempoInvalido++;
            nave_1->contTempo++;

            if (nave_1->contTempo == 100 || nave_1->x > SCREEN_W || nave_1->x < -nave_1->quadroW)
            {
                nave_1->atingido = 0;
                nave_1->tempoInvalido = 0;
                nave_1->contTempo = 0;                    
            }
        }
        
        // atualiza posicao da nave
        if (nave_1->x > SCREEN_W + 5 && nave_1->vel > 0)
        {
            nave_1->imgAtual = nave_1->imgE;
            nave_1->vel *= -1;
        }
        else if (nave_1->x < -w_xwing && nave_1->vel < 0)
        {
            nave_1->imgAtual = nave_1->imgD;
            nave_1->vel *= -1;
        }
        nave_1->x += nave_1->vel;

        if (!nave_1->imgAtual && nave_1->x < 0)
            nave_1->imgAtual = nave_1->imgD;
        else if (!nave_1->imgAtual && nave_1->x > SCREEN_W)
            nave_1->imgAtual = nave_1->imgE;

        // atualiza tiro
        if (nave_1->tiro.ativo && nave_1->vel > 0)
        {
            nave_1->tiro.x = nave_1->x + nave_1->quadroW;
            nave_1->tiro.vel_y += nave_1->tiro.acel_y;
            nave_1->tiro.y += nave_1->tiro.vel_y;
        }
        else if (nave_1->tiro.ativo && nave_1->vel < 0)
        {
            nave_1->tiro.x = nave_1->x;
            nave_1->tiro.vel_y += nave_1->tiro.acel_y;
            nave_1->tiro.y += nave_1->tiro.vel_y;
        }
        if (nave_1->tiro.x < -RAIO_TIRO || nave_1->tiro.x > SCREEN_W + RAIO_TIRO || nave_1->tiro.y > SCREEN_H + RAIO_TIRO)
            nave_1->tiro.ativo = 0;

        //atualiza tirof
        if (nave_1->tirof.ativo && nave_1->vel > 0)
            nave_1->tirof.x += nave_1->tirof.vel;
        else if (nave_1->tirof.ativo && nave_1->vel < 0)
            nave_1->tirof.x -= nave_1->tirof.vel;
        if (nave_1->tirof.x < -RAIO_TIRO || nave_1->tirof.x > SCREEN_W + RAIO_TIRO)
            nave_1->tirof.ativo = 0;
    }
}

void verifica_fase(Nave *nave, Nave *inimigo)
{
    if (!inimigo->ativo)
    {
        srand(time(NULL));
        int pseudo_aleatorio = -1;
        
        switch (nave->fase)
        {
            case 1:
                pseudo_aleatorio = rand() % 5;
                break;
            case 2:
                pseudo_aleatorio = rand() % 4;
                inimigo->vel = 2.5;
                break;
            case 3:
                pseudo_aleatorio = rand() % 3;
                inimigo->vel = 3;
                break;
            case 4:
                pseudo_aleatorio = rand() % 2;
                inimigo->vel = 3.5;
                break;
            case 5:
                pseudo_aleatorio = 0;
                inimigo->vel = 4;
                break;
            default:
                pseudo_aleatorio = -1;
                inimigo->vel = 1;
                break;
        }
        if (!pseudo_aleatorio)
        {
            if (nave->x + ((-1) * nave->vel) > SCREEN_W + 5 && nave->vel < 0)
            {
                inimigo->ativo = 1;
                inimigo->tirof.ativo = 1;
                inimigo->x = -inimigo->quadroW;
                if (nave->id < 200)
                {
                    inimigo->y = nave->y - inimigo->quadroH * 0.20;
                    inimigo->tirof.x = inimigo->x + inimigo->quadroW / 2; 
                    inimigo->tirof.y = inimigo->y + inimigo->quadroH * 0.55;
                }
                else if (nave->id < 300)
                {
                    inimigo->y = nave->y + 15;
                    inimigo->tirof.x = inimigo->x + inimigo->quadroW;
                    inimigo->tirof.y = inimigo->y + inimigo->quadroH * 0.7 - 15;
                }
            }
            else if (nave->x - nave->vel < -nave->quadroW && nave->vel > 0)
            {
                inimigo->ativo = 1;
                inimigo->tirof.ativo = 1;
                inimigo->x = SCREEN_W + 5;
                if (nave->id < 200)
                {
                    inimigo->y = nave->y - inimigo->quadroH * 0.20;
                    inimigo->tirof.x = inimigo->x - inimigo->quadroW / 2; 
                    inimigo->tirof.y = inimigo->y + inimigo->quadroH * 0.55;
                }
                else if (nave->id < 300)
                {
                    inimigo->y = nave->y + 15;
                    inimigo->tirof.x = inimigo->x; 
                    inimigo->tirof.y = inimigo->y + inimigo->quadroH * 0.7 - 15;
                }
            }
        }
    }
}

void init_nave_i(Nave *nave, ALLEGRO_BITMAP *img_nave_d, ALLEGRO_BITMAP *img_nave_e, int dim_w, int dim_h, int max_q, int id_nave)
{
    if (id_nave == 110) nave->cor_t = al_map_rgb(0,255,0);
    else if (id_nave == 210) nave->cor_t = al_map_rgb(255,255,255);
    nave->id = id_nave;
    nave->ativo = 0;
    nave->imgAtual = NULL; 
    nave->imgD = img_nave_d;
    nave->imgE = img_nave_e;
    nave->x = 0;
    nave->y = 0;
    nave->vel = 2;
    nave->quadroAtual = 0;
    nave->quadroCont = 0;
    nave->quadroMax = max_q;
    nave->quadroDelay = 1;
    nave->quadroH = dim_h;
    nave->quadroW = dim_w;
    nave->tirof.ativo = 1;
    nave->tirof.x = 0;
    nave->tirof.y = 0;
    nave->tirof.vel = 6;
}

void atualiza_nave_i(Nave *nave_1, Nave *nave_2)
{
    if (nave_1->ativo)
    {
        if (++(nave_1->quadroCont) >= nave_1->quadroDelay)
        {
            if (++(nave_1->quadroAtual) >= nave_1->quadroMax)
                nave_1->quadroAtual = 0;
            nave_1->quadroCont = 0;
        }   
        if (nave_1->tiro.ativo)
        {
            if (++(nave_1->tiro.quadroCont) >= nave_1->tiro.quadroDelay) 
            {
                if (++(nave_1->tiro.quadroAtual) >= nave_1->tiro.quadroMax)
                    nave_1->tiro.quadroAtual = 0;
                nave_1->tiro.quadroCont = 0;
            }
        }
        
        // atualiza posicao da nave
        if (nave_1->x > SCREEN_W && nave_1->vel > 0)
        {      
            nave_1->imgAtual = nave_1->imgE;
            nave_1->vel *= -1;
        }
        else if (nave_1->x < -nave_2->quadroW && nave_1->vel < 0)
        {      
            nave_1->imgAtual = nave_1->imgD;
            nave_1->vel *= -1;
        }
        nave_1->x += nave_1->vel;

        if (!nave_1->imgAtual && nave_1->x < 0)
            nave_1->imgAtual = nave_1->imgD;
        else if (!nave_1->imgAtual && nave_1->x > SCREEN_W)
            nave_1->imgAtual = nave_1->imgE;                

        // atualiza tirof
        if (nave_1->tirof.ativo && nave_1->vel > 0)
            nave_1->tirof.x += nave_1->tirof.vel;
        else if (nave_1->tirof.ativo && nave_1->vel < 0)
            nave_1->tirof.x -= nave_1->tirof.vel;
    }
}

void desenha_nave_i(Nave *nave)
{
    if (nave->ativo)
    {
        al_draw_bitmap_region(nave->imgAtual, nave->quadroAtual * nave->quadroW, 0, nave->quadroW, nave->quadroH, nave->x, nave->y, 0);
        if (nave->tirof.ativo)
            al_draw_filled_rectangle(nave->tirof.x, nave->tirof.y - 1, nave->tirof.x + 50, nave->tirof.y + 1, nave->cor_t);
    }
}