#ifndef GRID_H
#define GRID_H

#include "utils.h"

/* Structure de la représentation d'une grillec */
typedef struct grid {
  int originX;
  int originY;
  int side;
  int size;
  int screen;
  int** data;
  Button*** boxes; 
  Windw window; 
  Sprites* sprites_manager; 
  int* clicked_index;
  int orange_cross_sprite;
  int blue_cross_sprite; 
  int orange_player_sprite;
  int blue_player_sprite; 
} Grid;

/* Initialise une nouvelle grille */
Grid new_grid(Sprites* sprites_manager, Windw window, int originX, int originY, int side, int size, int screen);

/* Dessine une grille vide */
void draw_grid(Grid grid);

void update_grid(Grid grid);

/* Renvoie si une case de la grille a été cliquée */
int box_clicked(Grid grid);

int is_clicked_box_is_next_to_player(int player_id, Grid grid);

/* Renvoie si la case cliquée est vide ou non */
int is_free_clicked_box(Grid grid);

void remove_player_position(int player_id, Grid grid);

/* Déplace le joueur sur la case cliquée */
void move_player_to_clicked_box(int player_id, Grid grid);

/* Condamne la case cliquée */
void block_clicked_box(int player_id, Grid grid);

int has_won(int player_id, Grid grid);

void place_bot(int bot_id, Grid grid);

/* Fait jouer le bot */
void play_bot(int bot_id, Grid grid);

/* Renvoie si la vide grille est vide ou presque pour détecter si c'est le premier placement des deux joueurs */
int is_void_grid(Grid grid);

/* Libère la mémoire du contenu de la grille */
void free_content(Grid grid);

#endif /* GRID_H */ 
