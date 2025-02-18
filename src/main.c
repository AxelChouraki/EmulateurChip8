#ifdef _WIN32 //Si vous utilisez MSYS2 avec MinGW
#define SDL_MAIN_HANDLED // "Undefined reference to `WinMain'" This was caused by SDL defining it's own main function in SDL_main.h. To prevent SDL define the main function an SDL_MAIN_HANDLED macro has to be defined before the SDL.h header is included.
#define VITESSECPU 4 //nombre d'opérations par tour 
#define FPS 16      //pour le rafraîchissement 

#include "cpu.h" 
#include "pixel.h"

void initialiserSDL(); 
void quitterSDL(); 
void pause(); 
Uint8 chargerJeu(const char* chemin);
Uint8 listen(); 

int main() 
{ 
    initialiserSDL() ; 
    initialiserEcran() ; 
    initialiserPixel() ; 
    initialiserJump();
    chargerFont();

    cpu.pc = 0x200; // CHIP-8 démarre à l'adresse 512
    printf("PC initialise a %04X\n", cpu.pc);
    
    Uint8 continuer=1,demarrer=0,compteur=0; 



    //demarrer=chargerJeu("roms/Games/GAMES/MAZE.ch8") ;
    const char* jeu = "roms/Test/BC_test.ch8";
    printf("Jeu charge: %s\n", jeu);
    demarrer=chargerJeu(jeu) ;

    if (demarrer == 0) {
        fprintf(stderr, "Erreur : Impossible de charger la ROM\n");
        return EXIT_FAILURE;
    }

    if(demarrer==1) 
    { 
        do { 
            continuer=listen() ; //afin de pouvoir quitter l'émulateur 

            for(compteur=0;compteur<VITESSECPU;compteur++) 
            { 
                interpreterOpcode(recupererOpcode()) ; 
            } 
            
            updateEcran(); 
            decompter(); 
            SDL_Delay(FPS); //une pause de 16 ms 
        }while(continuer==1); 
    } 
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

Uint8 chargerJeu(const char* chemin) { 
    FILE *jeu = fopen(chemin, "rb"); 

    if (jeu != NULL) { 
        size_t taille = fread(&cpu.memoire[ADRESSEDEBUT], sizeof(Uint8), TAILLEMEMOIRE - ADRESSEDEBUT, jeu);
        fclose(jeu);

        printf("ROM chargee, %zu octets lus\n", taille);
        
        return (taille > 0) ? 1 : 0;
    } else { 
        fprintf(stderr, "Probleme d'ouverture du fichier\n");
        return 0;
    } 
}


Uint8 listen() 
{ 
    Uint8 continuer=1; 
    while(SDL_PollEvent(&event)) 
    { 
        switch(event.type) 
            { 
                case SDL_QUIT: {continuer = 0;break;} 
                case SDL_KEYDOWN:{continuer=0 ;break;} 

                default:{ break;} 
            } 
    } 
    return continuer; 
}

#endif