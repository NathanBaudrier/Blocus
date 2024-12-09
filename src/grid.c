#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

#include "utils.h"

#define PLAYER_1 1
#define PLAYER_2 2

typedef struct grid {
  int originX;
  int originY;
  int side;
  int size;
  int screen;
  int** data;
  Button** boxes; 
  Sprites* sprites_manager; 
  Windw window;
  int* clicked_index; 
  int orange_cross_sprite;
  int blue_cross_sprite; 
  int orange_player_sprite;
  int blue_player_sprite; 
} Grid;

/* Initialise une nouvelle grille vide */ 
Grid new_grid(Sprites* sprites_manager, Windw window, int originX, int originY, int side, int size, int screen) {
  int i, j;
  int x, y;
  char src[30];
  
  Grid grid;

  /*
    Utilisation de la fonction calloc() pour que tous les bits soient à 0.
    Signifie que toutes les cases sont vides.
  */
  int** data = (int**)calloc(size, sizeof(int*));
  Button** boxes = (Button**)malloc(size * sizeof(Button*));
  int* clicked_index = (int*)malloc(2 * sizeof(int));
 
  for(i = 0; i < size; i++) {
    data[i] = (int*)calloc(size, sizeof(int));
    boxes[i] = (Button*)malloc(size * sizeof(Button));
    
  }

  /*
    Pour être le plus précis possible lors de l'affichage de la grille,
    on cherche à avoir le côté de la grille divisible par le nombre de case.
  */
  while(side % size != 0) {
    side++;
  }

  x = originX;
  y = originY;

  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      boxes[i][j] = new_button(x, y, side / size, side / size);
      
      x += side / size; 
    }

    y += side / size;
    x = originX;
  }

  grid.originX = originX;
  grid.originY = originY;
  grid.side = side;
  grid.size = size;
  grid.screen = screen;
  grid.data = data;
  grid.boxes = boxes;
  grid.window = window;
  grid.clicked_index = clicked_index;
  sprintf(src, "assets/orange-cross-%d.png", size);
  grid.orange_cross_sprite = load_sprite(src, sprites_manager);
  sprintf(src, "assets/blue-cross-%d.png", size);
  grid.blue_cross_sprite = load_sprite(src, sprites_manager);
  sprintf(src, "assets/orange-player-%d.png", size);
  grid.orange_player_sprite = load_sprite(src, sprites_manager);
  sprintf(src, "assets/blue-player-%d.png", size);
  grid.blue_player_sprite = load_sprite(src, sprites_manager);

  return grid;		        
}

/* Dessine une grille vide sur le graphique */ 
void draw_grid(Grid grid) {
  int i;
  int x = grid.originX;
  int y = grid.originY;
  int side = grid.side; 
  int box = side / grid.size;

  ChoisirEcran(2);
  EffacerEcran(CouleurParNom("white"));
  
  DessinerRectangle(x, y, side, side);

  for(i = y + box; i < y + side; i += box) {
    DessinerSegment(x, i, x + side, i);
  }

  for(i = x + box; i < x + side; i += box) {
    DessinerSegment(i, y, i, y + side); 
  }
}

void update_grid(Grid grid) {
  int i, j;
  int data;
  Button box;

  show_screen(grid.screen, grid.window.width, grid.window.height);

  for(i = 0; i < grid.size; i++) {
    for(j = 0; j < grid.size; j++) {
      box = grid.boxes[i][j];
      data = grid.data[i][j];

      if(data == PLAYER_1) {
        AfficherSprite(grid.blue_player_sprite, box.x, box.y);
      } else if(data == PLAYER_2) {
        AfficherSprite(grid.orange_player_sprite, box.x, box.y);
      } else if(data == grid.orange_cross_sprite) {
        AfficherSprite(grid.orange_cross_sprite, box.x, box.y);
      } else if(data == grid.blue_cross_sprite) {
        AfficherSprite(grid.blue_cross_sprite, box.x, box.y);
      }
    }
  }
}

Coordinates get_player_coordinates(int player_id, Grid grid) {
  Coordinates coos; 
  int i, j;
  int stop = 0;
  
  /* Récupération des indices de la position du joueur sur la grille */
  for(i = 0; i < grid.size; i++) {
    for(j = 0; j < grid.size; j++) {
      if(grid.data[i][j] == player_id) {
        coos.i = i;
        coos.j = j;

        stop = 1;

        break;
      }
    }

    if(stop) break;
  }

  return coos;
}

int box_clicked(Grid grid) {
  int i, j;

  if(SourisCliquee()) {
    for(i = 0; i < grid.size; i++) {
      for(j = 0; j < grid.size; j++) {
        if(is_pressed_button(grid.boxes[i][j], _X, _Y)) {
          grid.clicked_index[0] = i;
          grid.clicked_index[1] = j;

          return 1;
        }
      }
    }
  }

  return 0;
}

