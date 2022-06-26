#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "di.h"




int di(char *filename,char *outfilename, int mode, int write)
{

    char *deck;
    int vitorias[3]={0};
    double stats[11]={0}, numtestes=0;
    FILE *fp, *op;

    if((fp = fopen(filename,"r")) == NULL )
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

    switch (mode)
    {
        case 1:

            deck = (char *) calloc(101, sizeof(char));

            while(load_deck(fp,deck,50)==0)
            {
                numtestes += di_1(deck,stats,fp,op,mode);
            }

            estatisticas_1(stats,numtestes,op);

            fclose(fp);
            if(write == 1)
            {
                fclose(op);
            }
            free(deck);
            return 0;

        case 2:

            deck = (char *) calloc(99, sizeof(char));

            while (load_deck(fp,deck,49) == 0)
            {
                numtestes += di_1(deck,stats,fp,op,mode);
            }
            estatisticas_1(stats,numtestes,op);

            fclose(fp);
            if(write==1)
            {
                fclose(op);
            }
            free(deck);
            return 0;

        case 3:

            deck = (char *) calloc(91, sizeof(char));

            while(load_deck(fp,deck,45) == 0)
            {
                numtestes += di_2(deck,stats,fp,op,mode,vitorias);
            }
            estatisticas_2(stats,vitorias,op,numtestes);

            fclose(fp);
            if(write == 1)
            {
               fclose(op);
            }
            free(deck);
            return 0;

        case 4:

            deck = (char *) calloc(101, sizeof(char));

            while(load_deck(fp,deck,50) == 0)
            {
                numtestes += di_2(deck,stats,fp,op,mode,vitorias);
            }
            estatisticas_2(stats,vitorias,op,numtestes);

            fclose(fp);
            if(write == 1)
            {
                fclose(op);
            }

            free(deck);
            return 0;
    }
    return 0;
}

int di_1(char *deck,double stats[11],FILE *fp,FILE *op,int mode)
{
    int i,j,k,a=0, *valcartas,*melhormao,pontos;
    char *cartas,*naipes,*melhornaipe, abc[3];

    switch(mode)
    {
    case 1:

        cartas    = (char *) calloc(11 , sizeof(char));
        naipes    = (char *) calloc(6  , sizeof(char));
        valcartas = (int *)  malloc(5  * sizeof(int));

        for(i=0;i<100;i+=10)
        {
            for(j=0;j<10;j++)
            {

                cartas[j] = deck[i+j];
                //deck[i+j] = \'0';
            }

            if(check_string(cartas,10,5) == 0 )
            {
                load_valcartas(valcartas,cartas,10);
                load_naipes(naipes,cartas,10);
                ordenar(cartas,naipes,valcartas,5);
                pontos = Check_Hand(valcartas,naipes);

                fprintf(op,"%d\n" , pontos);

            }else
            {
                pontos = 0;
                fprintf(op,"-1\n");
            }

            stats[pontos]++;
            a++;

        }
        for(i=0;i<2;i++)
        {
            fscanf(fp,"%s", abc);
        }

        fprintf(op,"\n" );

        free(naipes);
        free(valcartas);
        free(cartas);
        return a;

    case 2:

        cartas      = (char *) calloc(15, sizeof(char));
        naipes      = (char *) calloc(8 , sizeof(char));
        melhornaipe = (char *) calloc(6 , sizeof(char));
        melhormao   = (int *) malloc(5 * sizeof(int));
        valcartas   = (int *) malloc(7 * sizeof(int));

        for(i=0;i<98;i+=14)
        {
            for(j=0;j<14;j++)
            {
                cartas[j] = deck[i+j];
                //deck[i+j] = \'0';
            }

            if(check_string(cartas,14,7) == 0 )
            {
                load_valcartas(valcartas,cartas,14);
                load_naipes(naipes,cartas,14);
                ordenar(cartas,naipes,valcartas,7);
                pontos = Check_Combinacoes(valcartas,naipes,melhormao,melhornaipe);
                load_cartas(cartas,melhormao,melhornaipe,5);

                if ((pontos == 5 || pontos == 9) && (melhormao[0] == 14 && melhormao[1] == 5))
                {
                    Swap_Straight5(melhormao,melhornaipe);
                    load_cartas(cartas,melhormao,melhornaipe,5);
                }

                for(k=0;k<10;k+=2)
                {
                    fprintf(op,"%c%c " , cartas[k],cartas[k+1]);
                }
                fprintf(op,"%d\n" , pontos);
            }else
            {
                pontos = 0;
                fprintf(op,"-1\n");
            }

            stats[pontos]++;
            a++;

        }
        for(i=0;i<3;i++)
        {
            fscanf(fp,"%s",abc);
        }

        fprintf(op,"\n" );

        free(naipes);
        free(valcartas);
        free(cartas);
        free(melhormao);
        free(melhornaipe);

        return a;


    }
    return 0;
}

