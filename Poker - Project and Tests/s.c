#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "s.h"



int s1(char *filename,char *outfilename,int write)
{
    char read[3],deck[104]={0};
    long size=0;
    int i=0,j=0,*sequencia;
    carta *list = NULL;

    FILE *fp,*op;

    if((fp = fopen(filename,"r")) == NULL )    // caso o ficheiro input introduzido nao exista, o programa nao corre
    {
        fprintf(stdout,"-1\n");
        return 0;
    }
    if(write)
    {
        op = fopen(outfilename,"w");  // caso o programa esteja em mode escrita para ficheiro, op aponta para o ficheiro indicado, senao, aponta para stdout
    }else
    {
        op = stdout;
    }


    while(1)
    {
        sequencia = (int *) calloc(50,sizeof(int));    //a sequencia de shuffle tem tamanho variavel, e nao ha maneira de saber o tamanho do vetor a alocar previamente
                                                       //por isso alocamos um vetor inicial para 50 inteiros, caso o tamanho da sequencia seja maior do que a alocaçao incial, esta é realocada com mais com mais 50 posiçoes
        while(j!=52)
        {
            fscanf(fp,"%s",read); //lemos uma string do ficheiro, caso o seu tamanho seja um, é um numero da sequencia de shuffle, caso o tamanho seja 2, é uma carta, após ler 52 cartas, acaba o loop

            if(strlen(read) < 2)
            {
                if(size%50 == 0 && size != 0)
                {
                    sequencia = (int *) realloc(sequencia,(size+50) * sizeof(int));     //fazer realloc sempre que um novo elemento da sequencia é lida é pouco eficiente, por isso a memoria é realocada a cada 50 elementos
                }

                sscanf(read,"%d" , &sequencia[i]);
                size++;
                i++;
            }else

            {
                j++;
                deck[2*j-2] = read[0];   //é criada uma string como todas as cartas que depois é utilizada para criar a lista
                deck[2*j-1] = read[1];
                if(deck[2*j-4] == deck[2*j-2] && deck[2*j - 3] == deck[2*j-1])   // caso sejam lidas duas cartas iguais de seguida, significa que chegamos ao fim do ficheiro
                {
					free(sequencia);
					fclose(fp);
					if (write == 1)
					{
						fclose(op);
					}
                    return 0;
                }
            }
        }

        list = load_list(list,deck);   //carregamos a lista

        for(i=0;i<size;i++)        // agora percorremos a sequencia e chamamos a funçao de acordo com o inteiro lido
        {
            if(sequencia[i] == 1)
            {
                list = shuffle1(list);
            }
            if(sequencia[i] == 2)
            {
                list = shuffle2(list);
            }
            if(sequencia[i] == 3)
            {
                list = shuffle3(list);
            }
        }

        print_list(list,op);


        j=0;
        i=0;
        size=0;

        free_list(list);
        free(sequencia);

    }

    return 0;

}

carta *load_list(carta *list,char *deck)   // Esta função recebe uma ponteiro para carta e uma string que contem um deck, cria uma lista de 52 cartas e retorna um ponteiro para a cabeça da lista
{
    int i=0;
    carta *aux,*head;


    list = (carta*) calloc (1,sizeof(carta));
    head = list;

    for(i=1;i<=52;i++)
    {

        if(i<52)
        {
            aux = (carta *) calloc(1,sizeof(carta));     //alocamos memoria para uma proxima carta

            list->rank = deck[2*i-2];
            list->naipe = deck[2*i-1];
            list->next = aux;
            list=list->next;

        }

        if(i==52)               // para o ultimo elemento, especificamos que aponta para NULL
        {

            list->rank = deck[2*i-2];
            list->naipe = deck[2*i-1];
            list->next = NULL;
        }

    }
    return head;
}

void print_list(carta* list, FILE *op)    // esta funçao recebe um ponteiro para a cebeça da lista e dá print a todas as cartas dessa lista para o ficheiro apontado por op
{
    int i=0;
    carta *aux;

    aux = list;

    while(aux!= NULL)
    {
        fprintf(op,"%c%c " , aux->rank , aux->naipe);
        aux=aux->next;
        i++;
        if(i%13 == 0)   // a cada 13 cartas, muda de linha
        {
            fprintf(op,"\n");
        }

    }
    fprintf(op,"\n");

}

