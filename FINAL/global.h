#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>



//////////////////////Fun??es globais//////////////////////


int check_string(char*,int,int);
void ordenar(char*,char*,int*,int);
void load_valcartas(int*,char*,int);
void load_naipes(char*,char*,int);
void load_cartas(char*,int*,char*,int);
int Check_Combinacoes(int*,char*,int[5],char[5]);
int Check_Hand(int[5],char[5]);
int Check_Royal(int[5],char[5]);
int Check_Four(int[5]);
int Check_House(int[5]);
int Check_Straight_Flush(int[5],char[5]);
int Check_Flush(char[5]);
int Check_Straight(int[5]);
int Check_Trio(int[5]);
int Check_TwoPair(int[5]);
int Check_Pair(int[5]);
int Check_Straight5(int[5]);
int Desempate(int[5],int[5],int);
int Loc_Pair(int[5]);
int Loc_2pair(int[5]);
int House_trio(int[5]);
void Swap_Straight5(int[5],char[6]);
void mystrrev (char*);
int load_deck(FILE *,char*,int);
///////////////////////////////////////////////////////////





#endif // GLOBAL_H_INCLUDED
