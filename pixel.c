#include "pixel.h" 

SDL_Window* window;
SDL_Renderer* renderer; 
SDL_Texture *carre[2]; 
SDL_Surface *carreSurfaceNoir = NULL;
SDL_Surface *carreSurfaceBlanc = NULL;
PIXEL pixel[l][L]; 
SDL_Event event; //pour gérer la pause 

void initialiserPixel() 
{ 
    for(Uint8 x=0;x<l;x++) 
    { 
        for(Uint8 y=0;y<L;y++) 
        { 
            pixel[x][y].position.x=x*DIMPIXEL; 
            pixel[x][y].position.y=y*DIMPIXEL; 
            pixel[x][y].couleur=NOIR; 
        } 
    } 

} 

void initialiserEcran() 
{ 
    carre[0]=NULL; 
    carre[1]=NULL; 

    window = SDL_CreateWindow("BC-Chip8 By BestCoder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Création de la surface noire (dimension de chaque pixel)
    carreSurfaceNoir = SDL_CreateRGBSurface(0, DIMPIXEL, DIMPIXEL, 32, 0, 0, 0, 0);
    if (carreSurfaceNoir == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface noire : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Remplissage de la surface noire avec la couleur noire
    SDL_FillRect(carreSurfaceNoir, NULL, SDL_MapRGB(carreSurfaceNoir->format, 0x00, 0x00, 0x00));

    // Création de la surface blanche (dimension de chaque pixel)
    carreSurfaceBlanc = SDL_CreateRGBSurface(0, DIMPIXEL, DIMPIXEL, 32, 0, 0, 0, 0);
    if (carreSurfaceBlanc == NULL) {
        fprintf(stderr, "Erreur lors de la création de la surface blanche : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Remplissage de la surface blanche avec la couleur blanche
    SDL_FillRect(carreSurfaceBlanc, NULL, SDL_MapRGB(carreSurfaceBlanc->format, 0xFF, 0xFF, 0xFF));


    carre[0] = SDL_CreateTextureFromSurface(renderer, carreSurfaceNoir);
    carre[1] = SDL_CreateTextureFromSurface(renderer, carreSurfaceBlanc);
    if(carre[0]==NULL || carre[1]==NULL) 
    { 
       fprintf(stderr,"Erreur lors du chargement de la surface %s",SDL_GetError()); 
       exit(EXIT_FAILURE); 
    } 
} 

void dessinerPixel(PIXEL pixel) {
     /* pixel.couleur peut prendre deux valeurs : 0, auquel cas on dessine le pixel en noir, ou 1, on dessine alors le pixel en blanc */ 

    SDL_Texture *texture = (pixel.couleur == NOIR) ? carre[0] : carre[1];
    SDL_RenderCopy(renderer, texture, NULL, &pixel.position);
}

void effacerEcran() 
{ 
    //Pour effacer l'écran, on remet tous les pixels en noir 

    Uint8 x=0,y=0; 
    for(x=0;x<l;x++) 
    { 
        for(y=0;y<L;y++) 
        { 
            pixel[x][y].couleur=NOIR; 
        } 
    } 

    //on repeint l'écran en noir 
    SDL_Surface *surface = SDL_GetWindowSurface(window); // Obtient la surface de la fenêtre
    SDL_FillRect(surface, NULL, NOIR); // Remplir la surface avec la couleur NOIR
    SDL_UpdateWindowSurface(window); // Met à jour la fenêtre après avoir modifié la surface
} 
void updateEcran() 
{ 
  //On dessine tous les pixels à l'écran 
Uint8 x=0,y=0; 

 for(x=0;x<l;x++) 
    { 
        for(y=0;y<L;y++) 
        { 
             dessinerPixel(pixel[x][y]); 
        } 
    } 

    SDL_RenderPresent(renderer); //on affiche les modifications 
}