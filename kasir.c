#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 200
#define NAME_LEN  64

// fungsi format rupiah dengan titik ribuan
void formatRupiah(int angka, char *buffer) {
    char temp[50];
    sprintf(temp, "%d", angka);

    int len = strlen(temp);
    int count = 0;
    buffer[0] = '\0';

    for (int i = len - 1; i >= 0; i--) {
        char ch[2] = { temp[i], '\0' };
        strcat(buffer, ch);
        count++;
        if (count % 3 == 0 && i != 0) {
            strcat(buffer, ".");
        }
    }

    // balik string
    int n = strlen(buffer);
    for (int i = 0; i < n / 2; i++) {
        char c = buffer[i];
        buffer[i] = buffer[n - i - 1];
        buffer[n - i - 1] = c;
    }
}

int main() {
    // data barang dinamis dari file
    char namaList[MAX_ITEMS][NAME_LEN];
    int hargaList[MAX_ITEMS];
    int stok[MAX_ITEMS];
    int jumlahItem = 0;

    // ===================== BACA DATA BARANG DARI FILE ======================
    FILE *barangFile = fopen("barang.txt", "r");
    if (barangFile != NULL) {
        while (jumlahItem < MAX_ITEMS &&
               fscanf(barangFile, "%63s %d %d", namaList[jumlahItem], &hargaList[jumlahItem], &stok[jumlahItem]) == 3) {
            jumlahItem++;
        }
        fclose(barangFile);
        if (jumlahItem == 0) {
            printf("Peringatan: barang.txt kosong atau format salah. Memuat data default.\n");
        }
    } else {
        printf("Peringatan: barang.txt tidak ditemukan. Memuat data default.\n");
    }

    // fallback default bila file tidak ada/invalid
    if (jumlahItem == 0) {
        const char *defaultNama[] = {
            "KAPASITOR","RESISTOR","INDUKTOR","DIODA",
            "TRANSISTOR","IC","SAKLAR","TRANSFORMATOR"
        };
        int defaultHarga[] = {35000,10000,30000,15000,70000,50000,10000,85000};
        int defaultStok[]  = {20,50,30,40,25,35,60,15};

        for (int i = 0; i < 8; i++) {
            strncpy(namaList[i], defaultNama[i], NAME_LEN-1);
            namaList[i][NAME_LEN-1] = '\0';
            hargaList[i] = defaultHarga[i];
            stok[i] = defaultStok[i];
        }
        jumlahItem = 8;
    }

    // ===================== NOMOR TRANSAKSI (dari file) ======================
    FILE *f;
    int nomor_transaksi = 0;

    f = fopen("counter.txt", "r");
    if (f != NULL) {
        if (fscanf(f, "%d", &nomor_transaksi) != 1) {
            nomor_transaksi = 0;
        }
        fclose(f);
    }
    nomor_transaksi++; // transaksi baru

    f = fopen("counter.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d", nomor_transaksi);
        fclose(f);
    } else {
        printf("Peringatan: tidak bisa menulis counter.txt. Nomor transaksi mungkin tidak berlanjut.\n");
    }

    // ===================== HEADER TAMPILAN ======================
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
    printf("\t\t\t\t===============================================\n");

    // ===================== DAFTAR BARANG ======================
    printf("No   Kode     Nama Barang                Harga         Stok\n");
    printf("---------------------------------------------------------------\n");
    for (int s = 0; s < jumlahItem; s++) {
        char rup[50];
        formatRupiah(hargaList[s], rup);
        printf("%-4d %-8.3d %-25s Rp. %-10s %d\n",
               s + 1, s + 1, namaList[s], rup, stok[s]);
    }
    printf("---------------------------------------------------------------\n\n");

    // ===================== PEMBELIAN ======================
    int kode, harga, qty;
    int total_pembelian = 0, diskon = 0, total_bayar = 0, bayar = 0, kembalian = 0;
    char kar = 'y';

    char nama_barang[100][NAME_LEN];
    int subtotal_barang[100];
    int jumlah_barang[100];
    int jumlah_beli = 0;

    while (kar == 'y' || kar == 'Y') {
        printf("Masukkan No Barang yang dibeli : ");
        if (scanf("%d", &kode) != 1) {
            printf("Input tidak valid. Harus angka.\n");
            return 0;
        }

        int index = kode - 1;
        if (index < 0 || index >= jumlahItem) {
            printf("Input kode salah!\n");
            continue;
        }

        strncpy(nama_barang[jumlah_beli], namaList[index], NAME_LEN-1);
        nama_barang[jumlah_beli][NAME_LEN-1] = '\0';
        harga = hargaList[index];

        printf("Harga %s = Rp. %d\n", nama_barang[jumlah_beli], harga);
        printf("Jumlah yang dibeli : ");
        if (scanf("%d", &qty) != 1) {
            printf("Input tidak valid. Harus angka.\n");
            return 0;
        }

        if (qty <= 0) {
            printf("Jumlah tidak boleh nol atau negatif.\n\n");
            continue;
        }

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
    }

    // ===================== PEMBAYARAN ======================
    printf("=============================================================\n");
    char rupiah[50];
    formatRupiah(total_pembelian, rupiah);
    printf("%-22s = Rp. %s\n", "TOTAL PEMBELIAN", rupiah);

    // diskon bertingkat
    if (total_pembelian > 500000) diskon = (int)(0.20 * total_pembelian);
    else if (total_pembelian > 300000) diskon = (int)(0.15 * total_pembelian);
    else if (total_pembelian > 200000) diskon = (int)(0.10 * total_pembelian);
    else if (total_pembelian > 100000) diskon = (int)(0.05 * total_pembelian);
    else diskon = 0;

    total_bayar = total_pembelian - diskon;

    if (diskon > 0) {
        formatRupiah(diskon, rupiah);
        printf("%-22s = Rp. %s\n", "DISKON", rupiah);
    }

    formatRupiah(total_bayar, rupiah);
    printf("%-22s = Rp. %s\n", "TOTAL BAYAR", rupiah);

    // metode pembayaran (validasi loop)
    int metode = 0;
    char metodeStr[20];
    do {
        printf("\nPilih metode pembayaran:\n1. Tunai\n2. QRIS\n3. Debit\nPilihan: ");
        if (scanf("%d", &metode) != 1) {
            // bersihkan buffer jika perlu
            printf("Input tidak valid. Harus angka 1-3.\n");
            return 0;
        }
        if (metode < 1 || metode > 3) {
            printf("Pilihan metode tidak valid. Coba lagi.\n");
        }
    } while (metode < 1 || metode > 3);

    switch(metode) {
        case 1: strcpy(metodeStr, "Tunai"); break;
        case 2: strcpy(metodeStr, "QRIS"); break;
        case 3: strcpy(metodeStr, "Debit"); break;
    }

    // loop sampai bayar cukup
    do {
        printf("%-22s = Rp. ", "Masukkan uang bayar");
        if (scanf("%d", &bayar) != 1) {
            printf("Input tidak valid. Harus angka.\n");
            return 0;
        }

        if (bayar < total_bayar) {
            formatRupiah(total_bayar - bayar, rupiah);
            printf("Uang kurang Rp. %s, silakan tambah lagi!\n\n", rupiah);
        }
    } while (bayar < total_bayar);

    kembalian = bayar - total_bayar;
    formatRupiah(kembalian, rupiah);
    printf("%-22s = Rp. %s\n", "UANG KEMBALIAN", rupiah);

    // ===================== STRUK BELANJA (waktu) ======================
    time_t t;
    struct tm *tm_info;
    char buffer_waktu[30];
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer_waktu, 30, "%d-%m-%Y %H:%M:%S", tm_info);

    // ===================== CETAK STRUK KE LAYAR ======================
    printf("\n=================== STRUK BELANJA ===================\n");
    printf("Toko              : TOKO KANG UCUP\n");
    printf("Nomor Transaksi   : INV-%04d\n", nomor_transaksi);
    printf("Tanggal/Waktu     : %s\n", buffer_waktu);
    printf("Metode Pembayaran : %s\n", metodeStr);
    printf("No   Nama Barang                Qty     Subtotal\n");
    printf("-----------------------------------------------------\n");

    for (int a = 0; a < jumlah_beli; a++) {
        formatRupiah(subtotal_barang[a], rupiah);
        printf("%-5d %-25s %-7d Rp. %s\n",
               a + 1, nama_barang[a], jumlah_barang[a], rupiah);
    }

    printf("-----------------------------------------------------\n");
    formatRupiah(total_pembelian, rupiah);
    printf("%-20s = Rp. %s\n", "TOTAL PEMBELIAN", rupiah);
    if (diskon > 0) {
        formatRupiah(diskon, rupiah);
        printf("%-20s = Rp. %s\n", "DISKON", rupiah);
    }
    formatRupiah(total_bayar, rupiah);
    printf("%-20s = Rp. %s\n", "TOTAL BAYAR", rupiah);
    formatRupiah(bayar, rupiah);
    printf("%-20s = Rp. %s\n", "UANG BAYAR", rupiah);
    formatRupiah(kembalian, rupiah);
    printf("%-20s = Rp. %s\n", "KEMBALIAN", rupiah);

    printf("=================================================================\n");
    printf("          TERIMA KASIH SUDAH BERBELANJA DI TOKO KAMI!\n");
    printf("=================================================================\n");

    // ===================== SIMPAN STRUK KE FILE ======================
    char filename[64];
    sprintf(filename, "struk_INV%04d.txt", nomor_transaksi);

    FILE *strukFile = fopen(filename, "w");
    if (strukFile != NULL) {
        fprintf(strukFile, "=================== STRUK BELANJA ===================\n");
        fprintf(strukFile, "Toko              : TOKO KANG UCUP\n");
        fprintf(strukFile, "Nomor Transaksi   : INV-%04d\n", nomor_transaksi);
        fprintf(strukFile, "Tanggal/Waktu     : %s\n", buffer_waktu);
        fprintf(strukFile, "Metode Pembayaran : %s\n", metodeStr);
        fprintf(strukFile, "No   Nama Barang                Qty     Subtotal\n");
        fprintf(strukFile, "-----------------------------------------------------\n");

        for (int a = 0; a < jumlah_beli; a++) {
            char rup_sub[50];
            formatRupiah(subtotal_barang[a], rup_sub);
            fprintf(strukFile, "%-5d %-25s %-7d Rp. %s\n",
                    a + 1, nama_barang[a], jumlah_barang[a], rup_sub);
        }

        fprintf(strukFile, "-----------------------------------------------------\n");
        char rup_total[50];
        char rup_totalbayar[50], rup_bayar[50], rup_kembali[50];
        formatRupiah(total_pembelian, rup_total);
        formatRupiah(total_bayar, rup_totalbayar);
        formatRupiah(bayar, rup_bayar);
        formatRupiah(kembalian, rup_kembali);

        fprintf(strukFile, "%-20s = Rp. %s\n", "TOTAL PEMBELIAN", rup_total);
        if (diskon > 0) {
            char rup_disk[50];
            formatRupiah(diskon, rup_disk);
            fprintf(strukFile, "%-20s = Rp. %s\n", "DISKON", rup_disk);
        }
        fprintf(strukFile, "%-20s = Rp. %s\n", "TOTAL BAYAR", rup_totalbayar);
        fprintf(strukFile, "%-20s = Rp. %s\n", "UANG BAYAR", rup_bayar);
        fprintf(strukFile, "%-20s = Rp. %s\n", "KEMBALIAN", rup_kembali);

        fprintf(strukFile, "=================================================================\n");
        fprintf(strukFile, "          TERIMA KASIH SUDAH BERBELANJA DI TOKO KAMI!\n");
        fprintf(strukFile, "=================================================================\n");

        fclose(strukFile);
        printf("Struk berhasil disimpan ke file: %s\n", filename);
    } else {
        printf("Gagal menyimpan struk ke file!\n");
    }

    // ===================== SIMPAN DATA BARANG TERBARU KE FILE ======================
    barangFile = fopen("barang.txt", "w");
    if (barangFile != NULL) {
        for (int i = 0; i < jumlahItem; i++) {
            fprintf(barangFile, "%s %d %d\n", namaList[i], hargaList[i], stok[i]);
        }
        fclose(barangFile);
        printf("Data barang terbaru berhasil disimpan ke barang.txt\n");
    } else {
        printf("Gagal menyimpan data barang ke file!\n");
    }

    // ===================== SISA STOK ======================
    printf("\n=================== SISA STOK BARANG ===================\n");
    printf("Kode  Nama Barang                Sisa Stok\n");
    printf("--------------------------------------------------------\n");
    for (int s = 0; s < jumlahItem; s++) {
        printf("%-5d %-25s %d\n", s + 1, namaList[s], stok[s]);
    }
    printf("--------------------------------------------------------\n\n");

    return 0;
}
