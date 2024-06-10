#define ALLEGRO_COMMON

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>

#include "globals.h"
#include <stdlib.h>

#include "load_allegro.h"


int al_init_all (void)
{
    // inicializar o Allegro
    if (!al_init())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar lib allegro!\n");
        return 0;
    }

    // inicializar o módulo de primitivas do Allegro
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar primitivas allegro!\n");
        return 0;
    }

    // inicializar o modulo que permite carregar imagens no jogo
    if (!al_init_image_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar modulo de imagens!\n");
        return 0;
    }
    
    // instalar modulo de suporte a audio
    if (!al_install_audio())
    {
        fprintf(stderr, "ERRO 0: falha ao instalar módulo de audio!\n");
        return 0;
    }
    
    // incializar modulo acodec (suporte a codecs de audio)
    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar módulo acodec!\n");
        return 0;       
    }
    
    // inicializar modulo de suporte a video
    if (!al_init_video_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar módulo de video!\n");
        return 0;         
    }
        
    // instala o teclado
    if (!al_install_keyboard())
    {
        fprintf(stderr, "ERRO 0: falha ao instalar teclado!\n");
        return 0;
    }

    // inicializa o modulo allegro que carrega as fontes
    if (!al_init_font_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar módulo de fontes!\n");
        return 0; 
    }

    // inicializa o modulo allegro que entende arquivos tff de fontes
    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "ERRO 0: falha ao inicializar modulo de fontes ttf!\n");
        return 0;
    }
    return 1;
}

int al_init_resources(void)
{
    // criar "display"
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
    {
        fprintf(stderr, "ERRO 0: falha ao criar display!\n");
        al_destroy_display(display);
        return 0;
     
    }
    al_set_window_title(display, "Canyon Bomber - v3.b");
    
    // criar "event_queue"
    event_queue = al_create_event_queue();
    event_queue_menu_1 = al_create_event_queue();
    event_queue_menu_2 = al_create_event_queue();
    event_queue_configs = al_create_event_queue();
    event_queue_fim_while = al_create_event_queue();
    event_queue_historico = al_create_event_queue();
    event_queue_fim = al_create_event_queue();
    event_queue_intro = al_create_event_queue();
    
    if (!event_queue || !event_queue_menu_1 || !event_queue_menu_2 || !event_queue_configs || !event_queue_fim_while || !event_queue_fim || !event_queue_historico || !event_queue_intro)
    {
        fprintf(stderr, "ERRO 0: falha ao criar fila de eventos!\n");
        al_destroy_all(1);
    }
    
    // criar "timers"
    timer = al_create_timer(1.0 / FPS_GAME);
    timer_menu_1 = al_create_timer(1.0 / FPS_MENU);
    timer_menu_2 = al_create_timer(1.0 / FPS_MENU);
    timer_configs = al_create_timer(1.0 / FPS_MENU);
    timer_fim_while = al_create_timer(1.0 / FPS_MENU);
    timer_fim = al_create_timer(1.0 / FPS_MENU);
    timer_historico = al_create_timer(1.0 / FPS_MENU);
    timer_intro = al_create_timer(1.0 / FPS_MENU);
    
    if (!timer || !timer_menu_1 || !timer_menu_2 || !timer_configs || !timer_fim_while || !timer_fim || !timer_historico || !timer_intro)
    {
        fprintf(stderr, "ERRO 0: falha ao criar timer!\n");
        al_destroy_all(1);
    }
    // menu 1
    al_register_event_source(event_queue_menu_1, al_get_keyboard_event_source());
    al_register_event_source(event_queue_menu_1, al_get_display_event_source(display));
    al_register_event_source(event_queue_menu_1, al_get_timer_event_source(timer_menu_1));
    al_start_timer(timer_menu_1);
    //
    
    // menu 2
    al_register_event_source(event_queue_menu_2, al_get_display_event_source(display));
    al_register_event_source(event_queue_menu_2, al_get_keyboard_event_source());
    al_register_event_source(event_queue_menu_2, al_get_timer_event_source(timer_menu_2));
    al_start_timer(timer_menu_2);
    //
    
    // configuracoes
    al_register_event_source(event_queue_configs, al_get_keyboard_event_source());
    al_register_event_source(event_queue_configs, al_get_display_event_source(display));
    al_register_event_source(event_queue_configs, al_get_timer_event_source(timer_configs));
    al_flush_event_queue(event_queue_configs);
    //
    
    // historico
    al_register_event_source(event_queue_historico, al_get_keyboard_event_source());
    al_register_event_source(event_queue_historico, al_get_display_event_source(display));
    al_register_event_source(event_queue_historico, al_get_timer_event_source(timer_historico));   
    //
    
    // menu final
    al_register_event_source(event_queue_fim, al_get_keyboard_event_source());
    al_register_event_source(event_queue_fim, al_get_display_event_source(display));
    al_register_event_source(event_queue_fim, al_get_timer_event_source(timer_fim));
    //
    
    // fim while
    al_register_event_source(event_queue_fim_while, al_get_display_event_source(display));
    al_register_event_source(event_queue_fim_while, al_get_timer_event_source(timer_fim_while));
    //
    
    // jogo 
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    //
    
    // abertura
    al_register_event_source(event_queue_intro, al_get_display_event_source(display));
    al_register_event_source(event_queue_intro, al_get_timer_event_source(timer_intro));
    al_register_event_source(event_queue_intro, al_get_keyboard_event_source());
    //
    
    return 1;
}

