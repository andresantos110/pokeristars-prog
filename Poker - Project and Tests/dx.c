#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "dx.h"


int dx(char *filename,char *outfilename,int write)
{
    int i=0,inativos=0,numjogos=0,ordem[8]={0,1,2,3,4,5,6,7};
    char deck[43]={0},abc[3];
    double stats[10]={0};
    FILE *fp,*op;
    struct jogador arr_jogador[8];

    if((fp = fopen(filename,"r")) == NULL)          // caso o ficheiro input introduzido nao exista, o programa nao corre
    {
		fprintf(stdout,"-1\n");
		return 0;
	}

    if(write == 1)
    {
        op = fopen(outfilename,"w");            // caso o programa esteja em mode escrita para ficheiro, op aponta para o ficheiro indicado, senao, aponta para stdout
    }else
    {
        op = stdout;
    }

    for(i=0;i<8;i++)
    {                                   //incialização das flags de todos os jogadores
        arr_jogador[i].i = 0;
        arr_jogador[i].v = 0;
        arr_jogador[i].folds = 0;
        arr_jogador[i].jogos = 0;
        arr_jogador[i].pontos = 0;

    }

    while(load_deck(fp,deck,21) == 0)   //Este loop le as primeiras 21 cartas de cada deck (5 cartas da mesa mais 16 para os jogadores), quando nao consegue ler mais cartas, significa que chegou ao fim do ficheiro
    {
        Check_jogadores(arr_jogador,deck,op,inativos);          //Esta função trata distribui as cartas pelos jogadores ativos, calcula a pontução da mao e verifica se o jogador dá fold ou não
        numjogos += Check_vencedores(arr_jogador,op,stats);     //Esta função verifica qual a mão vencedora e quais os jogadores vencedores, caso nao haja nenhum jogador ativo, retorna 0, senao, retorna 1
        inativos = update_flags(arr_jogador,inativos);          //Esta função atualiza as flags dos jogadores para o próximo jogo, retorna o número de jogadores inativos na proxima ronda

        for(i=0;i<31;i++)               //este loop lê as cartas restantes do deck para poder ler do próximo deck
        {
            fscanf(fp,"%2s", abc);
        }

    }

    ordenar_pontos(arr_jogador,ordem);          //esta função reordena o vetor ordem de acordo com os pontos de cada jogador

    for(i=0;i<10;i++)
    {
        stats[i] = stats[i] / numjogos ;        //o vetor stats conta o numero de ocorrencias de cada pontuação, divide-se pelo numero de jogos para obter a percentagem de cada combinação
        fprintf(op,"%d %.2E\n", i+1, stats[i]);
    }
    fprintf(op,"\n");

    for(i=0;i<8;i++)

    {
        fprintf(op,"%d %.2f\n", ordem[i]+1, arr_jogador[ordem[i]].pontos); // por fim da-se print dos pontos de cada jogador pela ordem indicada pelo vetor ordem
    }

	fclose(fp);
	if(write)
    {
        fclose(op);
    }

	return 0;
}


