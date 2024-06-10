#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
    #include <allegro5/allegro_video.h>
    #include "load_allegro.h"
#endif

#include "scenario.h"
#include "globals.h"
#include "animations.h"
#include "settings.h"
#include "records.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screens.h"


void abertura_f(void)
{
    if (!xcon_3_save && primeira_vez_intro)
    {
        primeira_vez_intro = 0;
        al_start_timer(timer_intro);

        if (fadein_f(1, intro_img_file, display, event_queue_intro) == -1) return;
        al_rest(1);
        if (fadeout_f(1, display, event_queue_intro) == -1) return;
        
        al_set_audio_stream_playing(track_intro, __true);
        al_start_video(video_intro, al_get_default_mixer());
        
        al_register_event_source(event_queue_intro, al_get_video_event_source(video_intro));
        
        int bool_intro = 1;
        while (bool_intro)
        {
            ALLEGRO_EVENT ev_intro;
            al_wait_for_event(event_queue_intro, &ev_intro);
            if (ev_intro.type == ALLEGRO_EVENT_VIDEO_FRAME_SHOW)
            {    
                ALLEGRO_BITMAP *frame = al_get_video_frame(video_intro);
                al_draw_bitmap(frame,0,0,0);
                al_flip_display();
            }
            else if (ev_intro.type == ALLEGRO_EVENT_KEY_DOWN && ev_intro.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                fadeout_with_audio_less(1, display, event_queue_intro, track_intro);
                al_drain_audio_stream(track_intro);
                al_close_video(video_intro);
                return;
            }
            else if (ev_intro.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                al_destroy_all(0);
            else if (ev_intro.type == ALLEGRO_EVENT_VIDEO_FINISHED)
            {
                al_drain_audio_stream(track_intro);
                al_close_video(video_intro);
                bool_intro = 0;
            }   
        }
        if (fadeout_f(1, display, event_queue_intro) == -1) 
        {
            al_drain_audio_stream(track_intro);
            al_close_video(video_intro);
            return;
        }
    }
    return;
}

void menu_inicial_f(void)
{
    al_set_audio_stream_playing(track_menus, xcon_4_save);
    al_flush_event_queue(event_queue_menu_1);
    
    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);
    while (__true)
    {
        alfa_menu_1 += var_menu_1_op;
        if (alfa_menu_1 >= base_max_menu_1) var_menu_1_op *= (-1);
        else if (alfa_menu_1 <= base_min_menu_1) var_menu_1_op *= (-1);
        ALLEGRO_EVENT ev_menu_1;
        al_wait_for_event(event_queue_menu_1, &ev_menu_1);
        al_clear_to_color(al_map_rgb(0, 0, 0));                    
        if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            switch (var)
            {
                case 0:
                    var = 1;
                    break;              
                case 1:
                    var = 2;
                    break;
                case 2:
                    var = 3;
                    break;
                case 3:
                    var = 3;
            }
        }  
        else if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            switch (var)
            {
                case 0:
                    var = 0;
                    break;              
                case 1:
                    var = 0;
                    break;               
                case 2:
                    var = 1;
                    break;
                case 3:
                    var = 2;
                    break;
            }
        }  
        else if (ev_menu_1.type == ALLEGRO_EVENT_TIMER)
        {
            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                            
                    al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(alfa_menu_1, alfa_menu_1, alfa_menu_1));
                    al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(355 - alfa_menu_1, 355 - alfa_menu_1, 355 - alfa_menu_1));
                }
            }
            
            if (tempo_menu_1 > 55) tempo_menu_1 = 0;
            switch (var)
            {
                case 0:
                    if (tempo_menu_1 < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Iniciar");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Ajustes");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Histórico");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "Sair");
                    break;               
                case 1:
                    if (tempo_menu_1 < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Ajustes");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Iniciar");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Histórico");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "Sair");
                    break;                
                case 2:
                    if (tempo_menu_1 < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Histórico");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Iniciar");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Ajustes");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "Sair");   
                    break;
                case 3:
                    if (tempo_menu_1 < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2 + 80, ALLEGRO_ALIGN_CENTER, "Sair");   
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Iniciar");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Ajustes");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Histórico");
                    break;                     
            }
            tempo_menu_1++;
            al_flip_display();
        }                  
        else if(ev_menu_1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0); 
        else if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_ENTER && var == 0)
        {
            menu_ativo = 0;
            return;
        }
        else if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_ENTER && var == 1)
        {
            configuracoes_f();
            al_flush_event_queue(event_queue_menu_1);
        }
        else if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_ENTER && var == 2)
        {
            historico_f();
            al_flush_event_queue(event_queue_menu_1);
        }
        else if (ev_menu_1.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_1.keyboard.keycode == ALLEGRO_KEY_ENTER && var == 3)
        {
            save_settings();
            al_destroy_all(0);
        }
    }
}