void estatisticas_1(double stats[11], int k, FILE *op)
{
    int i;
    for(i=0;i<11;i++)
    {

        stats[i] = stats[i] / k;

        if(i==0)
        {
            fprintf(op,"-1 %.2E\n" , stats[i]);
        }else
        {
            fprintf(op,"%d %.2E\n" ,i, stats[i]);

        }
    }
    return;
}

int di_2(char *deck,double stats[11],FILE *fp,FILE *op,int mode,int vitorias[3])
{
    int i,j,k,a=0, *valcartas,*valhand,*melhormao,*valcartas1,*valhand1,*melhormao1,pontos,pontos1,vencedor=0;
    char *cartas,*naipes,*suithand,*melhornaipe,*cartas1,*naipes1,*suithand1,*melhornaipe1, abc[3];

    switch(mode)
    {
    case 3:

        cartas       = (char *) calloc(19 ,sizeof(char));
        naipes       = (char *) calloc(10 ,sizeof(char));
        melhornaipe  = (char *) calloc(6  ,sizeof(char));
        suithand     = (char *) calloc(6  ,sizeof(char));

        valhand      = (int *) malloc(5 * sizeof(int));
        melhormao    = (int *) malloc(5 * sizeof(int));
        valcartas    = (int *) malloc(9 * sizeof(int));

        cartas1      = (char *) calloc(19 ,sizeof(char));
        naipes1      = (char *) calloc(10 ,sizeof(char));
        melhornaipe1 = (char *) calloc(6  ,sizeof(char));
        suithand1    = (char *) calloc(6  ,sizeof(char));

        valhand1     = (int *) malloc(5 * sizeof(int));
        melhormao1   = (int *) malloc(5 * sizeof(int));
        valcartas1   = (int *) malloc(9 * sizeof(int));

        for(i=0;i<90;i+=18)
        {
            for(j=0;j<18;j++)
            {
                if(j<4)
                {
                    cartas[j]=deck[i+j];
                    deck[i+j]= '\0';
                }
                if(j>3 && j<8)
                {
                    cartas1[j-4] = deck[i+j];
                    //deck[i+j] = \'0';
                }
                if(j>=8)
                {
                    cartas[j-4] = deck[i+j];
                    cartas1[j-4] = deck[i+j];
                    //deck[i+j] = \'0';
                }
            }

            if(check_string(cartas,14,7) == 0 && check_string(cartas1,14,7) == 0 )
            {
                load_valcartas(valcartas,cartas,14);
                load_naipes(naipes,cartas,14);
                ordenar(cartas,naipes,valcartas,7);
                pontos = Check_Combinacoes(valcartas,naipes,melhormao,melhornaipe);
                load_cartas(cartas,melhormao,melhornaipe,5);
                if ((pontos == 5 || pontos == 9) && (melhormao[0] == 14 && melhormao[1] == 5))
                {
                    Swap_Straight5(melhormao,melhornaipe);
                    load_cartas(cartas,melhormao,melhornaipe,5);
                }



                load_valcartas(valcartas1,cartas1,14);
                load_naipes(naipes1,cartas1,14);
                ordenar(cartas1,naipes1,valcartas1,7);
                pontos1 = Check_Combinacoes(valcartas1,naipes1,melhormao1,melhornaipe1);
                load_cartas(cartas1,melhormao1,melhornaipe1,5);
                if ((pontos1 == 5 || pontos1 == 9) && (melhormao1[0] == 14 && melhormao1[1] == 5))
                {
                    Swap_Straight5(melhormao1,melhornaipe1);
                    load_cartas(cartas1,melhormao1,melhornaipe1,5);
                }

                if(pontos > pontos1)
                {
                    vencedor=1;
                }else
                {
                    if(pontos < pontos1)
                    {
                        vencedor=2;
                    }else
                    {
                        vencedor=Desempate(melhormao,melhormao1,pontos);
                    }
                }

                for(k=0;k<10;k+=2)
                {
                    fprintf(op,"%c%c " , cartas[k],cartas[k+1]);
                }
                fprintf(op,"%d " , pontos);
                for(k=0;k<10;k+=2)
                {
                    fprintf(op,"%c%c " , cartas1[k],cartas1[k+1]);
                }
                fprintf(op,"%d %d\n" , pontos1,vencedor);


            }else
            {
                pontos = 0;
                pontos1= 0;
                fprintf(op,"-1\n");
            }
            vitorias[vencedor]++;
            stats[pontos]++;
            stats[pontos1]++;
            a++;

        }

        for(i=0;i<7;i++)
        {
            fscanf(fp,"%s",abc);
        }
        fprintf(op,"\n" );


        free(naipes);
        free(naipes1);
        free(valcartas);
        free(valcartas1);
        free(cartas);
        free(cartas1);
        free(melhormao);
        free(melhormao1);
        free(melhornaipe);
        free(melhornaipe1);
        free(suithand);
        free(suithand1);
        free(valhand);
        free(valhand1);
        return a;




    case 4:

        cartas       = (char *) calloc(11, sizeof(char));
        suithand     = (char *) calloc(6 , sizeof(char));
        cartas1      = (char *) calloc(11, sizeof(char));
        suithand1    = (char *) calloc(6 , sizeof(char));

        valhand      = (int *) malloc(5 * sizeof(int));
        valhand1     = (int *) malloc(5 * sizeof(int));

        for(i=0;i<100;i+=20)
        {
            for(j=0;j<20;j++)
            {
                if(j<10)
                {
                    cartas[j]=deck[i+j];
                    //deck[i+j]='\0';
                }
                if(j>= 10 && j<20)
                {
                    cartas1[j-10] = deck[i+j];
                    //deck[i+j] = \'0';
                }

            }


            if(check_string(cartas,10,5) == 0 && check_string(cartas1,10,5) == 0)
            {

                load_valcartas(valhand,cartas,10);
                load_naipes(suithand,cartas,10);
                ordenar(cartas,suithand,valhand,5);
                pontos = Check_Hand(valhand,suithand);



                load_valcartas(valhand1,cartas1,10);
                load_naipes(suithand1,cartas1,10);
                ordenar(cartas1,suithand1,valhand1,5);
                pontos1 = Check_Hand(valhand1,suithand1);

                if(pontos > pontos1)
                {
                    vencedor=1;

                }else
                {
                    if(pontos < pontos1)
                    {
                        vencedor=2;

                    }else
                    {
                        vencedor=Desempate(valhand,valhand1,pontos);

                    }
                }
                fprintf(op,"%d\n",vencedor);

            }else
            {
                pontos = 0;
                pontos1= 0;
                vencedor = 0;
                fprintf(op,"-1\n");
            }

            vitorias[vencedor]++;
            stats[pontos]++;
            stats[pontos1]++;
            a++;
        }
        for(i=0;i<2;i++)
        {
            fscanf(fp,"%s",abc);
        }
        fprintf(op,"\n" );


        free(cartas1);
        free(cartas);
        free(suithand);
        free(valhand);
        free(suithand1);
        free(valhand1);
        return a;


        }
    return 0;
}

void estatisticas_2(double stats[11],int vitorias[3],FILE *op,int numtestes)
{
    int i;

    for(i=0;i<11;i++)
    {

        stats[i] = stats[i] / (2 * numtestes);

        if(i==0)
        {
            fprintf(op,"-1 %.2E\n" , stats[i]);
        }else
        {
            fprintf(op,"%d %.2E\n" ,i, stats[i]);
        }
    }
        fprintf(op,"\n");


        for(i=0;i<3;i++)
        {
            fprintf(op,"%d %d\n", i, vitorias[i]);
        }

}









