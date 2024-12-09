#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

typedef struct button {
  int x;
  int y;
  int width;
  int height;
} Button;

typedef struct sprites {
  int count;
} Sprites;

typedef struct window {
  int width;
  int height;
} Windw;

typedef struct coordinates {
  int i, j;
} Coordinates; 

Button new_button(int x, int y, int width, int height);

unsigned int is_pressed_button(Button button, int x, int y);

int show_screen(int screen, int width, int height);

void close_graph_error(char* error);

int load_sprite(char* src, Sprites* manager);

void free_sprites(Sprites* manager);

void print_text(int x, int y, int size, char* color, char* text); 

#endif /* UTILS_H */
