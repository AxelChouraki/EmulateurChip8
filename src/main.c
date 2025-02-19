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
    const char* jeu = "roms/Games/GAMES/BREAKOUT.ch8";
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
                        if(event.key.keysym.sym==SDLK_p) 
                           continuer=0; 
                    break;      
             default:   break; 
         } 
    }while(continuer==1); 
     
    SDL_Delay(200); //on fait une petite pause pour ne pas prendre le joueur au dépourvu 
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
    while( SDL_PollEvent(&event)) 
    { 
        switch(event.type) 
        { 
            case SDL_QUIT: {continuer = 0;break;} 
            case SDL_KEYDOWN:{ 
                switch(event.key.keysym.sym) 
                { 
                    case SDLK_KP_0:{ cpu.touche[0x0]=1;break;} 
                    case SDLK_KP_7:{ cpu.touche[0x1]=1;break;} 
                    case SDLK_KP_8:{ cpu.touche[0x2]=1;break;} 
                    case SDLK_KP_9:{ cpu.touche[0x3]=1;break;} 
                    case SDLK_KP_4:{ cpu.touche[0x4]=1;break;} 
                    case SDLK_KP_5:{ cpu.touche[0x5]=1;break;} 
                    case SDLK_KP_6:{ cpu.touche[0x6]=1;break;} 
                    case SDLK_KP_1:{ cpu.touche[0x7]=1;break;} 
                    case SDLK_KP_2:{ cpu.touche[0x8]=1;break;} 
                    case SDLK_KP_3:{ cpu.touche[0x9]=1;break;} 
                    case SDLK_RIGHT:{ cpu.touche[0xA]=1;break;} 
                    case SDLK_KP_PERIOD:{cpu.touche[0xB]=1;break;} 
                    case SDLK_KP_MULTIPLY:{cpu.touche[0xC]=1;break;} 
                    case SDLK_KP_MINUS:{cpu.touche[0xD]=1;break;} 
                    case SDLK_KP_PLUS:{cpu.touche[0xE]=1;break;} 
                    case SDLK_KP_ENTER:{cpu.touche[0xF]=1;break;} 
                    case SDLK_p:{pause();break;} 
                    case SDLK_r:{reset();break;} 
                    default:{ break;} 
                }                                      
                break;}         
            case SDL_KEYUP:{ 
                switch(event.key.keysym.sym) 
                { 
                    case SDLK_KP_0:{ cpu.touche[0x0]=0;break;} 
                    case SDLK_KP_7:{ cpu.touche[0x1]=0;break;} 
                    case SDLK_KP_8:{ cpu.touche[0x2]=0;break;} 
                    case SDLK_KP_9:{ cpu.touche[0x3]=0;break;} 
                    case SDLK_KP_4:{ cpu.touche[0x4]=0;break;} 
                    case SDLK_KP_5:{ cpu.touche[0x5]=0;break;} 
                    case SDLK_KP_6:{ cpu.touche[0x6]=0;break;} 
                    case SDLK_KP_1:{ cpu.touche[0x7]=0;break;} 
                    case SDLK_KP_2:{ cpu.touche[0x8]=0;break;} 
                    case SDLK_KP_3:{ cpu.touche[0x9]=0;break;} 
                    case SDLK_RIGHT:{ cpu.touche[0xA]=0;break;} 
                    case SDLK_KP_PERIOD:{cpu.touche[0xB]=0;break;} 
                    case SDLK_KP_MULTIPLY:{cpu.touche[0xC]=0;break;} 
                    case SDLK_KP_MINUS:{cpu.touche[0xD]=0;break;} 
                    case SDLK_KP_PLUS:{cpu.touche[0xE]=0;break;} 
                    case SDLK_KP_ENTER:{cpu.touche[0xF]=0;break;} 
                    default:{ break;} 
                } 
            break;}        
            default:{ break;} 
        }  
    }     
    return continuer; 
}

#endif