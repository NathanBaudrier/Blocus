#ifndef END_H
#define END_H

#include "utils.h"

#define QUIT_ACTION 1
#define RESTART_ACTION 2

typedef struct end {
  int screen;
  int winner_id;
  Button quit_button, restart_button;
  Sprites* sprites_manager;
  Windw window;
  int quit_sprite;
  int restart_sprite;
} End;

End* new_end(Windw window, Sprites* sprites_manager);

void draw_end(End* end);

void print_winner(End* end);

int get_action(End* end);

#endif /* END_H */ 