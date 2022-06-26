#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "dx.h"


int dx(char *filename,char *outfilename,int write)
{
    int i=0,inativos=0,numjogos=0,ordem[8]={1,2,3,4,5,6,7,8};
    char deck[43]={0},abc[3];
    double stats[10]={0};
    FILE *fp,*op;
    struct jogador arr_jogador[8];

    if((fp = fopen(filename,"r")) == NULL)
    {
		fprintf(stdout,"-1\n");
		return 0;
	}
	
    if(write == 1)
    {
        op = fopen(outfilename,"w");
    }else
    {
        op = stdout;
    }

    for(i=0;i<8;i++)
    {
        arr_jogador[i].i = 0;
        arr_jogador[i].v = 0;
        arr_jogador[i].folds = 0;
        arr_jogador[i].jogos = 0;
        arr_jogador[i].pontos = 0;

    }

    while(load_deck(fp,deck,21) == 0)
    {
        Check_jogadores(arr_jogador,deck,op,inativos);
        numjogos += Check_vencedores(arr_jogador,op,stats);
        inativos = update_flags(arr_jogador,inativos);

        for(i=0;i<31;i++)
        {
            fscanf(fp,"%2s", abc);
        }

    }

    ordenar_pontos(arr_jogador,ordem);

    for(i=0;i<10;i++)
    {
        stats[i] = stats[i] / numjogos ;
        fprintf(op,"%d %.2E\n", i+1, stats[i]);
    }
    fprintf(op,"\n");
    for(i=0;i<8;i++)

    {
        fprintf(op,"%d %.2f\n", ordem[i], arr_jogador[ordem[i]-1].pontos);
    }

	fclose(fp);
	fclose(op);
	return 0;
}


void ordenar_pontos(struct jogador arr_jogador[8],int ordem[8])
{
    int i=0,j=0,k=0;

    for(i=0;i<7;i++)
    {
        for(j=i;j<8;j++)
        {
            if(arr_jogador[i].pontos < arr_jogador[j].pontos)
            {
                k = ordem[i];
                ordem[i]=ordem[j];
                ordem[j]=k;
            }
        }
    }

}

void Check_jogadores(struct jogador arr_jogador[8],char *deck,FILE *op,int inativos)
{
    int i,k=0,x,j,valcartas[7] = {0};
    char naipes[8] = {0},cartas[15] = {0};

    for(i=0;i<8;i++)
    {

        if(arr_jogador[i].i == 0 )
        {
            for(x=0;x<4;x++)
            {
                cartas[x] = deck[k++];
            }
            for(x=4;x<14;x++)
            {
                cartas[x] = deck[28+x-(4*inativos)];

            }

            load_valcartas(valcartas,cartas,14);
            load_naipes(naipes,cartas,14);
            ordenar(cartas,naipes,valcartas,7);
            arr_jogador[i].pontos_mao = Check_Combinacoes(valcartas,naipes,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe);


            if ((arr_jogador[i].pontos_mao == 5 || arr_jogador[i].pontos_mao == 9) && (arr_jogador[i].melhormao[0] == 14 && arr_jogador[i].melhormao[1] == 5))
            {
                Swap_Straight5(arr_jogador[i].melhormao,arr_jogador[i].melhornaipe);
                load_cartas(arr_jogador[i].cartas,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe,5);
            }else
            {
                load_cartas(arr_jogador[i].cartas,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe,5);
            }


            if(arr_jogador[i].pontos_mao < i+1 && arr_jogador[i].folds < 4)
            {
                arr_jogador[i].folds++;
                arr_jogador[i].jogos = 0;
                arr_jogador[i].pontos_mao = 0;

            }else
            {
                arr_jogador[i].jogos++;
                arr_jogador[i].folds = 0;

                fprintf(op,"%d ",i+1);
                for(j=0;j<10;j+=2)
                {
                    fprintf(op,"%c%c " , arr_jogador[i].cartas[j],arr_jogador[i].cartas[j+1]);
                }
                fprintf(op,"%d\n", arr_jogador[i].pontos_mao);

            }
        }
    }
}

int Check_vencedores(struct jogador arr_jogador[8],FILE *op,double stats[10])
{
    int i,j,x,pontosmax=0,melhormao[5]={0};
    char melhornaipe[6]={0},cartas_vencedoras[11]={0};
    double nvencedores=0;

    for(i=0;i<8;i++)
    {
        if(arr_jogador[i].folds == 0 && arr_jogador[i].i == 0)
        {
            if (arr_jogador[i].pontos_mao > pontosmax )
            {
                for(j=0;j<i;j++)
                {
                    arr_jogador[j].v = 0;
                }
                pontosmax = arr_jogador[i].pontos_mao;
                strcpy(melhornaipe,arr_jogador[i].melhornaipe);
                strcpy(cartas_vencedoras,arr_jogador[i].cartas);
                arr_jogador[i].v = 1;


                for(j=0;j<5;j++)
                {
                    melhormao[j] = arr_jogador[i].melhormao[j];
                }
            }
            if(arr_jogador[i].pontos_mao == pontosmax)
            {
                x = Desempate(arr_jogador[i].melhormao,melhormao,pontosmax);

                if(x == 1)
                {
                    for(j=0;j<i;j++)
                    {
                        arr_jogador[j].v = 0;
                    }
                    arr_jogador[j].v = 1;

                    pontosmax = arr_jogador[i].pontos_mao;
                    strcpy(melhornaipe,arr_jogador[i].melhornaipe);
                    strcpy(cartas_vencedoras,arr_jogador[i].cartas);
                    for(j=0;j<5;j++)
                    {
                        melhormao[j] = arr_jogador[i].melhormao[j];
                    }
                }

                if(x == 0)
                {
                    arr_jogador[i].v = 1;

                }
            }
        }
    }

    for(i=0;i<8;i++)
    {
        if(arr_jogador[i].v == 1)
        {
            nvencedores++;
        }
    }

    if(nvencedores != 0)
    {
        fprintf(op,"W ");
        for(i=0;i<10;i+=2)
        {
            fprintf(op,"%c%c " , cartas_vencedoras[i],cartas_vencedoras[i+1]);
        }
        fprintf(op,"%d", pontosmax);

        for(i=0;i<8;i++)
        {
            if(arr_jogador[i].v == 1)
            {
                fprintf(op," %d" , i+1);
                arr_jogador[i].v = 0;

                arr_jogador[i].pontos +=  1 / nvencedores;

            }
        }

        stats[pontosmax-1]++;
        fprintf(op,"\n\n");

        return 1;
    }

    return 0;
}

int update_flags(struct jogador arr_jogador[8],int inativos)
{
    int i;

    for(i=0;i<8;i++)
    {

        arr_jogador[i].pontos_mao = 0;

        if(arr_jogador[i].i == 1)
        {
            arr_jogador[i].i = 0;
            arr_jogador[i].jogos = 0;
            inativos--;
        }

        if(arr_jogador[i].jogos == 2)
        {
            arr_jogador[i].i = 1;
            arr_jogador[i].jogos = 0;
            inativos++;
        }
    }
    return inativos;
}

