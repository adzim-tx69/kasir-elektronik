#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int kode, harga, qty, i = 1;
    int total_pembelian = 0, diskon = 0, total_bayar, bayar, kembalian;
    char kar = 'y';

    char nama_barang[100][50];
    int subtotal_barang[100];
    int jumlah_barang[100];
    int jumlah_beli = 0;

    int stok[8] = {20, 50, 30, 40, 25, 35, 60, 15};

    char *namaList[] = {
        "KAPASITOR","RESISTOR","INDUKTOR","DIODA",
        "TRANSISTOR","IC","SAKLAR","TRANSFORMATOR"
    };

    int hargaList[] = {35000,10000,30000,15000,70000,50000,10000,85000};

    // ===================== HEADER ==========================
    printf("\t\t\t\t===============================================\n");
    printf("\t\t\t\t||         NAMA KELOMPOK KING BAHLIL         ||\n");
    printf("\t\t\t\t|| -MUHAMMAD NUR ADZIM           -411251100  ||\n");
    printf("\t\t\t\t|| -IHSAN IBNU ABDURRAUF         -411251110  ||\n");
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
            printf("Stok %s tinggal %d saja!\n\n", nama_barang[jumlah_beli], stok[index]);
            continue;
        }

        // kurangi stok
        stok[index] -= qty;

        int subtotal = harga * qty;
        total_pembelian += subtotal;

        subtotal_barang[jumlah_beli] = subtotal;
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

    // diskon bertingkat
    if (total_pembelian > 500000) {
        diskon = 0.2 * total_pembelian;
    } else if (total_pembelian > 300000) {
        diskon = 0.15 * total_pembelian;
    } else if (total_pembelian > 200000) {
        diskon = 0.1 * total_pembelian;
    } else if (total_pembelian > 100000) {
        diskon = 0.05 * total_pembelian;
    } else {
        diskon = 0;
    }

    total_bayar = total_pembelian - diskon;

    if (diskon > 0)
        printf("%-22s = Rp. %-10d\n", "DISKON", diskon);

    printf("%-22s = Rp. %-10d\n", "TOTAL BAYAR", total_bayar);

    // loop sampai bayar cukup
    do {
        printf("%-22s = Rp. ", "Masukkan uang bayar");
        scanf("%d", &bayar);

        if (bayar < total_bayar) {
            printf("Uang kurang Rp. %d, silakan tambah lagi!\n\n", total_bayar - bayar);
        }
    } while (bayar < total_bayar);

    kembalian = bayar - total_bayar;
    printf("%-22s = Rp. %-10d\n", "UANG KEMBALIAN", kembalian);

    // ===================== STRUK BELANJA ==========================
    // ambil waktu sekarang
    time_t t;
    struct tm *tm_info;
    char buffer[30];
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, 30, "%d-%m-%Y %H:%M:%S", tm_info);

    // nomor transaksi (simulasi, bisa dibuat auto increment dari file)
    static int nomor_transaksi = 1;

    printf("\n=================== STRUK BELANJA ===================\n");
    printf("Nomor Transaksi : INV-%04d\n", nomor_transaksi);
    printf("Tanggal/Waktu   : %s\n", buffer);
    printf("No   Nama Barang           Qty     Subtotal\n");
    printf("-----------------------------------------------------\n");

    for (int a = 0; a < jumlah_beli; a++) {
        printf("%-5d %-20s %-7d Rp. %d\n",
            a + 1,
            nama_barang[a],
            jumlah_barang[a],
            subtotal_barang[a]);
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