void menu_nomes_f(void)
{  
    al_set_audio_stream_playing(track_menus, xcon_4_save);
    al_flush_event_queue(event_queue_menu_2);
    
    int bool_nick_1 = 1;
    int bool_nick_2 = 1;
    int verifica_fila = 1;
    int var_menu_2_op = 1;
    int base_max_menu_2 = 165;
    int base_min_menu_2 = 90;
    int alfa_menu_2 = base_min_menu_2;

    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);
    
    while(__true)
    {
        alfa_menu_2 += var_menu_2_op;
        if (alfa_menu_2 >= base_max_menu_2) var_menu_2_op *= (-1);
        else if (alfa_menu_2 <= base_min_menu_2) var_menu_2_op *= (-1);
        ALLEGRO_EVENT ev_menu_2;
        al_wait_for_event(event_queue_menu_2, &ev_menu_2);
        if(bool_nick_1)
        {
            bool_nick_1 = nickname(ev_menu_2, nick_1);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_text(font_bsg_1, al_map_rgb(0, 0, 255), SPACE_TEXT + SCREEN_W / 2, SCREEN_H / 3, ALLEGRO_ALIGN_RIGHT, "Jogador 1: ");

            if (strlen(nick_1) > 0)             
                al_draw_text(font_chronosfer, al_map_rgb(255, 255, 255), SPACE_TEXT + SCREEN_W / 2 - 17, SCREEN_H / 3 - 14, ALLEGRO_ALIGN_LEFT, nick_1);
        }
        if (!bool_nick_1 && verifica_fila)
        {
            al_flush_event_queue(event_queue_menu_2);
            verifica_fila = 0;
        }
        else if (!bool_nick_1)    
        {
            bool_nick_2 = nickname(ev_menu_2, nick_2);
            al_clear_to_color(al_map_rgb(0, 0, 0));               
            al_draw_text(font_bsg_1, al_map_rgb(0, 0, 255), SPACE_TEXT + SCREEN_W / 2, SCREEN_H / 3, ALLEGRO_ALIGN_RIGHT, "Jogador 1: ");
            al_draw_text(font_chronosfer, al_map_rgb(255, 255, 255), SPACE_TEXT + SCREEN_W / 2 - 17, SCREEN_H / 3 - 14, ALLEGRO_ALIGN_LEFT, nick_1);
            al_draw_text(font_bsg_1, al_map_rgb(255, 0, 0), SPACE_TEXT + SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_RIGHT, "Jogador 2: ");
            if (strlen(nick_2) > 0)             
                al_draw_text(font_chronosfer, al_map_rgb(255, 255, 255), SPACE_TEXT + SCREEN_W / 2 - 17, SCREEN_H / 2 - 14, ALLEGRO_ALIGN_LEFT, nick_2);
        }

        for (int i = 0; i < NUM_PLANOS; i++)
        {
            for (int j = 0; j < MAX_ESTRELAS; j++)
            {                           
                al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(67, alfa_menu_2, alfa_menu_2 + 42));
                al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(67, 255 - alfa_menu_2, 339 - (alfa_menu_2 + 42)));
            }
        }
        al_flip_display();

        if(!bool_nick_2) 
        {
            fadeout_with_audio_less(1, display, event_queue_menu_2, track_menus);
            return;
        }
        else if (ev_menu_2.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        else if (ev_menu_2.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu_2.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            menu_inicial_f();
            al_flush_event_queue(event_queue_menu_2);
        }
    }             
}

