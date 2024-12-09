#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "grid.h"

#define ONE_PLAYER 1
#define TWO_PLAYERS 2

#define PLACE_TYPE 1
#define BLOCK_TYPE 2

typedef struct player {
  int id;
  unsigned short int bot;
  int next_move[2];
} Player;

typedef struct game {
  unsigned int started; /* Partie débutée (booleen) */ 
  unsigned int ended; /* Partie terminée (booleen) */ 
  Sprites* sprites_manager;
  Windw window;
  Grid grid;
  Player player1;
  Player player2;
  Player player_turn;
  int turn_type;
} Game; 

Game* new_game(Sprites* sprites_manager, Windw window, int number_players, Grid grid) {
  Game* game = (Game*) malloc(sizeof(Game));
  Player player1, player2;

  player1.id = ONE_PLAYER;
  player1.bot = 0;

  player2.id = TWO_PLAYERS;
  player2.bot = number_players == ONE_PLAYER ? 1 : 0; /* S'il n'y a un qu'un vrai joueur, le J2 sera donc un bot */ 

  game->started = 0;
  game->ended = 0;
  game->sprites_manager = sprites_manager;
  game->window = window;
  game->grid = grid;
  game->player1 = player1;
  game->player2 = player2;
  game->player_turn = player1;
  game->turn_type = PLACE_TYPE;

  return game; 
}

void start_game(Game* game) {
  game->started = 1;

  draw_grid(game->grid);
}

void next_turn(Game* game) {
  game->player_turn = game->player_turn.id == game->player1.id ? game->player2 : game->player1;
  game->turn_type = PLACE_TYPE;
}

void stop_game(Game* game) {
  free_content(game->grid);
  free_sprites(game->sprites_manager);
}


