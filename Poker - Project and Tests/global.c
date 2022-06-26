#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"




int check_string(char *cartas,int k,int n)
{
    int i,j;

    for (i=0;i<k;i++)
    {
        if ((cartas[i] < 50 || cartas[i]>57) && cartas[i] != 'T' && cartas[i] != 'J' && cartas[i] != 'Q' && cartas[i] != 'K'  && cartas[i] != 'A')                  //verifica os valores das cartas
        {

            return -1;
        }
        i++;
    }

    for(j=1;j<k;j++)
    {
        if(cartas[j] != 'C' && cartas[j] != 'E' && cartas[j] != 'O' && cartas[j] != 'P')                         //verifica os naipes
        {

            return -1;
        }
        j++;
    }

    if (n!=10)                                                                  // verifica se ha cartas repetidas, caso sejam 10 cartas verifica cada mao individualmente
    {
        for (i=0;i<=k-4;i++)
        {                                                                        // i identifica uma cartas e j identifica a proxima carta
            for (j=i+2;j<=k;j++)
            {
                if (( cartas[i] == cartas[j]) && (cartas[i+1] == cartas[j+1]))
                {

                    return -1;
                }
                j++;
            }
            i++;
        }
    }
    if(n==10)
    {
        for (i=0;i<=6;i++)
        {
            for (j=i+2;j<10;j++)
            {
                if (( cartas[i] == cartas[j]) && (cartas[i+1] == cartas[j+1]))
                {

                    return -1;
                }
                j++;
            }
            i++;
        }

        for (i=10;i<=16;i++)
        {
            for (j=i+2;j<20;j++)
            {
                if (( cartas[i] == cartas[j]) && (cartas[i+1] == cartas[j+1]))
                {

                    return -1;
                }
                j++;
            }
            i++;
        }
    }

    return 0;
}

void ordenar(char *cartas, char *naipe, int *valcartas,int k)
{
    int ordem[10];                      //esta funçao ordena a string cartas, a string naipes e o vetor valcartas
    int i, j, temp;
    char *naipetemp, vtemp;



    naipetemp = (char *) calloc(k+1,sizeof(char));

    for (i=0;i<k;i++)
    {                           // cria um vetor que guarda a ordem das cartas
        ordem[i]=i;
    }

    for(i=0;i<k;i++)
    {
        for(j=i+1;j<k;j++)
        {
            if (valcartas[i]<valcartas[j])                // reordena o vetor dos valores das cartas e o vetor da ordem
            {
                temp = valcartas[i];
                valcartas[i] = valcartas[j];
                valcartas[j] = temp;

                temp = ordem[i];
                ordem[i] = ordem[j];
                ordem[j] = temp;
            }
        }
    }

    for(i=0;i<k;i++)                          // ordena o vetor dos naipes de acordo com o vetor ordem
    {
        naipetemp[i] = naipe[ordem[i]];
    }
    for(i=0;i<k;i++)
    {
        naipe[i]=naipetemp[i];

    }

    for(i=0;i<k;i++)
    {
        for(j=i+1;j<k;j++)                          // ordena alfabeticamente os naipes
        {
            if(valcartas[i]==valcartas[j] && naipe[i]>naipe[j])
            {

                vtemp = naipe[i];
                naipe[i] = naipe[j];
                naipe[j] = vtemp;
            }
        }
    }



    j = 0;
    for (i=0; i<k; i++)             // reescreve a string das cartas com a nova ordem
    {

        if(valcartas[i] >= 2 && valcartas[i] <= 9)
        {
            cartas[j] = valcartas[i] + '0';
            cartas[j+1] = naipe[i];
            j=j+2;
        }
        if(valcartas[i] == 10)
        {
            cartas[j] = 'T';
            cartas[j+1] = naipe[i];
            j=j+2;
        }

        if(valcartas[i] == 11)
        {
            cartas[j] = 'J';
            cartas[j+1] = naipe[i];
            j=j+2;
        }

        if(valcartas[i] == 12)
        {
            cartas[j] = 'Q';
            cartas[j+1] = naipe[i];
            j=j+2;
        }

        if(valcartas[i] == 13)
        {
            cartas[j] = 'K';
            cartas[j+1] = naipe[i];
            j=j+2;
        }

        if(valcartas[i] == 14)
        {
            cartas[j] = 'A';
            cartas[j+1] = naipe[i];
            j=j+2;
        }
    }
	free(naipetemp);

    return;
}

