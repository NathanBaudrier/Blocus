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

Home* new_home(Windw window, Sprites* sprites_manager) {
  Home* home = (Home*) malloc(sizeof(Home));

  home->screen = 1;
  home->window = window;
  
  home->grid_size = 3;
  home->up_button = new_button(600, 300, 30, 30);
  home->down_button = new_button(300, 300, 30, 30);
  home->select_button = new_button(400, 500, 280, 60);
  home->one_player_button = new_button(50, 400, 280, 60);
  home->two_players_button = new_button(50, 450, 280, 60);
  
  home->right_arrow_sprite = load_sprite("assets/right-arrow.png", sprites_manager);
  home->left_arrow_sprite = load_sprite("assets/left-arrow.png", sprites_manager);
  home->select_sprite = load_sprite("assets/select.png", sprites_manager);
  home->one_player_sprite = load_sprite("assets/one-player.png", sprites_manager);
  home->two_players_sprite = load_sprite("assets/two-players.png", sprites_manager);
  home->one_player_selected_sprite = load_sprite("assets/one-player-selected.png", sprites_manager);
  home->two_players_selected_sprite = load_sprite("assets/two-players-selected.png", sprites_manager);

  home->sprites_manager = sprites_manager;

  home->number_players = 1;

  home->end = 0;

  return home; 
}

void draw_home(Home* home) {
   char text[20];

   ChoisirEcran(home->screen);
   EffacerEcran(CouleurParNom("white"));  

   AfficherSprite(home->right_arrow_sprite, home->up_button.x, home->up_button.y);
   AfficherSprite(home->left_arrow_sprite, home->down_button.x, home->down_button.y);
   AfficherSprite(home->select_sprite, home->select_button.x, home->select_button.y);
   
   AfficherSprite(home->one_player_selected_sprite, home->one_player_button.x, home->one_player_button.y);
   AfficherSprite(home->two_players_sprite, home->two_players_button.x, home->two_players_button.y);
 
   sprintf(text, "Taille %dx%d", home->grid_size, home->grid_size);
   print_text((home->window.width / 2) - (TailleChaineEcran(text, 2) / 2), 100, 2, "black", text);
}

void update_home(Home* home) {
  char text[20];

  if(!home->end) {
    EffacerEcran(CouleurParNom("white"));

    AfficherSprite(home->right_arrow_sprite, home->up_button.x, home->up_button.y);
    AfficherSprite(home->left_arrow_sprite, home->down_button.x, home->down_button.y);
    AfficherSprite(home->select_sprite, home->select_button.x, home->select_button.y);

    if(home->number_players == 1) {
      AfficherSprite(home->one_player_selected_sprite, home->one_player_button.x, home->one_player_button.y);
      AfficherSprite(home->two_players_sprite, home->two_players_button.x, home->two_players_button.y);
    } else {
      AfficherSprite(home->one_player_sprite, home->one_player_button.x, home->one_player_button.y);
      AfficherSprite(home->two_players_selected_sprite, home->two_players_button.x, home->two_players_button.y);
    }
    
    sprintf(text, "Taille %dx%d", home->grid_size, home->grid_size);
    print_text((home->window.width / 2) - (TailleChaineEcran(text, 2) / 2), 100, 2, "black", text);
  }
}
  

int mouse_click_home(Home* home) {
    
  if(SourisCliquee()) {
    int x = _X, y = _Y;

    if(is_pressed_button(home->up_button, x, y)) {
      if(home->grid_size < 9) {
        home->grid_size++;
      }
      return 1;
    }

    if(is_pressed_button(home->down_button, x, y)) {
      if(home->grid_size > 3) {
        home->grid_size--;
        return 1;
      }
    }

    if(is_pressed_button(home->select_button, x, y)) {
      home->end = 1;
      return 1;
    }

    if(is_pressed_button(home->one_player_button, x, y)) {
      home->number_players = 1;
      return 1;
    }

    if (is_pressed_button(home->two_players_button, x, y)) {
      home->number_players = 2;
      return 1;
    } 
  }

  return 0;
}
