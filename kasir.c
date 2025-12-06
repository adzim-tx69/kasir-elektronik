#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

int kode, harga, qty, i = 1;
int total_pembelian = 0, diskon = 0, total_bayar, bayar, kembalian;
char kar = 'y';

char nama_barang[100][50];
int harga_barang[100];
int jumlah_barang[100];
int jumlah_beli = 0;

int stok[10] = {
    20, 50, 30, 40, 25, 35, 60, 15
};

char *namaList[] = {
    "KAPASITOR","RESISTOR","INDUKTOR","DIODA",
    "TRANSISTOR","IC","SAKLAR","TRANSFORMATOR"
};

int hargaList[] = {35000,10000,30000,15000,70000,50000,10000,85000};

printf("\t\t\t\t===============================================\n");
printf("\t\t\t\t||         NAMA KELOMPOK KING KOPLO          ||\n");
printf("\t\t\t\t|| -MUHAMMAD NUR ADZIM           -411251100  ||\n");
printf("\t\t\t\t|| -IHSAN IBNU ABDURRAUF         -41125111   ||\n");
printf("\t\t\t\t|| -DICKY FACHRIE RHAMADHAN      -411251097  ||\n");
printf("\t\t\t\t|| -MUHAMMAD RAYA PUTRA ELIZHA   -411251116  ||\n");

printf("\t\t\t\t===============================================\n");
printf("\t\t\t\t||       SELAMAT DATANG DI TOKO KANG UCUP    ||\n");
printf("\t\t\t\t||           SEDIA BERBAGAI KOMPONEN         ||\n");
printf("\t\t\t\t||                 ELEKTRONIKA               ||\n");
printf("\t\t\t\t===============================================\n\n");

// ===================== DAFTAR BARANG ==========================
printf("----------------------------------------------------------------\n");
printf("                          DAFTAR BARANG\n");
printf("----------------------------------------------------------------\n");
printf("No   Kode     Nama Barang        Harga        Stok\n");
printf("----------------------------------------------------------------\n");

for (int s = 0; s < 8; s++) {
    printf("%-4d %-8.3d %-18s Rp. %-10d %d\n",
        s + 1,
        s + 1,
        namaList[s],
        hargaList[s],
        stok[s]);
}

printf("----------------------------------------------------------------\n\n");

// ===================== PEMBELIAN ==========================
while (kar == 'y') {

    printf("Masukkan No Barang yang dibeli : ");
    scanf("%d", &kode);

    int index = kode - 1;

    if (kode < 1 || kode > 8) {
        printf("Input kode salah!\n");
        continue;
    }

    strcpy(nama_barang[jumlah_beli], namaList[index]);
    harga = hargaList[index];

    printf("Harga %s = Rp. %d\n", nama_barang[jumlah_beli], harga);

    printf("Jumlah yang dibeli : ");
    scanf("%d", &qty);

    if (qty > stok[index]) {
        printf("⚠️  Stok %s tinggal %d saja!\n\n", nama_barang[jumlah_beli], stok[index]);
        continue;
    }

    // kurangi stok
    stok[index] -= qty;

    int subtotal = harga * qty;
    total_pembelian += subtotal;

    harga_barang[jumlah_beli] = subtotal;
    jumlah_barang[jumlah_beli] = qty;

    jumlah_beli++;

    printf("Mau beli barang lain? (y/t) : ");
    scanf(" %c", &kar);
    printf("\n");

    i++;
}

// ===================== PEMBAYARAN ==========================
printf("=============================================================\n");
printf("%-22s = Rp. %-10d\n", "TOTAL PEMBELIAN", total_pembelian);

if (total_pembelian > 200000) {
    diskon = 0.1 * total_pembelian;
    total_bayar = total_pembelian - diskon;
    printf("%-22s = Rp. %-10d\n", "DISKON", diskon);
} else {
    total_bayar = total_pembelian;
}

printf("%-22s = Rp. %-10d\n", "TOTAL BAYAR", total_bayar);

printf("%-22s = Rp. ", "Masukkan uang bayar");
scanf("%d", &bayar);

kembalian = bayar - total_bayar;

if (bayar >= total_bayar)
    printf("%-22s = Rp. %-10d\n", "UANG KEMBALIAN", kembalian);
else
    printf("%-22s = Rp. %-10d\n", "UANG KURANG", total_bayar - bayar);

// ===================== STRUK BELANJA ==========================
printf("\n=================== STRUK BELANJA ===================\n");
printf("No   Nama Barang           Qty     Subtotal\n");
printf("-----------------------------------------------------\n");

for (int a = 0; a < jumlah_beli; a++) {
    printf("%-5d %-20s %-7d Rp. %d\n",
        a + 1,
        nama_barang[a],
        jumlah_barang[a],
        harga_barang[a]);
}

printf("-----------------------------------------------------\n");
printf("%-20s = Rp. %d\n", "TOTAL PEMBELIAN", total_pembelian);
if (diskon > 0)
    printf("%-20s = Rp. %d\n", "DISKON", diskon);

printf("%-20s = Rp. %d\n", "TOTAL BAYAR", total_bayar);
printf("%-20s = Rp. %d\n", "UANG BAYAR", bayar);
printf("%-20s = Rp. %d\n", "KEMBALIAN", kembalian);

printf("=================================================================\n");
printf("          TERIMA KASIH SUDAH BERBELANJA DITOKO KAMI !\n");
printf("=================================================================\n");

// ===================== SISA STOK ==========================
printf("\n=================== SISA STOK BARANG ===================\n");
printf("Kode  Nama Barang         Sisa Stok\n");
printf("--------------------------------------------------------\n");

for (int s = 0; s < 8; s++) {
    printf("%-5d %-20s %d\n", s + 1, namaList[s], stok[s]);
}

printf("--------------------------------------------------------\n\n");

system("pause");
return 0;


}