void configuracoes_f(void)
{
    if (menu_ativo) al_set_audio_stream_playing(track_menus, xcon_4_save);
    if (jogando) al_set_audio_stream_playing(track_play_game, xcon_1_save);
    al_flush_event_queue(event_queue_configs);
    al_start_timer(timer_configs);
    
    int xcon_1 = xcon_1_save;
    int xcon_2 = xcon_2_save;
    int xcon_3 = xcon_3_save;
    int xcon_4 = xcon_4_save;
    int var_configs = 0;

    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);

    while (__true)
    {
        alfa_configs += var_configs_op;
        if (alfa_configs >= base_max_configs) var_configs_op *= (-1);
        else if (alfa_configs <= base_min_configs) var_configs_op *= (-1);
        ALLEGRO_EVENT ev_configs;
        al_wait_for_event(event_queue_configs, &ev_configs);
        if (ev_configs.type == ALLEGRO_EVENT_KEY_DOWN && ev_configs.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            if (!pause_game)
            {
                switch (var_configs)
                {
                    case 0:
                        var_configs = 1;
                        break;              
                    case 1:
                        var_configs = 2;
                        break;                
                    case 2:
                        var_configs = 3;
                        break;
                    case 3:
                        var_configs = 3;
                        break;
                }
            }
            else
            {
                switch (var_configs)
                {
                    case 0:
                        var_configs = 1;
                        break;              
                    case 1:
                        var_configs = 1;
                        break;                
                }                   
            }
        }  
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_DOWN && ev_configs.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            if (!pause_game)
            {
                switch (var_configs)
                {
                    case 0:
                        var_configs = 0;
                        break;              
                    case 1:
                        var_configs = 0;
                        break;               
                    case 2:
                        var_configs = 1;
                        break;
                    case 3:
                        var_configs = 2;
                        break;
                }
            }
            else
            {
                switch (var_configs)
                {
                    case 0:
                        var_configs = 0;
                        break;              
                    case 1:
                        var_configs = 0;
                        break;               
                }                                    
            }
        }
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_DOWN && ev_configs.keyboard.keycode == ALLEGRO_KEY_ENTER) 
        {
            switch (var_configs)
            {
                case 0:
                    if (xcon_1) xcon_1 = 0;
                    else xcon_1 = 1;
                    break;
                case 1:
                    if (xcon_2) xcon_2 = 0;
                    else xcon_2 = 1;
                    break;
                case 2:
                    if (xcon_4) xcon_4 = 0;
                    else xcon_4 = 1;
                    break;     
                case 3:
                    if (xcon_3) xcon_3 = 0;
                    else xcon_3 = 1;
                    break;
            }
        }
        else if (ev_configs.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (pause_game)
                al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), SCREEN_W / 2, 40, ALLEGRO_ALIGN_CENTER, "Jogo Pausado");

            al_draw_rectangle((SCREEN_W / 3) + 85, SCREEN_H / 3, (SCREEN_W / 3) + 115 , (SCREEN_H / 3) + 30, al_map_rgb(67, 165, 207), 2);
            if (xcon_1)
                al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), (SCREEN_W / 3) + 88.5, (SCREEN_H / 3) - 11.5, 0, "x");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), (SCREEN_W / 3) + 135, (SCREEN_H / 3) - 10, 0, "Música Geral");

            al_draw_rectangle((SCREEN_W / 3) + 85, (SCREEN_H / 2) - 45, (SCREEN_W / 3) + 115 , (SCREEN_H / 2) - 15, al_map_rgb(67, 165, 207), 2);
            if (xcon_2)
                al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), (SCREEN_W / 3) + 88.5, (SCREEN_H / 2) - 56.5, 0, "x");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), (SCREEN_W / 3) + 135, (SCREEN_H / 2) - 53, 0, "Efeitos Sonoros");

            if (!pause_game)
            {
                al_draw_rectangle((SCREEN_W / 3) + 85, (SCREEN_H / 2) + 30, (SCREEN_W / 3) + 115 , (SCREEN_H / 2) + 60, al_map_rgb(67, 165, 207), 2);
                if (xcon_3)
                    al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), (SCREEN_W / 3) + 88.5, (SCREEN_H / 2) + 95.5, 0, "x");
                al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), (SCREEN_W / 3) + 135, (SCREEN_H / 2) + 24, 0, "Música dos Menus");
                al_draw_rectangle((SCREEN_W / 3) + 85, (SCREEN_H / 2) + 107, (SCREEN_W / 3) + 115 , (SCREEN_H / 2) + 137, al_map_rgb(67, 165, 207), 2);
                if (xcon_4)
                    al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), (SCREEN_W / 3) + 88.5, (SCREEN_H / 2) + 18.5, 0, "x");
                al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), (SCREEN_W / 3) + 135, (SCREEN_H / 2) + 100, 0, "Pular Abertura");
            }
            al_draw_text(font_chronosfer, al_map_rgb(150, 0, 0), SCREEN_W / 2, SCREEN_H - 100, ALLEGRO_ALIGN_CENTER, "Pressione H para acessar opções de teclas");

            if (var_configs == 0)
                al_draw_line((SCREEN_W / 3) + 130, (SCREEN_H / 3) + 32, (SCREEN_W / 3) + 364, (SCREEN_H / 3) + 32, al_map_rgb(150, 0, 0), 2);
            else if (var_configs == 1)
               al_draw_line((SCREEN_W / 3) + 130, (SCREEN_H / 2) - 10, (SCREEN_W / 3) + 420, (SCREEN_H / 2) - 10, al_map_rgb(150, 0, 0), 2);
            else if (var_configs == 2 && !pause_game)
                al_draw_line((SCREEN_W / 3) + 130, (SCREEN_H / 2) + 65, (SCREEN_W / 3) + 455, (SCREEN_H / 2) + 65, al_map_rgb(150, 0, 0), 2);
            else if (var_configs == 3 && !pause_game)
                al_draw_line((SCREEN_W / 3) + 130, (SCREEN_H / 2) + 142, (SCREEN_W / 3) + 400, (SCREEN_H / 2) + 142, al_map_rgb(150, 0, 0), 2);

            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(67, alfa_configs, alfa_configs + 42));
                    al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(67, 255 - alfa_configs, 339 - (alfa_configs + 42)));
                }
            }                
            al_flip_display();
        }
        else if(ev_configs.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_DOWN && ev_configs.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            if (pause_game) pause_game = 0;
            return;
        }
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_CHAR && ev_configs.keyboard.keycode == ALLEGRO_KEY_S)
        {
            xcon_1_save = xcon_1;
            xcon_2_save = xcon_2;
            xcon_3_save = xcon_3;
            xcon_4_save = xcon_4;
        }
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_CHAR && ev_configs.keyboard.keycode == ALLEGRO_KEY_H)
        {
            teclas_ajuda_p();
            al_flush_event_queue(event_queue_configs);
        }
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_CHAR && ev_configs.keyboard.keycode == ALLEGRO_KEY_V)
        {
            controles_volume_p();
            al_flush_event_queue(event_queue_configs);
        }
        if (pause_game)
        {
            if (ev_configs.type == ALLEGRO_EVENT_KEY_CHAR && ev_configs.keyboard.keycode == ALLEGRO_KEY_W)
            {
                pause_game = 0;
                jogando = 0;
                vencedor = -1;
                return;
            }
        }
    }
}

