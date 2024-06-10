#ifndef ALLEGRO_COMMON
    #include "load_allegro.h"
#endif

#include "animations.h"


void init_exp(Explosao exp[][COLUNAS], ALLEGRO_BITMAP *IMGexp)
{
    for (int i=0; i<LINHAS; i++)
    {
        for (int j=0; j<COLUNAS; j++)
        {
            exp[i][j].x = 0;
            exp[i][j].y = 0;       
            exp[i][j].ativo = 0;
            exp[i][j].maxQ = expMax;
            exp[i][j].atualQ = 0;
            exp[i][j].contQ = 0;
            exp[i][j].delayQ = 1;
            exp[i][j].wQ = expW;
            exp[i][j].hQ = expH;
            exp[i][j].numCol = expCol;
            exp[i][j].dir = 1;
            exp[i][j].imagem = IMGexp;     
        }
    }
}

void desenha_exp(Explosao exp[][COLUNAS])
{
    int x, y;
    for (int i=0; i<LINHAS; i++)
    {
        for (int j=0; j<COLUNAS; j++)
        {
            if (exp[i][j].ativo)
            {
                x = (exp[i][j].atualQ % exp[i][j].numCol) * exp[i][j].wQ;
                y = (exp[i][j].atualQ / exp[i][j].numCol) * exp[i][j].hQ;
                al_draw_bitmap_region(exp[i][j].imagem, x, y, exp[i][j].wQ, exp[i][j].hQ, exp[i][j].x - exp[i][j].wQ/2, exp[i][j].y - exp[i][j].hQ/2, 0);
            }
        }
    }
}

void inicia_exp(Explosao exp[][COLUNAS], int x, int y)
{
    for (int i=0; i<LINHAS; i++)
    {
        for (int j=0; j<COLUNAS; j++)
        {
            if (!exp[i][j].ativo)
            {
                exp[i][j].ativo = 1;
                exp[i][j].x = x;
                exp[i][j].y = y;
                break;
            }
        }
    }
}

void atualiza_exp(Explosao exp[][COLUNAS])
{
    for (int i=0; i<LINHAS; i++)
    {
        for (int j=0; j<COLUNAS; j++)
        {
            if (exp[i][j].ativo)
            {
                if (++exp[i][j].contQ >= exp[i][j].delayQ)
                {
                    exp[i][j].atualQ += exp[i][j].dir;
                    if (exp[i][j].atualQ >= exp[i][j].maxQ)
                    {
                        if (var_win) jogando = 0;
                        exp[i][j].atualQ = 0;
                        exp[i][j].ativo = 0;
                    }  
                    exp[i][j].contQ = 0;
                }
            }
        }
    }
}

int fadein_f(int velocidade, ALLEGRO_BITMAP *imagem, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue)
{
    if (velocidade < 0)
        velocidade = 1;
    else if (velocidade > 15)
        velocidade = 15;
    
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {    
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(imagem, al_map_rgba(alfa, alfa, alfa, alfa), 0, 0, 0);
        al_flip_display();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            return -1;
        al_rest(0.005);       
        alfa += velocidade;
    }
    return 1;
}

int fadeout_f(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue)
{
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(display));

    if (velocidade <= 0)
        velocidade = 1;
    else if (velocidade > 15)
        velocidade = 15;

    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);        
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);   
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
            return -1;
        al_rest(0.005);
    }
    al_destroy_bitmap(buffer);
    return 1;
}

void fadeout_with_audio_less(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_AUDIO_STREAM *audio_stream)
{
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
    
    float mixer_gain = 1.0;
    al_set_mixer_gain(al_get_default_mixer(), mixer_gain);

    if (velocidade <= 0)
        velocidade = 1;
    else if (velocidade > 15)
        velocidade = 15;
    
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        if (mixer_gain <= 0.0) al_drain_audio_stream(audio_stream);
        mixer_gain -= 0.01;
        al_set_mixer_gain(al_get_default_mixer(), mixer_gain);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);        
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        al_rest(0.005);
    }
    if (mixer_gain > 0.0)
    {
        while (mixer_gain > 0.0) 
        {
            mixer_gain -= 0.001;
            al_set_mixer_gain(al_get_default_mixer(), mixer_gain);
            al_rest(0.005);
        }
    }
    al_destroy_bitmap(buffer);
    return;
}

void fadeout_with_audio_plus(int velocidade, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_AUDIO_STREAM *audio_stream)
{
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(display), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(display));
    
    float mixer_gain = 0.001;
    al_set_mixer_gain(al_get_default_mixer(), mixer_gain);
    al_set_audio_stream_playing(audio_stream, xcon_1_save);

    if (velocidade <= 0)
        velocidade = 1;
    else if (velocidade > 15)
        velocidade = 15;
    
    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        mixer_gain += 0.001;
        if (mixer_gain >= 1.0) mixer_gain = 1.0;
        al_set_mixer_gain(al_get_default_mixer(), mixer_gain);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);        
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            al_destroy_all(0);
        al_rest(0.005);
    }
    if (mixer_gain < 1.0)
    {
        while (mixer_gain < 1.0) 
        {
            mixer_gain += 0.001;
            al_set_mixer_gain(al_get_default_mixer(), mixer_gain);
            al_rest(0.005);
        }
    }
    al_destroy_bitmap(buffer);
    return;
}

void carregando_f(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue)
{   
    for (int i=0; i<=2; i++)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev); 
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Carrengando");
        al_flip_display();
        al_rest(0.5);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Carrengando.");
        al_flip_display();
        al_rest(0.5);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Carrengando..");
        al_flip_display();
        al_rest(0.5);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(67, 165, 207), SCREEN_W / 2, SCREEN_H / 2, ALLEGRO_ALIGN_CENTER, "Carrengando...");
        al_flip_display();
        al_rest(0.5);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) al_destroy_all(0);
    }
    return;
}
