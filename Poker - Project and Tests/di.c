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

    if((fp = fopen(filename,"r")) == NULL )     // caso o ficheiro input introduzido nao exista, o programa nao corre
    {
		fprintf(stdout,"-1\n");
		return 0;
	}
    if(write == 1)
    {
        op = fopen(outfilename,"w");                // caso o programa esteja em mode escrita para ficheiro, op aponta para o ficheiro indicado, senao, aponta para stdout
    }else
    {
        op = stdout;
    }

    switch (mode)      //a funçao funciona de forma diferente dependendo do modo escolhido
    {
        case 1:

            deck = (char *) calloc(101, sizeof(char));   // no modo d1, vao ser lidas 50 cartas de cada deck, logo aloca-se um bloco de 101 carateres para guardar uma string com 50 cartas

            while(load_deck(fp,deck,50)==0)   // a função load deck apenas retorna 1 quando nao consegue ler o numero de cartas indicado, o que significa que chegou ao fim do ficheiro e para o loop
            {
                numtestes += di_1(deck,stats,fp,op,mode); // a função di_1 trata verificação das cartas para apenas um jogador, e retorna o numero de testes realizados por cada deck, neste caso 10
            }

            estatisticas_1(stats,numtestes,op); // a funçao estaticas_1 trata da saida de dados para apenas 1 jogador

            fclose(fp);
            if(write)
            {
                fclose(op);
            }
            free(deck);
            return 0;

        case 2:

            deck = (char *) calloc(99, sizeof(char)); //no modo d2, sao lidas 49 cartas por deck, por isso é alocada uma string com 99 carateres

            while (load_deck(fp,deck,49) == 0) // a função load deck apenas retorna 1 quando nao consegue ler o numero de cartas indicado, o que significa que chegou ao fim do ficheiro e para o loop
            {
                numtestes += di_1(deck,stats,fp,op,mode); // a função di_1 trata verificação das cartas para apenas um jogador, e retorna o numero de testes realizados por cada deck, neste caso 7
            }
            estatisticas_1(stats,numtestes,op); // a funçao estaticas_1 trata da saida de dados para apenas 1 jogador

            fclose(fp);
            if(write)
            {
                fclose(op);
            }
            free(deck);
            return 0;

        case 3:

            deck = (char *) calloc(91, sizeof(char)); // no modo d3 sao lidas 45 cartas por deck, por isso é alocada uma string com 91 carateres

            while(load_deck(fp,deck,45) == 0)
            {
                numtestes += di_2(deck,stats,fp,op,mode,vitorias);  // a função di_2 trata verificação das cartas para dois jogadores, e retorna o numero de testes realizados por cada deck, neste caso 5
            }
            estatisticas_2(stats,vitorias,op,numtestes); // a funçao estatisticas_2 trata da saida de dados para 2 jogadores

            fclose(fp);
            if(write)
            {
               fclose(op);
            }
            free(deck);
            return 0;

        case 4:

            deck = (char *) calloc(101, sizeof(char)); // no modo d4 sao lidas 50 cartas por deck, por isso é alocada uma string com 101 carateres

            while(load_deck(fp,deck,50) == 0)
            {
                numtestes += di_2(deck,stats,fp,op,mode,vitorias); // a função di_2 trata verificação das cartas para dois jogadores, e retorna o numero de testes realizados por cada deck, neste caso 5
            }
            estatisticas_2(stats,vitorias,op,numtestes); // a funçao estatisticas_2 trata da saida de dados para 2 jogadores

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
        {                                               //o modo d1 funciona da mesma maneira que o modo c de 5 cartas, mas dentro de um loop.
            for(j=0;j<10;j++)
            {

                cartas[j] = deck[i+j];
                                                        //em cada deck existem 10 maos de 5 cartas, este loop lê cada uma dessas maos, verifica a sua legalidade e calcula os seus pontos
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
                pontos = 0;             //quando a mão é ilegal, a sua pontuação é zero de modo a contar o numero de maos ilegais neste deck
                fprintf(op,"-1\n");
            }

            stats[pontos]++;            //atualiza o vetor que conta as ocorrencias de cada mao
            a++;                        //esta variavel conta o numero de testes realizados neste loop

        }
        for(i=0;i<2;i++)                //este loop  le as duas cartas restantes no deck atual de modo a passar para o proximo deck
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
            for(j=0;j<14;j++)                       //o modo d2 funciona da mesma maneira que o modo c de 7 cartas, mas dentro de um loop.
            {
                cartas[j] = deck[i+j];              //em cada deck existem 7 conjuntos de 7 cartas, este loop lê cada um desses conuntos, verifica a sua legalidade e calcula os pontos da melhor mao possivel formar com esse conjunto

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
                pontos = 0;             //quando o conjunto é ilegal, a sua pontuação é zero de mode a contara o numeo de conjuntos ilegais no deck
                fprintf(op,"-1\n");
            }

            stats[pontos]++;            //atualiza o vetor que conta as ocorrencias de cada mao
            a++;                        //esta variavel conta o numero de testes realizados neste loop

        }
        for(i=0;i<3;i++)                     //este loop  lê as três cartas restantes no deck atual de modo a passar para o proximo deck
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

