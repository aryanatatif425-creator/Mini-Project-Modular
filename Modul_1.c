#include <stdio.h>
#include <string.h>

struct PosAnggaran  {
   char pos[100];
   long int BatasNominal;
                    };  


int PosAnggaran(){
    
    struct PosAnggaran TabelSatu;

    /*menerima masukan berupa nama pos anggaran*/
    printf("Masukan nama pos anggaran:");
    fgets(TabelSatu.pos,100,stdin);
    
    /*untuk menghapus input enter pada saat memasukkan nama posanggaran*/
    TabelSatu.pos[strcspn(TabelSatu.pos,"\n")] = 0; 
    
    /*menerima masukan batas nominal tiap anggaran*/
    printf("Masukan batas nominal tanpa titik atau koma (misal 5000):");
    scanf("%ld",&TabelSatu.BatasNominal); 
    
    /*respon saat data telah diinput*/
    printf("\n------- Data Telah Masuk -------\n");
    printf("Pos : %s\n", TabelSatu.pos);
    printf("Batas Nominal: %ld \n",TabelSatu.BatasNominal);
    printf("--------------------------------\n");

    return 0;
}