void ordenar_pontos(struct jogador arr_jogador[8],int ordem[8])
{
    int i=0,j=0,k=0;

    for(i=0;i<7;i++)
    {
        for(j=i;j<8;j++)
        {
            if(arr_jogador[ordem[i]].pontos < arr_jogador[ordem[j]].pontos)   //este loop ordena o vetor ordem comparando os pontos do jogador (ordem[i]) com os pontos do jogador (ordem[j])
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
                cartas[x] = deck[28+x-(4*inativos)];   //as cartas que teem que ser carregadas sao difrentes dependendo do numero de jogadores inativos

            }

            load_valcartas(valcartas,cartas,14);            // carregam-se os arrays com as cartas
            load_naipes(naipes,cartas,14);
            ordenar(cartas,naipes,valcartas,7);
            arr_jogador[i].pontos_mao = Check_Combinacoes(valcartas,naipes,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe);   // calcula-se os pontos da mao

            if ((arr_jogador[i].pontos_mao == 5 || arr_jogador[i].pontos_mao == 9) && (arr_jogador[i].melhormao[0] == 14 && arr_jogador[i].melhormao[1] == 5))  //caso a mao tenha a sequencia A 5 4 3 2 reordena-se a mao
            {
                Swap_Straight5(arr_jogador[i].melhormao,arr_jogador[i].melhornaipe);
                load_cartas(arr_jogador[i].cartas,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe,5);
            }else
            {
                load_cartas(arr_jogador[i].cartas,arr_jogador[i].melhormao,arr_jogador[i].melhornaipe,5);
            }


            if(arr_jogador[i].pontos_mao < i+1 && arr_jogador[i].folds < 4)  //se os pontos da mao forem inferiores ao numero do jogador e o jogador nao tenha dado fold 4 vezes seguidas, o jogador da fold
            {
                arr_jogador[i].folds++;
                arr_jogador[i].jogos = 0;
                arr_jogador[i].pontos_mao = 0;

            }else  // se o jogador nao deu fold, entao vai a jogo e da-se print á sua mao
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
        if(arr_jogador[i].folds == 0 && arr_jogador[i].i == 0)   //a função só verifica os jogadores que foram a jogo
        {
            if (arr_jogador[i].pontos_mao > pontosmax ) // quando um jogador tem uma mao mais alta que a mao mais alta atual
            {
                for(j=0;j<i;j++)
                {
                    arr_jogador[j].v = 0;   // limpam-se todas as flags de vencedor que possam ter sido criadas ate agora
                }
                pontosmax = arr_jogador[i].pontos_mao;              //guardam-se os pontos da mao mais alta

                strcpy(melhornaipe,arr_jogador[i].melhornaipe);     //guardam-se a arrays das cartas da mao mais alta
                strcpy(cartas_vencedoras,arr_jogador[i].cartas);
                for(j=0;j<5;j++)
                {
                    melhormao[j] = arr_jogador[i].melhormao[j];
                }

                arr_jogador[i].v = 1;   //o jogador i recebe a flag de vencedor
            }

            if(arr_jogador[i].pontos_mao == pontosmax)  // quando um jogador tem os mesmos pontos que a mao mais alta, tem que se desempatar
            {
                x = Desempate(arr_jogador[i].melhormao,melhormao,pontosmax);

                if(x == 1)  // quando x==1, o jogador i tem uma mao mais forte que a mao mais alta anterior, logo realiza-se o mesmo que  que no loop anterior
                {
                    for(j=0;j<i;j++)
                    {
                        arr_jogador[j].v = 0;
                    }


                    pontosmax = arr_jogador[i].pontos_mao;
                    strcpy(melhornaipe,arr_jogador[i].melhornaipe);
                    strcpy(cartas_vencedoras,arr_jogador[i].cartas);
                    for(j=0;j<5;j++)
                    {
                        melhormao[j] = arr_jogador[i].melhormao[j];
                    }

                    arr_jogador[i].v = 1;
                }

                if(x == 0)   // quando x == 0, que dizer que as maos sao equivalentes, logo basta dizer que o jogador i é tambem vencedor
                {
                    arr_jogador[i].v = 1;

                } // quando x==2, nao é preciso de fazer nada
            }
        }
    }

    for(i=0;i<8;i++)
    {
        if(arr_jogador[i].v == 1)   //conta-se quantos jogadores teem a flag vencedor
        {
            nvencedores++;
        }
    }

    if(nvencedores != 0) // quando nao ha vencedores, nao se realiza este loop
    {
        fprintf(op,"W ");
        for(i=0;i<10;i+=2)
        {
            fprintf(op,"%c%c " , cartas_vencedoras[i],cartas_vencedoras[i+1]); // print à mao vencedora
        }
        fprintf(op,"%d", pontosmax);

        for(i=0;i<8;i++)
        {
            if(arr_jogador[i].v == 1)
            {
                fprintf(op," %d" , i+1);
                arr_jogador[i].v = 0;

                arr_jogador[i].pontos +=  1 / nvencedores;  // os vencedores ganham 1 ponto dividido por todos os vencedores

            }
        }

        stats[pontosmax-1]++;  //aumenta-se as ocorrencias dos pontos da mao vencedora
        fprintf(op,"\n\n");

        return 1;
    }

    return 0; //quando nao há vencedores, a funçao retorna 0 de modo a nao incrementar o numero de rondas jogadas
}

int update_flags(struct jogador arr_jogador[8],int inativos)  // antes de passar à próxima ronda, é preciso de atualizar as flags dos jogadores
{
    int i;

    for(i=0;i<8;i++)
    {

        arr_jogador[i].pontos_mao = 0;  //reset dos pontos da mao


        if(arr_jogador[i].i == 1) //se o jogador esteve inativo esta ronda, volta a estar ativo na proxima
        {
            arr_jogador[i].i = 0;
            arr_jogador[i].jogos = 0;
            inativos--;
        }

        if(arr_jogador[i].jogos == 2) // caso o jogador participe em duas rondas seguidas, passa a estar inativo
        {
            arr_jogador[i].i = 1;
            arr_jogador[i].jogos = 0;
            inativos++;
        }
    }
    return inativos;   //retorna o numero de jogadores inativos na proxima ronda
}

