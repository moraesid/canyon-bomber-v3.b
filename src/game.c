#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
    #include "load_allegro.h"
#endif

#include "screens.h"
#include "globals.h"
#include "stats.h"
#include <stdlib.h>

#include "game.h"


void run_game(Nave *nave_1, Nave *nave_2, Nave *inimigo_1, Nave *inimigo_2, Explosao explosoes[][COLUNAS], Tile grid[][COLUNAS], Estrelas planos[][MAX_ESTRELAS])
{   
    srand(time(NULL));
    al_flush_event_queue(event_queue);
    jogando = 1;
    while (jogando)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);       
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_SPACE:  
                    if (xcon_2_save)
                        al_play_sample_instance(inst_sfx_xwing_fire);
                    if (!nave_1->escudo && !nave_1->atingido)
                    {
                        nave_1->tiro.ativo = 1;
                        nave_1->tiro.hit = 0;
                        nave_1->tiro.x = nave_1->x;
                        nave_1->tiro.y = nave_1->y + nave_1->quadroH / 2;
                        nave_1->tiro.vel_y = 0;
                    }
                    break;
                case ALLEGRO_KEY_ENTER:
                    if (xcon_2_save)
                        al_play_sample_instance(inst_sfx_viper_fire);
                    if (!nave_2->escudo && !nave_2->atingido)
                    {
                        nave_2->tiro.ativo = 1;
                        nave_2->tiro.hit = 0;
                        if (nave_2->vel > 0)
                            nave_2->tiro.x = nave_2->x + nave_2->quadroW / 2 - 50;
                        else 
                            nave_2->tiro.x = nave_2->x + nave_2->quadroW / 2 + 50;					
                        nave_2->tiro.y = nave_2->y + (nave_2->quadroH / 2) + 10;
                        nave_2->tiro.vel_y = 0;
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if (!nave_2->escudo && !nave_2->atingido)
                        if (nave_2->vel > 0)
                        {
                            if (xcon_2_save)
                                al_play_sample_instance(inst_sfx_viper_fire);
                            nave_2->tirof.ativo = 1;
                            nave_2->tirof.x = nave_2->x + nave_2->quadroW;
                            nave_2->tirof.y = nave_2->y + nave_2->quadroH * 0.7;
                        }
                    break;
                case ALLEGRO_KEY_LEFT:
                    if (!nave_2->escudo && !nave_2->atingido)
                        if (nave_2->vel < 0)
                        {
                            if (xcon_2_save)
                                al_play_sample_instance(inst_sfx_viper_fire);
                            nave_2->tirof.ativo = 1;
                            nave_2->tirof.x = nave_2->x;
                            nave_2->tirof.y = nave_2->y + nave_2->quadroH * 0.7;
                        }
                    break;
                case ALLEGRO_KEY_A:
                    if (!nave_1->escudo && !nave_1->atingido)
                        if (nave_1->vel < 0)
                            {
                                if (xcon_2_save)
                                        al_play_sample_instance(inst_sfx_xwing_fire);
                                    nave_1->tirof.ativo = 1;
                                    nave_1->tirof.x = nave_1->x;
                                    nave_1->tirof.y = nave_1->y + nave_1->quadroH / 2;
                            }
                    break;
                case ALLEGRO_KEY_D:
                    if (!nave_1->escudo && !nave_1->atingido)
                        if (nave_1->vel > 0)
                            {
                                if (xcon_2_save)
                                    al_play_sample_instance(inst_sfx_xwing_fire);
                                nave_1->tirof.ativo = 1;
                                nave_1->tirof.x = nave_1->x + nave_1->quadroW;
                                nave_1->tirof.y = nave_1->y + nave_1->quadroH / 2;
                            }
                    break;
                case ALLEGRO_KEY_Q:
                    pause_game = 1;
                    configuracoes_f();
                    al_flush_event_queue(event_queue);
                    break;                   
                case ALLEGRO_KEY_F:
                    if (nave_1->defesa > 0) nave_1->escudo = 1;
                    break;
                case ALLEGRO_KEY_L:
                    if (nave_2->defesa > 0) nave_2->escudo = 1;
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_F:
                    nave_1->escudo = 0;
                    break;
                case ALLEGRO_KEY_L:
                    nave_2->escudo = 0;
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER)
        { 
            al_clear_to_color(al_map_rgb(0,0,0));
            
            atualiza_planos(planos);
            atualiza_exp(explosoes);
            seleciona_sprites_naves(nave_1, nave_2);
            atualiza_nave(nave_1);
            atualiza_nave(nave_2);
            seleciona_posy_naves(nave_1, nave_2);
            verifica_fase(nave_1, inimigo_1);
            verifica_fase(nave_2, inimigo_2);
            atualiza_nave_i(inimigo_1, nave_1);
            atualiza_nave_i(inimigo_2, nave_2);
            verifica_colisao_1(explosoes, inst_sfx_exp_colision, nave_1, inimigo_1);
            verifica_colisao_2(explosoes, inst_sfx_exp_colision, nave_2, inimigo_2);
            atualiza_grid(grid, nave_1, inst_sfx_exp_file, explosoes);
            atualiza_grid(grid, nave_2, inst_sfx_exp_file, explosoes);  
            desenha_planos(planos);
            desenha_grid(death_starS, grid);
            desenha_nave(nave_1);
            desenha_nave(nave_2);
            desenha_nave_i(inimigo_1);
            desenha_nave_i(inimigo_2);
            desenha_exp(explosoes);
            desenha_atributos_nave(nave_1, nave_2, size_32, font_chronosfer);
            
            if (nave_1->win || nave_2->win) var_win = 1;
            else if ((var_grid = verifica_grid(grid)) == (LINHAS * COLUNAS)) jogando = 0; 
            else if (nave_1->vidas <= 0 || nave_2->vidas <= 0) jogando = 0;    
     
            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
    }
    if (!vencedor) fadeout_with_audio_less(1, display, event_queue, track_play_game);
    return;
}

