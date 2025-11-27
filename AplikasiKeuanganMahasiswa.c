//Aplikasi Keuangan Mahasiswa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 30 //Untuk membatasi jumlah transaksi dan jumlah pos Anggaran

//Struktur data variabel record
//=======================================================================
//Variabel record untuk menyimpan data-data input transaksi
struct transaksi {
	int nominal;
	char posAnggaran[20];
	int ID;
	char jenis[12];
	char deskripsi[50];
	char tanggal[11];
};
//=======================================================================

//=======================================================================
//Variabel record untuk menyimpan data-data pos anggaran
struct posAnggaran {
	int realisasi;
	int batasPengeluaran;
	char posAnggaran[20];
	char status[11];
	int totalTransaksi;
	int sisaAnggaran;
};
//=======================================================================

//Spesifikasi modul-modul
//============================================
//Procedure untuk menampilkan menu
//I.S. : Tidak ada tampilan menu di awal
//F.S. : Memiliki tampilan menu di awal
//============================================
void tampilMenu(){
	printf("\n===========Menu===========\n");
	printf("1. Tambah Data Transaksi\n");
	printf("2. Tampilkan Data Keuangan\n");
	printf("3. Keluar Program\n");
}
//============================================

//=======================================================================
//Procedure untuk memberikan nilai awal pada variabel record transaksi
//I.S. : Nilai untuk variabel bertipe transaksi masih kosong
//F.S. : Variabel bertipe transaksi sudah memiliki nilai awal
//=======================================================================
void inisialisasiTransaksi(struct transaksi transaksiMhs[], int indeks){
	//Loop untuk inisialisasi variabel struct bertipe transaksi
		int i;
		for (i = 0; i < indeks; i++){
		transaksiMhs[i].nominal = 0;
		transaksiMhs[i].ID = 0;
		strcpy(transaksiMhs[i].posAnggaran, "Kosong");
		strcpy(transaksiMhs[i].jenis, "Kosong");
		strcpy(transaksiMhs[i].deskripsi, "Kosong");
		strcpy(transaksiMhs[i].tanggal, "Kosong");
	}
}
//=======================================================================

//=============================================================================
//Procedure untuk memberikan nilai awal pada variabel record posAnggaran
//I.S. : Nilai untuk variabel bertipe posAnggaran masih kosong
//F.S. : Variabel bertipe posAnggaran sudah memiliki nilai awal
//=============================================================================
void inisialisasiPosAnggaran(struct posAnggaran posAnggaranMhs[], int indeks){
	int i;
	for (i = 0; i < indeks; i++){
		posAnggaranMhs[i].realisasi = 0;
		posAnggaranMhs[i].batasPengeluaran = 0;
		strcpy(posAnggaranMhs[i].posAnggaran, "Kosong");
		strcpy(posAnggaranMhs[i].status, "Kosong");
		posAnggaranMhs[i].totalTransaksi = 0;
		posAnggaranMhs[i].sisaAnggaran = 0;
	}
}
//=============================================================================

//Menampilkan menu untuk membuat pos anggaran
void tampilPosAnggaran(){
	printf("=========Buat Pos Anggaran=========");
	printf("\n1. Tambah pos anggaran");
	printf("\n2. Simpan pos anggaran");
}

//====================================================================================
//Procedure untuk memberikan nama pos anggaran di variabel record pos anggaran
//I.S. : Nama dari pos anggaran dari variabel struct bertipe posAnggaran masih kosong
//F.S. : Variabel struct bertipe posAnggaran telah berisi nama-nama pos anggaran
//====================================================================================
void golonganPosAnggaran(struct posAnggaran posAnggaranMhs[], int *varJmlPos){
	int i;
	int j;
	int duplikat;
		do {
			duplikat = 0;
			printf("Masukan nama pos anggaran : ");
			fgets(posAnggaranMhs[*varJmlPos].posAnggaran, sizeof(posAnggaranMhs[*varJmlPos].posAnggaran), stdin);
			for (j = 0; posAnggaranMhs[*varJmlPos].posAnggaran[j] != '\0'; j++) {
    			posAnggaranMhs[*varJmlPos].posAnggaran[j] = tolower(posAnggaranMhs[*varJmlPos].posAnggaran[j]);
			}
			posAnggaranMhs[*varJmlPos].posAnggaran[strcspn(posAnggaranMhs[*varJmlPos].posAnggaran, "\n")] = '\0';
			for (i = 0; i < *varJmlPos; i++){
				if (strcmp(posAnggaranMhs[*varJmlPos].posAnggaran, posAnggaranMhs[i].posAnggaran) == 0){
					printf("Pos Anggaran telah diinput sebelumnya. Coba lagi.\n");
					duplikat = 1;
				}
			}
		} while (duplikat == 1);
}
//====================================================================================

