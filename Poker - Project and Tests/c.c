#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c.h"
#include "global.h"



int c(int argc,char *argv[])
{
    char *cartas,*naipes,*cartas1,*cartas2,*naipes1;
    char melhornaipe[6]={0},melhornaipe1[6];

    int *valcartas,*valcartas1,melhormao[5],melhormao1[5];
    int numcartas=0,pontos=0,pontos1=0,pontos2=0,vencedor=0;
    int i=0,k=0;

    numcartas = (argc - 2);
    k=2*numcartas;

    cartas = (char *) calloc(k+1 ,sizeof(char));
    if (load_string_cartas(argc,cartas,argv) != 0)         //esta funçao gera uma string com todas as cartas, caso exista uma carta ilegal, retorna -1
    {
        fprintf(stdout,"-1\n");
        return 0;
    }


    switch(numcartas)
    {
        case 5:

            naipes    = (char *) calloc(6  , sizeof(char));
            valcartas = (int *)  malloc(5  * sizeof(int));


            load_valcartas(valcartas,cartas,10);                //esta funçao gera um vetor com os valores das cartas
            load_naipes(naipes,cartas,10);                      //esta funçao gera uma string com os naipes das cartas
            ordenar(cartas, naipes,valcartas,5);                //esta funçao ordena os vetores por ordem decrescente e alfabetica
            pontos = Check_Hand(valcartas,naipes);              //esta funçao calcula o valor das maos

            fprintf(stdout,"%d\n" , pontos);

            free(cartas);
            free(naipes);
            free(valcartas);
            return 0;


        case 7:


            naipes      = (char *) calloc(8 , sizeof(char));
            valcartas   = (int *) malloc(7 * sizeof(int));

            load_valcartas(valcartas,cartas,14);
            load_naipes(naipes,cartas,14);
            ordenar(cartas, naipes, valcartas,7);
            pontos = Check_Combinacoes(valcartas,naipes,melhormao,melhornaipe);   //esta funçao calcula os pontos de todas as maos possiveis formar com as 7 cartas, retorna o valor mais alto e guarda a melhor mao
            load_cartas(cartas,melhormao,melhornaipe,5);                                          //esta funçao gera uma string com as 5 melhor cartas

                                                                                                   //quando a melhor mao é uma sequencia do tipo A 5 4 3 2, tem que se mudar a ordem das cartas para 5 4 3 2 A
            if ((pontos == 5 || pontos == 9) && (melhormao[0] == 14 && melhormao[1] == 5))
            {
                Swap_Straight5(melhormao,melhornaipe);
                load_cartas(cartas,melhormao,melhornaipe,5);
            }

            for(i=0;i<10;i++)                                    //depois de descobrir a melhor mao possivel, damos print as cartas e aos pontos dessa mao
            {
                fprintf(stdout,"%c" , cartas[i]);
                i++;
                fprintf(stdout,"%c " , cartas[i]);
            }

            fprintf(stdout,"%d\n" , pontos);

            free(naipes);
            free(valcartas);
            free(cartas);
            return 0;


        case 9:


            naipes       = (char *) calloc(8 ,sizeof(char));
            valcartas    = (int *)  malloc(7 * sizeof(int));
            cartas1      = (char *) calloc(15 ,sizeof(char));

            naipes1      = (char *) calloc(8 ,sizeof(char));
            valcartas1   = (int *)  malloc(7 * sizeof(int));
            cartas2      = (char *) calloc(15 ,sizeof(char));


            for(i=0;i<18;i++)
            {
                if(i<4)
                {
                    cartas1[i]=cartas[i];
                }
                if(i>3 && i<8)
                {
                    i++;
                }
                if(i>=8)
                {
                    cartas1[i-4] = cartas[i];

                }
            }

            load_valcartas(valcartas,cartas1,14);
            load_naipes(naipes,cartas1,14);
            ordenar(cartas1,naipes,valcartas,7);
            pontos1 = Check_Combinacoes(valcartas,naipes,melhormao,melhornaipe);
            load_cartas(cartas1,melhormao,melhornaipe,5);

            if ((pontos1 == 5 || pontos1 == 9) && (melhormao[0] == 14 && melhormao[1] == 5))       //quando a melhor mao é uma sequencia do tipo A 5 4 3 2, tem que se mudar a ordem das cartas para 5 4 3 2 A
            {
                Swap_Straight5(melhormao,melhornaipe);
                load_cartas(cartas1,melhormao,melhornaipe,5);
            }



            for(i=0;i<10;i++)                      //print à melhor mao do primeiro jogador e dos pontos dessa mao
            {
                fprintf(stdout,"%c" , cartas1[i]);
                i++;
                fprintf(stdout,"%c " , cartas1[i]);
            }
            fprintf(stdout,"%d " , pontos1);



            for(i=4;i<18;i++)
            {
                cartas1[i-4] = cartas[i];
            }

            load_valcartas(valcartas,cartas1,14);                       //carregamos a mao do segundo jogador
            load_naipes(naipes,cartas1,14);
            ordenar(cartas1,naipes,valcartas,7);
            pontos2 = Check_Combinacoes(valcartas,naipes,melhormao1,melhornaipe1);
            load_cartas(cartas1,melhormao1,melhornaipe1,5);

            if ((pontos2 == 5 || pontos2 == 9) && (melhormao1[0] == 14 && melhormao1[1] == 5))      //quando a melhor mao é uma sequencia do tipo A 5 4 3 2, tem que se mudar a ordem das cartas para 5 4 3 2 A
            {
                Swap_Straight5(melhormao1,melhornaipe1);
                load_cartas(cartas1,melhormao1,melhornaipe1,5);
            }


            for(i=0;i<10;i++)                                   //print à melhor mao do segundo jogador e dos pontos dessa mao
            {
                fprintf(stdout,"%c" , cartas1[i]);
                i++;
                fprintf(stdout,"%c " , cartas1[i]);
            }
            fprintf(stdout,"%d " , pontos2);


            if (pontos1 == pontos2)                                 //caso ambas as maos tenham os mesmos pontos, temos que desempatalas
            {
                pontos = pontos1;
                vencedor = Desempate(melhormao,melhormao1,pontos);

            }else
            {
                if (pontos1>pontos2)
                {
                    vencedor = 1;
                }else
                {
                    vencedor = 2;
                }

            }
            fprintf(stdout,"%d\n" , vencedor);


            free(naipes1);
            free(valcartas1);
            free(cartas2);
            free(cartas1);
            free(naipes);
            free(valcartas);
            return 0;

        case 10:

            naipes       = (char *) calloc(6 ,sizeof(char));
            valcartas    = (int *) malloc(5 *  sizeof(int));
            cartas1      = (char *) calloc(11 ,sizeof(char));
            naipes1      = (char *) calloc(6 ,sizeof(char));
            valcartas1   = (int *) malloc(5 *  sizeof(int));
            cartas2      = (char *) calloc(11 ,sizeof(char));

            for(i=0;i<10;i++)
            {
                cartas1[i] = cartas[i];
                cartas2[i] = cartas[i+10];
            }

            load_valcartas(valcartas,cartas1,10);
            load_naipes(naipes,cartas1,10);
            ordenar(cartas1,naipes,valcartas,5);
            pontos1 = Check_Hand(valcartas,naipes);

            load_valcartas(valcartas1,cartas2,10);
            load_naipes(naipes1,cartas2,10);
            ordenar(cartas2,naipes1,valcartas1,5);
            pontos2 = Check_Hand(valcartas1,naipes1);


            if (pontos1 == pontos2)                     //caso ambos os jogadores tenham os mesmos pontos, temos que desempatar-los
            {
                pontos = pontos1;
                vencedor = Desempate(valcartas,valcartas1,pontos);

            }else
            {
                if (pontos1>pontos2)
                {
                    vencedor = 1;
                }else
                {
                    vencedor = 2;
                }

            }

            fprintf(stdout,"%d\n" , vencedor);    // no final basta so dar print ao numero correspondente ao vencedor

            free(naipes);
            free(valcartas);
            free(naipes1);
            free(valcartas1);
            free(cartas1);
            free(cartas2);
            return 0;

    }

    fprintf(stdout,"-1\n");
    return 0;
}

int load_string_cartas(int n,char *cartas,char *argv[12])
{
    int i,k;             //Esta funçao cria uma string com todas as cartas introduzidas
    k = 2* (n-2);        // k é o numero o numero total de carateres da string cartas, como cada carta tem 2 carateres, k= 2 * numcartas == k = 2 * (argc-2)

    for (i=2;i<n;i++)
    {
        strcat(cartas,argv[i]);
    }

    if (check_string(cartas,k,n-2) != 0)        //a funçao check_string verifica se existem cartas ilegais
    {

        return -1;
    }

    return 0;

}








