#ifndef DX_H_INCLUDED
#define DX_H_INCLUDED
#include <stdio.h>




int dx(char*,char*,int);
struct jogador
    {
        double pontos;
        int i;
        int v;
        int folds;
        int jogos;
        int melhormao[5];
        int pontos_mao;
        char melhornaipe[6];
        char cartas[11];
    };

void Check_jogadores(struct jogador [8] ,char*,FILE*,int);
int Check_vencedores(struct jogador [8],FILE*,double[10]);
int update_flags(struct jogador [8],int);
void ordenar_pontos(struct jogador [8],int[8]);




#endif // DX_H_INCLUDED
