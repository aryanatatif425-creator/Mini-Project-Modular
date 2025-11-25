#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// ============================================================================
// 1. MODUL DATA (DATABASE)
// ============================================================================
typedef struct {
    char pos[100];
    int Batas;
    int Realisasi;
    int JumlahTransaksi;
} LayoutPosAnggaran;

// Data Mentah (Transaksi Pos Anggaran)
LayoutPosAnggaran Cetakan1[5] = {
    {"Makan", 60000, 35000, 5},
    {"Transportasi", 45000, 7000, 6},
};
int JumlahData = 2;

// VARIABEL GLOBAL 
int TotalPemasukan;
int TotalPengeluaran;
int SaldoAkhir;
float RataRata;
float PersentaseSisa;

// ============================================================================
// 2. MODUL INPUT (Tugas: Minta Data User)
// ============================================================================
void InputData() {
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf(" SETUP DATA AWAL \n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("Masukkan total pemasukan (RP) : ");
    scanf("%d", &TotalPemasukan); // Mengisi variabel TotalPemasukan
}

// ============================================================================
// 3. MODUL PROSES / LOGIC (Tugas: Menghitung Matematika)
//    Fungsi mengisi variabel TotalPengeluaran, SaldoAkhir, RataRata, PersentaseSisa
// ============================================================================
void HitungSemuaData() {
    int i;
    int totalTrx = 0;
    
    // Reset nilai ke 0 dulu suapaya aman
    TotalPengeluaran = 0; 
    
    // 1. Hitung Total Pengeluaran & Jumlah Transaksi dari Array
    for (i = 0; i < JumlahData; i++) {
        TotalPengeluaran = TotalPengeluaran + Cetakan1[i].Realisasi;
        totalTrx = totalTrx + Cetakan1[i].JumlahTransaksi;
    }

    // 2. Hitung Saldo Akhir
    SaldoAkhir = TotalPemasukan - TotalPengeluaran;

    // 3. Hitung Rata-rata 
    if (totalTrx > 0) {
        RataRata = (float)TotalPengeluaran / totalTrx;
    } else {
        RataRata = 0;
    }

    // 4. Hitung Persentase Sisa 
    if (TotalPemasukan > 0) {
        PersentaseSisa = ((float)abs(SaldoAkhir) / TotalPemasukan) * 100;
    } else {
        PersentaseSisa = 0;
    }
}

// ============================================================================
// 4. MODUL OUTPUT / TAMPILAN (Tugas: Menampilkan Laporan)
// ============================================================================

void TampilRekap() {
    // Cuma menampilkan ajah
    printf("\n========================================= LAPORAN KEUANGAN BULAN NOVEMBER 2025 =========================================\n");
    printf("Total Pemasukan         : Rp %d\n", TotalPemasukan);
    printf("Total Pengeluaran       : Rp %d\n", TotalPengeluaran);
    printf("Saldo Akhir             : Rp %d\n", SaldoAkhir);
    printf("Rata - rata pengeluaran : Rp %.2f per transaksi\n", RataRata);
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
}

void TampilTabel() {
    int i;
    printf("\nPOS ANGGARAN\n");
    printf("%-15s | %-12s | %-12s | %-10s | %-8s | %-10s\n", "Pos", "Batas(RP)", "Realisasi(RP)", "Jml Trx", "Sisa(Rp)", "Status");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < JumlahData; i++) {
        // Logika kecil tampilan per baris
        int sisa = Cetakan1[i].Batas - Cetakan1[i].Realisasi;
        char *status = (sisa >= 0) ? "Aman" : "Tidak aman";

        printf("%-15s | %-12d | %-12d | %-10d | %-8d | %-10s\n", 
               Cetakan1[i].pos, Cetakan1[i].Batas, Cetakan1[i].Realisasi, Cetakan1[i].JumlahTransaksi, sisa, status);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
}

void TampilAnalisis() {
    printf("Kondisi keuangan : ");

    // Menampilkan Status berdasarkan SaldoAkhir
    if (SaldoAkhir > 0) {
        printf("SURPLUS (sisa %.2f%% dari total pemasukan)\n", PersentaseSisa);
    } else if (SaldoAkhir == 0) {
        printf("SEIMBANG (0%%)\n");
    } else {
        printf("DEFISIT (Minus %.2f%%)\n", PersentaseSisa);
    }
    
    printf("Kesimpulan       : ");

    // Menampilkan Kesimpulan berdasarkan SaldoAkhir & PersentaseSisa
    if (SaldoAkhir > 0) {     
        if (PersentaseSisa > 25) {
            printf("Anda termasuk mahasiswa hemat dan produktif.\n");
            printf("                   Pengeluaran masih jauh di bawah batas anggaran.\n");
            printf("                   Kondisi keuangan bulan ini sangat sehat.\n");
        } else {
            printf("Keuangan Anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.\n");
        }
    } else {
        if (PersentaseSisa < 10) {
            printf("Anda mulai boros, perhatikan pengeluaran harian.\n");
        } else {
            printf("Kondisi keuangan kurang sehat. Kurangi pengeluaran.\n");
        }
    }
    printf("====================================================================================================================\n");
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================
int main() {
    // 1. TUGAS INPUT
    InputData();

    // 2. TUGAS PROSES (Hitung Matematika di belakang layar)
    HitungSemuaData(); 

    // 3. BERSIHKAN LAYAR
    system("cls"); 

    // 4. TUGAS OUTPUT (Tampilkan Hasil)
    TampilRekap();
    TampilTabel();
    TampilAnalisis();

    // Tahan layar
    getchar(); 
    getchar(); 
    return 0;
}