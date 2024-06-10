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

#include "globals.h"

#include "load_midias.h"


void init_audios_resources(void)
{   
    al_reserve_samples(MAX_SAMPLES);
    
    // carrega midias (sfx) - inicio
    sfx_exp_file = al_load_sample("../resources/Audios/sfx_exp_tile.ogg");
    sfx_exp_colision = al_load_sample("../resources/Audios/sfx_exp_colision.ogg");
    sfx_xwing_fire = al_load_sample("../resources/Audios/sfx_xwing_fire.ogg");
    sfx_viper_fire = al_load_sample("../resources/Audios/sfx_viper_fire.ogg");
    
    if (!sfx_exp_file || !sfx_exp_colision || !sfx_xwing_fire || !sfx_viper_fire)
    {
        fprintf(stderr, "ERRO 1: arquivo de audio não existe ou não pode ser acessado!\n");
        al_destroy_all(1);
    }
    
    inst_sfx_exp_file = al_create_sample_instance(sfx_exp_file);
    al_attach_sample_instance_to_mixer(inst_sfx_exp_file, al_get_default_mixer());
    
    inst_sfx_exp_colision = al_create_sample_instance(sfx_exp_colision);
    al_attach_sample_instance_to_mixer(inst_sfx_exp_colision, al_get_default_mixer());

    inst_sfx_xwing_fire = al_create_sample_instance(sfx_xwing_fire);
    al_attach_sample_instance_to_mixer(inst_sfx_xwing_fire, al_get_default_mixer());

    inst_sfx_viper_fire = al_create_sample_instance(sfx_viper_fire);
    al_attach_sample_instance_to_mixer(inst_sfx_viper_fire, al_get_default_mixer());
    // fim
    
    // carrega midias (tracks) - inicio
    track_intro = al_load_audio_stream("../resources/Audios/track_intro.ogg", 4, 1024);
    track_menus = al_load_audio_stream("../resources/Audios/track_menus.ogg", 4, 1024);
    track_play_game = al_load_audio_stream("../resources/Audios/track_play_game.ogg", 4, 1024);
    track_end_menu = al_load_audio_stream("../resources/Audios/track_end_menu.ogg", 4, 1024);
    
    if (!track_intro || !track_menus || !track_play_game)
    {
        fprintf(stderr, "ERRO 1: arquivo de audio não existe ou não pode ser acessado!\n");
        al_destroy_all(1);
    }
    
    al_attach_audio_stream_to_mixer(track_intro, al_get_default_mixer());
    al_set_audio_stream_playmode(track_menus, ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_playing(track_intro, __false);

    al_attach_audio_stream_to_mixer(track_menus, al_get_default_mixer());
    al_set_audio_stream_playmode(track_menus, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(track_menus, __false);

    al_attach_audio_stream_to_mixer(track_play_game, al_get_default_mixer());
    al_set_audio_stream_playmode(track_play_game, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(track_play_game, __false);
    
    al_attach_audio_stream_to_mixer(track_end_menu, al_get_default_mixer());
    al_set_audio_stream_playmode(track_end_menu, ALLEGRO_PLAYMODE_LOOP);
    al_set_audio_stream_playing(track_end_menu, __false);
    //fim
}

void init_images_resources(void)
{
    // carrega imagens
    intro_img_file = al_load_bitmap("../resources/Images/first_intro.bmp");
    xwingS1_100 = al_load_bitmap("../resources/Images/xwing.png");
    xwingS2_100 = al_load_bitmap("../resources/Images/xwing_back.png");
    xwingS1_101 = al_load_bitmap("../resources/Images/xwing_t-65.png");
    xwingS2_101 = al_load_bitmap("../resources/Images/xwing_t-65_back.png");
    xwingS1_102 = al_load_bitmap("../resources/Images/xwing_t-70.png");
    xwingS2_102 = al_load_bitmap("../resources/Images/xwing_t-70_back.png");
    viperS1_200 = al_load_bitmap("../resources/Images/viper.png");
    viperS2_200 = al_load_bitmap("../resources/Images/viper_back.png");
    viperS1_201 = al_load_bitmap("../resources/Images/viper-mark3.png");
    viperS2_201 = al_load_bitmap("../resources/Images/viper-mark3_back.png");
    viperS1_202 = al_load_bitmap("../resources/Images/viper-mark4.png");
    viperS2_202 = al_load_bitmap("../resources/Images/viper-mark4_back.png");
    tieS1_110 = al_load_bitmap("../resources/Images/tie.png");
    tieS2_110 = al_load_bitmap("../resources/Images/tie_back.png");
    craiderS1_210 = al_load_bitmap("../resources/Images/cylon_raider-mark2.png");
    craiderS2_210 = al_load_bitmap("../resources/Images/cylon_raider-mark2_back.png");
    death_starS = al_load_bitmap("../resources/Images/death_star.png");
    expS = al_load_bitmap("../resources/Images/exp6.png");
    torpedoS = al_load_bitmap("../resources/Images/torpedo16.png");
    game_intro = al_load_bitmap("../resources/Images/game_intro.bmp");
    
    if (!intro_img_file || !xwingS1_100 || !xwingS2_100 || !xwingS1_101 || !xwingS2_101 || !xwingS1_102 || !xwingS2_102 || 
            !viperS1_200 || !viperS2_200 || !viperS1_201 || !viperS2_201 || !viperS1_202 || !viperS2_202 || !tieS1_110 || !tieS2_110 || 
                                                    !craiderS1_210 || !craiderS2_210 || !death_starS || !expS || !torpedoS || !game_intro )
    {
        fprintf(stderr, "ERRO 1: arquivo de imagem não existe ou não pode ser acessado!\n");
        al_destroy_all(1);
    }
}

void init_fonts_resources(void)
{
    // carrega fontes
    size_32 = al_load_font("../resources/Fonts/arial.ttf", 32, 1);
    font_bsg_1 = al_load_font("../resources/Fonts/font_bsg_1.ttf", 28, 1);
    font_sw_1 = al_load_font("../resources/Fonts/font_sw_1.ttf", 28, 1);
    font_chronosfer = al_load_font("../resources/Fonts/Chronosfer-Demo.ttf", 46, 1);
    
    if (!size_32 || !font_bsg_1 || !font_sw_1 || !font_chronosfer)
    {
        fprintf(stderr, "ERRO 1: arquivo de fontes não existe ou não pode ser acessado!\n");
        al_destroy_all(1);
    }
    //
}

void init_videos_resources(void)
{
    video_intro = al_open_video("../resources/Videos/star_wars_intro.ogv");
    if (!video_intro)
    {
        fprintf(stderr,"arquivo de video não existe ou não pode ser acessado!\n");
        al_destroy_all(1);
    }
}