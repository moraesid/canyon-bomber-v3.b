#ifndef ALLEGRO_COMMON
    #include "load_allegro.h"
#endif

#include "scenario.h"


void init_planos(Estrelas planos[][MAX_ESTRELAS])
{
    for (int i = 0; i < NUM_PLANOS; i++)
    {
        for (int j = 0; j < MAX_ESTRELAS; j++)
        {
            planos[i][j].x = 5 + rand() % (SCREEN_W - 10);
            planos[i][j].y = 5 + rand() % (SCREEN_H - 10);
            planos[i][j].vel = 1.5 * (i + 1);
        }
    }
}

void atualiza_planos(Estrelas planos[][MAX_ESTRELAS])
{
    for (int i = 0; i < NUM_PLANOS; i++)
    {
        for (int j = 0; j < MAX_ESTRELAS; j++)
        {
            planos[i][j].x -= planos[i][j].vel;

            if (planos[i][j].x < 0)
                planos[i][j].x = SCREEN_W;
        }
    }
}

void desenha_planos(Estrelas planos[][MAX_ESTRELAS])
{
    for (int i = 0; i < NUM_PLANOS; i++)
    {
        for (int j = 0; j < MAX_ESTRELAS; j++)
        {
            al_draw_pixel(planos[i][j].x, planos[i][j].y, al_map_rgb(255, 255, 255));
        }
    }
}

void init_grid(Tile g[][COLUNAS])
{
    int i, j;   
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            g[i][j].investigado = 0;
            g[i][j].pontuacao = (i + 1) * (2);
        }
    }
}

void desenha_grid(ALLEGRO_BITMAP *img, Tile g[][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (g[i][j].investigado == 0)
                al_draw_bitmap_region(img, j*DIM_X, i*DIM_Y, DIM_X , DIM_Y, j*DIM_X, (SCREEN_H - ARRAY_H) + (i*DIM_Y), 0);
        }
    }
}

void atualiza_grid(Tile grid[][COLUNAS], Nave *nave, ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_tile, Explosao exp[][COLUNAS])
{
    if (nave->tiro.y >= (SCREEN_H - ARRAY_H) && nave->tiro.ativo == 1 && nave->tiro.x < SCREEN_W && nave->tiro.x > 0)
    {
        int j = nave->tiro.x / (SCREEN_W / COLUNAS);
        int i = ((nave->tiro.y - (SCREEN_H - ARRAY_H)) / DIM_Y);

        if (nave->tiro.y >= (SCREEN_H - ARRAY_H) + 100 && nave->tiro.y <= (SCREEN_H - ARRAY_H) + 120 &&
                                nave->tiro.x >= 870 && nave->tiro.x <= 892 && grid[i][j].investigado == 0)
        {
            nave->win = 1;
            nave->pontos += 100;
            for (int i=0; i < LINHAS; i++)
                for (int j = 0; j < COLUNAS; j++)
                {
                    //inicia_exp(exp, j*DIM_X + DIM_X / 2, ((SCREEN_H - ARRAY_H) + (3*DIM_Y)) + DIM_Y / 2);
                    grid[i][j].investigado = 1;
                    exp[i][j].ativo = 1;
                    exp[i][j].x = j*DIM_X + DIM_X / 2;
                    exp[i][j].y = ((SCREEN_H - ARRAY_H) + (i*DIM_Y)) + DIM_Y / 2;
                }   
        }
        else if (grid[i][j].investigado == 0 && nave->tiro.y < SCREEN_H)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_tile);
            nave->tiro.hit += grid[i][j].pontuacao;
            nave->pontos += grid[i][j].pontuacao;
            grid[i][j].investigado = 1;
            inicia_exp(exp, nave->tiro.x, nave->tiro.y);
        }
        else if (nave->tiro.hit == 0 && i == 7)
        {
            nave->vidas--;
            nave->tiro.ativo = 0;
        }
    }
}

int verifica_grid(Tile g[][COLUNAS])
{
    int countTile = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (g[i][j].investigado)
                    countTile++;
        }
    }
    return countTile;
}

void falhou(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS])
{
    int valor = 50;
    int tempo = 0;
    int var_op = 1;
    int base_min = 50;
    int base_max = 255;
    int alfa = base_min;

    while(__true) 
    {   
        alfa += var_op;
        if (alfa >= base_max) var_op *= (-1);
        else if (alfa <= base_min) var_op *= (-1);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_draw_text(font, al_map_rgb(255, 0, 0), SCREEN_W / 2, SCREEN_H / 3 + 50, ALLEGRO_ALIGN_CENTER, "MISSÃO NÃO CONCLUÍDA");
            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(planos_1[i][j].x, planos_1[i][j].y, al_map_rgba(alfa, 0, 0, alfa));
                    al_draw_pixel(planos_2[i][j].x, planos_2[i][j].y, al_map_rgba((255 + valor) - alfa, 0, 0, (255 + valor) - alfa));
                }
            }
            al_flip_display();  
            if (tempo == 150) 
            {
                fadeout_f(1, display, event_queue);
                return;
            }
        }     
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0); 
        tempo++;                   
    }
}