//===================================================================================================================================
//Procedure untuk input batas pengeluaran
//I.S. : Nominal batas pengeluaran untuk masing-masing pos anggaran pada variabel struct bertipe posAnggaran bernilai 0
//F.S. : Nominal batas pengeluaran untuk masing-masing pos anggaran pada variabel struct bertipe posAnggaran telah diinput oleh user
//===================================================================================================================================
void inputBatasPengeluaran(struct posAnggaran posAnggaranMhs[], int indeks){
	do {
		printf("Input batas Pengeluaran : ");
		scanf("%d", &posAnggaranMhs[indeks].batasPengeluaran);
		if (posAnggaranMhs[indeks].batasPengeluaran < 0){
			printf("Input tidak boleh kurang dari 0. Coba lagi.");
		}
	} while (posAnggaranMhs[indeks].batasPengeluaran < 0);
	
}
//===================================================================================================================================

//=======================================================================================
//Procedure untuk input jumlah transaksi
//I.S. : Jumlah transaksi belum diketahui
//F.S. : Jumlah transaksi telah diinput oleh user
//=======================================================================================
void inputjmlTransaksi(int *varJmlTransaksi, int *varlanjutTransaksi){
	do {
		printf("\nMasukkan jumlah aktivitas transaksi (MAX 30) : ");
		scanf("%d", varJmlTransaksi);
		while (getchar() != '\n');
		if (*varJmlTransaksi < 0 || *varJmlTransaksi > 30){
			printf("Input tidak boleh kurang dari 0 atau lebih dari 30! Coba lagi!\n\n");
		} else {
			*varlanjutTransaksi = *varJmlTransaksi; 
		}
	} while (*varJmlTransaksi < 0 || *varJmlTransaksi > 30);
}
//=======================================================================================

//=======================================================================================
//Procedure untuk mengisi tanggal
//I.S. : Tanggal pada variabel struct bertipe transaksi belum diketahui
//F.S. : Tanggal pada variabel struct bertipe transaksi telah diinput oleh user
//=======================================================================================
void inputTanggal(struct transaksi transaksiMhs[], int indeks){
	printf("\nMasukan tanggal transaksi (dd/mm/yyyy) : ");
	fgets(transaksiMhs[indeks].tanggal, sizeof(transaksiMhs[indeks].tanggal), stdin);
	while (getchar() != '\n');
}
//=======================================================================================

//=======================================================================================
//Procedure untuk menampilkan menu pos anggaran
//I.S. : Tampilan pilihan pos anggaran masih kosong
//F.S. : Menampilkan pilihan dari pos anggaran
//=======================================================================================
void tampilkanPosAnggaran(struct posAnggaran posAnggaranMhs[], int varJmlPos) {
    printf("=== PILIH POS ANGGARAN ===\n");
    printf("0. Pemasukan");
    int i = 0;
    while (i < varJmlPos){
    	printf("\n%d. %s, Batas Pengeluaran : %d", i + 1, posAnggaranMhs[i].posAnggaran, posAnggaranMhs[i].batasPengeluaran);
    	i++;
	}
}
//=======================================================================================

//============================================================================================================
//Procedure untuk input nama pos anggaran
//I.S. : Nama pos anggaran dari variabel struct bertipe transaksi masih kosong
//F.S. : Nama pos anggaran dari variabel struct bertipe transaksi telah diinput oleh user berdasarkan pilihan
//============================================================================================================
void inputPosAnggaran(struct transaksi transaksiMhs[], struct posAnggaran posAnggaranMhs[], int indeks, int varJmlPos){
	int pilihan;
	do {
		printf("\nPilih nomor pos anggaran : ");
		scanf("%d", &pilihan);
		getchar();
		if (pilihan == 0){
			strcpy(transaksiMhs[indeks].posAnggaran, "pemasukan");
		} 
		if (pilihan > 0 && pilihan < varJmlPos){
			strcpy(transaksiMhs[indeks].posAnggaran, posAnggaranMhs[pilihan - 1].posAnggaran);
		}
		if (pilihan < 0 || pilihan > varJmlPos){
			printf("Input tidak valid. Coba lagi.");
		}
	} while (pilihan < 0 || pilihan > varJmlPos);
	

    
}
//=======================================================================================