void teclas_ajuda_p(void)
{
    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);
    
    al_flush_event_queue(event_queue_configs);
    while (__true)
    {
        alfa_configs += var_configs_op;
        if (alfa_configs >= base_max_configs) var_configs_op *= (-1);
        else if (alfa_configs <= base_min_configs) var_configs_op *= (-1);
        ALLEGRO_EVENT ev_configs;
        al_wait_for_event(event_queue_configs, &ev_configs);
        if (ev_configs.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            if (pause_game)
            {
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 150, ALLEGRO_ALIGN_CENTER, "S: salva alterações");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 225, ALLEGRO_ALIGN_CENTER, "ENTER: seleciona opção");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 300 , ALLEGRO_ALIGN_CENTER, "ESC: retorna à partida");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 375 , ALLEGRO_ALIGN_CENTER, "V: acessa ajustes de volume");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 450 , ALLEGRO_ALIGN_CENTER, "W: salvar progesso e sair");

            }
            else if (!pause_game)
            {
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 200, ALLEGRO_ALIGN_CENTER, "S: salva alterações");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 275, ALLEGRO_ALIGN_CENTER, "ENTER: seleciona opção");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 350 , ALLEGRO_ALIGN_CENTER, "ESC: retorna à tela anterior");
                al_draw_text(font_chronosfer, al_map_rgb(67,165,207), SCREEN_W / 2, 425 , ALLEGRO_ALIGN_CENTER, "V: acessa ajustes de volume");
            }

            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(67, alfa_configs, alfa_configs + 42));
                    al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(67, 255 - alfa_configs, 339 - (alfa_configs + 42)));
                }
            }                
            al_flip_display();
        }
        else if(ev_configs.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        else if (ev_configs.type == ALLEGRO_EVENT_KEY_DOWN && ev_configs.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            return;                                                               
    }
}

