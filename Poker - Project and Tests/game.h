#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void game(char*);

typedef struct player{

        double cash;          //guarda os pontos totais do jogador
        int v;                //flag que indica que o jogador e vencedor esta ronda
        int f;
        int pontos_mao;       //pontos da mao do jogador
        char melhorcartas[11];
        int melhormao[5];     //vetor com os valores das cartas da melhor mao do jogador
        char melhornaipe[6];  //string com os naipes das cartas da melhor mao do jogador
        char cartas[15];
        int valcartas[7];
        char naipes[8];


}player;

#endif // 2PLAYER_H_INCLUDED
