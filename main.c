#ifdef _WIN32 //Si vous utilisez MSYS2 avec MinGW

#define SDL_MAIN_HANDLED
#include "cpu.h" 
#include "pixel.h"

void initialiserSDL(); 
void quitterSDL(); 
void pause(); 

int main(int argc, char *argv[]) 
{ 
    initialiserSDL(); 
    initialiserEcran(); 
    initialiserPixel(); 

    updateEcran(); 
    pause(); 

    return EXIT_SUCCESS; 
} 


void initialiserSDL() 
{ 
    atexit(quitterSDL); 

    if(SDL_Init(SDL_INIT_VIDEO)==-1) 
    { 
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL %s",SDL_GetError()); 
        exit(EXIT_FAILURE); 
    } 
} 


void quitterSDL() {
    if (carre[0]) SDL_DestroyTexture(carre[0]);
    if (carre[1]) SDL_DestroyTexture(carre[1]);
    if (carreSurfaceNoir) SDL_FreeSurface(carreSurfaceNoir);
    if (carreSurfaceBlanc) SDL_FreeSurface(carreSurfaceBlanc);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void pause() 
{
    Uint8 continuer=1; 
 
    do 
    { 
        SDL_WaitEvent(&event); 

        switch(event.type) 
         { 
             case SDL_QUIT: 
                    continuer=0; 
                    break; 
             case SDL_KEYDOWN: 
                    continuer=0; 
                    break; 
             default: break; 
         } 
    }while(continuer==1); 

}

#endif