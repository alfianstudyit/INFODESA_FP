#include "infodesa.h"
#include "style.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;


void screenPD(string nama) {
    system("cls");
    cout << BLUE << BOLD;
    cout << "  ======================================================\n";
    cout << "  ||                                                  ||\n";
    cout << "  ||          I N F O D E S A - A D M I N             ||\n";
    cout << "  ||             Dashboard Perangkat Desa             ||\n";
    cout << "  ||                                                  ||\n";
    cout << "  ======================================================\n" << RESET;

    cout << "\n  Selamat datang, " << BOLD << GREEN << nama << RESET << " (Perangkat Desa)\n";
    cout << "  Silakan pilih menu manajemen sistem:\n\n";

    cout << BOLD << "  [ MENU MANAJEMEN ]\n" << RESET;
    cout << CYAN << "  1. " << RESET << "Manajemen Administrasi & Persuratan\n";
    cout << CYAN << "  2. " << RESET << "Pengelolaan Data Kependudukan\n";
    cout << CYAN << "  3. " << RESET << "Manajemen Pengaduan & Tugas\n";
    cout << CYAN << "  4. " << RESET << "Kabar Desa (Publikasi)\n";
    cout << CYAN << "  5. " << RESET << "Manajemen Account Aktif\n";
    cout << RED << "  6. " << BOLD << "Panic Button Monitor\n" << RESET;
    cout << YELLOW << "  7. " << RESET << "Logout\n";
    cout << YELLOW << "  8. " << RESET << "Exit\n\n";
    cout << "  Masukkan pilihan Anda: ";
}

// FITUR MANAJEMEN SURAT PERANGKAT DESA
void menuSuratPD(vector<Surat>& daftarSurat) {
    int pilihan;
    do {
        system("cls");
        cout << BLUE << BOLD << "\n  === MANAJEMEN PERSURATAN WARGA ===\n\n" << RESET;
        cout << "  1. Lihat & Proses Antrian Surat\n";
        cout << "  2. Kembali ke Dashboard\n\n";
        cout << "  " << BOLD << "Pilih Menu: " << RESET;
        cin >> pilihan;

        if (pilihan == 1) {
            system("cls");
            cout << CYAN << BOLD << "\n  >>> DAFTAR ANTRIAN SURAT WARGA <<<\n\n" << RESET;
            cout << "  --------------------------------------------------------------------------------------\n";
            cout << "  " << left << setw(5) << "ID"
                << setw(15) << "NIK Warga"
                << setw(35) << "Jenis Surat"
                << "Status\n";
            cout << "  --------------------------------------------------------------------------------------\n";

            for (size_t i = 0; i < daftarSurat.size(); i++) {
                string warnaStatus = (daftarSurat[i].status == "Selesai") ? GREEN : (daftarSurat[i].status == "Ditolak" ? RED : YELLOW);
                cout << "  " << left << setw(5) << daftarSurat[i].id
                    << setw(15) << daftarSurat[i].usernameWarga
                    << setw(35) << daftarSurat[i].jenisSurat
                    << warnaStatus << "[" << daftarSurat[i].status << "]\n" << RESET;
            }

            if (daftarSurat.empty()) {
                cout << YELLOW << "  Belum ada antrian pengajuan surat saat ini.\n" << RESET;
                cout << "  --------------------------------------------------------------------------------------\n\n";
                system("pause");
                continue;
            }
            cout << "  --------------------------------------------------------------------------------------\n\n";

            int idAksi;
            cout << "  Masukkan ID Surat yang ingin diproses: ";
            cin >> idAksi;
            bool berhasil = false;

            for (size_t i = 0; i < daftarSurat.size(); i++) {
                if (daftarSurat[i].id == idAksi) {
                    berhasil = true;
                    int opsiTindakan;
                    cout << BOLD << "\n  [ TINDAKAN UNTUK SURAT ID " << idAksi << " ]\n" << RESET;
                    cout << GREEN << "  1. Setujui (Selesai)\n" << RESET;
                    cout << RED << "  2. Tolak Pengajuan\n" << RESET;
                    cout << "  Pilih Tindakan: ";
                    cin >> opsiTindakan;

                    if (opsiTindakan == 1) {
                        daftarSurat[i].status = "Selesai";
                        daftarSurat[i].lampiran = "Surat telah diverifikasi.";
                        cout << GREEN << BOLD << "\n  [SUKSES] " << RESET << "Surat berhasil disetujui.\n\n";
                    }
                    else {
                        daftarSurat[i].status = "Ditolak";
                        cout << "  Masukkan Alasan Penolakan: ";
                        cin.ignore();
                        getline(cin, daftarSurat[i].lampiran);
                        cout << RED << BOLD << "\n  [INFO] " << RESET << "Surat ditolak.\n\n";
                    }
                    break;
                }
            }
            if (!berhasil) cout << RED << "\n  [GAGAL] ID tidak ditemukan.\n\n" << RESET;
            system("pause");
        }
    } while (pilihan != 2);
}