void load_valcartas(int *valcartas,char *cartas,int k)
{
    int i,j = 0;
    for (i=0; i<k; i++)  // percorre o vetor das cartas e atribui valores a cada carta num vetor separado
    {
        if (cartas[i] >= 50 && cartas[i]<=57) // se o caracter encontrado estiver entre 50 (char 2) e 57 (char 9) basta subtrair 48 ao codigo ASCII para obter o valor da carta
        {
            valcartas[j] = cartas[i] - 48;
            j++;
        }

        if(cartas[i] == 'T')  // atribui o valor 10 ao caracter T que representa o numero 10 nas cartas
        {
            valcartas[j] = 10;
            j++;
        }

        if (cartas[i] == 'J')      // atribui valor 11 ao valete
        {
            valcartas[j] = 11;
            j++;
        }

        if (cartas[i] == 'Q') // atribui valor 12 à dama
        {
            valcartas[j] = 12;
            j++;
        }

        if (cartas[i] == 'K') // atribui valor 13 ao rei
        {
            valcartas[j] = 13;
            j++;
        }

        if (cartas[i] == 'A') // atribui valor 14 ao às
        {
            valcartas[j] = 14;
            j++;
        }
    }
    return;
}

void load_naipes(char *naipes,char *cartas,int k)
{

    int i,j=0;

    for(i=0;i<k;i++)  //percorre o vetor das cartas colocando os naipes num vetor separado pela mesma ordem
    {
        if(cartas[i]=='C' || cartas[i]=='E' || cartas[i]=='O' || cartas[i]=='P') // C=67, E=69, O=79, P=80
        {
            naipes[j] = cartas[i];
            j++;
        }
    }
    return;
}

int Check_Combinacoes(int *valcartas,char *naipes,int melhormao[5],char melhornaipe[6])
{
    int i,j,k,l,m,a,valhand[5]={0};
    int pontosmax = 0, pontosaux = 0;
    char suithand[6]={0};




    for (i=0;i<3;i++)                                  //Esta funçao gera todas as maos de 5 cartas possiveis a partir de 7 cartas
    {
        valhand[0] = valcartas[i];
        suithand[0] = naipes[i];
        for(j=i+1;j<4;j++)                      //para gerar todas as combinaçoes, usamos 5 loops for, 1 por cada carta
        {
            while(j<=i)                         //quando o indice de um dos loops é inferior ou igual ao loop anterior, incrementa-se ate ser superior,para nao ter cartas repetidas
            {
                j++;
            }
            valhand[1] = valcartas[j];
            suithand[1] = naipes[j];
            for(k=i+2;k<5;k++)
            {
                while( k <= j)
                {
                    k++;
                }
                valhand[2] = valcartas[k];
                suithand[2] = naipes[k];
                for(l=i+3;l<6;l++)
                {
                    while (l<=k)
                    {
                        l++;
                    }
                    valhand[3] = valcartas[l];
                    suithand[3] = naipes[l];
                    for(m=i+4;m<7;m++)
                    {
                        while(m<=l)
                        {
                            m++;
                        }
                        valhand[4] = valcartas[m];
                        suithand[4] = naipes[m];
                        pontosaux = Check_Hand(valhand,suithand);


                        if (pontosaux == pontosmax)
                        {                                                                   //depois de gerar a mao, a funçao Check_Hand calcula os pontos dessa mao, se os pontos forem superiores aos pontos da
                            if (Desempate(valhand,melhormao,pontosaux) == 1)                //mao mais alta, a mao atual passa a ser a mao mais alta, caso  tenham os mesmos pontos, a funçao Desempate desempata
                            {                                                               //as duas maos e guarda a mao mais alta
                                 for(a=0;a<5;a++)
                                {

                                    melhormao[a] = valhand[a];

                                }
                                strcpy(melhornaipe,suithand);
                            }
                        }else
                        {

                            if(pontosaux > pontosmax)
                            {
                                for(a=0;a<5;a++)
                                {
                                    melhormao[a] = valhand[a];


                                }
                                strcpy(melhornaipe,suithand);
                                pontosmax = pontosaux;
                            }
                        }
                    }
                }
            }
        }
    }

    return pontosmax;                               // a funçao retorna os pontos da mao mais alta possivel
}

