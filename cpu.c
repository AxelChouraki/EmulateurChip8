#include "cpu.h" 

CPU cpu;

void initialiserCpu() 
{ 
  //On initialise le tout 

    Uint16 i=0; 

    for(i=0;i<TAILLEMEMOIRE;i++) //faisable avec memset, mais je n'aime pas cette fonction ^_^ 
    { 
        cpu.memoire[i]=0; 
    } 

     for(i=0;i<16;i++) 
     { 
        cpu.V[i]=0; 
        cpu.saut[i]=0; 
     } 

    cpu.pc=ADRESSEDEBUT; 
    cpu.nbrsaut=0; 
    cpu.compteurJeu=0; 
    cpu.compteurSon=0; 
    cpu.I=0; 

} 

void decompter() 
{ 
    if(cpu.compteurJeu>0) 
    cpu.compteurJeu--; 

    if(cpu.compteurSon>0) 
    cpu.compteurSon--; 
}