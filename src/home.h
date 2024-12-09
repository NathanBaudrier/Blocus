#ifndef HOME_H
#define HOME_H

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <string.h>
#include "/usr/include/X11/keysymdef.h"

#include "utils.h"

typedef struct home {
  int screen;
  Windw window;
  Button up_button, down_button, select_button, one_player_button, two_players_button;
  int grid_size;
  int right_arrow_sprite;
  int left_arrow_sprite;
  int select_sprite;
  int one_player_sprite;
  int two_players_sprite;
  int one_player_selected_sprite;
  int two_players_selected_sprite;
  Sprites* sprites_manager;
  int number_players; 
  int end;
} Home;

Home* new_home(Windw window, Sprites* sprites_manager);

void draw_home(Home* home);

void update_home(Home* home);

int mouse_click_home(Home* home);

#endif /* HOME_H */