// INSERTION SORT & BINARY SEARCH
void insertionSortPenduduk(vector<Penduduk>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        Penduduk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].NIK > key.NIK) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int binarySearchPenduduk(const vector<Penduduk>& arr, string targetNIK) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].NIK == targetNIK) return mid;
        if (arr[mid].NIK < targetNIK) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// MENU DATA KEPENDUDUKAN
void menuKependudukanPD(vector<Penduduk>& daftarPenduduk) {
    int pilihan;
    do {
        system("cls");
        cout << BLUE << BOLD << "\n  === PENGELOLAAN DATA KEPENDUDUKAN ===\n\n" << RESET;
        cout << "  1. Tambah Data Penduduk \n";
        cout << "  2. Lihat & Urutkan Data \n";
        cout << "  3. Cari Data Penduduk   \n";
        cout << "  4. Edit Data Penduduk   \n";
        cout << "  5. Hapus Data Penduduk  \n";
        cout << "  6. Export Data ke EXCEL / PDF\n";
        cout << "  7. Kembali ke Dashboard\n\n";
        cout << "  " << BOLD << "Pilih Menu: " << RESET;
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            system("cls");
            Penduduk pBaru;
            cout << GREEN << BOLD << "\n  >>> TAMBAH PENDUDUK BARU <<<\n\n" << RESET;
            cin.ignore();
            cout << "  Masukkan NIK                     : "; getline(cin, pBaru.NIK);
            cout << "  Masukkan Nama                    : "; getline(cin, pBaru.nama);
            cout << "  Masukkan Tempat Tanggal Lahir    : "; getline(cin, pBaru.birth);
            cout << "  Masukkan Agama                   : "; getline(cin, pBaru.agama);
            cout << "  Masukkan Pekerjaan               : "; getline(cin, pBaru.pekerjaan);
            cout << "  Masukkan Pendidikan              : "; getline(cin, pBaru.pendidikan);
            cout << "  Masukkan Alamat                  : "; getline(cin, pBaru.alamat);

            daftarPenduduk.push_back(pBaru);
            cout << GREEN << "\n  [SUKSES] Data berhasil ditambahkan ke dalam sistem!\n\n" << RESET;
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            if (daftarPenduduk.empty()) {
                cout << YELLOW << "\n  [INFO] Data Kependudukan masih kosong!\n\n" << RESET;
                system("pause");
                break;
            }

            insertionSortPenduduk(daftarPenduduk);

            cout << CYAN << BOLD << "\n  >>> DATA KEPENDUDUKAN (Terurut Berdasarkan NIK) <<<\n\n" << RESET;
            cout << "  -------------------------------------------------------------------------------------------------------------------------\n";
            cout << "  " << left << setw(18) << "NIK"
                << setw(22) << "Nama"
                << setw(25) << "Tempat, Tgl Lahir"
                << setw(12) << "Agama"
                << setw(15) << "Pekerjaan"
                << setw(15) << "Pendidikan"
                << "Alamat\n";
            cout << "  -------------------------------------------------------------------------------------------------------------------------\n";

            for (size_t i = 0; i < daftarPenduduk.size(); i++) {
                cout << "  " << left << setw(18) << daftarPenduduk[i].NIK
                    << setw(22) << daftarPenduduk[i].nama
                    << setw(25) << daftarPenduduk[i].birth
                    << setw(12) << daftarPenduduk[i].agama
                    << setw(15) << daftarPenduduk[i].pekerjaan
                    << setw(15) << daftarPenduduk[i].pendidikan
                    << daftarPenduduk[i].alamat << "\n";
            }
            cout << "  -------------------------------------------------------------------------------------------------------------------------\n\n";
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            if (daftarPenduduk.empty()) {
                cout << YELLOW << "\n  [INFO] Data Kependudukan masih kosong!\n\n" << RESET;
                system("pause");
                break;
            }

            insertionSortPenduduk(daftarPenduduk);
            string target;
            cout << YELLOW << BOLD << "\n  >>> CARI DATA PENDUDUK <<<\n\n" << RESET;
            cout << "  Masukkan NIK yang dicari: ";
            cin >> target;

            int index = binarySearchPenduduk(daftarPenduduk, target);

            if (index != -1) {
                cout << GREEN << BOLD << "\n  [ DATA DITEMUKAN ]\n" << RESET;
                cout << "  -----------------------------------------\n";
                cout << "  NIK              : " << daftarPenduduk[index].NIK << "\n";
                cout << "  Nama             : " << daftarPenduduk[index].nama << "\n";
                cout << "  Tempat, Tgl Lahir: " << daftarPenduduk[index].birth << "\n";
                cout << "  Agama            : " << daftarPenduduk[index].agama << "\n";
                cout << "  Pekerjaan        : " << daftarPenduduk[index].pekerjaan << "\n";
                cout << "  Pendidikan       : " << daftarPenduduk[index].pendidikan << "\n";
                cout << "  Alamat           : " << daftarPenduduk[index].alamat << "\n";
                cout << "  -----------------------------------------\n\n";
            }
            else {
                cout << RED << "\n  [GAGAL] Data dengan NIK " << target << " tidak ditemukan.\n\n" << RESET;
            }
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            if (daftarPenduduk.empty()) {
                cout << YELLOW << "\n  [INFO] Data Kependudukan masih kosong!\n\n" << RESET;
                system("pause");
                break;
            }

            insertionSortPenduduk(daftarPenduduk);
            string target;
            cout << BLUE << BOLD << "\n  >>> EDIT DATA PENDUDUK <<<\n\n" << RESET;
            cout << "  Masukkan NIK yang ingin di-edit: ";
            cin >> target;

            int index = binarySearchPenduduk(daftarPenduduk, target);
            if (index != -1) {
                cout << "\n  " << BOLD << "Data Ditemukan:" << RESET << "\n";
                cout << "  Nama Saat Ini: " << daftarPenduduk[index].nama << "\n\n";

                cin.ignore();
                cout << "  Masukkan Nama Baru               : "; getline(cin, daftarPenduduk[index].nama);
                cout << "  Masukkan Tempat Tgl Lahir Baru   : "; getline(cin, daftarPenduduk[index].birth);
                cout << "  Masukkan Agama Baru              : "; getline(cin, daftarPenduduk[index].agama);
                cout << "  Masukkan Pekerjaan Baru          : "; getline(cin, daftarPenduduk[index].pekerjaan);
                cout << "  Masukkan Pendidikan Baru         : "; getline(cin, daftarPenduduk[index].pendidikan);
                cout << "  Masukkan Alamat Baru             : "; getline(cin, daftarPenduduk[index].alamat);
                cout << GREEN << "\n  [SUKSES] Data berhasil diperbarui!\n\n" << RESET;
            }
            else {
                cout << RED << "\n  [GAGAL] Data dengan NIK " << target << " tidak ditemukan.\n\n" << RESET;
            }
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            if (daftarPenduduk.empty()) {
                cout << YELLOW << "\n  [INFO] Data Kependudukan masih kosong!\n\n" << RESET;
                system("pause");
                break;
            }

            insertionSortPenduduk(daftarPenduduk);
            string target;
            cout << RED << BOLD << "\n  >>> HAPUS DATA PENDUDUK <<<\n\n" << RESET;
            cout << "  Masukkan NIK yang ingin dihapus: ";
            cin >> target;

            int index = binarySearchPenduduk(daftarPenduduk, target);
            if (index != -1) {
                cout << YELLOW << "\n  Menghapus data atas nama: " << BOLD << daftarPenduduk[index].nama << RESET << "...\n";
                daftarPenduduk.erase(daftarPenduduk.begin() + index);
                cout << GREEN << "  [SUKSES] Data berhasil dihapus!\n\n" << RESET;
            }
            else {
                cout << RED << "\n  [GAGAL] Data dengan NIK " << target << " tidak ditemukan.\n\n" << RESET;
            }
            system("pause");
            break;
        }
        case 6: {
            system("cls");
            if (daftarPenduduk.empty()) {
                cout << YELLOW << "\n  [INFO] Data Kependudukan masih kosong!\n\n" << RESET;
                system("pause");
                break;
            }

            insertionSortPenduduk(daftarPenduduk);
            cout << BLUE << BOLD << "\n  >>> EXPORT DATA KEPENDUDUKAN <<<\n\n" << RESET;
            cout << "  1. Cetak ke Microsoft Excel (.csv)\n";
            cout << "  2. Cetak ke Laporan PDF (.html)\n\n";
            cout << "  " << BOLD << "Pilih Format: " << RESET;
            int format; cin >> format;

            // PATH
            string pathFolder = "D:\\kampus\\SEM 2\\STRUKTUR_DATA\\TUGAS AKHIR\\HASIL_PRINT\\";

            if (format == 1) {
                string namaFile = pathFolder + "Data_Penduduk_INFODESA.csv";
                ofstream fileExcel(namaFile.c_str());

                // Header CSV
                fileExcel << "NIK,Nama,Tempat Tanggal Lahir,Agama,Pekerjaan,Pendidikan,Alamat\n";

                // Isi Data dibungkus kutip dua "" agar aman dari tanda koma pembatas
                for (size_t i = 0; i < daftarPenduduk.size(); i++) {
                    fileExcel << "\"" << daftarPenduduk[i].NIK << "\","
                        << "\"" << daftarPenduduk[i].nama << "\","
                        << "\"" << daftarPenduduk[i].birth << "\","
                        << "\"" << daftarPenduduk[i].agama << "\","
                        << "\"" << daftarPenduduk[i].pekerjaan << "\","
                        << "\"" << daftarPenduduk[i].pendidikan << "\","
                        << "\"" << daftarPenduduk[i].alamat << "\"\n";
                }
                fileExcel.close();

                cout << GREEN << BOLD << "\n  [SUKSES] " << RESET << "Data berhasil diexport!\n";
                cout << "  Lokasi: " << BOLD << namaFile << RESET << "\n";
                cout << "  Silakan buka file tersebut menggunakan Microsoft Excel.\n\n";
            }
            else if (format == 2) {
                string namaFile = pathFolder + "Laporan_Penduduk_INFODESA.html";
                ofstream filePDF(namaFile.c_str());

                filePDF << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Laporan Kependudukan</title>\n";
                filePDF << "<style>\n";
                filePDF << "body { background-color: #525659; display: flex; justify-content: center; padding: 20px; font-family: 'Times New Roman', Times, serif; }\n";
                filePDF << ".kertas { background-color: white; width: 297mm; min-height: 210mm; padding: 20mm; box-shadow: 0 0 10px rgba(0,0,0,0.5); box-sizing: border-box; }\n"; // Diubah ke landscape (A4) karena kolom bertambah
                filePDF << ".kop { text-align: center; border-bottom: 3px double black; padding-bottom: 5px; margin-bottom: 20px; }\n";
                filePDF << ".kop h2 { margin: 0; font-size: 18px; text-transform: uppercase; font-weight: normal; }\n";
                filePDF << ".kop h1 { margin: 2px 0; font-size: 24px; text-transform: uppercase; font-weight: bold; }\n";
                filePDF << ".kop p { margin: 5px 0 0 0; font-size: 12pt; }\n";
                filePDF << "h3.judul { text-align: center; text-decoration: underline; margin-bottom: 20px; text-transform: uppercase; font-size: 14pt; }\n";
                filePDF << "table { width: 100%; border-collapse: collapse; margin-bottom: 40px; font-size: 10pt; }\n";
                filePDF << "th, td { border: 1px solid black; padding: 6px 8px; text-align: left; }\n";
                filePDF << "th { background-color: #e0e0e0; text-align: center; font-weight: bold; }\n";
                filePDF << ".center { text-align: center; }\n";
                filePDF << ".ttd { float: right; width: 250px; text-align: center; margin-top: 30px; }\n";
                filePDF << ".ttd p { margin: 0; font-size: 11pt; }\n";
                filePDF << ".clear { clear: both; }\n";
                filePDF << "@media print { body { background-color: white; padding: 0; display: block; } .kertas { box-shadow: none; width: auto; min-height: auto; padding: 0; margin: 0; } }\n";
                filePDF << "</style></head><body>\n";

                filePDF << "<div class='kertas'>\n";
                filePDF << "<div class='kop'>\n";
                filePDF << "<div style='border-bottom: 1px solid black; padding-bottom: 10px;'>\n";
                filePDF << "<h2>PEMERINTAH KABUPATEN SLEMAN</h2>\n";
                filePDF << "<h2>KECAMATAN GODEAN</h2>\n";
                filePDF << "<h1>KANTOR KEPALA DESA INFODESA</h1>\n";
                filePDF << "<p>Jl. Raya Sleman-Godean No. 45, Godean, Sleman, Daerah Istimewa Yogyakarta 55264</p>\n";
                filePDF << "</div></div>\n";

                filePDF << "<h3 class='judul'>Laporan Rekapitulasi Data Kependudukan</h3>\n";
                filePDF << "<table>\n";

                // Kolom HTML PDF diperbarui agar memuat semua data baru
                filePDF << "<tr>"
                    << "<th style='width: 4%;'>No</th>"
                    << "<th style='width: 14%;'>NIK</th>"
                    << "<th style='width: 18%;'>Nama Lengkap</th>"
                    << "<th style='width: 18%;'>Tempat, Tgl Lahir</th>"
                    << "<th style='width: 10%;'>Agama</th>"
                    << "<th style='width: 12%;'>Pekerjaan</th>"
                    << "<th style='width: 12%;'>Pendidikan</th>"
                    << "<th style='width: 12%;'>Alamat Domisili</th>"
                    << "</tr>\n";

                for (size_t i = 0; i < daftarPenduduk.size(); i++) {
                    filePDF << "<tr>"
                        << "<td class='center'>" << (i + 1) << "</td>"
                        << "<td class='center'>" << daftarPenduduk[i].NIK << "</td>"
                        << "<td>" << daftarPenduduk[i].nama << "</td>"
                        << "<td>" << daftarPenduduk[i].birth << "</td>"
                        << "<td class='center'>" << daftarPenduduk[i].agama << "</td>"
                        << "<td>" << daftarPenduduk[i].pekerjaan << "</td>"
                        << "<td>" << daftarPenduduk[i].pendidikan << "</td>"
                        << "<td>" << daftarPenduduk[i].alamat << "</td>"
                        << "</tr>\n";
                }
                filePDF << "</table>\n";

                filePDF << "<div class='ttd'>\n";
                filePDF << "<p>Godean, 15 Juni 2026</p>\n";
                filePDF << "<p><b>Kepala Desa Infodesa</b></p>\n";
                filePDF << "<br><br><br><br>\n";
                filePDF << "<p style='text-decoration: underline;'><b>( NAMA KEPALA DESA )</b></p>\n";
                filePDF << "<p>NIP. 19800101 201001 1 001</p>\n";
                filePDF << "</div>\n";

                filePDF << "<div class='clear'></div>\n";
                filePDF << "</div></body></html>\n";

                filePDF.close();

                cout << GREEN << BOLD << "\n  [SUKSES] " << RESET << "File Laporan PDF Digital berhasil dibuat!\n";
                cout << "  Lokasi: " << BOLD << namaFile << RESET << "\n";
                cout << "  Cara Save: Buka file HTML tersebut di Browser -> Tekan Ctrl+P -> Pilih Save As PDF.\n\n";
            }
            else {
                cout << RED << "\n  [ERROR] Pilihan format tidak valid!\n\n" << RESET;
            }

            system("pause");
            break;
        }
        }
    } while (pilihan != 7);
}

