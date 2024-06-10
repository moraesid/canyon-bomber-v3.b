#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
#endif

#include "load_allegro.h"
#include "load_midias.h"
#include "settings.h"
#include "globals.h"
#include "animations.h"
#include "ships.h"
#include "scenario.h"
#include "stats.h"
#include "records.h"
#include "screens.h"
#include "game.h"

#include <stdio.h>

int main(void)
{  
    fprintf(stderr, "Running canyon-bomber\n");
    
    load_settings();
    al_init_all();
    al_init_resources();
    init_audios_resources();
    init_images_resources();
    init_fonts_resources();
    init_videos_resources();
    
    abertura_f();
    menu_inicial_f();

    do {
        // cria objetos
        Nave p1, p2, i1, i2;
        Tile grid[LINHAS][COLUNAS];
        Estrelas planos[NUM_PLANOS][MAX_ESTRELAS];
        Explosao explosoes[LINHAS][COLUNAS];
        //

        // inicializa objetos
        init_nave(&p1, torpedoS, w_xwing, h_xwing, 5, 100);
        init_nave(&p2, torpedoS, w_viper, h_viper, 5, 200);
        init_nave_i(&i1, tieS1_110, tieS2_110, w_tie, h_tie, 5, 110);
        init_nave_i(&i2, craiderS1_210, craiderS2_210, w_craider, h_craider, 1, 210);
        init_exp(explosoes, expS);
        init_planos(planos);
        init_grid(grid);
        //
        
        menu_nomes_f();
        
        al_start_timer(timer);
        carregando_f(font_chronosfer, event_queue);
        fadeout_with_audio_plus(1, display, event_queue, track_play_game);
        contagem_regressiva_f(event_queue);

        run_game(&p1, &p2, &i1, &i2, explosoes, grid, planos);
        end_game(&p1, &p2);

        save_history(&p1, &p2);
        menu_final_f();
    } while (!__exit_program);
    
    al_destroy_all(0);
    
    return EXIT_SUCCESS;
}