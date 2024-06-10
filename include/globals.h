#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef ALLEGRO_COMMON
    #include <allegro5/allegro.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_ttf.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_audio.h>
    #include <allegro5/allegro_acodec.h>
    #include <allegro5/allegro_video.h>
#endif

#include <stdio.h>


extern FILE *file;

extern const unsigned int __false;
extern const unsigned int __true;
extern unsigned int MAX_SAMPLES;
extern unsigned int primeira_vez_intro;
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int RAIO_TIRO;
extern const int RAIO_VIDA;
extern const int ARRAY_W;
extern const int ARRAY_H;
extern const int COLUNAS;
extern const int LINHAS;
extern const int DIM_X;
extern const int DIM_Y;
extern const int CORES_COL;
extern const int CORES_LIN;
extern const int MAX_ESTRELAS;
extern const int NUM_PLANOS;
extern const int MAX_STRING;
extern const int MAX_REGS;
extern const int frameDelay;
extern const int expW;
extern const int expH;
extern const int expMax;
extern const int expCol;
extern const int SPACE_TEXT;
extern const int MAX_SPRITES;
extern int __exit_program;
extern int vencedor;
extern int xcon_1_save;
extern int xcon_2_save;
extern int xcon_3_save;
extern int xcon_4_save;
extern int var;
extern int var_fim;
extern int var_win;
extern int jogando;
extern int var_grid;
extern int pause_game;
extern int menu_1_first_time;
extern int menu_2_first_time;
extern int configs_first_time;
extern int tela_de_abertura_first_time;
extern int var_inimigo;
extern int y_text;
extern int x_circle;
extern int y_circle;
extern int raio;
extern int vol_sel;
extern int menu_ativo;
extern int tempo_menu_1;
extern int var_menu_1_op;
extern int base_min_menu_1;
extern int base_max_menu_1;
extern int alfa_menu_1;
extern int var_configs_op;
extern int base_max_configs;
extern int base_min_configs;
extern int alfa_configs;
extern float x1_vol;
extern float x2_vol;
extern float x3_vol;
extern const float FPS_MENU;
extern const float FPS_GAME;
extern float GAIN_TRACK_MENUS;
extern float GAIN_TRACK_PLAY_GAME;
extern float GAIN_SFX;
extern char nick_1[5];
extern char nick_2[5];
extern char v1[20];
extern char v2[20];
extern char historico_arq[];
extern char configs_arq[];

extern int posy_inicial_1;
extern int posy_inicial_2;

extern const int h_xwing;
extern const int w_xwing;
extern const int h_viper;
extern const int w_viper;
extern const int h_tie;
extern const int w_tie;
extern const int h_craider;
extern const int w_craider;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT_QUEUE *event_queue_menu_1;
extern ALLEGRO_EVENT_QUEUE *event_queue_menu_2;
extern ALLEGRO_EVENT_QUEUE *event_queue_configs;
extern ALLEGRO_EVENT_QUEUE *event_queue_fim_while;
extern ALLEGRO_EVENT_QUEUE *event_queue_historico;
extern ALLEGRO_EVENT_QUEUE *event_queue_fim;
extern ALLEGRO_EVENT_QUEUE *event_queue_intro;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_TIMER *timer_menu_1;
extern ALLEGRO_TIMER *timer_menu_2;
extern ALLEGRO_TIMER *timer_configs;
extern ALLEGRO_TIMER *timer_fim_while;
extern ALLEGRO_TIMER *timer_historico;
extern ALLEGRO_TIMER *timer_fim;
extern ALLEGRO_TIMER *timer_intro;
extern ALLEGRO_FONT *size_32;
extern ALLEGRO_FONT *font_bsg_1;
extern ALLEGRO_FONT *font_sw_1;
extern ALLEGRO_FONT *font_chronosfer;
extern ALLEGRO_SAMPLE *sfx_viper_fire;
extern ALLEGRO_SAMPLE *sfx_xwing_fire;
extern ALLEGRO_SAMPLE *sfx_exp_file;
extern ALLEGRO_SAMPLE *sfx_exp_colision;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sfx_viper_fire;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sfx_xwing_fire;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sfx_exp_file;
extern ALLEGRO_SAMPLE_INSTANCE *inst_sfx_exp_colision;
extern ALLEGRO_AUDIO_STREAM *track_menus;
extern ALLEGRO_AUDIO_STREAM *track_play_game;
extern ALLEGRO_AUDIO_STREAM *track_end_menu;
extern ALLEGRO_AUDIO_STREAM *track_intro;
extern ALLEGRO_BITMAP *intro_img_file;
extern ALLEGRO_BITMAP *game_intro;
extern ALLEGRO_VIDEO *video_intro;
extern ALLEGRO_BITMAP *xwingS1_100;
extern ALLEGRO_BITMAP *xwingS2_100;
extern ALLEGRO_BITMAP *xwingS1_101;
extern ALLEGRO_BITMAP *xwingS2_101;
extern ALLEGRO_BITMAP *xwingS1_102;
extern ALLEGRO_BITMAP *xwingS2_102;
extern ALLEGRO_BITMAP *viperS1_200;
extern ALLEGRO_BITMAP *viperS2_200;
extern ALLEGRO_BITMAP *viperS1_201;
extern ALLEGRO_BITMAP *viperS2_201;
extern ALLEGRO_BITMAP *viperS1_202;
extern ALLEGRO_BITMAP *viperS2_202;
extern ALLEGRO_BITMAP *death_starS;
extern ALLEGRO_BITMAP *expS;
extern ALLEGRO_BITMAP *tieS1_110;
extern ALLEGRO_BITMAP *tieS2_110;
extern ALLEGRO_BITMAP *craiderS1_210;
extern ALLEGRO_BITMAP *craiderS2_210;
extern ALLEGRO_BITMAP *torpedoS;
extern ALLEGRO_BITMAP *sprites_xwing[6];
extern ALLEGRO_BITMAP *sprites_viper[6];

#endif