//=============================================================================================================
//Procedure untuk input jumlah nominal
//I.S. : Jumlah nominal untuk setiap transaksi dalam variabel struct bertipe transaksi belum diketahui
//F.S. : Jumlah nominal untuk setiap transaksi dalam variabel struct bertipe transaksi telah diinput oleh user
//=============================================================================================================
void inputNominal(struct transaksi transaksiMhs[], int indeks){
	int varNominal;
	do {
		printf("Masukkan jumlah nominal (jangan menggunakan titik/koma) : ");
		scanf("%d", &varNominal);
		while (getchar() != '\n');
		if (varNominal < 0){
			printf("Input tidak boleh kurang dari 0! Coba lagi!\n\n");
		}
	} while (varNominal < 0);
	transaksiMhs[indeks].nominal = varNominal;
}
//=============================================================================================================

//=========================================================================================================
//Procedure untuk menggolongkan jenis
//I.S. : Jenis-jenis dari setiap transaksi dalam variabel struct bertipe transaksi belum diketahui
//F.S. : Jenis-jenis dari setiap transaksi dalam variabel struct bertipe transaksi telah diklasifikasikan
//=========================================================================================================
void cekJenisTransaksi(struct transaksi transaksiMhs[], int indeks){
	if (strcmp(transaksiMhs[indeks].posAnggaran, "pemasukan") == 0){
		strcpy(transaksiMhs[indeks].jenis, "Pemasukan");
	} else {
		strcpy(transaksiMhs[indeks].jenis, "Pengeluaran");
	}
}
//=========================================================================================================

//=========================================================================================================
//Procedure untuk memberikan deskripsi transaksi
//I.S. : Deskripsi dari setiap transaksi dalam variabel struct bertipe transaksi tidak diketahui
//F.S. : Deskripsi dari setiap transaksi dalam variabel struct bertipe transaksi telah diinput oleh user
//=========================================================================================================
void deskripsiTransaksi(struct transaksi transaksiMhs[], int indeks){
	char varDeskripsi[100];
	printf("Deskripsi dari transaksi : ");
	fgets(varDeskripsi, sizeof(varDeskripsi), stdin);
	varDeskripsi[strcspn(varDeskripsi, "\n")] = '\0';
	strcpy(transaksiMhs[indeks].deskripsi, varDeskripsi);
}
//=========================================================================================================

//===========================================================================================================================
//Procedure untuk memberikan nomor ID setiap transaksi
//I.S. : Nomor ID untuk setiap transaksi dalam variabel struct bertipe record belum diketahui
//F.S. : Nomor ID untuk setiap transaksi dalam variabel struct bertipe record telah diisi secara beurutan mulai dari angka 1
//==========================================================================================================================
void IDTransaksi(struct transaksi transaksiMhs[], int indeks){
	transaksiMhs[indeks].ID = indeks + 1;
}
//==========================================================================================================================

//================================================================================================================================================
//Procedure untuk menghitung jumlah transaksi yang dilakukan oleh masing-masing pos anggaran
//I.S. : Jumlah aktivitas transaksi masing-masing pos anggaran berjumlah 0
//F.S. : Jumlah aktivitas transaksi masing-masing pos anggaran berjumlah sesuai dengan jumlah aktivitas transaksi dari pos anggaran masing-masing
//================================================================================================================================================
void jmlTransaksiPos(struct posAnggaran posAnggaranMhs[], int varJmlPos, struct transaksi transaksiMhs[], int indeks){
	int i;
	for (i = 0; i < varJmlPos; i++){
		if (strcmp(posAnggaranMhs[i].posAnggaran, transaksiMhs[indeks].posAnggaran) == 0){
			posAnggaranMhs[i].totalTransaksi = posAnggaranMhs[i].totalTransaksi + 1;
		}
	}
} 
//================================================================================================================================================

//======================================================================================================================================================
//Fungsi untuk menghitung realisasi anggaran pengeluaran dari masing-masing pos Anggaran pengeluaran
//Input1 : Nilai dari variabel struct bertipe transaksi dengan subvariabel yaitu posAnggaran
//Input2 : Nilai dari variabel struct bertipe posAnggaran dengan subvariabel yaitu nominal
//Output : Nilai dari variabel struct bertipe posAnggaran dengan subvariabel yaitu realisasi yaitu hasil penjumlahan nominal masing-masing pos anggaran
//======================================================================================================================================================
int hitungRealisasiPengeluaran(struct transaksi transaksiMhs[], int indeks, struct posAnggaran posAnggaranMhs[], int varJmlPos){
	int i;
	for (i = 0; i < varJmlPos; i++){
		if (strcmp(transaksiMhs[indeks].posAnggaran, posAnggaranMhs[i].posAnggaran) == 0){
			posAnggaranMhs[i].realisasi = posAnggaranMhs[i].realisasi + transaksiMhs[indeks].nominal;
		}
	}
	return 1;
}
//======================================================================================================================================================

