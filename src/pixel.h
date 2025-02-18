#ifndef PIXEL_H 
#define PIXEL_H 
#include <SDL2/SDL.h> 

#define NOIR  0 
#define BLANC 1 
#define l 64      //nombre de pixels suivant la largeur 
#define L 32       //nombre de pixels suivant la longueur 
#define DIMPIXEL 8  //pixel carré de côté 8 
#define WIDTH   l*DIMPIXEL      //largeur de l'écran 
#define HEIGHT  L*DIMPIXEL       //longueur de l'écran 

typedef struct 
{ 
    SDL_Rect position; //regroupe l'abscisse et l'ordonnée 
    Uint8 couleur;   //comme son nom l'indique, c'est la couleur 
} PIXEL; 


extern SDL_Window* window;
extern SDL_Renderer* renderer; 
extern SDL_Texture *carre[2]; 
extern SDL_Surface *carreSurfaceNoir;
extern SDL_Surface *carreSurfaceBlanc;
extern PIXEL pixel[l][L]; 
extern SDL_Event event; //pour gérer la pause 

void initialiserEcran() ; 
void initialiserPixel() ; 
void dessinerPixel(PIXEL pixel) ; 
void effacerEcran() ; 
void updateEcran() ; 

#endif