void al_destroy_all(int modo)
{
    if (al_is_video_playing(video_intro)) al_close_video(video_intro);
    if (event_queue != NULL) al_destroy_event_queue(event_queue);
    if (event_queue_menu_1 != NULL) al_destroy_event_queue(event_queue_menu_1);
    if (event_queue_menu_2 != NULL) al_destroy_event_queue(event_queue_menu_2);
    if (event_queue_configs != NULL) al_destroy_event_queue(event_queue_configs);
    if (event_queue_fim != NULL) al_destroy_event_queue(event_queue_fim);
    if (event_queue_historico != NULL) al_destroy_event_queue(event_queue_historico);
    if (event_queue_fim_while != NULL) al_destroy_event_queue(event_queue_fim_while);
    if (event_queue_intro != NULL) al_destroy_event_queue(event_queue_intro);
    if (sfx_exp_file != NULL) al_destroy_sample(sfx_exp_file);
    if (sfx_viper_fire != NULL) al_destroy_sample(sfx_viper_fire);
    if (sfx_xwing_fire != NULL) al_destroy_sample(sfx_xwing_fire);
    if (sfx_exp_colision != NULL) al_destroy_sample(sfx_exp_colision);   
    if (inst_sfx_exp_file != NULL) al_destroy_sample_instance(inst_sfx_exp_file);
    if (inst_sfx_viper_fire != NULL) al_destroy_sample_instance(inst_sfx_viper_fire);
    if (inst_sfx_xwing_fire != NULL) al_destroy_sample_instance(inst_sfx_xwing_fire);
    if (inst_sfx_exp_colision != NULL) al_destroy_sample_instance(inst_sfx_exp_colision);
    if (track_menus != NULL) al_destroy_audio_stream(track_menus);
    if (track_play_game != NULL) al_destroy_audio_stream(track_play_game);
    if (track_end_menu != NULL) al_destroy_audio_stream(track_end_menu);
    if (track_intro != NULL) al_destroy_audio_stream(track_intro);
    if (xwingS1_100 != NULL) al_destroy_bitmap(xwingS1_100);
    if (xwingS2_100 != NULL) al_destroy_bitmap(xwingS2_100);
    if (xwingS1_101 != NULL) al_destroy_bitmap(xwingS1_101);
    if (xwingS2_101 != NULL) al_destroy_bitmap(xwingS2_101);
    if (xwingS1_102 != NULL) al_destroy_bitmap(xwingS1_102);
    if (xwingS2_102 != NULL) al_destroy_bitmap(xwingS2_102);
    if (viperS1_200 != NULL) al_destroy_bitmap(viperS1_200);
    if (viperS2_200 != NULL) al_destroy_bitmap(viperS2_200);
    if (viperS1_201 != NULL) al_destroy_bitmap(viperS1_201);
    if (viperS2_201 != NULL) al_destroy_bitmap(viperS2_201);
    if (viperS1_202 != NULL) al_destroy_bitmap(viperS1_202);
    if (viperS2_202 != NULL) al_destroy_bitmap(viperS2_202);
    if (tieS1_110 != NULL) al_destroy_bitmap(tieS1_110);
    if (tieS2_110 != NULL) al_destroy_bitmap(tieS2_110);
    if (craiderS1_210 != NULL) al_destroy_bitmap(craiderS1_210);
    if (craiderS2_210 != NULL) al_destroy_bitmap(craiderS2_210);
    if (death_starS != NULL) al_destroy_bitmap(death_starS);
    if (expS != NULL) al_destroy_bitmap(expS);
    if (timer != NULL) al_destroy_timer(timer);
    if (timer_menu_1 != NULL) al_destroy_timer(timer_menu_1);
    if (timer_menu_2 != NULL) al_destroy_timer(timer_menu_2);
    if (timer_configs != NULL) al_destroy_timer(timer_configs);
    if (timer_fim_while != NULL) al_destroy_timer(timer_fim_while);
    if (timer_historico != NULL) al_destroy_timer(timer_historico);
    if (timer_fim != NULL) al_destroy_timer(timer_fim);
    if (timer_intro != NULL) al_destroy_timer(timer_intro);
    if (display != NULL) al_destroy_display(display);
    if (size_32 != NULL) al_destroy_font(size_32);
    if (font_bsg_1 != NULL) al_destroy_font(font_bsg_1);
    if (font_sw_1 != NULL) al_destroy_font(font_sw_1);
    if (font_chronosfer != NULL) al_destroy_font(font_chronosfer);
    
    al_uninstall_system();
    
    if (!modo) exit(EXIT_SUCCESS);
    else exit(EXIT_FAILURE);
}