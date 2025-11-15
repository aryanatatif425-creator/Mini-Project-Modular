#include <stdio.h>
#include <string.h>

struct PosAnggaran
{
   char pos[100];
   long int BatasNominal;
};

/*Algoritma*/
struct PosAnggaran inputPosBaru() {
    struct PosAnggaran dataBaru;

    printf("Masukan nama pos anggaran:");
    fgets(dataBaru.pos, 100, stdin);
    dataBaru.pos[strcspn(dataBaru.pos, "\n")] = 0; 

    printf("Masukan batas nominal (misal 5000):");
    scanf("%ld", &dataBaru.BatasNominal);
    while (getchar() != '\n'); // Membersihkan buffer

    return dataBaru; // Mengembalikan data yang sudah jadi
}