void completou(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS], int nave_win, char nick[])
{
    int valor = 50;
    int var_op = 1;
    int base_min = 50;
    int base_max = 255;
    int alfa = base_min;
    int tam_font = 0;
    int tam_font_2 = 0;

    while(__true) 
    {   
        alfa += var_op;
        if (alfa >= base_max) var_op *= (-1);
        else if (alfa <= base_min) var_op *= (-1);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        if (tam_font < 200)
            font = al_load_font("resources/Fonts/Chronosfer-Demo.ttf", tam_font, 0);
        else
            font = al_load_font("resources/Fonts/Chronosfer-Demo.ttf", tam_font_2, 0); 

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (tam_font < 200)
            {
                al_draw_text(font, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 3 + 50, ALLEGRO_ALIGN_CENTER, "MISSÃO CONCLUÍDA");
                tam_font++;
            }
            else if (tam_font_2 < 75)
            {
                if (nave_win) al_draw_text(font, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 3 - 50, ALLEGRO_ALIGN_CENTER, "BÔNUS +100");
                al_draw_textf(font, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 2 - 50, ALLEGRO_ALIGN_CENTER, "%s VENCEU!!!", nick);
                tam_font_2++;
            }
            else
            {
                if (nave_win) al_draw_text(font, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 3 - 50, ALLEGRO_ALIGN_CENTER, "BÔNUS +100");
                al_draw_textf(font, al_map_rgb(0, 255, 0), SCREEN_W / 2, SCREEN_H / 2 - 50, ALLEGRO_ALIGN_CENTER, "%s VENCEU!!!", nick);
            }

            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(planos_1[i][j].x, planos_1[i][j].y, al_map_rgba(0, alfa, 0, alfa));
                    al_draw_pixel(planos_2[i][j].x, planos_2[i][j].y, al_map_rgba(0, (255 + valor) - alfa, 0, (255 + valor) - alfa));
                }
            }
            al_flip_display();
            if (tam_font_2 == 75)
            {
                fadeout_f(1, display, event_queue);
                return;
            }
        }     
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);                              
    }
}

void incompleto(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_DISPLAY *display, Estrelas planos_1[][MAX_ESTRELAS], Estrelas planos_2[][MAX_ESTRELAS], char nick[])
{
    int valor = 50;
    int tempo = 0;
    int var_op = 1;
    int base_min = 50;
    int base_max = 255;
    int alfa = base_min;

    while(__true) 
    {   
        alfa += var_op;
        if (alfa >= base_max) var_op *= (-1);
        else if (alfa <= base_min) var_op *= (-1);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_draw_text(font, al_map_rgb(0, 0, 255), SCREEN_W / 2, SCREEN_H / 3, ALLEGRO_ALIGN_CENTER, "MISSÃO INCOMPLETA");
            al_draw_textf(font, al_map_rgb(0, 0, 255), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "%s VENCEU", nick);
            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(planos_1[i][j].x, planos_1[i][j].y, al_map_rgba(0, 0, alfa, alfa));
                    al_draw_pixel(planos_2[i][j].x, planos_2[i][j].y, al_map_rgba(0, 0, (255 + valor) - alfa, (255 + valor) - alfa));
                }
            }
            al_flip_display();  
            if (tempo == 150) 
            {
                fadeout_f(1, display, event_queue);
                return;
            }
        }     
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        tempo++;                     
    }
}

void verifica_colisao_1(Explosao exp[][COLUNAS], ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_colision, Nave *nave, Nave *inimigo)
{
    if (nave->vel > 0)
    {
        // Colisao entre Nave-Jogador e Nave-Inimigo
        if (inimigo->ativo && nave->x >= inimigo->x - nave->quadroW)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x, inimigo->y + inimigo->quadroH / 2);        
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 10;
        }
        // Colisao Tiro-Jogador -> Inimigo
        if (inimigo->ativo && nave->tirof.ativo && nave->tirof.x >= inimigo->x - inimigo->quadroW / 2)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            nave->tirof.ativo = 0;
            nave->pontos += 15;
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x, inimigo->y + inimigo->quadroH / 2);            
        }
        // Colisao Tiro-Inimigo -> Jogador
        if (inimigo->ativo && inimigo->tirof.ativo && inimigo->tirof.x <= nave->x + nave->quadroW - 45)
        {
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }            
            else
                nave->defesa -= 5;
            inimigo->tirof.ativo = 0;
        }
    }
    else if (nave->vel < 0)
    {
        // Colisao entre Nave-Jogador e Nave-Inimigo
        if (inimigo->ativo && inimigo->x >= nave->x - nave->quadroW / 2)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x + inimigo->quadroW * 0.7, inimigo->y + inimigo->quadroH / 2);        
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 10;
        }
        // Colisao Tiro-Jogador -> Inimigo
        if (inimigo->ativo && nave->tirof.ativo && nave->tirof.x <= inimigo->x - (inimigo->quadroW / 5))
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            nave->tirof.ativo = 0;
            nave->pontos += 15;
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x, inimigo->y + inimigo->quadroH / 2);            
        }
        // Colisao Tiro-Inimigo -> Jogador
        if (inimigo->ativo && inimigo->tirof.ativo && inimigo->tirof.x >= nave->x + (nave->quadroW / 4))
        {
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 5;
            inimigo->tirof.ativo = 0;
        }
    }
    if (nave->defesa <= 0) 
    {
        nave->defesa = 0;
        nave->escudo = 0;
    }
}