//============================================================================================================
//Fungsi untuk menjumlahkan total pemasukan
//Input1 : Nilai nominal pemasukan yang tersimpan dalam variabel struct bertipe transaksi bernama transaksiMhs
//Input2 : Nilai dari parameter varTotalPemasukan
//Output : Hasil Penjumlahan dari dari keseluruhan nominal pemasukan dari variabel struct bertipe transaksi
//============================================================================================================
int jumlahTotalPemasukan(struct transaksi transaksiMhs[], int indeks, int varTotalPemasukan){
	if (strcmp(transaksiMhs[indeks].jenis, "Pemasukan") == 0){
		varTotalPemasukan = varTotalPemasukan + transaksiMhs[indeks].nominal;
	}
	return varTotalPemasukan;
}
//============================================================================================================

//==============================================================================================================
//Fungsi untuk menjumlahkan total pengeluaran
//Input1 : Nilai nominal pengeluaran yang tersimpan dalam variabel struct bertipe transaksi bernama transaksiMhs
//Input2 : Nilai dari parameter varTotalPemasukan
//Output : Hasil Penjumlahan dari dari keseluruhan nominal pengeluaran dari variabel struct bertipe transaksi
//==============================================================================================================
int jumlahTotalPengeluaran(struct transaksi transaksiMhs[], int indeks, int varTotalPengeluaran){
	if (strcmp(transaksiMhs[indeks].jenis, "Pengeluaran") == 0){
		varTotalPengeluaran = varTotalPengeluaran + transaksiMhs[indeks].nominal;
	}
	return varTotalPengeluaran;
}
//==============================================================================================================

//===============================================================================================
//Fungsi untuk menghitung saldo akhir
//Input1 : Nilai dari parameter varTotalPemasukan
//Input2 : Nilai dari parameter varTotalPengeluaran
//Output : Nilai varSaldoAkhir hasil pengurangan varTotalPemasukan dikurang varTotalPengeluaran
//===============================================================================================
int jumlahSaldoAkhir(int varTotalPemasukan, int varTotalPengeluaran){
	int varSaldoAkhir = varTotalPemasukan - varTotalPengeluaran; 
	//varTotalPemasukan tidak boleh lebih kecil dari varTotalPengeluaran
	if (varSaldoAkhir < 0){
		printf("Sisa saldo tidak boleh kurang dari 0!\n");
	}
	return varSaldoAkhir;
}
//===============================================================================================

//=================================================================================================================
//Fungsi untuk menghitung rata-rata pengeluaran per transaksi
//Input1 : Nilai dari parameter varTotalPengeluaran
//Input2 : Nilai dari parameter varJmlTransaksi
//Output : Nilai varRataPengeluaran yaitu rata-rata hasil pembagian varTotalPengeluaran dibagi varTotalPengeluaran
//=================================================================================================================
int rataRataPengeluaran(int varTotalPengeluaran, int varJmlTransaksi){
	float varRataPengeluaran;
	varRataPengeluaran = (varTotalPengeluaran / varJmlTransaksi);
	return varRataPengeluaran;
}
//=================================================================================================================

//======================================================================================
//Fungsi untuk menghitung persentase sisa terhadap pemasukan
//Input1 : Nilai dari parameter varSaldoAkhir
//Input2 : Nilai dari parameter varTotalPemasukan
//Output : Nilai varPersentaseSisa yaitu persentase sisa dari saldo terhadap pemasukan
//======================================================================================
float persentaseSisa(int varSaldoAkhir, int varTotalPemasukan){
	float varPersentaseSisa;
	varPersentaseSisa = (((float)varSaldoAkhir / varTotalPemasukan) * 100);
	return varPersentaseSisa;
}
//======================================================================================

//=====================================================================================================================
//Fungsi untuk menghitung jumlah transaksi pemasukan
//Input1 : Nilai dari variabel struct bertipe transaksi dengan subvariabel yaitu jenis
//Output : Nilai totalTransaksiPemasukan akan terus bertambah jika untuk setiap jenis transaksi sama dengan pemasukan
//=====================================================================================================================
int jumlahTransaksiPemasukan(struct transaksi transaksiMhs[], int indeks, int varJmlTransaksiMasuk){
		if (strcmp(transaksiMhs[indeks].jenis, "Pemasukan") == 0){
			varJmlTransaksiMasuk = varJmlTransaksiMasuk + 1;
		}
	return varJmlTransaksiMasuk;
}
//=====================================================================================================================