// MENU KABAR DESA
void menuKabarDesa(vector<Berita>& daftarBerita, Role roleActive) {
    int pilihan;
    do {
        system("cls");
        cout << CYAN << BOLD << "\n  === MADING KABAR DESA ===\n\n" << RESET;
        cout << "  1. Lihat Berita & Pengumuman\n";
        if (roleActive == PerangkatDesa) {
            cout << "  2. Tambah Berita Baru\n";
        }
        cout << "  9. Kembali\n\n";
        cout << "  " << BOLD << "Pilih: " << RESET;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');

            system("cls");
            cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
            system("pause");
            continue;
        }

        // 1. LIHAT BERITA (TAMPIL 1 PER 1 DENGAN NAVIGASI)
        if (pilihan == 1) {
            if (daftarBerita.empty()) {
                system("cls");
                cout << YELLOW << "\n  [INFO] Belum ada berita atau pengumuman saat ini.\n\n" << RESET;
                system("pause");
            }
            else {
                size_t indexBerita = daftarBerita.size() - 1;
                // Catatan: Jika ingin berita terbaru muncul duluan, bisa diset: indexBerita = daftarBerita.size() - 1;

                char nav;
                do {
                    system("cls");
                    cout << CYAN << BOLD << "\n  >>> KABAR DESA DIGITAL <<<\n" << RESET;
                    cout << "  [ Berita " << indexBerita + 1 << " dari " << daftarBerita.size() << " ]\n\n";

                    // Pembungkus Berita berupa Kotak/Card Tradisional
                    cout << "  ==================================================================\n";
                    cout << "  | JUDUL   : " << BOLD << left << setw(50) << daftarBerita[indexBerita].judul << RESET << " |\n";
                    cout << "  | TANGGAL : " << left << setw(50) << daftarBerita[indexBerita].tanggal << " |\n";
                    cout << "  | LOKASI  : " << left << setw(50) << daftarBerita[indexBerita].lokasi << " |\n";
                    cout << "  ------------------------------------------------------------------\n";
                    cout << "    " << daftarBerita[indexBerita].isi << "\n";
                    cout << "  ==================================================================\n\n";

                    // Menu Navigasi Dinamis
                    cout << "  Pilihan Navigasi:\n";
                    if (indexBerita < daftarBerita.size() - 1) {
                        cout << "  [N] Berita Selanjutnya (Next)\n";
                    }
                    if (indexBerita > 0) {
                        cout << "  [P] Berita Sebelumnya (Previous)\n";
                    }
                    cout << "  [K] Kembali ke Menu Mading\n\n";
                    cout << "  Masukkan Opsi Navigasi: ";
                    cin >> nav;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');

                        system("cls");
                        cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
                        system("pause");
                        continue;
                    }

                    nav = tolower(nav); // Menangani input huruf kapital/kecil

                    // Logika Perpindahan Berita
                    if (nav == 'n' && indexBerita < daftarBerita.size() - 1) {
                        indexBerita++;
                    }
                    else if (nav == 'p' && indexBerita > 0) {
                        indexBerita--;
                    }

                } while (nav != 'k');
            }
        }
        // 2. TAMBAH BERITA BARU (INPUT LENGKAP)
        else if (pilihan == 2 && roleActive == PerangkatDesa) {
            system("cls");
            Berita bBaru;
            bBaru.id = daftarBerita.size() + 1;

            cout << BLUE << BOLD << "\n  >>> PUBLIKASI BERITA BARU <<<\n\n" << RESET;
            cin.ignore(); 

            cout << "  Judul Berita     : "; getline(cin, bBaru.judul);
            cout << "  Tanggal / Waktu  : "; getline(cin, bBaru.tanggal);
            cout << "  Lokasi Kegiatan  : "; getline(cin, bBaru.lokasi);
            cout << "  Isi Pengumuman   : "; getline(cin, bBaru.isi);

            daftarBerita.push_back(bBaru);
            cout << GREEN << "\n  [SUKSES] Berita berhasil ditempel di mading desa!\n\n" << RESET;
            system("pause");
        }
    } while (pilihan != 9);
}