void verifica_colisao_2(Explosao exp[][COLUNAS], ALLEGRO_SAMPLE_INSTANCE *inst_track_exp_colision, Nave *nave, Nave *inimigo)
{
    if (nave->vel > 0)
    {
        // Colisao entre Nave-Jogador e Nave-Inimigo
        if (inimigo->ativo && nave->x >= inimigo->x - nave->quadroW)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x + inimigo->quadroW / 4, inimigo->y + inimigo->quadroH / 2);        
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 10;
        }
        // Colisao Tiro-Jogador -> Inimigo
        if (inimigo->ativo && nave->tirof.ativo && nave->tirof.x >= inimigo->x + inimigo->quadroW / 4)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            nave->tirof.ativo = 0;
            nave->pontos += 15;
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x + inimigo->quadroW / 4, inimigo->y + inimigo->quadroH / 2);            
        }
        // Colisao Tiro-Inimigo -> Jogador
        if (inimigo->ativo && inimigo->tirof.ativo && inimigo->tirof.x <= nave->x + nave->quadroW - 45)
        {
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }            
            else
                nave->defesa -= 5;
            inimigo->tirof.ativo = 0;
        }
    }
    else if (nave->vel < 0)
    {
        // Colisao entre Nave-Jogador e Nave-Inimigo
        if (inimigo->ativo && inimigo->x >= nave->x - nave->quadroW)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            inimigo->ativo = 0;
            inicia_exp(exp, nave->x - nave->quadroW / 4, inimigo->y + inimigo->quadroH / 2);        
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 10;
        }
        // Colisao Tiro-Jogador -> Inimigo
        if (inimigo->ativo && nave->tirof.ativo && nave->tirof.x <= inimigo->x + inimigo->quadroW / 2)
        {
            if (xcon_2_save)
                al_play_sample_instance(inst_track_exp_colision);
            nave->tirof.ativo = 0;
            nave->pontos += 15;
            inimigo->ativo = 0;
            inicia_exp(exp, inimigo->x + inimigo->quadroW / 2, inimigo->y + inimigo->quadroH / 2);            
        }
        // Colisao Tiro-Inimigo -> Jogador
        if (inimigo->ativo && inimigo->tirof.ativo && inimigo->tirof.x >= nave->x + (nave->quadroW / 4))
        {
            if (!nave->escudo)
            {
                nave->atingido = 1;
                nave->vidas--;
            }
            else
                nave->defesa -= 5;
            inimigo->tirof.ativo = 0;
        }
    }
    if (nave->defesa <= 0) 
    {
        nave->defesa = 0;
        nave->escudo = 0;
    }
}

void contagem_regressiva_f(ALLEGRO_EVENT_QUEUE *event_queue)
{
    Estrelas planos_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas planos_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(planos_1);
    init_planos(planos_2);
    
    ALLEGRO_FONT *font = NULL;
    int var_op = 1;
    int base_min = 90;
    int base_max = 165;
    int alfa = base_min;
    int tam_font = 0;
    int num = 3;
    
    while (__true)
    {
        alfa += var_op;
        if (alfa >= base_max) var_op *= (-1);
        else if (alfa <= base_min) var_op *= (-1);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        font = al_load_font("../resources/Fonts/Chronosfer-Demo.ttf", tam_font, 0);
        
        if (tam_font < 200)
        {
            al_draw_textf(font, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 50, ALLEGRO_ALIGN_CENTER, "%i", num);
            tam_font++;
        } 
        else 
        {
            tam_font = 0;
            num--;
        }
        if (num <=0 ) return;
        for (int i = 0; i < NUM_PLANOS; i++)
        {
            for (int j = 0; j < MAX_ESTRELAS; j++)
            {                           
                al_draw_pixel(planos_1[i][j].x, planos_1[i][j].y, al_map_rgb(67, alfa, alfa + 42));
                al_draw_pixel(planos_2[i][j].x, planos_2[i][j].y, al_map_rgb(67, 255 - alfa, 339 - (alfa + 42)));
            }
        }
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) al_destroy_all(0);
        al_flip_display();
        al_destroy_font(font);
    }
}