//=====================================================================================================================
//Fungsi untuk menghitung jumlah transaksi pengeluaran
//Input1 : Nilai dari variabel struct bertipe transaksi dengan subvariabel yaitu jenis
//Output : Nilai totalTransaksiPemasukan akan terus bertambah jika untuk setiap jenis transaksi sama dengan pemasukan
//=====================================================================================================================
int jumlahTransaksiPengeluaran(struct transaksi transaksiMhs[], int indeks, int varJmlTransaksiKeluar){
	if (strcmp(transaksiMhs[indeks].jenis, "Pengeluaran") == 0){
			varJmlTransaksiKeluar = varJmlTransaksiKeluar + 1;
		}
	return varJmlTransaksiKeluar;
}
//=====================================================================================================================

//=====================================================================================================
//Fungsi untuk menghitung sisa anggaran berdasarkan batas nominal untuk masing-masing pos anggaran
//Input1 : Nilai dari variabel struct bertipe posAnggaran dengan subvariabel batasPengeluaran
//Input2 : Nilai dari variabel struct bertipe posAnggaran dengan subvariabel realisasi
//Output : Nilai dari variabel struct bertipe posAnggaran dengan subvariabel sisaAnggaran
//=====================================================================================================
int hitungSisaAnggaran(struct posAnggaran posAnggaranMhs[], int varJmlPos){
	int i;
	for (i = 0; i < varJmlPos; i++){
			posAnggaranMhs[i].sisaAnggaran = posAnggaranMhs[i].batasPengeluaran - posAnggaranMhs[i].realisasi;
	}
	return 1;
}
//=====================================================================================================

//======================================================================================================================================================
//Procedure untuk menentukan status pengeluaran dari masing-masing pos anggaran
//I.S. : Isi dari variabel struct bertipe posAnggaran dengan subvariabel yaitu status masih bernilai kosong
//F.S. : Isi dari variabel struct bertipe posAnggaran dengan subvariabel yaitu status berubah nilai menjadi aman atau tidak aman tergantung pengeluaran
//======================================================================================================================================================
void cekStatus(struct posAnggaran posAnggaranMhs[]){
	if (posAnggaranMhs[0].realisasi > posAnggaranMhs[0].batasPengeluaran){
		strcpy(posAnggaranMhs[0].status, "Tidak Aman");
	} else {
		strcpy(posAnggaranMhs[0].status, "Aman");
	}
	if (posAnggaranMhs[1].realisasi > posAnggaranMhs[1].batasPengeluaran){
		strcpy(posAnggaranMhs[1].status, "Tidak Aman");
	} else {
		strcpy(posAnggaranMhs[1].status, "Aman");
	}
	if (posAnggaranMhs[2].realisasi > posAnggaranMhs[2].batasPengeluaran){
		strcpy(posAnggaranMhs[2].status, "Tidak Aman");
	} else {
		strcpy(posAnggaranMhs[2].status, "Aman");
	}
	if (posAnggaranMhs[3].realisasi > posAnggaranMhs[3].batasPengeluaran){
		strcpy(posAnggaranMhs[3].status, "Tidak Aman");
	} else {
		strcpy(posAnggaranMhs[3].status, "Aman");
	}
	if (posAnggaranMhs[4].realisasi > posAnggaranMhs[4].batasPengeluaran){
		strcpy(posAnggaranMhs[4].status, "Tidak Aman");
	} else {
		strcpy(posAnggaranMhs[4].status, "Aman");
	}
}
//======================================================================================================================================================

//==========================================================================================================================
//Procedure untuk menentukan kondisi keuangan mahasiswa secara keseluruhan
//I.S. : Kondisi keuangan dari variabel string kondisiKeuangan belum diketahui
//F.S. : Kondisi keuangan dari variabel string kondisiKeuangan telah ditentukan berdasarkan nilai parameter varSaldoAkhir
//==========================================================================================================================
void cekKondisiTotal(int varSaldoAkhir, char kondisiKeuangan[]){
	if (varSaldoAkhir > 0){
		strcpy(kondisiKeuangan, "Surplus");
	}
	if (varSaldoAkhir == 0){
		strcpy(kondisiKeuangan, "Seimbang");
	}
	if (varSaldoAkhir < 0){
		strcpy(kondisiKeuangan, "Defisit");
	}
}
//==========================================================================================================================

