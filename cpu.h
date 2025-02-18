#ifndef CPU_H 
#define CPU_H 
#include <SDL2/SDL.h> 

#define TAILLEMEMOIRE 4096 
#define ADRESSEDEBUT 512 
#define NBROPCODE 35 


typedef struct 
{ 
    Uint8 memoire[TAILLEMEMOIRE]; 
    Uint8 V[16]; //le registre 
    Uint16 I; //stocke une adresse mémoire ou dessinateur 
    Uint16 saut[16]; //pour gérer les sauts dans « mémoire », 16 au maximum 
    Uint8 nbrsaut; //stocke le nombre de sauts effectués pour ne pas dépasser 16 
    Uint8 compteurJeu; //compteur pour la synchronisation 
    Uint8 compteurSon; //compteur pour le son 
    Uint16 pc; //pour parcourir le tableau « mémoire » 
} CPU; 

typedef struct 
{ 
    Uint16 masque [NBROPCODE];   //la Chip 8 peut effectuer 35 opérations, chaque opération possédant son masque 
    Uint16 id[NBROPCODE];   //idem, chaque opération possède son propre identifiant 

}JUMP; 

extern CPU cpu;  //déclaration de notre CPU 
extern JUMP jp; 

void initialiserCpu() ; 
void decompter() ; 
Uint16 recupererOpcode() ;
void initialiserJump () ; 
Uint8 recupererAction(Uint16) ; 
void interpreterOpcode(Uint16) ; 
void dessinerEcran(Uint8 b1,Uint8 b2, Uint8 b3) ;
void chargerFont() ;

#endif