void controles_volume_p(void)
{
    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);
    
    ALLEGRO_COLOR color_1 = al_map_rgb(0,255,0);
    ALLEGRO_COLOR color_2 = al_map_rgb(0,255,0);
    ALLEGRO_COLOR color_3 = al_map_rgb(0,255,0);
    
    al_flush_event_queue(event_queue_configs);
    while (__true)
    {
        alfa_configs += var_configs_op;
        if (alfa_configs >= base_max_configs) var_configs_op *= (-1);
        else if (alfa_configs <= base_min_configs) var_configs_op *= (-1);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue_configs, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            switch (vol_sel)
            {
                case 1: 
                    vol_sel = 2;
                    break;
                case 2:
                    vol_sel = 3;
                    break;
                case 3:
                    vol_sel = 3;
                    break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            switch (vol_sel)
            {
                case 3: 
                    vol_sel = 2;
                    break;
                case 2:
                    vol_sel = 1;
                    break;
                case 1:
                    vol_sel = 1;
                    break;
            }
        }        
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            switch (vol_sel)
            {
                case 1:
                    GAIN_SFX -= 0.1;
                    x1_vol += 400.0 * 0.1;
                    break;
                case 2:
                    GAIN_TRACK_PLAY_GAME -= 0.1;
                    x2_vol += 400.0 * 0.1;
                    break;
                case 3:
                    GAIN_TRACK_MENUS -= 0.1;
                    x3_vol += 400.0 * 0.1;
                    break;
            }

        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            switch (vol_sel)
            {
                case 1:
                    GAIN_SFX += 0.1;
                    x1_vol -= 400.0 * 0.1;
                    break;
                case 2:
                    GAIN_TRACK_PLAY_GAME += 0.1;
                    x2_vol -= 400.0 * 0.1;
                    break;
                case 3:
                    GAIN_TRACK_MENUS += 0.1;
                    x3_vol -= 400.0 * 0.1;
                    break;
            }
        }

        if (GAIN_SFX > 1.0) GAIN_SFX = 1.0;
        else if (GAIN_SFX < 0.0) GAIN_SFX = 0.0;
        if (GAIN_TRACK_PLAY_GAME > 1.0) GAIN_TRACK_PLAY_GAME = 1.0;
        else if (GAIN_TRACK_PLAY_GAME < 0.0) GAIN_TRACK_PLAY_GAME = 0.0;
        if (GAIN_TRACK_MENUS > 1.0) GAIN_TRACK_MENUS = 1.0;
        else if (GAIN_TRACK_MENUS < 0.0) GAIN_TRACK_MENUS = 0.0;

        al_set_audio_stream_gain(track_menus, GAIN_TRACK_MENUS);
        al_set_audio_stream_gain(track_play_game, GAIN_TRACK_PLAY_GAME);
        al_set_sample_instance_gain(inst_sfx_exp_colision, GAIN_SFX);
        al_set_sample_instance_gain(inst_sfx_exp_file, GAIN_SFX);
        al_set_sample_instance_gain(inst_sfx_xwing_fire, GAIN_SFX);
        al_set_sample_instance_gain(inst_sfx_viper_fire, GAIN_SFX);

        if (x1_vol> 550) x1_vol = 550;
        else if (x1_vol < 150) x1_vol = 150;
        if (x2_vol > 550) x2_vol = 550;
        else if (x2_vol < 150) x2_vol = 150;
        if (x3_vol > 550) x3_vol = 550;
        else if (x3_vol < 150) x3_vol = 150;

        if (x1_vol > 250 && x1_vol < 400) color_1 = al_map_rgb(255,255,0);
        else if (x1_vol >= 150 && x1_vol <= 250) color_1 = al_map_rgb(00,255,0);
        else if (x1_vol > 400) color_1 = al_map_rgb(255,0,0);

        if (x2_vol > 250 && x2_vol < 400) color_2 = al_map_rgb(255,255,0);
        else if (x2_vol >= 150 && x2_vol <= 250) color_2 = al_map_rgb(00,255,0);
        else if (x2_vol > 400) color_2 = al_map_rgb(255,0,0);

        if (x3_vol > 250 && x3_vol < 400) color_3 = al_map_rgb(255,255,0);
        else if (x3_vol >= 150 && x3_vol <= 250) color_3 = al_map_rgb(00,255,0);
        else if (x3_vol > 400) color_3 = al_map_rgb(255,0,0);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0,0,0));

            for (int i = 0; i < NUM_PLANOS; i++)
            {
                for (int j = 0; j < MAX_ESTRELAS; j++)
                {                           
                    al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(67, alfa_configs, alfa_configs + 42));
                    al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(67, 255 - alfa_configs, 339 - (alfa_configs + 42)));
                }
            }  

            switch (vol_sel)
            {
                case 1:
                    al_draw_filled_triangle(350, 110, 380, 110, 365, 140, al_map_rgb(200,0,0));
                    x_circle = SCREEN_W / 24;
                    break;
                case 2:
                    al_draw_filled_triangle(625, 110, 655, 110, 640, 140, al_map_rgb(200,0,0));
                    x_circle = SCREEN_W / 2 - SCREEN_W / 10;
                    break;
                case 3:
                    al_draw_filled_triangle(900, 110, 930, 110, 915, 140, al_map_rgb(200,0,0));
                    x_circle = SCREEN_W / 2 + SCREEN_W / 5.1;
                    break;
            }
            al_draw_filled_circle(x_circle, y_circle, raio, al_map_rgb(200,0,0));

            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, 30, ALLEGRO_ALIGN_CENTER, "Controles de Volume");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 18, y_text, ALLEGRO_ALIGN_LEFT, "Efeitos Sonoros");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, y_text, ALLEGRO_ALIGN_CENTER, "Música Geral");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W - 50, y_text, ALLEGRO_ALIGN_RIGHT, "Música dos Menus");

            al_draw_rectangle(350, 148, 380, 551, al_map_rgb(67, 165, 207), 2);
            al_draw_filled_rectangle(351, x1_vol, 379, 550, color_1);

            al_draw_rectangle(625, 148, 655, 550, al_map_rgb(67, 165, 207), 2);
            al_draw_filled_rectangle(626, x2_vol, 654, 550, color_2);

            al_draw_rectangle(900, 148, 930, 551, al_map_rgb(67, 165, 207), 2);
            al_draw_filled_rectangle(901, x3_vol, 929, 550, color_3);

            al_flip_display();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            return; 
    }
}