void end_game(Nave *nave_1, Nave *nave_2)
{
    al_start_timer(timer_fim_while);
    
    Estrelas planos_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas planos_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(planos_1);
    init_planos(planos_2);
    
    if (!vencedor)
    {
        if (nave_1->win) vencedor = 1;           
        else if (nave_2->win) vencedor = 2;
        else if (nave_1->vidas > 0 && nave_2->vidas <=0) nave_1->win = 1;
        else if (nave_2->vidas > 0 && nave_1->vidas <=0) nave_2->win = 1;
        else if (nave_1->vidas > 0 && nave_1->pontos > nave_2->pontos) nave_1->win = 1;
        else if (nave_2->vidas > 0 && nave_2->pontos > nave_1->pontos) nave_2->win = 1;
        else if (nave_1->pontos == nave_2->pontos && nave_1->vidas > nave_2->vidas && nave_1->vidas > 0) nave_1->win = 1;
        else if (nave_1->pontos == nave_2->pontos && nave_1->vidas < nave_2->vidas && nave_2->vidas > 0) nave_2->win = 1;
        else if (nave_1->vidas <= 0 && nave_2->vidas <= 0) vencedor = -1;
        else if (nave_1->pontos == 0 && nave_2->pontos == 0) vencedor = -1;

        if (vencedor)
        {
            switch (vencedor)
            {
                case 1:
                    completou(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nave_1->win, nick_1);
                    break;
                case 2:
                    completou(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nave_2->win, nick_2);
                    break;
                case -1:
                    falhou(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2);
                    break;
            }
        }
        else
        {
            if (nave_1->win)
            {
                if (var_grid == (LINHAS*COLUNAS))
                    completou(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nave_1->win, nick_1);
                else
                    incompleto(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nick_1);
            }
            else if (nave_2->win)
            {
                if (var_grid == (LINHAS*COLUNAS))
                    completou(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nave_2->win, nick_2);
                else
                    incompleto(event_queue_fim_while, font_chronosfer, display, planos_1, planos_2, nick_2);
            }
        }
    }
    return;
}