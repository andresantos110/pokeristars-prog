#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c.h"
#include "di.h"
#include "dx.h"
#include "s.h"


int checkd(int,char**,char*);
int checkc(int,char**);
int checks(int,char**,char*);


int main(int argc,char *argv[])
{


    int mode=0,filenamesize=0,outfilenamesize=0,write=0;
    char *filename,*outfilename = NULL;


    if(argc <3)
    {
        fprintf(stdout,"-1\n");
        return 0;
    }


     if (strncmp(argv[1],"-c",2) == 0)
     {
        if(checkc(argc,argv) == 0)
           {
               c(argc,argv);
               return 0;
           }

        fprintf(stdout,"-1\n");
        return 0;
     }



    if (strncmp(argv[1],"-d",2) == 0)
    {
        filenamesize = strlen(argv[2]);
        filename = (char *) malloc (filenamesize * (sizeof (char))+1);
        strcpy(filename, argv[2]);

        if((write = checkd(argc,argv,filename) )== -1)
        {
            fprintf(stdout,"-1\n");
            free(filename);
            return 0;
        }
        if(write == 1)
        {
			outfilenamesize = strlen(argv[4]);
			outfilename = (char *) malloc ((outfilenamesize +1) * sizeof(char));
			strcpy(outfilename,argv[4]);
        }

        if(argv[1][2] == 'x')
        {


           dx(filename,outfilename,write);

           free(filename);
           if(write == 1)
           {
               free(outfilename);
           }
           return 0;
        }

        mode = argv[1][2] - '0';

        di(filename,outfilename,mode,write);

        free(filename);
        if(write == 1)
        {
            free(outfilename);
        }
        return 0;
    }

    if (strcmp(argv[1],"-s1") == 0)
    {
        filenamesize = strlen(argv[2]);
        filename = (char *) malloc (filenamesize * (sizeof (char))+1);
        strcpy(filename, argv[2]);

        if((write = checks(argc,argv,filename) )== -1)
        {
            fprintf(stdout,"-1\n");
            free(filename);
            return 0;
        }
        if(write == 1)
        {
			outfilenamesize = strlen(argv[4]);
			outfilename = (char *) malloc ((outfilenamesize +1) * sizeof(char));
			strcpy(outfilename,argv[4]);
        }

        s1(filename,outfilename,write);

        free(filename);
        if(write == 1)
        {
            free(outfilename);
        }
        return 0;
    }

    fprintf(stdout,"-1\n");
    return 0;
}

int checkc(int argc, char *argv[])
{
    int i;
    if (argc!=7 && argc!=9 && argc!=11 && argc!=12)
    {
        return -1;
    }

    for (i=2;i<argc;i++)
    {
        if(strlen(argv[i]) != 2)
        {
            return -1;
        }
    }
    return 0;
}

int checkd(int argc,char *argv[],char *filename)
{
    int mode=0,k;

    if(argc != 3 && argc != 5)
    {

        return -1;
    }

    if (strlen(argv[1]) != 3)
    {

        return -1;
    }
    mode = argv[1][2] -  '0';

    if((mode < 1 || mode > 4)  && (argv[1][2] != 'x'))
    {
        return -1;
    }

    k=strlen(filename) - 5;
    if (strncmp((filename + k),".deck",5) != 0)
    {

        return -1;
    }

    if(argc == 5)
    {
        if ( strcmp(argv[3],"-o") != 0)
        {
            return -1;
        }
        return 1;
    }

    return 0;
}

int checks(int argc,char *argv[],char *filename)
{
    int k;

    if(argc != 3 && argc != 5)
    {

        return -1;
    }
    k=strlen(filename) - 8;
    if (strncmp((filename + k),".shuffle",8) != 0)
    {

        return -1;
    }

    if(argc == 5)
    {
        if ( strcmp(argv[3],"-o") != 0)
        {
            return -1;
        }
        return 1;
    }

    return 0;
}
