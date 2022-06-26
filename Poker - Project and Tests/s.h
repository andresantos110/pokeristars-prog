#ifndef S_H_INCLUDED
#define S_H_INCLUDED
#include <stdio.h>

//este ficheiro contem a declaração das funções do modo -s1 e a definiçao da estrutura utilizada para guardar uma carta

int s1(char*,char*,int);
void s0(char*,int);
typedef struct _carta {

    char rank;
    char naipe;
    struct _carta *next;

} carta;
carta *load_list(carta*,char*);
carta *shuffle1(carta *ListHead);
carta *shuffle2(carta *);
carta *shuffle3(carta *);
carta *reverse_list(carta*);
void print_list(carta*,FILE*);
void free_list(carta*);





#endif // S_H_INCLUDED
