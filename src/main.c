#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

#include "/usr/include/X11/keysymdef.h"

#include "grid.h"
#include "game.h"
#include "utils.h"
#include "home.h"
#include "end.h"

/* Fréquence de rafraichissement en milisecondes */
#define MICRO 1000000L

/* Taille de la fenêtre graphique */ 
#define WIDTH 900 /* Largeur */ 
#define HEIGHT 700 /* Hauteur */

/* Dimensions de l'écran */ 
#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

int main(void) {
  unsigned long next;
  Windw window;
  Game* game;
  Home* home;
  End* end;
  Sprites* sprites_manager = (Sprites*)malloc(sizeof(Sprites));

  /* NE PAS TOUCHER AUX VARIABLES QUI SUIVENT ! */ 
  int screenX = (MAX_WIDTH - WIDTH) / 2;
  int screenY = (MAX_HEIGHT - HEIGHT) / 2;
  int side = 500;
  int gridX = (WIDTH - side) / 2;
  int gridY = (HEIGHT - side) / 2;

  int action;

  window.width = WIDTH;
  window.height = HEIGHT;

  sprites_manager->count = 0;

  /* Test si la taille de la fenêtre renseignée est capable de prendre en charge l'affichage de la grille avec une marge pour divers affichages */
  if(WIDTH < (side + 100) || HEIGHT < (side + 100)) {
    printf("Taille de la fenêtre trop petite. La largeur et la hauteur de la fenêtre doivent être supérieur ou égal à 600.\n");
    return EXIT_FAILURE;
  }
  
  InitialiserGraphique();
  
  /* Créer une fenêtre toujours à peu près au milieu de l'écran */ 
  CreerFenetre(screenX, screenY, WIDTH, HEIGHT);

  home = new_home(window, sprites_manager);
  end = new_end(window, sprites_manager);

  draw_home(home);
  draw_end(end);
  show_screen(home->screen, WIDTH, HEIGHT);
  
  ChoisirEcran(0);
  
  next = Microsecondes() + MICRO;
  while(1) {
    /* SI la touche escape est pressée, cela arrête le programme. */ 
    if(ToucheEnAttente() == 1) {
      if(Touche() == XK_Escape) break;
    }
    
    if(Microsecondes() > next) {
      next = Microsecondes() + MICRO;

      if(!home->end) {
        if(mouse_click_home(home)) { 
          update_home(home);

          if(home->end) {
            game = new_game(sprites_manager, window, home->number_players, new_grid(sprites_manager, window, gridX, gridY, side, home->grid_size, 2));
            start_game(game);
            show_screen(game->grid.screen, WIDTH, HEIGHT);
          }
        }
      } else if(game->started) {
        update_grid(game->grid);

        if(game->player_turn.bot) {
          if(is_void_grid(game->grid)) {
            place_bot(game->player_turn.id, game->grid);
          } else {
            play_bot(game->player_turn.id, game->grid);
            next_turn(game);
          }
        } else if(box_clicked(game->grid)) {
          if(is_void_grid(game->grid)) {
            if(is_free_clicked_box(game->grid)) {
              move_player_to_clicked_box(game->player_turn.id, game->grid);
              next_turn(game);
            }
          } else {
            if(game->turn_type == PLACE_TYPE) {
              if(is_free_clicked_box(game->grid) && is_clicked_box_is_next_to_player(game->player_turn.id, game->grid)) {
                move_player_to_clicked_box(game->player_turn.id, game->grid);
                game->turn_type = BLOCK_TYPE;
              }
            } else {
              if(is_free_clicked_box(game->grid)) {
                block_clicked_box(game->player_turn.id, game->grid);
                next_turn(game);
              }
            }

            if(has_won(game->player1.id, game->grid)) {
              end->winner_id = game->player1.id;
              game->ended = 1; 
              game->started = 0;
              print_winner(end);
              show_screen(end->screen, WIDTH, HEIGHT);
            } else if(has_won(game->player2.id, game->grid)) {
              end->winner_id = game->player2.id;
              game->ended = 1;
              game->started = 0;
              print_winner(end);
              show_screen(end->screen, WIDTH, HEIGHT);
            }
          }
        }

      } else if(game->ended) {
        action = get_action(end);

        if(action == QUIT_ACTION) {
          stop_game(game);

          free(home);
          free(end);

          break;
        } else if(action == RESTART_ACTION) {
          home = new_home(window, sprites_manager);
          end = new_end(window, sprites_manager);

          draw_home(home);
          draw_end(end);
          show_screen(home->screen, WIDTH, HEIGHT);
        }
      }
    }
  }

  FermerGraphique();
  
  return EXIT_SUCCESS;
}