void free_list(carta* list)   //esta funçao dá free a todos os elementos da lista
{
    carta *temp;

    while(list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);

    }
}

carta *shuffle1(carta *ListHead)     // o modo de shuffle 1 tem dois passos, primeiro dividir o baralho em dois, depois alternar entre cada baralho
{
    int i;
    carta *aux1,*aux2,*a,*b;
    aux1 = ListHead;


    for(i=0;i<25;i++)               //primeiro percorremos a lista até a 26ª carta e dividimos a lista
    {
        aux1=aux1->next;
    }
    aux2=aux1->next;
    aux1->next = NULL;

    aux1=ListHead;


    while(aux1 != NULL && aux2 != NULL)   //depois alternamos entre as duas listas, utilizando dois ponteiros auxiliares para nao perdermos as proximas cartas quando mudamos as ligaçoes
    {
        a = aux1->next;         // a e b salvaguardam as proximas cartas de ambas as listas
        b = aux2->next;

        aux1->next = aux2;      //a proxima carta da lista 1 passa a ser a carta da lista 2
        aux2->next = a;         //a proxima carta da lista 2 passa ser a proxima carta da lista 1

        aux1 = a;
        aux2 = b;

    }


    return ListHead;
}

carta *shuffle2(carta *ListHead)    // o modo shuffle 2 é semelhante ao modo shuffle 1, mas agora inverte-se a segunda metade do baralho
{
    int i;
    carta *aux1,*aux2,*a,*b;
    aux1 = ListHead;

    for(i=0;i<25;i++)
    {
        aux1=aux1->next;
    }
    aux2=aux1->next;
    aux1->next = NULL;

    aux2 = reverse_list(aux2);  //esta funçao retorna um ponteiro para a cebeça da lista invertida
    aux1 = ListHead;


    while(aux1 != NULL && aux2 != NULL)
    {
        a = aux1->next;
        b = aux2->next;

        aux1->next = aux2;
        aux2->next = a;

        aux1 = a;
        aux2 = b;

    }


    return ListHead;
}

carta *reverse_list(carta *ListHead)
{
    carta *aux1 = NULL , *list = ListHead , *aux2;   //esta funçao utiliza 3 ponteiros, um aponta para a carta anterior (aux1), outro para a carta atual, e outro para a proxima carta (aux2)

    while(list != NULL)
    {
        aux2 = list->next;      //aux2 aponta para a proxima carta
        list->next = aux1;      //a carta atual passa a apontar para a carta anterior
        aux1 = list;            //aux1 aponta para a carta atual
        list = aux2;            //avança para a proxima carta
    }

    return aux1;

}

carta *shuffle3(carta *ListHead)            // o modo shuffle 3 divide o baralho em dois e mete a primeira metade após a segunda metade
{
    int i;
    carta *aux1, *aux2, *head_aux2;

    aux1 = ListHead;
    for(i=0;i<25;i++)           //dividimos o baralho em dois
    {
        aux1=aux1->next;
    }

    aux2=aux1->next;
    aux1->next=NULL;
    aux1=ListHead;
    head_aux2=aux2;

    for(i=0;i<25;i++)
    {
        aux2=aux2->next;
    }

    aux2->next = aux1;          // a ultima carta da segunda metade passa a apontar para a primeira carta da primeira metade


    return head_aux2;
}

void s0(char *filename,int baralhos)
{

    int i,j,seq=0,aux=0;
    char a[39] = "AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC", b[39] = "AE 2E 3E 4E 5E 6E 7E 8E 9E TE JE QE KE", c[39] = "AO 2O 3O 4O 5O 6O 7O 8O 9O TO JO QO KO", d[39] = "AP 2P 3P 4P 5P 6P 7P 8P 9P TP JP QP KP";
    FILE *fp;
    srand(time(0));
    fp = fopen(filename,"w");

    for(i=0;i<baralhos;i++)
    {
        seq = (rand() % 9999 )+100;
        for(j=0;j<seq;j++)
        {
            aux = rand() % 3 +1;
            fprintf(fp,"%d " , aux);
        }
        fprintf(fp,"\n%s\n%s\n%s\n%s\n" ,a,b,c,d);

    }
    fclose(fp);
    return;

}
