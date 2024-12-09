#ifndef GAME_H
#define GAME_H

#include <graph.h>

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

/* Initialise une nouvelle partie */ 
Game* new_game(Sprites* sprites_manager, Windw window, int number_players, Grid grid);

/* Démarre la partie */
void start_game(Game* game);

/* Passe au tour suivant */
void next_turn(Game* game);

/* Mets fin définitivement à la partie */
void stop_game(Game* game);

#endif /* GAME_H */ 