// MENU PANIC BUTTON
void menuPanicButton(vector<Darurat>& daftarDarurat, Role roleActive, string usernameActive) {
    if (roleActive == Warga) {
        system("cls");
        cout << RED << BOLD;
        cout << "\n  ======================================\n";
        cout << "  !!       P A N I C  B U T T O N     !!\n";
        cout << "  ======================================\n\n" << RESET;
        cout << "  Pilih jenis keadaan darurat:\n";
        cout << "  1. Darurat Medis / Ambulans\n";
        cout << "  2. Tindak Kriminal / Keamanan\n";
        cout << "  3. Bencana Alam / Kebakaran\n\n";
        cout << "  " << BOLD << "Kirim Sinyal (Pilih 1-3): " << RESET;
        int p; cin >> p;

        if (p >= 1 && p <= 3) {
            Darurat d;
            d.id = daftarDarurat.size() + 1;
            d.pelapor = usernameActive;
            d.status = "Butuh Bantuan Segera!";
            d.kondisi = (p == 1) ? "Medis" : (p == 2) ? "Kriminal" : "Kebakaran/Bencana";

            daftarDarurat.push_back(d);
            cout << RED << BOLD << "\n  [!!!] SINYAL DARURAT TELAH DIKIRIM KE PERANGKAT DESA [!!!]\n" << RESET;
            cout << "  Harap tetap tenang, bantuan sedang dikerahkan.\n\n";
            system("pause");
        }
    }
    else { 
        system("cls");
        cout << RED << BOLD << "\n  >>> MONITOR PANGGILAN DARURAT (S.O.S) <<<\n\n" << RESET;
        cout << "  --------------------------------------------------------------\n";
        cout << "  " << left << setw(5) << "ID"
            << setw(20) << "Kondisi"
            << setw(15) << "Pelapor"
            << "Status\n";
        cout << "  --------------------------------------------------------------\n";

        if (daftarDarurat.empty()) {
            cout << GREEN << "  Situasi aman. Tidak ada laporan darurat saat ini.\n" << RESET;
        }
        else {
            for (size_t i = 0; i < daftarDarurat.size(); i++) {
                cout << "  " << left << setw(5) << daftarDarurat[i].id
                    << RED << setw(20) << daftarDarurat[i].kondisi << RESET
                    << setw(15) << daftarDarurat[i].pelapor
                    << YELLOW << daftarDarurat[i].status << RESET << "\n";
            }
        }
        cout << "  --------------------------------------------------------------\n\n";
        system("pause");
    }
}