//=========================================================================================================================================
//Procedure untuk menampilkan hasil rekap transaksi keuangan
//I.S. : Layar tidak menampilkan struktur laporan keuangan
//F.S. : Layar menampilkan struktur laporan keuangan
//=========================================================================================================================================
void TampilRekap(FILE *fp, int varJmlTransaksiMasuk, int varJmlTransaksiKeluar, int varTotalPemasukan, int varTotalPengeluaran, int varSaldoAkhir, float varRataPengeluaran) {
    //Data akan ditampilkan di layar
	printf("\n\n========================================= LAPORAN KEUANGAN BULAN NOVEMBER 2025 =========================================\n");
    printf("Total Pemasukan    (%d Transaksi) : Rp %d\n", varJmlTransaksiMasuk, varTotalPemasukan);
    printf("Total Pengeluaran  (%d Transaksi) : Rp %d\n", varJmlTransaksiKeluar, varTotalPengeluaran);
    printf("Saldo Akhir             	 : Rp %d\n", varSaldoAkhir);
    printf("Rata - rata pengeluaran 	 : Rp %.2f per transaksi\n", varRataPengeluaran);
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
	
	//Data akan diinput ke file
	fprintf(fp, "\n========================================= LAPORAN KEUANGAN BULAN NOVEMBER 2025 =========================================\n");
    fprintf(fp, "Total Pemasukan    (%d Transaksi) : Rp %d\n", varJmlTransaksiMasuk, varTotalPemasukan);
    fprintf(fp, "Total Pengeluaran  (%d Transaksi) : Rp %d\n", varJmlTransaksiKeluar, varTotalPengeluaran);
    fprintf(fp, "Saldo Akhir             	 : Rp %d\n", varSaldoAkhir);
    fprintf(fp, "Rata - rata pengeluaran 	 : Rp %.2f per transaksi\n", varRataPengeluaran);
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------\n");
}
//=========================================================================================================================================

//=============================================================================================================================================================================================
//Procedure untuk menampilkan tabel laporan keuangan
//I.S. : layar tidak menampilkan tabel laporan keuangan
//F.S. : layar menampilkan tabel laporan keuangan
//=============================================================================================================================================================================================
void TampilTabel(FILE *fp, struct posAnggaran posAnggaranMhs[], int varSaldoAkhir, int varJmlPos ) {
    int i;
    //Data akan ditampilkan di layar
    printf("\nPOS ANGGARAN\n");
    printf("%-15s | %-12s | %-12s | %-10s | %-8s | %-10s\n", "Pos", "Batas(RP)", "Realisasi(RP)", "Jumlah Transaksi", "Sisa(Rp)", "Status");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < varJmlPos; i++) {
        printf("%-15s | %-12d | %-13d | %-16d | %-9d | %-10s\n", 
        posAnggaranMhs[i].posAnggaran, posAnggaranMhs[i].batasPengeluaran, posAnggaranMhs[i].realisasi, posAnggaranMhs[i].totalTransaksi, posAnggaranMhs[i].sisaAnggaran, posAnggaranMhs[i].status);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    
    //Data akan diinput ke file
    fprintf(fp, "\nPOS ANGGARAN\n");
    fprintf(fp, "%-15s | %-12s | %-12s | %-10s | %-8s | %-10s\n", "Pos", "Batas(RP)", "Realisasi(RP)", "Jumlah Transaksi", "Sisa(Rp)", "Status");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < varJmlPos; i++) {
        fprintf(fp, "%-15s | %-12d | %-13d | %-16d | %-9d | %-10s\n", 
        posAnggaranMhs[i].posAnggaran, posAnggaranMhs[i].batasPengeluaran, posAnggaranMhs[i].realisasi, posAnggaranMhs[i].totalTransaksi, posAnggaranMhs[i].sisaAnggaran, posAnggaranMhs[i].status);
    }
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------\n");
}
//=============================================================================================================================================================================================

//===================================================================================================================
//Procedure untuk menuliskan kesimpulan terhadap kondisi keseluruhan keuangan mahasiswa
//I.S. : Kesimpulan terhadap kondisi keuangan mahasiswa tidak diketahui
//F.S. : Kesimpulan terhadap kondisi keuangan mahasiswa telah ditulis dan ditampilkan dilayar
//===================================================================================================================
void kesimpulanKondisi(FILE *fp, int varSaldoAkhir, int varTotalPemasukan){
	//Data akan ditampilkan di layar
	if (varSaldoAkhir > (0.25 * varTotalPemasukan)){
		printf("\nKesimpulan	 : Anda termasuk mahasiswa hemat dan produktif.");
	}
	if (varSaldoAkhir > 0 && varSaldoAkhir < (0.25 * varTotalPemasukan)){
		printf("\nKesimpulan	 : Keuangan anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.");
	}
	if (varSaldoAkhir > (-0.10 * varTotalPemasukan) && varSaldoAkhir <= 0){
		printf("\nkesimpulan	 : Anda mulai boros, perhatikan pengeluaran harian.");
	}
	if (varSaldoAkhir <= (-0.10 * varTotalPemasukan)){
		printf("\nKesimpulan	 : Kondisi keuangan kurang sehat. Kurangi pengeluaran dan cari tambahan pemasukan");
	}
	
	//Data akan diinput ke file
	if (varSaldoAkhir > (0.25 * varTotalPemasukan)){
		fprintf(fp, "\nKesimpulan	 : Anda termasuk mahasiswa hemat dan produktif.");
	}
	if (varSaldoAkhir > 0 && varSaldoAkhir < (0.25 * varTotalPemasukan)){
		fprintf(fp, "\nKesimpulan	 : Keuangan anda seimbang, tetap waspada terhadap pengeluaran tidak perlu.");
	}
	if (varSaldoAkhir > (-0.10 * varTotalPemasukan) && varSaldoAkhir <= 0){
		fprintf(fp, "\nkesimpulan	 : Anda mulai boros, perhatikan pengeluaran harian.");
	}
	if (varSaldoAkhir <= (-0.10 * varTotalPemasukan)){
		fprintf(fp, "\nKesimpulan	 : Kondisi keuangan kurang sehat. Kurangi pengeluaran dan cari tambahan pemasukan");
	}
}
//===================================================================================================================

