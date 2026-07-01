#include "infodesa.h"
#include "style.h"
#include <iostream>
#include <fstream> 
#include <iomanip>

using namespace std;

// --- FUNGSI UTAS QUEUE ---
void inisialisasi(QueueOnline& q) {
    q.depan = q.belakang = -1;
}

bool isEmpty(QueueOnline& q) {
    return (q.belakang == -1);
}

bool isFull(QueueOnline& q) {
    return (q.belakang >= (MAX_QUEUE - 1));
}





// --- FITUR UTAMA: AMBIL ANTREAN WARGA & CETAK KARCIS ---
void ambilAntreanOnline(QueueOnline& q) {
    int pilihan;
    do {
        system("cls");
        cout << CYAN << BOLD << "\n  === LAYANAN ANTREAN DIGITAL DESA ===\n\n" << RESET;
        cout << "  1. Ambil Nomor Antrean Baru\n";
        cout << "  9. Keluar Aplikasi\n\n";
        cout << "  Pilih Menu: "; cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (pilihan == 1) {
            if (isFull(q)) {
                system("cls");
                cout << RED << BOLD << "\n  [ERROR] Antrean hari ini sudah penuh! Silakan coba besok.\n\n" << RESET;
                system("pause");
                return;
            }

            Antrean wargaBaru;
            system("cls");
            cout << CYAN << BOLD << "=== SISTEM ANTREAN MANDIRI DESA ===\n\n" << RESET;

            cin.ignore();
            cout << "  Masukkan Nama Anda : "; getline(cin, wargaBaru.namaWarga);
            cout << "  Keperluan / Surat  : "; getline(cin, wargaBaru.keperluan);
            wargaBaru.waktuDaftar = "10:30 WIB"; 

            int nomorUrut = (q.belakang == -1) ? 1 : q.belakang + 2;
            wargaBaru.noTiket = "A-" + to_string(nomorUrut);

            if (isEmpty(q)) q.depan = 0;
            q.belakang++;
            q.data[q.belakang] = wargaBaru;

            //ath folder
            string folderPath = "D:\\kampus\\SEM 2\\STRUKTUR_DATA\\TUGAS AKHIR\\HASIL_PRINT\\";

            // 2. Gabungkan folder dengan nama file
            string namaFile = folderPath + "Karcis_" + wargaBaru.noTiket + ".html";

            ofstream fileKarcis(namaFile);

            if (fileKarcis.is_open()) {
                fileKarcis << "<!DOCTYPE html>\n<html>\n<head>\n<title>Karcis Antrean</title>\n";
                fileKarcis << "<style>\n";
                fileKarcis << "  body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #eef2f3; display: flex; justify-content: center; padding: 40px; }\n";
                fileKarcis << "  .karcis-box { background: #ffffff; width: 350px; padding: 30px; border-radius: 12px; box-shadow: 0 8px 16px rgba(0,0,0,0.1); text-align: center; border-top: 10px solid #0056b3; }\n";
                fileKarcis << "  .header { font-size: 20px; font-weight: bold; color: #333; letter-spacing: 1px; }\n";
                fileKarcis << "  .sub-header { font-size: 13px; color: #777; margin-bottom: 25px; }\n";
                fileKarcis << "  .title-nomor { font-size: 14px; color: #555; font-weight: 600; }\n";
                fileKarcis << "  .nomor-antrean { font-size: 55px; font-weight: 900; color: #0056b3; margin: 10px 0 20px 0; padding: 15px; background: #e9f2fa; border-radius: 8px; border: 2px dashed #0056b3; }\n";
                fileKarcis << "  .tabel-detail { width: 100%; text-align: left; font-size: 14px; margin-top: 20px; border-top: 1.5px solid #eee; padding-top: 15px; line-height: 1.8; }\n";
                fileKarcis << "  .tabel-detail th { color: #555; width: 35%; }\n";
                fileKarcis << "  .tabel-detail td { color: #222; font-weight: 600; }\n";
                fileKarcis << "  .footer-warning { margin-top: 25px; font-size: 12px; color: #c62828; background: #ffebee; padding: 12px; border-radius: 6px; border-left: 4px solid #c62828; text-align: left; line-height: 1.5; }\n";
                fileKarcis << "</style>\n";
                fileKarcis << "</head>\n<body>\n";

                // --- ISI KONTEN KARCIS ---
                fileKarcis << "<div class='karcis-box'>\n";
                fileKarcis << "  <div class='header'>PEMERINTAH DESA</div>\n";
                fileKarcis << "  <div class='sub-header'>Sistem Antrean Layanan Mandiri</div>\n";

                fileKarcis << "  <div class='title-nomor'>NOMOR ANTREAN ANDA:</div>\n";
                fileKarcis << "  <div class='nomor-antrean'>" << wargaBaru.noTiket << "</div>\n";

                // Tabel supaya titik duanya rapi
                fileKarcis << "  <table class='tabel-detail'>\n";
                fileKarcis << "    <tr><th>Nama</th><td>: " << wargaBaru.namaWarga << "</td></tr>\n";
                fileKarcis << "    <tr><th>Keperluan</th><td>: " << wargaBaru.keperluan << "</td></tr>\n";
                fileKarcis << "    <tr><th>Waktu</th><td>: " << wargaBaru.waktuDaftar << "</td></tr>\n";
                fileKarcis << "  </table>\n";

                // Catatan peringatan
                fileKarcis << "  <div class='footer-warning'>\n";
                fileKarcis << "    <b>* PERINGATAN PENTING:</b><br>Jika nomor dipanggil 3 kali berturut-turut dan Anda tidak hadir, maka antrean dinyatakan <b>HANGUS</b>.\n";
                fileKarcis << "  </div>\n";
                fileKarcis << "</div>\n";

                fileKarcis << "</body>\n</html>\n";
                fileKarcis.close();
            }

            // 3. Perintah buka file.
            string commandBukaHTML = "start \"\" \"" + namaFile + "\"";
            system(commandBukaHTML.c_str());
            

            system("cls");
            cout << GREEN << BOLD << "\n  [SUKSES] Nomor antrean berhasil dibuat!\n" << RESET;
            cout << "  --------------------------------------------\n";
            cout << "  Nomor Antrean Anda : " << BOLD << wargaBaru.noTiket << RESET << "\n";
            cout << "  File Karcis        : " << CYAN << namaFile << RESET << "\n";
            cout << "  --------------------------------------------\n";
            cout << RED << BOLD << "  NOTE: Jika dipanggil 3 kali tidak datang,\n";
            cout << "        maka karcis HANGUS.\n\n" << RESET;

            system("pause");
        }

    } while (pilihan != 9);
    
}