// SMART REPORT PERANGKAT DESA
void menuPengaduanPD(vector<Laporan>& daftarLaporan) {
    int pilihan;
    do {
        system("cls");
        cout << BLUE << BOLD << "\n  === MANAJEMEN PENGADUAN & ASPIRASI ===\n\n" << RESET;
        cout << "  1. Lihat & Tanggapi Laporan Warga\n";
        cout << "  2. Kembali ke Dashboard\n\n";
        cout << "  " << BOLD << "Pilih Menu: " << RESET;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');

            system("cls");
            cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
            system("pause");
            continue;
        }

        if (pilihan == 1) {
            system("cls");
            cout << CYAN << BOLD << "\n  >>> DAFTAR LAPORAN MASUK <<<\n\n" << RESET;

            if (daftarLaporan.empty()) {
                cout << YELLOW << "  Belum ada laporan atau aspirasi masuk.\n\n" << RESET;
                system("pause");
                continue;
            }

            for (size_t i = 0; i < daftarLaporan.size(); i++) {
                string warnaStatus = (daftarLaporan[i].status == "Selesai") ? GREEN : YELLOW;
                cout << "  " << BOLD << "[ID: " << daftarLaporan[i].id << "] - " << daftarLaporan[i].jenis << RESET << "\n";
                cout << "  Isi Laporan: " << daftarLaporan[i].isi << "\n";
                cout << "  Status     : " << warnaStatus << "[" << daftarLaporan[i].status << "]" << RESET << "\n";
                if (!daftarLaporan[i].tanggapan.empty()) {
                    cout << "  Tanggapan  : " << daftarLaporan[i].tanggapan << "\n";
                }
                cout << "  ------------------------------------------------------\n";
            }

            cout << "\n  Masukkan ID Laporan untuk menanggapi (0 untuk batal): ";
            int idAksi;
            cin >> idAksi;

            if (idAksi == 0) continue;

            bool ditemukan = false;
            for (size_t i = 0; i < daftarLaporan.size(); i++) {
                if (daftarLaporan[i].id == idAksi) {
                    ditemukan = true;
                    cout << BOLD << "\n  Update Status Laporan:\n" << RESET;
                    cout << "  1. Diproses\n";
                    cout << "  2. Selesai\n";
                    cout << "  Pilih (1/2): ";
                    int st; cin >> st;

                    daftarLaporan[i].status = (st == 1) ? "Diproses" : "Selesai";

                    cout << "  Ketikkan tanggapan/solusi: ";
                    cin.ignore();
                    getline(cin, daftarLaporan[i].tanggapan);

                    cout << GREEN << "\n  [SUKSES] Laporan berhasil ditanggapi.\n\n" << RESET;
                    break;
                }
            }
            if (!ditemukan) cout << RED << "\n  [GAGAL] ID Laporan tidak ditemukan.\n\n" << RESET;

            system("pause");
        }
    } while (pilihan != 2);
}


