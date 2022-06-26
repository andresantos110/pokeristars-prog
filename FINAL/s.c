#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s.h"



int s1(char *filename,char *outfilename,int write)
{
    char read[3],deck[104]={0},c=0;
    long size=0;
    int i=0,j=0,k=1,*sequencia;
    carta *list = NULL;

    FILE *fp,*op;

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


    while(1)
    {

        sequencia = (int *) calloc(50,sizeof(int));

        while(j!=52)
        {
            fscanf(fp,"%s",read);
            if(strlen(read) < 2)
            {
                if(size%50 == 0 && size != 0)
                {
                    sequencia = (int *) realloc(sequencia,(size+50) * sizeof(int));
                }

                sscanf(read,"%d" , &sequencia[i]);
                size++;
                i++;


            }else
            {

                j++;
                deck[2*j-2] = read[0];
                deck[2*j-1] = read[1];
                if(deck[2*j-4] == deck[2*j-2] && deck[2*j - 3] == deck[2*j-1])
                {
                    return 0;
                }
            }
        }

        list = load_list(list,deck);

        for(i=0;i<size;i++)
        {
            if(sequencia[i] == 1)
            {
                list = alternar(list);
            }
            if(sequencia[i] == 2)
            {
                list = alternar2(list);
            }
            if(sequencia[i] == 3)
            {
                list = s3(list);
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

carta *load_list(carta *list,char *deck)
{
    int i=0;
    carta *aux,*head;


    list = (carta*) calloc (1,sizeof(carta));
    head = list;

    for(i=1;i<=52;i++)
    {

        if(i<52)
        {
            aux = (carta *) calloc(1,sizeof(carta));

            list->rank = deck[2*i-2];
            list->naipe = deck[2*i-1];
            list->next = aux;
            list=list->next;

        }

        if(i==52)
        {

            list->rank = deck[2*i-2];
            list->naipe = deck[2*i-1];
            list->next = NULL;
        }

    }
    return head;
}

void print_list(carta* list, FILE *op)
{
    int i=0;
    carta *a;

    a = list;

    while(a!= NULL)
    {
        fprintf(op,"%c%c " , a->rank , a->naipe);
        a=a->next;
        i++;
        if(i%13 == 0)
        {
            fprintf(op,"\n");
        }

    }
    fprintf(op,"\n");

}

void free_list(carta* list)
{
    carta *temp;

    while(list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);

    }
}

carta *alternar(carta *ListHead)
{
    int i;
    carta *aux1, *aux2,*a,*b;
    aux1 = ListHead;

    for(i=0;i<25;i++) aux1=aux1->next;

    aux2=aux1->next;
    aux1->next = NULL;


    aux1=ListHead;




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

carta *alternar2(carta *ListHead)
{
    int i;
    carta *aux1, *aux2,*a,*b;
    aux1 = ListHead;

    for(i=0;i<25;i++) aux1=aux1->next;

    aux2=aux1->next;
    aux1->next = NULL;

    aux2 = reverse_list(aux2);
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

carta *reverse_list(carta *deck)
{
    carta *pre = NULL , *cur = deck , *next = NULL ,*head;

    while(cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head = pre;

    return head;

}

carta *s3(carta *ListHead)
{
    int i;
    carta *aux1, *aux2, *ordenados;
    aux1 = ListHead;

    for(i=0;i<25;i++) aux1=aux1->next;

    aux2=aux1->next;
    aux1->next=NULL;
    aux1=ListHead;
    ordenados=aux2;

    for(i=0;i<25;i++) aux2=aux2->next;

    aux2->next = aux1;




    return ordenados;
}
