# Documentation

<br>

## Configuration  

<br>

Pour modifier la fréquence de rafraichissement, vous pouvez modifier la valeur de la constante `MICRO`.
Initialement, cette constante est égale à 1 secondes, cela veut dire que l'interface graphique sera raffraichie une fois par seconde.  
<u>La valeur doit être en microsecondes !</u>

```c
/* Fréquence de rafraichissement en microsecondes */ 
#define MICRO 1000000L
```  

<br>

Vous pouvez également définir les dimensions de l'écran sur lequel vous vous trouvez pour profiter d'une meilleure expérience en modifiant les constantes `MAX_WIDTH` et `MAX_HEIGHT`. 

```c
/* Taille de l'écran */ 
#define MAX_WIDTH 1270 /* Largeur */ 
#define MAX_HEIGHT 740 /* Hauteur */ 
```

<br>

Pour finir, il vous est possible de modifier la taille de la fenêtre graphique à l'aide des constantes `WIDTH` et `HEIGHT`.  
<u>Vous devez obligatoirement mettre des valeurs supérieures à 600 !</u>

```c
#define WIDTH 900 /* Largeur */
#define HEIGHT 600 /* Hauteur */ 
``` 

<br>

###### Ces deux derniers paramètres vous permettront d'avoir une fenêtre et une grille de jeu centrée, le tout de manière totalement automatisé.

<br>

## Exécution  

<br>

Pour lancer le programme, il vous suffit d'ouvrir un terminal, de vous placer à la racine du projet et d'exécuter la commande `make run`.

Si vous souhaitez supprimer tous les fichiers exécutables (`.o`), il vous suffit d'exécuter la commande `make clean`.