void menuKonfirmasiAdminBaru(vector<Users>& daftarUser) {
    int pilihan;
    do {
        system("cls");
        cout << BLUE << BOLD << "\n  === KONFIRMASI PERANGKAT DESA BARU ===\n\n" << RESET;

        bool adaPending = false;
        for (size_t i = 0; i < daftarUser.size(); i++) {
            if (daftarUser[i].level == PerangkatDesa && !daftarUser[i].isApproved) {
                adaPending = true;
                cout << "  " << YELLOW << "[PENDING] " << RESET << daftarUser[i].username
                    << " - " << daftarUser[i].name << "\n";
            }
        }

        if (!adaPending) {
            cout << GREEN << "  Tidak ada antrian pendaftaran admin baru.\n\n" << RESET;
            system("pause");
            return;
        }

        cout << "\n  1. Approve Akun\n  2. Kembali\n\n  " << BOLD << "Pilih: " << RESET;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');

            system("cls");
            cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
            system("pause");
            continue;
        }

        if (pilihan == 1) {
            string targetNIK;
            cout << "  Masukkan NIK yang ingin di-approve: ";
            cin >> targetNIK;

            bool ketemu = false;
            for (size_t i = 0; i < daftarUser.size(); i++) {
                if (daftarUser[i].username == targetNIK && daftarUser[i].level == PerangkatDesa && !daftarUser[i].isApproved) {
                    daftarUser[i].isApproved = true; // AKUN DISETUJUI DI SINI
                    cout << GREEN << "\n  [SUKSES] Akun atas nama " << daftarUser[i].name << " berhasil disetujui dan kini bisa login!\n\n" << RESET;
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << RED << "\n  [GAGAL] NIK tidak ditemukan di daftar tunggu.\n\n" << RESET;
            system("pause");
        }
    } while (pilihan != 2);
}


void menuManajemenAkun(vector<Users>& daftarUser, const vector<Penduduk>& daftarPenduduk, string usernameActive) {
    int pilihan;
    do {
        system("cls");
        cout << CYAN << BOLD << "\n  === MANAJEMEN AKUN & VERIFIKASI ===\n\n" << RESET;
        cout << "  1. Verifikasi Akun Perangkat Desa Baru\n";
        cout << "  2. Lihat Semua Akun Terdaftar\n";
        cout << "  3. Tambah Akun Manual\n";
        cout << "  4. Edit Data Akun\n";
        cout << "  5. Hapus Akun\n";
        cout << "  6. Kembali ke Menu Utama\n\n";
        cout << "  " << BOLD << "Pilih Menu (1-6): " << RESET;
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');

            system("cls");
            cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
            system("pause");
            continue;
        }

        switch (pilihan) {
        case 1: { 
            system("cls");
            cout << YELLOW << BOLD << "\n  >>> VERIFIKASI AKUN PERANGKAT DESA <<<\n\n" << RESET;
            cout << "  -----------------------------------------------------------------------\n";
            cout << "  " << left << setw(20) << "Username (NIK)" << setw(25) << "Nama Lengkap" << "Status\n";
            cout << "  -----------------------------------------------------------------------\n";

            bool adaPending = false;
            for (size_t i = 0; i < daftarUser.size(); i++) {
                if (!daftarUser[i].isApproved) {
                    cout << "  " << left << setw(20) << daftarUser[i].username
                        << setw(25) << daftarUser[i].name
                        << RED << "[MENUNGGU KONFIRMASI]\n" << RESET;
                    adaPending = true;
                }
            }
            cout << "  -----------------------------------------------------------------------\n\n";

            if (!adaPending) {
                cout << GREEN << "  (Tidak ada akun yang menunggu verifikasi saat ini)\n\n" << RESET;
                system("pause");
                break;
            }

            string targetUser;
            cout << "  Masukkan Username (NIK) yang ingin diproses: ";
            cin >> targetUser;

            bool ketemu = false;
            for (vector<Users>::iterator it = daftarUser.begin(); it != daftarUser.end(); ++it) {
                if (it->username == targetUser && !it->isApproved) {
                    ketemu = true;
                    cout << "\n  Tindakan untuk akun " << BOLD << it->name << RESET << ":\n";
                    cout << "  1. Setujui (Approve)\n";
                    cout << "  2. Tolak & Hapus Data\n";
                    cout << "  Pilihan (1/2): ";
                    int aksi; cin >> aksi;

                    if (aksi == 1) {
                        it->isApproved = true;
                        cout << GREEN << "\n  [SUKSES] Akun berhasil diverifikasi. User kini bisa login!\n\n" << RESET;
                    }
                    else {
                        daftarUser.erase(it);
                        cout << RED << "\n  [INFO] Pengajuan ditolak dan data akun dihapus.\n\n" << RESET;
                    }
                    break;
                }
            }
            if (!ketemu) cout << RED << "\n  [GAGAL] Username tidak ditemukan atau sudah disetujui sebelumnya.\n\n" << RESET;
            system("pause");
            break;
        }
        case 2: { // READ ALL ACCOUNTS
            system("cls");
            cout << BLUE << BOLD << "\n  >>> DAFTAR AKUN TERDAFTAR <<<\n\n" << RESET;
            cout << "  ------------------------------------------------------------------------------------------\n";
            cout << "  " << left << setw(20) << "Username (NIK)"
                << setw(30) << "Nama Lengkap"
                << setw(20) << "Role"
                << "Status Akses\n";
            cout << "  ------------------------------------------------------------------------------------------\n";

            for (size_t i = 0; i < daftarUser.size(); i++) {
                string strRole = (daftarUser[i].level == PerangkatDesa) ? "Perangkat Desa" : "Warga";
                string strStatus = (daftarUser[i].isApproved) ? (GREEN + string("AKTIF") + RESET) : (RED + string("PENDING") + RESET);

                cout << "  " << left << setw(20) << daftarUser[i].username
                    << setw(30) << daftarUser[i].name
                    << setw(20) << strRole
                    << strStatus << "\n";
            }
            cout << "  ------------------------------------------------------------------------------------------\n\n";
            system("pause");
            break;
        }
        case 3: { // CREATE ACCOUNT MANUAL
            system("cls");
            cout << GREEN << BOLD << "\n  >>> TAMBAH AKUN MANUAL <<<\n\n" << RESET;

            Users uBaru;
            cin.ignore();
            cout << "  Masukkan NIK (Username) : ";
            getline(cin, uBaru.username);

            // Cek duplikasi
            bool duplikat = false;
            for (size_t i = 0; i < daftarUser.size(); i++) {
                if (daftarUser[i].username == uBaru.username) {
                    duplikat = true; break;
                }
            }
            if (duplikat) {
                cout << RED << "\n  [GAGAL] Username/NIK tersebut sudah terdaftar!\n\n" << RESET;
                system("pause"); break;
            }

            cout << "  Nama Lengkap            : ";
            getline(cin, uBaru.name);
            cout << "  Password                : ";
            getline(cin, uBaru.passwd);

            cout << "  Role (1. Admin / 2. Warga): ";
            int r; cin >> r;
            uBaru.level = (r == 1) ? PerangkatDesa : Warga;
            uBaru.isApproved = true; 

            daftarUser.push_back(uBaru);
            cout << GREEN << BOLD << "\n  [SUKSES] Akun baru berhasil ditambahkan!\n\n" << RESET;
            system("pause");
            break;
        }
        case 4: { // UPDATE ACCOUNT
            system("cls");
            cout << YELLOW << BOLD << "\n  >>> EDIT DATA AKUN <<<\n\n" << RESET;

            string targetUser;
            cout << "  Masukkan Username (NIK) yang akan diedit: ";
            cin >> targetUser;

            bool ketemu = false;
            for (size_t i = 0; i < daftarUser.size(); i++) {
                if (daftarUser[i].username == targetUser) {
                    ketemu = true;
                    cout << "\n  Ditemukan akun milik: " << BOLD << daftarUser[i].name << RESET << "\n";
                    cout << "  Apa yang ingin diubah?\n";
                    cout << "  1. Nama Lengkap\n";
                    cout << "  2. Password\n";
                    cout << "  3. Role / Hak Akses\n";
                    cout << "  Pilihan (1-3): ";
                    int u; cin >> u;

                    cin.ignore();
                    if (u == 1) {
                        cout << "  Masukkan Nama Baru: ";
                        getline(cin, daftarUser[i].name);
                        cout << GREEN << "\n  [SUKSES] Nama berhasil diubah.\n\n" << RESET;
                    }
                    else if (u == 2) {
                        cout << "  Masukkan Password Baru: ";
                        getline(cin, daftarUser[i].passwd);
                        cout << GREEN << "\n  [SUKSES] Password berhasil diubah.\n\n" << RESET;
                    }
                    else if (u == 3) {
                        cout << "  Pilih Role Baru (1. Admin / 2. Warga): ";
                        int rBaru; cin >> rBaru;
                        daftarUser[i].level = (rBaru == 1) ? PerangkatDesa : Warga;
                        cout << GREEN << "\n  [SUKSES] Role berhasil diubah.\n\n" << RESET;
                    }
                    break;
                }
            }
            if (!ketemu) cout << RED << "\n  [GAGAL] Username (NIK) tidak ditemukan.\n\n" << RESET;
            system("pause");
            break;
        }
        case 5: { // DELETE ACCOUNT
            system("cls");
            cout << RED << BOLD << "\n  >>> HAPUS AKUN <<<\n\n" << RESET;

            string targetUser;
            cout << "  Masukkan Username (NIK) yang akan dihapus: ";
            cin >> targetUser;

            if (targetUser == usernameActive) {
                cout << RED << "\n  [AKSES DITOLAK] Anda tidak bisa menghapus akun Anda sendiri saat sedang login!\n\n" << RESET;
                system("pause");
                break;
            }

            bool ketemu = false;
            for (vector<Users>::iterator it = daftarUser.begin(); it != daftarUser.end(); ++it) {
                if (it->username == targetUser) {
                    ketemu = true;
                    cout << YELLOW << "\n  Yakin ingin menghapus akun " << it->name << "? (y/n): " << RESET;
                    string konfirmasi; cin >> konfirmasi;

                    if (konfirmasi == "y" || konfirmasi == "Y") {
                        daftarUser.erase(it);
                        cout << GREEN << "\n  [SUKSES] Akun berhasil dihapus permanen dari sistem.\n\n" << RESET;
                    }
                    else {
                        cout << "\n  [INFO] Penghapusan dibatalkan.\n\n";
                    }
                    break;
                }
            }
            if (!ketemu) cout << RED << "\n  [GAGAL] Username (NIK) tidak ditemukan.\n\n" << RESET;
            system("pause");
            break;
        }
        }
    } while (pilihan != 6);
}