void historico_f(void)
{
    al_flush_event_queue(event_queue_historico);
    al_start_timer(timer_historico);
    
    Registro *regs[MAX_REGS];
    int num_cads = ler_regs(regs);    
    if (!num_cads)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));       
        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Histórico Vazio");        
        al_flip_display();
        al_rest(1.5);
        return;
    }
    int h = 50;
    int fator = 50;
    int mais = 30;
    int var_his = 0;
    int j = 0;
    
    Estrelas plano_1[NUM_PLANOS][MAX_ESTRELAS];
    Estrelas plano_2[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(plano_1);
    init_planos(plano_2);
    
    while (__true)
    {
        ALLEGRO_EVENT ev_his;
        al_wait_for_event(event_queue_historico, &ev_his);
        if (ev_his.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev_his.keyboard.keycode)
            {
                case ALLEGRO_KEY_DOWN:
                    var_his += 1;
                    if (var_his >= MAX_REGS - 5) var_his = MAX_REGS - 6;
                    break;
                case ALLEGRO_KEY_UP:
                    var_his -= 1;
                    if (var_his < 0) var_his = 0;
                    break;
            }
        }
        else if (ev_his.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0)); 
            if (menu_ativo)
            {
                alfa_menu_1 += var_menu_1_op;
                if (alfa_menu_1 >= base_max_menu_1) var_menu_1_op *= (-1);
                else if (alfa_menu_1 <= base_min_menu_1) var_menu_1_op *= (-1);
                for (int i = 0; i < NUM_PLANOS; i++)
                {
                    for (int j = 0; j < MAX_ESTRELAS; j++)
                    {                            
                        al_draw_pixel(plano_1[i][j].x, plano_1[i][j].y, al_map_rgb(alfa_menu_1, alfa_menu_1, alfa_menu_1));
                        al_draw_pixel(plano_2[i][j].x, plano_2[i][j].y, al_map_rgb(355 - alfa_menu_1, 355 - alfa_menu_1, 355 - alfa_menu_1));
                    }
                }
            }
            else if (!menu_ativo) 
            {
                desenha_planos(plano_1);
                atualiza_planos(plano_1);
            }
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), 220, h, ALLEGRO_ALIGN_LEFT, "Jogador");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), 555, h, ALLEGRO_ALIGN_LEFT, "Vitórias");
            al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), 890, h, ALLEGRO_ALIGN_LEFT, "Pontuação");
            al_draw_line(65, 100, SCREEN_W - 65, 100, al_map_rgb(67, 165, 207), 2);
            for (int i=var_his; i<MAX_REGS; i++)
            {
                al_draw_textf(font_chronosfer, al_map_rgb(67, 165, 207), 80, (j+1)*(2*h) + mais, ALLEGRO_ALIGN_LEFT, "%i", (i+1));
                if (i < num_cads)
                {
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), fator + 220, (j+1)*(2*h) + mais, ALLEGRO_ALIGN_CENTER, regs[i]->nome);
                    al_draw_textf(font_chronosfer, al_map_rgb(67, 165, 207), fator + 555, (j+1)*(2*h) + mais, ALLEGRO_ALIGN_CENTER, "%i", regs[i]->vitorias);
                    al_draw_textf(font_chronosfer, al_map_rgb(67, 165, 207), 70 + 890, (j+1)*(2*h) + mais, ALLEGRO_ALIGN_CENTER, "%i", regs[i]->pontos);
                }
                j++;
            }
            j = 0;
            al_flip_display();
        }
        else if (ev_his.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        if (ev_his.type == ALLEGRO_EVENT_KEY_DOWN && ev_his.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            return;
    }
}