int is_free_clicked_box(Grid grid) {
  return grid.data[grid.clicked_index[0]][grid.clicked_index[1]] == 0; 
}

int is_clicked_box_is_next_to_player(int player_id, Grid grid) {
  int player_i, player_j;
  int diff_i, diff_j;
  int stop = 0;

  /* Récupération des indices de la position du joueur sur la grille */
  for(player_i = 0; player_i < grid.size; player_i++) {
    for(player_j = 0; player_j < grid.size; player_j++) {
      if(grid.data[player_i][player_j] == player_id) {
        stop = 1;
        break;
      }
    }

    if(stop) break;
  }

  diff_i = abs(player_i - grid.clicked_index[0]);
  diff_j = abs(player_j - grid.clicked_index[1]);

  return (diff_i <= 1 && diff_j <= 1) && !(diff_i == 0 && diff_j == 0);
}

void remove_player_position(int player_id, Grid grid) {
  int i, j; 

  for(i = 0; i < grid.size; i++) {
    for(j = 0; j < grid.size; j++) {
      if(grid.data[i][j] == player_id) {
        grid.data[i][j] = 0;
      }
    }
  }
}

void move_player_to_clicked_box(int player_id, Grid grid) { 
  remove_player_position(player_id, grid);

  grid.data[grid.clicked_index[0]][grid.clicked_index[1]] = player_id;
}

void block_clicked_box(int player_id, Grid grid) {
  if(player_id == PLAYER_1) {
    grid.data[grid.clicked_index[0]][grid.clicked_index[1]] = grid.blue_cross_sprite;
  } else {
    grid.data[grid.clicked_index[0]][grid.clicked_index[1]] = grid.orange_cross_sprite;
  }
}

int has_won(int player_id, Grid grid) {
    int player_i, player_j;
    int i, j;
    int won = 1; 

    Coordinates player_pos = get_player_coordinates(player_id, grid);
    player_i = player_pos.i;
    player_j = player_pos.j;

    for(i = player_i - 1; i <= player_i + 1; i++) {
        for(j = player_j - 1; j <= player_j + 1; j++) {
            if(i >= 0 && i < grid.size && j >= 0 && j < grid.size) {
                if(i == player_i && j == player_j) {
                    continue;
                }
                
                if(grid.data[i][j] == 0) {
                    won = 0;  
                    break; 
                }

                if(grid.data[i][j] != PLAYER_1 && grid.data[i][j] != PLAYER_2) {
                    continue;
                }
            }
        }
        if(won == 0) break; 
    }

    return won;
}

void place_bot(int bot_id, Grid grid) {
    int rand_i, rand_j;

    srand((unsigned int)time(NULL));

    do {
        rand_i = rand() % grid.size;
        rand_j = rand() % grid.size;
    } while (grid.data[rand_i][rand_j] == PLAYER_1);

    grid.data[rand_i][rand_j] = bot_id;
}

void play_bot(int bot_id, Grid grid) {
    Coordinates bot_pos;
    int adjacents[8][2]; 
    int adj_count;       
    int i, j, random_index;
    int rand_i, rand_j;

    bot_pos = get_player_coordinates(bot_id, grid);
    adj_count = 0;

    for (i = bot_pos.i - 1; i <= bot_pos.i + 1; i++) {
        for (j = bot_pos.j - 1; j <= bot_pos.j + 1; j++) {
            if (i >= 0 && i < grid.size && j >= 0 && j < grid.size) { 
                if (!(i == bot_pos.i && j == bot_pos.j) && grid.data[i][j] == 0) {
                    adjacents[adj_count][0] = i;
                    adjacents[adj_count][1] = j;
                    adj_count++;
                }
            }
        }
    }

    if (adj_count > 0) {
        random_index = rand() % adj_count;
        grid.data[bot_pos.i][bot_pos.j] = 0; 
        grid.data[adjacents[random_index][0]][adjacents[random_index][1]] = bot_id;
    }

    do {
        rand_i = rand() % grid.size;
        rand_j = rand() % grid.size;
    } while (grid.data[rand_i][rand_j] != 0);

    if (bot_id == PLAYER_1) {
        grid.data[rand_i][rand_j] = grid.blue_cross_sprite; 
    } else {
        grid.data[rand_i][rand_j] = grid.orange_cross_sprite; 
    }
}

int is_void_grid(Grid grid) {
  int count = 0;
  int i, j; 

  for(i = 0; i < grid.size; i++) {
    for(j = 0; j < grid.size; j++) {
      if(grid.data[i][j] != 0) count++;
    }
  }

  return count < 2; 
}

void free_content(Grid grid) {
  int i;

  for(i = 0; i < grid.size; i++) {
    free(grid.data[i]);
    free(grid.boxes[i]);
  }

  free(grid.data);
  free(grid.boxes);
  free(grid.clicked_index);
}


