#ifndef DX_H_INCLUDED
#define DX_H_INCLUDED
#include <stdio.h>


//este ficheiro contem a declaração das funções do modo -dx e da estrutura jogador

int dx(char*,char*,int);
struct jogador
    {
        double pontos;        //guarda os pontos totais do jogador
        int i;                //flag que indica que o jogador está inativo
        int v;                //flag que indica que o jogador e vencedor esta ronda
        int folds;            //quantas vezes deu fold
        int jogos;            //quantas vezes foi a jogo
        int pontos_mao;       //pontos da mao do jogador
        int melhormao[5];     //vetor com os valores das cartas da melhor mao do jogador
        char melhornaipe[6];  //string com os naipes das cartas da melhor mao do jogador
        char cartas[11];      //string com as cartas da melhor mao do jogador
    };

void Check_jogadores(struct jogador [8] ,char*,FILE*,int);
int Check_vencedores(struct jogador [8],FILE*,double[10]);
int update_flags(struct jogador [8],int);
void ordenar_pontos(struct jogador [8],int[8]);




#endif // DX_H_INCLUDED
