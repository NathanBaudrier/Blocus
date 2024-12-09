#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

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

End* new_end(Windw window, Sprites* sprites_manager) {
  End* end = (End*)malloc(sizeof(End));

  end->screen = 3;

  end->window = window;
  end->sprites_manager = sprites_manager;

  end->quit_button = new_button((window.width / 2) - 280, (window.height / 2) - 60, 280, 60);
  end->restart_button = new_button((window.width / 2) - 280, (window.height / 2) - 120, 280, 60);

  end->quit_sprite = load_sprite("assets/quit.png", sprites_manager);
  end->restart_sprite = load_sprite("assets/restart.png", sprites_manager);

  return end;
}

void draw_end(End* end) {
  ChoisirEcran(end->screen);
  EffacerEcran(CouleurParNom("white"));

  AfficherSprite(end->restart_sprite, end->restart_button.x, end->restart_button.y);
  AfficherSprite(end->quit_sprite, end->quit_button.x, end->quit_button.y);
}

void print_winner(End* end) {
  char text[30];

  ChoisirEcran(end->screen);
  sprintf(text, "Winner : Player %d", end->winner_id);
  print_text((end->window.width / 2) - (TailleChaineEcran(text, 2) / 2), 100, 2, "black", text);
}

int get_action(End* end) {
  if(SourisCliquee()) {
    int x = _X, y = _Y;

    if(is_pressed_button(end->quit_button, x, y)) {
      return QUIT_ACTION;  
    }

    if (is_pressed_button(end->restart_button, x, y)){
      return RESTART_ACTION;
    } 
  }

  return 0;
}