void menu_final_f(void)
{
    al_set_audio_stream_playing(track_end_menu, xcon_4_save);
    al_flush_event_queue(event_queue_fim);
    al_start_timer(timer_fim);
    
    Estrelas planos[NUM_PLANOS][MAX_ESTRELAS];
    init_planos(planos);
    int tempo_fim = 0;  
    
    while (__true)
    {
        ALLEGRO_EVENT ev_fim;
        al_wait_for_event(event_queue_fim, &ev_fim);      
        if (ev_fim.type == ALLEGRO_EVENT_KEY_DOWN && ev_fim.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            switch (var_fim)
            {
                case 0:
                    var_fim = 1;
                    break;              
                case 1:
                    var_fim = 2;
                    break;                
                case 2:
                    var_fim = 2;
                    break;
            }
        }  
        else if (ev_fim.type == ALLEGRO_EVENT_KEY_DOWN && ev_fim.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            switch (var_fim)
            {
                case 0:
                    var_fim = 0;
                    break;              
                case 1:
                    var_fim = 0;
                    break;               
                case 2:
                    var_fim = 1;
                    break;
            }
        }        
        else if (ev_fim.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            desenha_planos(planos);
            atualiza_planos(planos);
            if (tempo_fim > 55) tempo_fim = 0;
            switch (var_fim)
            {
                case 0:
                    if (tempo_fim < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Jogar novamente");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Histórico");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Sair");
                    break;               
                case 1:
                    if (tempo_fim < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Histórico");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Jogar novamente");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Sair");
                    break;                
                case 2:
                    if (tempo_fim < 15)
                        al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Sair");   
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 4, ALLEGRO_ALIGN_CENTER, "Jogar novamente");
                    al_draw_text(font_chronosfer, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 3 + 30, ALLEGRO_ALIGN_CENTER, "Histórico");
                    break;          
            }            
            tempo_fim++;
            al_flip_display();
        }        
        else if (ev_fim.type == ALLEGRO_EVENT_KEY_DOWN && ev_fim.keyboard.keycode == ALLEGRO_KEY_ENTER && var_fim == 2)
        {
            save_settings();
            return;
        }
        else if (ev_fim.type == ALLEGRO_EVENT_KEY_DOWN && ev_fim.keyboard.keycode == ALLEGRO_KEY_ENTER && var_fim == 1)
        {
            historico_f();
            al_flush_event_queue(event_queue_fim);
        }
        else if (ev_fim.type == ALLEGRO_EVENT_KEY_DOWN && ev_fim.keyboard.keycode == ALLEGRO_KEY_ENTER && var_fim == 0)
        {
            nick_1[0] = '\0';
            nick_2[0] = '\0';
            __exit_program = 0;
            return;
        }
        else if (ev_fim.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
            al_destroy_all(0);
    }
}