void estatisticas_1(double stats[11], int numtestes, FILE *op)
{
    int i;
    for(i=0;i<11;i++)
    {

        stats[i] = stats[i] / numtestes;          //divide-se o numero de ocorrrencias de cada combinação pelo numero de testes para obter a percentagem de cada mao

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
    char *cartas,*naipes,*suithand,*melhornaipe,*cartas1,*naipes1,*suithand1,*melhornaipe1,*cartas_aux,abc[3];

    switch(mode)
    {
    case 3:

        cartas       = (char *) calloc(19 ,sizeof(char));
        naipes       = (char *) calloc(10 ,sizeof(char));
        melhornaipe  = (char *) calloc(6  ,sizeof(char));

        melhormao    = (int *) malloc(5 * sizeof(int));
        valcartas    = (int *) malloc(9 * sizeof(int));

        cartas1      = (char *) calloc(19 ,sizeof(char));
        naipes1      = (char *) calloc(10 ,sizeof(char));
        melhornaipe1 = (char *) calloc(6  ,sizeof(char));

        melhormao1   = (int *) malloc(5 * sizeof(int));
        valcartas1   = (int *) malloc(9 * sizeof(int));

        cartas_aux = (char*) calloc(19, sizeof(char));



        for(i=0;i<90;i+=18)
        {
            for(j=0;j<18;j++)               //o modo d3 funciona da mesma maneira que o modo c de 9 cartas, mas dentro de um loop.
            {
                if(j<4)                     //em cada deck existem 5 conjuntos de 9 cartas, este loop lê cada um desses conuntos, verifica a sua legalidade, calcula os pontos de cada jogador e determina o vencedor
                {
                    cartas[j]=deck[i+j];

                }
                if(j>3 && j<8)
                {
                    cartas1[j-4] = deck[i+j];

                }
                if(j>=8)
                {
                    cartas[j-4] = deck[i+j];
                    cartas1[j-4] = deck[i+j];

                }
                cartas_aux[j]=deck[i+j];        //a string cartas_aux e utilizada para verificar a legalidade do conjunto
            }

            if(check_string(cartas_aux,18,9) == 0)
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
                vencedor = 0;           //um conunto ilegal conta como um impate, logo o vencedor é zero
                pontos = 0;
                pontos1= 0;
                fprintf(op,"-1\n");
            }
            vitorias[vencedor]++;       //estes vetores contam o numero de vitorias de cada jogador e o numero de ocorrencias de cada combinação
            stats[pontos]++;
            stats[pontos1]++;
            a++;                        //esta variavel conta o numero de testes realizados neste loop

        }

        for(i=0;i<7;i++)                    //este loop  lê as sete cartas restantes no deck atual de modo a passar para o proximo deck
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
        free(cartas_aux);
        return a;




    case 4:

        cartas       = (char *) calloc(11, sizeof(char));
        cartas1      = (char *) calloc(11, sizeof(char));

        suithand     = (char *) calloc(6 , sizeof(char));
        suithand1    = (char *) calloc(6 , sizeof(char));

        valhand      = (int *) malloc(5 * sizeof(int));
        valhand1     = (int *) malloc(5 * sizeof(int));

        for(i=0;i<100;i+=20)                //o modo d4 funciona da mesma maneira que o modo c de 10 cartas, mas dentro de um loop.
        {
            for(j=0;j<20;j++)               //em cada deck existem 5 conjuntos de 10 cartas, este loop lê cada um desses conuntos, verifica a sua legalidade, calcula os pontos de cada jogador e determina o vencedor
            {
                if(j<10)
                {
                    cartas[j]=deck[i+j];

                }
                if(j>= 10 && j<20)
                {
                    cartas1[j-10] = deck[i+j];

                }

            }


            if(check_string(cartas,10,5) == 0 && check_string(cartas1,10,5) == 0)           //verifica-se a legalidade de cada mao individualmente
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

            vitorias[vencedor]++;           //estes vetores contam o numero de vitorias de cada jogador e o numero de ocorrencias de cada combinação
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

        stats[i] = stats[i] / (2 * numtestes);          //quando temos dois jogadores, cada teste tem produz dois resultados, logo para obter a percentagem de cada combinação temos que dividir pelo dobro dos testes

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









