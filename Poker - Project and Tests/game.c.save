#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "game.h"

void game(char *filename)
{
    int i,j;
    char deck[19],abc[3];
    FILE *fp;
    player player[2];

    if ((fp = fopen(filename,"r")) == NULL )
    {
        fprintf(stdout,"-1");
        return;
    }
    for(i=0;i<2;i++)
    {
        player[i].cash = 1000;
        player[i].f=0;
        player[i].v=0;
        player[i].pontos_mao=0;
    }

    while(load_deck(fp,deck,9) == 0)
    {
        for(i=0;i<2;i++)
        {
            for(j=0;j<4;j++)
            {
                player[i].cartas[j] = deck[4*i+j];

            }
        }
        fprintf(stdout,"Hand: %c%c  %c%c" , player[0].cartas[0],player[0].cartas[1],player[0].cartas[2],player[0].cartas[3]);

        if(player[0].cartas[0] == player[0].cartas[2])
        {
            fprintf(stdout," -- Pair\n");
        }else
        {
            fprintf(stdout," -- High card\n");
        }








        for(i=0;i<43;i++) fscanf(fp,"%s",abc);
    }


    fclose(fp);
    return;
}
