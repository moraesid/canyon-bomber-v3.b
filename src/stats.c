#include "stats.h"


int nickname(ALLEGRO_EVENT ev_menu, char nick[])
{
    if (ev_menu.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(nick) < 4)
        {
            char temp[] = {ev_menu.keyboard.unichar, '\0'};
            if (ev_menu.keyboard.unichar >= '0' &&
                ev_menu.keyboard.unichar <= '9')
            {
              strcat(nick, temp);
            }
            else if (ev_menu.keyboard.unichar >= 'A' &&
                ev_menu.keyboard.unichar <= 'Z')
            {
              strcat(nick, temp);
            }
            else if (ev_menu.keyboard.unichar >= 'a' &&
                ev_menu.keyboard.unichar <= 'z')
            {
              strcat(nick, temp);
            }
        }
        if (ev_menu.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(nick) != 0)
            nick[strlen(nick) - 1] = '\0';        
        else if (ev_menu.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(nick) == 0)
            return 1;       
        else
            return 1;
    }
    else if (ev_menu.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(nick) >= 3 ) return 0;    
    else if (ev_menu.type == ALLEGRO_EVENT_KEY_DOWN && ev_menu.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(nick) < 3 ) return 1; 
    return 1;
}

void desenha_atributos_nave(Nave *nave_1, Nave *nave_2, ALLEGRO_FONT *font_1, ALLEGRO_FONT *font_2)
{
    // Jogador 1 // 378
    al_draw_textf(font_2, al_map_rgb(175, 175, 175), 215, -7, ALLEGRO_ALIGN_LEFT, "[%s]", nick_1); // Nome
    al_draw_rectangle(338, 10, 492, 30, al_map_rgb(100, 100, 100), 2); // Escudo
    al_draw_filled_rectangle(340, 12, 340 + nave_1->defesa, 28, al_map_rgb(0, 0, 200)); // Escudo
    al_draw_textf(font_1, al_map_rgb(0, 0, 190), 7, 5, 0, "%i", nave_1->pontos); // Pontos
    for (int i = 0; i < nave_1->vidas; i++)
        al_draw_filled_circle((i * 3 * RAIO_VIDA) + 110, 20, RAIO_VIDA, al_map_rgb(0, 0, 190)); // Vidas
    
    // Jogador 2 // 838
    al_draw_textf(font_2, al_map_rgb(175, 175, 175), 970, -7, ALLEGRO_ALIGN_LEFT, "[%s]", nick_2); // Nome
    al_draw_rectangle(788, 10, 942, 30, al_map_rgb(100, 100, 100), 2); // Escudo
    al_draw_filled_rectangle(790, 12, 790 + nave_2->defesa, 28, al_map_rgb(200, 0, 0)); // Escudo
    al_draw_textf(font_1, al_map_rgb(190, 0, 0), 1195, 5, 0, "%i", nave_2->pontos); // Pontos 
    for (int i = 0; i < nave_2->vidas; i++)
        al_draw_filled_circle((i * 3 * RAIO_VIDA) + 1100, 20, RAIO_VIDA, al_map_rgb(190, 0, 0)); // Vidas
}