void load_cartas(char *cartasn,int *valcartasn,char *naipesn,int k)
{
    int i,j=0;


    for (i=0;i<k;i++)           // cria uma string cartasn com os vetores dos valores e naipes das cartas, resultado numa string com toda a informaçao sobre as cartas
    {

        if(valcartasn[i] >= 2 && valcartasn[i] <= 9)
        {
            cartasn[j] = valcartasn[i] + '0';     // soma-se '0' ao valor valcartasn[i] para converter o int em char
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
        if(valcartasn[i] == 10)
        {
            cartasn[j] = 'T';
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
        if(valcartasn[i] == 11)
        {
            cartasn[j] = 'J';
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
        if(valcartasn[i] == 12)
        {
            cartasn[j] = 'Q';
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
        if(valcartasn[i] == 13)
        {
            cartasn[j] = 'K';
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
        if(valcartasn[i] == 14)
        {
            cartasn[j] = 'A';
            cartasn[j+1] = naipesn[i];
            j=j+2;
        }
    }
    cartasn[j]='\0';




}

int Check_Hand(int valhand[5],char suithand[5])
{
                                                //Esta funçao atribui os pontos a uma mao, chamando varias funçoes que verificam cada combinaçao, quando uma função retorna 1,
                                                //a funçao Check_Hand retornao valor correspondente a essa mão, por isso começamos por verificar as combinaçoes mais valiosas
    if(Check_Royal(valhand,suithand) == 1)
    {

        return 10;
    }

    if(Check_Straight_Flush(valhand,suithand)==1)
    {

        return 9;
    }

    if(Check_Four(valhand)==1)
    {

        return 8;
    }

    if(Check_House(valhand)==1)
    {

        return 7;
    }

    if(Check_Flush(suithand)==1)
    {

        return 6;
    }

    if(Check_Straight(valhand)==1)
    {

        return 5;
    }

    if(Check_Trio(valhand)==1)
    {

        return 4;
    }
    if(Check_TwoPair(valhand)==1)
    {

        return 3;
    }
    if(Check_Pair(valhand)==1)
    {

        return 2;
    }

    return 1;
}

int Check_Pair(int valhand[5])
{
    int i;
    for (i=0;i<4;i++)                          //Para ver se uma mao tem um par, usa-se um for que percorre a mao e verifica se uma carta é igual a próxima carta
    {
        if (valhand[i] == valhand[i+1])
        {
            return 1;
        }
    }
    return 0;
}

int Check_TwoPair(int valhand[5])
{
    int i,j=0;

    for (i=0;i<4;i++)
    {                                         //Para verificar se a mao tem dois pares, faz-se o mesmo que na funçao anterior, mas agora conta-se o numero de pares, e a funçao so retorna 1 se encontrar dois pares
        if (valhand[i] == valhand[i+1])
        {
            j++;
            if (j==2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Check_Trio(int valhand[5])
{
    int i;

    for (i=0;i<3;i++)                          //A funçao percorre a mao e retorna 1 se existirem 3 cartas consecutivas iguais
    {
        if (valhand[i] == valhand[i+1] && valhand[i+1] == valhand[i+2])
        {
            return 1;
        }
    }
    return 0;
}

int Check_Straight(int valhand[5])
{
    int i;


    if (Check_Straight5(valhand) == 1)      //A sequencia  5 4 3 2 A  nao pode ser vista como as outras sequencias por isso chama-se uma funçao que verifica este caso especial
    {
        return 1;
    }

    for (i=0;i<4;i++)
    {                                                           //se a diferença entre os valores de duas cartas consecutivas nao for igual a 1, a funçao retorna 0
        if ( ( valhand[i] - valhand[i+1] ) != 1)
        {
            return 0;
        }
    }
    return 1;
}

int Check_Flush(char suithand[5])
{
    int i;

    for (i=0;i<4;i++)
    {                                                   //Para ver se a mao tem um flush, basta ver se todas as cartas têm o mesmo naipe
        if ( suithand[i] != suithand[i+1])
        {
            return 0;
        }

    }
    return 1;
}

int Check_House(int valhand[5])
{
    if (((valhand[0] == valhand[1]) && ( valhand[2] == valhand[3] && valhand[3] == valhand[4])) || ((valhand[4] == valhand[3]) && ( valhand[2] == valhand[1] && valhand[1] == valhand[0])))
    {
        return 1;                                      //Os Full houses têm dois formatos, A A B B B ou A A A B B, este if verica se a mao tem um destes formatos
    }else
    {
        return 0;
    }
}

int Check_Four(int valhand[5])
{
    int i;

    for (i=0;i<2;i++)                     //a funçao percorre a mao e retorna 1 caso existam 4 cartas seguidas iguais
    {
        if (valhand[i] == valhand[i+1] && valhand[i+1] == valhand[i+2] && valhand[i+2] == valhand[i+3])
        {
            return 1;
        }
    }
    return 0;
}

int Check_Straight_Flush(int valhand[5], char suithand[5])
{
    if ((Check_Flush(suithand)) ==1 && (Check_Straight(valhand) ==1))           //se uma mao tiver um straight e um flush, entao é straight flush
    {
        return 1;
    }
    return 0;
}

int Check_Royal(int valhand[5], char suithand[5])
{


    if ((Check_Straight_Flush(valhand,suithand) == 1)  && (valhand[4] == 10))         //se uma mao for straight flush e a ultima carta tiver valor 10, entao é um royal flush
    {
        return 1;
    }
    return 0;
}

int Check_Straight5(int valhand[5])
{
    int i;
    if ((valhand[0] == 14)  && (valhand[1] == 5))  //caso a primeira carta da mao for um ás e a segunda for um 5, percorrem-se todas as cartas menos a primeira tal como se fez na funçao Check_straight
    {
        for (i=1;i<4;i++)
        {
            if(valhand[i] - valhand[i+1] != 1)
            {
                return 0;
            }
        }

        return 1;
    }
    return 0;
}

int Desempate(int mao1[5],int mao2[5],int flag)
{
    int i=0,j=0,a=0,b=0;

    if (flag == 10)                                         // quando ambas as maos sao royal flush, é sempre empate
    {
        return 0;
    }

    if(flag == 5 || flag == 9)                                //Como o às pode ser a maior ou a menor carta de uma sequencia, temos que ter em atençao ao caso especial A 5 4 3 2 vs  6 5 4 3 2,
    {                                                         //para detetar este caso, basta verificar se a primeira carta de apenas uma das sequencias é ás, e verificar se a segunda de ambas
        if (mao1[0] == 14 || mao2[0] == 14)                   //as maos sao iguais, caso ambas as condiçoes se verifiquem, ganha a mao cuja primeira carta não é o ás
        {

            if (mao1[0] == 14 && mao2[0] == 14)               //Quando ambas as maos teem um ás, basta comparar a segunda carta para desempatar, pois podem ser  A K Q J T   ou    A 5 4 3 2
            {
                if (mao1[1] > mao2[1])
                {
                    return 1;
                }else
                {
                    if (mao1[1] < mao2[1])
                    {
                        return 2;
                    }else
                    {
                        return 0;
                    }

                }
            }

            if (mao1[1] > mao2[1])
            {
                return 1;
            }else
            {
                if (mao1[1] < mao2[1])
                {
                    return 2;
                }else
                {
                    if (mao1[0] < mao2[0])
                    {
                        return 1;
                    }else
                    {
                        return 2;
                    }
                }
            }

        }

    }

    if (flag == 7)                                                        //No full house, as maos podem ter dois formatos : A A A B B  ou  B B A A A, quando ambas as maos teem o mesmo formato
    {                                                                     //podemos comparalas diretamente como as outras maos, mas quando teem formatos diferentes, temos que comparar primeiro
        if (House_trio(mao1) == House_trio(mao2))                         //os trios, e apenas depois as duplas.
        {
            if(House_trio(mao1) == 1)                                     //a funçao House_trio retorna 1 caso a mao tenha um formato A A A B B, e retorna 0 quando tem um formato B B A A A
            {
                for (i=0;i<5;i++)
                {
                    if (mao1[i] > mao2[i])
                    {
                        return 1;
                    }

                    if (mao1[i] < mao2[i])
                    {
                        return 2;
                    }
                }
                return 0;
            }else
            {
                for (i=4;i>=0;i--)
                {
                    if (mao1[i] > mao2[i])
                    {
                        return 1;
                    }

                    if (mao1[i] < mao2[i])
                    {
                        return 2;
                    }
                }
                return 0;
            }
        }else
        {
            if(House_trio(mao1) == 1)
            {
                for (i=0;i<5;i++)
                {
                    if (mao1[i] > mao2[4-i])
                    {
                        return 1;
                    }

                    if (mao1[i] < mao2[4-i])
                    {
                        return 2;
                    }
                }
            }else
            {
                for(i=0;i<5;i++)
                {

                    if (mao1[4-i] > mao2[i])
                    {
                        return 1;
                    }
                    if (mao1[4-i] < mao2[i])
                    {
                        return 2;
                    }
                }
            }
        }
        return 0;
    }

    if (flag == 2)                                    //Para os Pairs, primeiro temos que comparar os pares e depois comparar as cartas independentes, a função Loc_pair retorna a posiçao
    {                                                 //da primeira carta do par, depois comparamos essa carta, caso sejam iguais, comparam-se as cartas normalmente

        a = Loc_Pair(mao1);
        b = Loc_Pair(mao2);

        if(mao1[a] > mao2[b])
        {
            return 1;
        }
        if(mao1[a] < mao2[b])
        {
            return 2;
        }

        for(i=0;i<5;i++)
        {

            if(mao1[i] > mao2[i])
            {
                return 1;
            }
            if(mao1[i] < mao2[i])
            {
                return 2;
            }
        }

        return 0;

    }

    if (flag == 3)
    {
                                                    //Para Two Pairs, as maos podem ter tres formas difrentes A B C ;; A C B  ;; C A B, onde A e B representam um par e C
        a = Loc_2pair(mao1);                        //uma carta independente, a funçao Loc_2pair retorna a localizaçao da carta C, depois usamos um loop para comparar os
        b = Loc_2pair(mao2);                        //pares de ambas as maos, caso sejam iguais, comparam-se as cartas independentes



        for(i=0,j=0; i<4 && j<4; i++,j++)
        {
            if(i == a && i!= 4)
            {
                i++;
            }
            if(j == b && j!= 4)
            {
                j++;
            }
            if(mao1[i] > mao2[j])
            {
                return 1;
            }
            if(mao1[i] < mao2[j])
            {
                return 2;
            }
        }
            if(mao1[a] > mao2[b])
            {
                return 1;
            }
            if(mao1[a] < mao2[b])
            {
                return 2;
            }
        return 0;
    }

    if (flag == 4)                                 //Os trios podem ter as formas  A A A B C ; B A A A C ; B C A A A, logo basta comparar primeiro a terceira carta ( elemento 2 do vetor) pois faz
    {                                              //sempre parte do trio caso os trios sejam iguais, podemos comparar carta a carta
        if (mao1[2] > mao2[2])
        {
            return 1;
        }
        if (mao1[2] < mao2[2])
        {
            return 2;
        }
    }


    if (flag == 8)                                   //As quadras podem ter duas formas, A A A A B ou B A A A A, tal como no trio, podemos so comparar a terceira carta (neste caso tambem
    {                                                //podia ser a segunda ou a quarta carta),e caso sejam iguais, comparar carta a carta
        if (mao1[2] > mao2[2])
        {
            return 1;
        }
        if (mao1[2] < mao2[2])
        {
            return 2;
        }
    }


    for (i=0;i<5;i++)                                 //Caso nenhuma das condiçoes anteriores se verificar, comparam-se as maos carta a carta
    {
        if (mao1[i] > mao2[i])
        {
            return 1;
        }

        if (mao1[i] < mao2[i])
        {
            return 2;
        }
    }
    return 0;


}

int Loc_Pair(int pair[5])
{
    int i;
    for(i=0;i<4;i++)
    {                                   //a funçao retorna a posição da primeira carta do par
        if(pair[i] == pair[i+1])
        {
            return i;
        }
    }
    return 0;
}

int Loc_2pair(int tpair[5])
{
    if(tpair[0] != tpair[1])                    // a função retorna a posição da carta independente num Two Pair
    {
        return 0;
    }

    if(tpair[2] != tpair[3] && tpair[2]!= tpair[1])
    {
        return 2;
    }

    return 4;
}

int House_trio(int house[5])
{
    if(house[0] == house[1] && house[1] == house[2])            // a funçao retorna 1 se o trio vier antes do par, e 0 caso contrario
        return 1;
    else
        return 0;
}

void Swap_Straight5(int val[5], char naipe[6])       //Caso uma contenha a sequencia A 5 4 3 2, esta funçao altera a ordem dessa mao para 5 4 3 2 A
{
    int aux;
    char caux;

    aux = val[0];
    val[0]=val[1];
    val[1]=val[2];
    val[2]=val[3];
    val[3]=val[4];
    val[4]=aux;

    caux = naipe[0];
    naipe[0]=naipe[1];
    naipe[1]=naipe[2];
    naipe[2]=naipe[3];
    naipe[3]=naipe[4];
    naipe[4]=caux;

    return;
}


int load_deck(FILE *fp,char *deck,int n)             //esta funçao lê n cartas do ficheiro apontado por fp e mete as na string deck, caso nao consiga ler as n cartas, retorna -1
{
    int i;
    char read[3]={0};

    for(i=1;i<=n;i++)
    {
        if(fscanf(fp,"%2s",read) != 1)
        {
            return -1;
        }
        deck[2*i-2] = read[0];
        deck[2*i-1] = read[1];

    }
    return 0;
}























