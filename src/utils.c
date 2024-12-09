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

Button new_button(int x, int y, int width, int height) {
  Button button;

  button.x = x;
  button.y = y;
  button.width = width;
  button.height = height;

  return button; 
}

int is_pressed_button(Button button, int x, int y) {
  return x >= button.x && x <= button.x + button.width && y >= button.y && y <= button.y + button.height;

  return 0; 
}

/* Renvoie l'écran affiché ou 0 si un problème est intervenu pendant l'exécution du programme */
int show_screen(int screen, int width, int height) {
  if(screen <= 0 || screen > 10) return 0;
  
  ChoisirEcran(0);
  EffacerEcran(CouleurParNom("white"));
  CopierZone(screen, 0, 0, 0, width, height, 0, 0);

  return screen;
}

void close_graph_error(char* error) {
  printf("%s\n", error);
  /*FermerGraphique();*/
}

int load_sprite(char* src, Sprites* manager) {
  int sprite = ChargerSprite(src);

  if(sprite == -1) {
    close_graph_error("Erreur lors du chargement d'un sprite.\n");
  }
  
  manager->count++;

  return sprite; 
}

void free_sprites(Sprites* manager) {
  int sprite;

  for(sprite = 1; sprite <= manager->count; sprite++) {
    LibererSprite(sprite);
  }
}

void print_text(int x, int y, int size, char* color, char* text) {
  ChoisirCouleurDessin(CouleurParNom(color));
  EcrireTexte(x, y, text, size);
}

