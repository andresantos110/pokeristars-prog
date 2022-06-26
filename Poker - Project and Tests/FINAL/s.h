#ifndef S_H_INCLUDED
#define S_H_INCLUDED
#include <stdio.h>


int s1(char*,char*,int);
typedef struct _carta {

    char rank;
    char naipe;
    struct _carta *next;

} carta;
carta *load_list(carta*,char*);
void print_list(carta*,FILE*);
void free_list(carta*);
carta *alternar(carta *ListHead);
carta *reverse_list(carta*);
carta *alternar2(carta *);
carta *s3(carta *);





#endif // S_H_INCLUDED