//Variabel Global
int transaksiGlobal;
//Program Utama
int main(){
	
	//Deklarasi
	struct transaksi transaksiMhs[MAX];
	struct posAnggaran posAnggaranMhs[MAX];
	int lanjutTransaksi = 0;
	int jmlPos = 0;
	int nomorMenu;
	int nomor;
	int jmlTransaksi = 0;
	int totalPemasukan = 0;
	int totalPengeluaran = 0;
	int saldoAkhir;
	int jmlTransaksiMasuk = 0;
	int jmlTransaksiKeluar = 0;
	int i;
	char kondisi[9];
	char kondisiKeuangan[9];
	float persenSisa;
	float rataPengeluaran = 0;
	
	//Inisialisasi data transaksi
	inisialisasiTransaksi(transaksiMhs, 30);
	inisialisasiPosAnggaran(posAnggaranMhs, 30);
	
	//Menampilkan pilihan menu
	do {
		tampilMenu();
		printf("Pilih Nomor Menu : ");
		scanf("%d", &nomorMenu);
		printf("\n");
		switch (nomorMenu) {
			case 1:
				//Menginput nama pos anggaran dan batas pengeluaran di variabel record posAnggaran
				do {
					tampilPosAnggaran();
					printf("\nPilih Nomor : ");
					scanf("%d", &nomor);
					getchar();
					switch (nomor) {
						case 1:
							if (jmlPos < MAX){
								golonganPosAnggaran(posAnggaranMhs, &jmlPos);
								inputBatasPengeluaran(posAnggaranMhs, jmlPos);
								jmlPos++;
							} else {
								printf("Kapasitas pos anggaran penuh!\n");
							}
							break;
						case 2:
							printf("\nPos anggaran telah disimpan.\n\n");
							tampilkanPosAnggaran(posAnggaranMhs, jmlPos);
							break;
						default:
							printf("Pilihan tidak valid. Coba lagi.\n");
					}
					printf("\n");	
				} while (nomor != 2);
	
				//Input jumlah transaksi yang dilakukan
				inputjmlTransaksi(&jmlTransaksi, &lanjutTransaksi);
				if (jmlTransaksi == 0){
					printf("Tidak ada transaksi.");
					return 0; //Program langusng berakhir karena tidak ada transaksi
				}
				
				//Mengisi data di variabel record keuangan mahasiswa
				for (i = 0; i < jmlTransaksi; i++){
					//input transaksi
					inputTanggal(transaksiMhs, i);
					tampilkanPosAnggaran(posAnggaranMhs, jmlPos);
					inputPosAnggaran(transaksiMhs, posAnggaranMhs, i, jmlPos);
					inputNominal(transaksiMhs, i);
					cekJenisTransaksi(transaksiMhs, i); 									//Menggolongkan jenis transaksi (pemasukan/pengeluaran)
					deskripsiTransaksi(transaksiMhs, i); 									//Memberikan deskripsi untuk setiap transaksi
					IDTransaksi(transaksiMhs, i); 											//Memberikan nomor ID untuk setiap transaksi
					
					hitungRealisasiPengeluaran(transaksiMhs, i, posAnggaranMhs, jmlPos); 	//Menghitung realisasi nominal masing-masing pos anggaran
					jmlTransaksiPos(posAnggaranMhs, jmlPos, transaksiMhs, i); 				//Menghitung jumlah transaksi yang dilakukan oleh masing-masing pos anggaran
				}
	
				//Perhitungan total nominal masing masing jenis transkasi keuangan
				for (i = 0; i < jmlTransaksi; i++){
					totalPemasukan = jumlahTotalPemasukan(transaksiMhs, i, totalPemasukan);
					totalPengeluaran = jumlahTotalPengeluaran(transaksiMhs, i, totalPengeluaran);
					jmlTransaksiMasuk = jumlahTransaksiPemasukan(transaksiMhs, i, jmlTransaksiMasuk); 		//Menghitung jumlah aktivitas transaski pemasukan
					jmlTransaksiKeluar = jumlahTransaksiPengeluaran(transaksiMhs, i, jmlTransaksiKeluar); 	//Menghitung jumlah aktivitas transaksi pengeluaran
				}
	
				saldoAkhir = jumlahSaldoAkhir(totalPemasukan, totalPengeluaran); 				//Menghitung saldo akhir
				rataPengeluaran = rataRataPengeluaran(totalPengeluaran, jmlTransaksi); 			//Menghitung rata-rata Pengeluaran per transaksi
				persenSisa = persentaseSisa(saldoAkhir, totalPemasukan); 						//Menghitung persentase sisa terhadap pemasukan
				hitungSisaAnggaran(posAnggaranMhs, jmlPos); 									//Menghitung sisa anggaran berdasarkan berdasarkan batas pengeluaran dari masing-masing pos anggaran
				cekStatus(posAnggaranMhs); 														//Mengecek status untuk setiap sisa anggaran dari masing-masing pos anggaran
				cekKondisiTotal(saldoAkhir, kondisiKeuangan); 									//Menentukan kondisi total keuangan mahasiswa
				jmlTransaksi = jmlTransaksi + lanjutTransaksi;
	
				break;
			case 2:
				printf("\nJumlah transaksi dalam 1 bulan : %d\n", jmlTransaksi);
				for (i = 0; i < jmlTransaksi; i++){
					if (transaksiMhs[i].ID > 9){
						printf("\nID = T0%d\n", transaksiMhs[i].ID);
					} else {
						printf("\nID = T00%d\n", transaksiMhs[i].ID);
					}
					printf("Tanggal = %s", transaksiMhs[i].tanggal);
					printf("\nPos Anggaran = %s\n", transaksiMhs[i].posAnggaran);
					printf("Nominal = %d\n", transaksiMhs[i].nominal);
					printf("Jenis = %s\n", transaksiMhs[i].jenis);
					printf("Deskripsi = %s\n", transaksiMhs[i].deskripsi);
				}
				printf("\nTotal pemasukan : %d", totalPemasukan);
				printf("\nTotal pengeluaran : %d", totalPengeluaran);
				printf("\nTotal saldo akhir : %d", saldoAkhir);
				printf("\nRata-rata pengeluaran per transaksi : %.2f", rataPengeluaran);
				if (totalPemasukan == 0){
					printf("\nPersentase sisa terhadap pemasukan : tidak valid!");
				} else if (totalPemasukan > 0){
					printf("\nPersentase sisa terhadap pemasukan : %.2f%%", persenSisa);
				}
				printf("\nJumlah transaksi pemasukan : %d", jmlTransaksiMasuk);
				printf("\nJumlah transaksi pengeluaran : %d", jmlTransaksiKeluar);
	
				//Menginput hasil rekapan transaksi keuangan ke dalam file
				FILE *fp = fopen("Keuangan.txt", "w");
				if (fp == NULL) {
   					printf("Gagal membuka file!\n");
    				exit(1);
				} else {
					TampilRekap(fp, jmlTransaksiMasuk, jmlTransaksiKeluar, totalPemasukan, totalPengeluaran, saldoAkhir, rataPengeluaran); 	//Menampilkan total pemasukan, total pengeluaran, saldo akhir, dan rata-rata pengeluaran
					TampilTabel(fp, posAnggaranMhs, saldoAkhir, jmlPos); 																	//Menampilkan tabel berisi data-data dari variabel struct bertipe posAnggaran
					printf("Kondisi Keuangan : %s (Sisa %.2f%% dari total pemasukan)", kondisiKeuangan, persenSisa);
					fprintf(fp, "Kondisi Keuangan : %s (Sisa %.2f%% dari total pemasukan)", kondisiKeuangan, persenSisa);
					kesimpulanKondisi(fp, saldoAkhir, totalPemasukan); 																		//Menentukan kesimpulan berdasarkan kondisi keuangan mahasiswa 
				}
				fclose(fp);
				break;
			case 3:
				printf("Keluar dari program...\n");
				break;
			default:
				printf("Pilihan tidak valid!\n");
		}
	} while (nomorMenu != 3);
	
	return 0;
}


