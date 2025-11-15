#include <stdio.h>
#include <string.h>

struct PosAnggaran
{
   char pos[100];
   long int BatasNominal;
};

/*Algoritma*/
void CetakPosAnggaran (struct PosAnggaran data) {
    printf("\n----------------------\n");
    printf("Pos : %s\n", data.pos);
    printf("Batas Nominal : %ld\n",data.BatasNominal );
    printf("\n----------------------\n");
                                                }