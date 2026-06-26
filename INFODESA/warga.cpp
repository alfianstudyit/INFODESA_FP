#include "infodesa.h"
#include "style.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

void screenWarga(string nama) {
    system("cls");
    cout << CYAN << BOLD;
    cout << "  ======================================================\n";
    cout << "  ||                                                  ||\n";
    cout << "  ||               I N F O D E S A                    ||\n";
    cout << "  ||         Sistem Informasi Desa Digital            ||\n";
    cout << "  ||                                                  ||\n";
    cout << "  ======================================================\n" << RESET;

    cout << "\n  Selamat datang, " << BOLD << GREEN << nama << RESET << "!\n";
    cout << "  Silakan pilih layanan yang Anda butuhkan hari ini:\n\n";

    cout << BOLD << "  [ MENU LAYANAN ]\n" << RESET;
    cout << CYAN << "  1. " << RESET << "Layanan Surat\n";
    cout << CYAN << "  2. " << RESET << "Layanan Pengaduan\n";
    cout << CYAN << "  3. " << RESET << "Kabar Desa\n";
    cout << RED << "  4. " << "Panic Button\n" << RESET;
    cout << YELLOW << "  5. " << RESET << "Logout\n";
    cout << YELLOW << "  6. " << RESET << "Exit\n\n";
    cout << "  Masukkan pilihan Anda: ";
}

void menuSuratWarga(vector<Surat>& daftarSurat, string usernameActive, string namaActive) {
    int pilihan;
    do {
        system("cls");
        cout << CYAN << BOLD << "\n  === LAYANAN SURAT MENYURAT ===\n\n" << RESET;
        cout << "  1. Ajukan Surat Baru\n";
        cout << "  2. Tracking Status Surat\n";
        cout << "  3. Hapus Pengajuan Surat\n";
        cout << "  4. Cetak / Print Surat\n";
        cout << "  5. Kembali ke Menu Utama\n\n";
        cout << "  " << BOLD << "Pilih Menu: " << RESET;
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            system("cls");
            Surat sBaru;
            sBaru.id = daftarSurat.size() + 1;
            sBaru.usernameWarga = usernameActive;
            sBaru.status = "Menunggu";
            sBaru.lampiran = "-";

            cout << CYAN << BOLD << "\n  >>> AJUKAN SURAT BARU <<<\n\n" << RESET;
            cout << "  Pilih Jenis Surat yang Diperlukan:\n";
            cout << "  1. Surat Keterangan Tidak Mampu (SKTM)\n";
            cout << "  2. Surat Keterangan Usaha (SKU)\n";
            cout << "  3. Surat Keterangan Domisili\n";
            cout << "  4. Surat Pengantar SKCK\n";
            cout << "  Pilih (1-4): ";
            int pilSurat; cin >> pilSurat;

            if (pilSurat == 1) sBaru.jenisSurat = "Surat Keterangan Tidak Mampu (SKTM)";
            else if (pilSurat == 2) sBaru.jenisSurat = "Surat Keterangan Usaha (SKU)";
            else if (pilSurat == 3) sBaru.jenisSurat = "Surat Keterangan Domisili";
            else if (pilSurat == 4) sBaru.jenisSurat = "Surat Pengantar SKCK";

            cin.ignore();
            cout << "\n  [ Jenis terpilih: " << sBaru.jenisSurat << " ]\n";
            cout << "  Tanggal Pengajuan (misal: 15 Juni 2026) : ";
            getline(cin, sBaru.tanggal);
            cout << "  Keterangan / Keperluan Tambahan : ";
            getline(cin, sBaru.keterangan);

            daftarSurat.push_back(sBaru);
            cout << GREEN << BOLD << "\n  [SUKSES] " << RESET << "Surat berhasil diajukan! Cek menu Tracking secara berkala.\n\n";
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            cout << CYAN << BOLD << "\n  >>> TRACKING STATUS SURAT <<<\n\n" << RESET;

            cout << "  ----------------------------------------------------------------------------------------------------------------------\n";
            cout << "  " << left << setw(5) << "ID"
                << setw(40) << "Jenis Surat"
                << setw(20) << "Tanggal Pengajuan"
                << setw(15) << "Status"
                << "Catatan / Lampiran\n";
            cout << "  ----------------------------------------------------------------------------------------------------------------------\n";

            bool ketemu = false;
            for (size_t i = 0; i < daftarSurat.size(); i++) {
                if (daftarSurat[i].usernameWarga == usernameActive) {
                    string warnaStatus = (daftarSurat[i].status == "Selesai") ? GREEN : (daftarSurat[i].status == "Ditolak") ? RED : YELLOW;

                    cout << "  " << left << setw(5) << daftarSurat[i].id
                        << setw(40) << daftarSurat[i].jenisSurat
                        << setw(20) << daftarSurat[i].tanggal
                        << warnaStatus << setw(15) << ("[" + daftarSurat[i].status + "]") << RESET
                        << daftarSurat[i].lampiran << "\n";
                    ketemu = true;
                }
            }
            if (!ketemu) cout << YELLOW << "  Belum ada riwayat pengajuan surat.\n" << RESET;
            cout << "  ----------------------------------------------------------------------------------------------------------------------\n\n";
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            cout << RED << BOLD << "\n  >>> HAPUS / BATALKAN PENGAJUAN SURAT <<<\n\n" << RESET;

            cout << "  Daftar Riwayat Surat Anda:\n";
            cout << "  ------------------------------------------------------------------------\n";
            bool adaSurat = false;
            for (size_t i = 0; i < daftarSurat.size(); i++) {
                if (daftarSurat[i].usernameWarga == usernameActive) {
                    string warnaStatus = (daftarSurat[i].status == "Selesai") ? GREEN : (daftarSurat[i].status == "Ditolak") ? RED : YELLOW;

                    cout << "  " << BOLD << "[ID: " << daftarSurat[i].id << "] " << RESET
                        << left << setw(40) << daftarSurat[i].jenisSurat
                        << warnaStatus << "[" << daftarSurat[i].status << "]\n" << RESET;
                    adaSurat = true;
                }
            }
            if (!adaSurat) {
                cout << YELLOW << "  (Anda belum memiliki riwayat pengajuan surat.)\n" << RESET;
                cout << "  ------------------------------------------------------------------------\n\n";
                system("pause");
                break;
            }
            cout << "  ------------------------------------------------------------------------\n\n";

            int idHapus;
            cout << "  Masukkan ID Surat yang ingin dibatalkan/dihapus: ";
            cin >> idHapus;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << RED << "\n  [ERROR] ID harus berupa angka!\n\n" << RESET;
                system("pause");
                break;
            }

            bool berhasil = false;
            for (vector<Surat>::iterator it = daftarSurat.begin(); it != daftarSurat.end(); ++it) {
                if (it->id == idHapus && it->usernameWarga == usernameActive) {

                    string konfirmasi;
                    cout << YELLOW << "  Apakah Anda yakin ingin menghapus surat ini? (y/n): " << RESET;
                    cin >> konfirmasi;

                    if (konfirmasi == "y" || konfirmasi == "Y") {
                        daftarSurat.erase(it);
                        berhasil = true;
                        cout << GREEN << "\n  [BERHASIL] Pengajuan surat dengan ID " << idHapus << " telah dihapus permanen.\n\n" << RESET;
                    }
                    else {
                        berhasil = true; 
                        cout << "\n  [INFO] Penghapusan dibatalkan.\n\n";
                    }
                    break;
                }
            }
            if (!berhasil) cout << RED << "\n  [GAGAL] ID Surat tidak ditemukan atau bukan milik Anda.\n\n" << RESET;
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            cout << BLUE << BOLD << "\n  >>> CETAK DOKUMEN DIGITAL <<<\n\n" << RESET;

            cout << "  Daftar Surat Anda yang siap dicetak:\n";
            cout << "  ------------------------------------------------------------------------\n";
            bool adaSiapCetak = false;
            for (size_t i = 0; i < daftarSurat.size(); i++) {
                if (daftarSurat[i].usernameWarga == usernameActive && daftarSurat[i].status == "Selesai") {
                    cout << "  " << BOLD << "[ID: " << daftarSurat[i].id << "] " << RESET << daftarSurat[i].jenisSurat << "\n";
                    adaSiapCetak = true;
                }
            }

            if (!adaSiapCetak) {
                cout << YELLOW << "  (Tidak ada surat dengan status 'Selesai' yang bisa dicetak saat ini)\n" << RESET;
                cout << "  ------------------------------------------------------------------------\n\n";
                system("pause");
                break;
            }
            cout << "  ------------------------------------------------------------------------\n\n";

            int idCtxt;
            cout << "  Masukkan ID Surat yang ingin dicetak: ";
            cin >> idCtxt;

            cin.ignore();
            string namaCetak;
            cout << "  Masukkan Nama Lengkap untuk di surat: ";
            getline(cin, namaCetak);

            //PATH
            string pathFolder = "D:\\kampus\\SEM 2\\STRUKTUR_DATA\\TUGAS AKHIR\\HASIL_PRINT\\";

            bool ketemu = false;
            for (size_t i = 0; i < daftarSurat.size(); i++) {
                if (daftarSurat[i].id == idCtxt && daftarSurat[i].usernameWarga == usernameActive) {
                    ketemu = true;
                    if (daftarSurat[i].status == "Selesai") {
                        stringstream ss; ss << daftarSurat[i].id;

                        string namaFileDoc = pathFolder + "Surat_INFODESA_" + ss.str() + ".doc";
                        string namaFileWeb = pathFolder + "Surat_INFODESA_" + ss.str() + ".html";

                        ofstream cetakSuratDoc(namaFileDoc.c_str());
                        ofstream cetakSuratWeb(namaFileWeb.c_str());

                        stringstream bufferHTML;

                        string kodeSurat = "000";
                        if (daftarSurat[i].jenisSurat == "Surat Keterangan Tidak Mampu (SKTM)") kodeSurat = "400/SKTM";
                        else if (daftarSurat[i].jenisSurat == "Surat Keterangan Usaha (SKU)") kodeSurat = "500/SKU";
                        else if (daftarSurat[i].jenisSurat == "Surat Keterangan Domisili") kodeSurat = "470/DOM";
                        else if (daftarSurat[i].jenisSurat == "Surat Pengantar SKCK") kodeSurat = "300/SKCK";

                        // GENERATE HTML KE BUFFER
                        bufferHTML << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Surat Resmi - Infodesa</title></head>";
                        bufferHTML << "<body style='display: flex; justify-content: center; padding: 20px; background-color: #f4f4f4;'>";
                        bufferHTML << "<div style='width: 210mm; font-family: \"Times New Roman\", Times, serif; color: black; background-color: white; padding: 20mm; box-shadow: 0 0 10px rgba(0,0,0,0.2);'>";

                        bufferHTML << "<div style='text-align: center; border-bottom: 3px double black; padding-bottom: 5px; margin-bottom: 2px;'>";
                        bufferHTML << "<div style='border-bottom: 1px solid black; padding-bottom: 10px;'>";
                        bufferHTML << "<h2 style='margin: 0; font-size: 20px; text-transform: uppercase; font-weight: normal;'>PEMERINTAH KABUPATEN SLEMAN</h2>";
                        bufferHTML << "<h2 style='margin: 2px 0; font-size: 22px; text-transform: uppercase; font-weight: bold;'>KECAMATAN GODEAN</h2>";
                        bufferHTML << "<h1 style='margin: 2px 0; font-size: 26px; text-transform: uppercase; font-weight: bold;'>KANTOR KEPALA DESA INFODESA</h1>";
                        bufferHTML << "<p style='margin: 5px 0 0 0; font-size: 12pt;'>Jl. Raya Sleman-Godean No. 45, Godean, Sleman, Daerah Istimewa Yogyakarta 55264</p>";
                        bufferHTML << "</div></div>";

                        bufferHTML << "<div style='text-align: center; margin-top: 35px;'>";
                        bufferHTML << "<h3 style='margin: 0; font-size: 14pt; text-transform: uppercase; text-decoration: underline;'>" << daftarSurat[i].jenisSurat << "</h3>";
                        bufferHTML << "<p style='margin: 5px 0 0 0; font-size: 12pt;'>Nomor: " << kodeSurat << " / " << daftarSurat[i].id << " / VI / 2026</p>";
                        bufferHTML << "</div>";

                        bufferHTML << "<div style='margin-top: 40px; font-size: 12pt; line-height: 1.5; text-align: justify;'>";
                        bufferHTML << "<p style='text-indent: 40px;'>Yang bertanda tangan di bawah ini, Kepala Desa Infodesa, Kecamatan Godean, Kabupaten Sleman, menerangkan dengan sesungguhnya bahwa:</p>";

                        bufferHTML << "<table style='margin-left: 50px; margin-top: 10px; margin-bottom: 10px; width: 85%; font-size: 12pt;'>";

                        // MEMASUKAN NAMA
                        bufferHTML << "<tr><td style='width: 220px; padding: 3px 0;'>Nama Lengkap</td><td style='width: 15px;'>:</td><td><b>" << namaCetak << "</b></td></tr>";

                        bufferHTML << "<tr><td style='padding: 3px 0;'>Nomor Induk Kependudukan (NIK)</td><td>:</td><td>" << usernameActive << "</td></tr>";
                        bufferHTML << "<tr><td style='padding: 3px 0;'>Kewarganegaraan</td><td>:</td><td>Indonesia</td></tr>";
                        bufferHTML << "</table>";

                        if (daftarSurat[i].jenisSurat == "Surat Keterangan Tidak Mampu (SKTM)") {
                            bufferHTML << "<p style='text-indent: 40px;'>Berdasarkan data yang ada pada kami, nama tersebut di atas benar-benar warga yang berdomisili di desa kami dan saat ini tergolong keluarga yang mempunyai tingkat ekonomi kurang mampu. Surat keterangan ini dibuat untuk keperluan penunjang pengajuan: <b>" << daftarSurat[i].keterangan << "</b>.</p>";
                        }
                        else if (daftarSurat[i].jenisSurat == "Surat Keterangan Usaha (SKU)") {
                            bufferHTML << "<p style='text-indent: 40px;'>Bahwa nama tersebut di atas benar merupakan warga kami yang saat ini memiliki dan menjalankan rintisan usaha mandiri yang berlokasi di wilayah Desa Infodesa. Surat keterangan usaha ini dikeluarkan secara resmi untuk keperluan: <b>" << daftarSurat[i].keterangan << "</b>.</p>";
                        }
                        else if (daftarSurat[i].jenisSurat == "Surat Keterangan Domisili") {
                            bufferHTML << "<p style='text-indent: 40px;'>Menyatakan bahwa yang bersangkutan adalah benar warga menetap dan berdomisili sah di wilayah hukum Desa Infodesa. Surat keterangan ini diberikan untuk memenuhi persyaratan administrasi pengurusan: <b>" << daftarSurat[i].keterangan << "</b>.</p>";
                        }
                        else {
                            bufferHTML << "<p style='text-indent: 40px;'>Sepanjang catatan dan pengamatan kami, warga tersebut di atas dikenal berkelakuan baik dalam kehidupan bermasyarakat serta tidak pernah terlibat tindakan kriminalitas atau melanggar hukum. Pengantar ini diberikan untuk syarat pembuatan SKCK dalam rangka: <b>" << daftarSurat[i].keterangan << "</b>.</p>";
                        }

                        bufferHTML << "<p style='text-indent: 40px;'>Demikian surat keterangan ini kami buat dengan sebenarnya dan penuh tanggung jawab untuk dapat dipergunakan sebagaimana mestinya oleh pihak yang berkepentingan.</p>";
                        bufferHTML << "</div>";

                        bufferHTML << "<div style='margin-top: 60px; float: right; width: 300px; text-align: center; font-size: 12pt;'>";
                        bufferHTML << "<p style='margin: 0;'>Godean, 15 Juni 2026</p>";
                        bufferHTML << "<p style='margin: 0;'><b>Kepala Desa Infodesa</b></p>";
                        bufferHTML << "<br><br><br><br>";
                        bufferHTML << "<p style='margin: 0; text-decoration: underline;'><b>( NAMA KEPALA DESA )</b></p>";
                        bufferHTML << "<p style='margin: 0;'>NIP. 19800101 201001 1 001</p>";
                        bufferHTML << "</div>";

                        bufferHTML << "<div style='clear: both;'></div>";
                        bufferHTML << "<div style='margin-top: 50px; border-top: 1px dashed gray; padding-top: 10px; font-size: 9pt; color: gray;'>";
                        bufferHTML << "Dokumen ini dicetak secara digital melalui Sistem Infodesa.<br>ID Verifikasi Sistem: <b>ID-" << daftarSurat[i].id << "-DGT</b>";
                        bufferHTML << "</div>";

                        bufferHTML << "</div></body></html>";

                        // CETAK BUFFER KE 2 FILE
                        cetakSuratDoc << bufferHTML.str();
                        cetakSuratWeb << bufferHTML.str();

                        cetakSuratDoc.close();
                        cetakSuratWeb.close();

                        cout << GREEN << "\n  [SUKSES] Dokumen surat resmi telah dicetak dalam 2 format sekaligus!\n" << RESET;
                        cout << "  1. Format MS Word (.doc) : " << BOLD << namaFileDoc << RESET << "\n";
                        cout << "  2. Format Website (.html): " << BOLD << namaFileWeb << RESET << "\n\n";
                        cout << "  Silakan cek folder tujuan untuk membuka berkas Anda.\n\n";
                    }
                    else if (daftarSurat[i].status == "Ditolak") {
                        cout << RED << "\n  [INFO] Maaf, pengajuan surat ini DITOLAK oleh perangkat desa.\n";
                        cout << "  Alasan Penolakan: " << BOLD << daftarSurat[i].lampiran << RESET << "\n\n";
                    }
                    else {
                        cout << YELLOW << "\n  [INFO] Surat ini masih berstatus PENDING (Menunggu verifikasi admin).\n\n" << RESET;
                    }
                    break;
                }
            }
            if (!ketemu) cout << RED << "\n  [GAGAL] ID Surat tidak ditemukan atau bukan milik Anda.\n\n" << RESET;
            system("pause");
            break;
        }
        } 
    } while (pilihan != 5); 
} 

void menuPengaduanWarga(vector<Laporan>& daftarLaporan, string usernameActive) {
    int pilihan;
    do {
        system("cls");
        cout << BLUE << BOLD << "\n  === S M A R T   R E P O R T ===\n\n" << RESET;
        cout << "  Mari bangun desa kita bersama!\n\n";
        cout << "  1. Buat Pengaduan\n";
        cout << "  2. Sampaikan Aspirasi\n";
        cout << "  3. Tracking Laporan Saya\n";
        cout << "  4. Kembali ke Menu Utama\n\n";
        cout << "  " << BOLD << "Pilih Menu: " << RESET;
        cin >> pilihan;

        if (pilihan == 1 || pilihan == 2) {
            system("cls");
            Laporan l;
            l.id = daftarLaporan.size() + 1;
            l.usernameWarga = usernameActive;
            l.status = "Pending";
            l.jenis = (pilihan == 1) ? "Pengaduan" : "Aspirasi";

            cout << CYAN << BOLD << "\n  >>> FORM " << ((pilihan == 1) ? "PENGADUAN" : "ASPIRASI") << " <<<\n\n" << RESET;
            cin.ignore();
            cout << "  Tuliskan isi " << ((pilihan == 1) ? "pengaduan" : "aspirasi") << " Anda:\n  > ";
            getline(cin, l.isi);
            cout << "\n Tanggal diajukan : ";
            getline(cin, l.tanggal);

            daftarLaporan.push_back(l);
            cout << GREEN << BOLD << "\n  [TERKIRIM] " << RESET << "Terima kasih atas partisipasi Anda!\n\n";
            system("pause");
        }
        else if (pilihan == 3) {
            system("cls");
            cout << CYAN << BOLD << "\n  >>> TRACKING LAPORAN & ASPIRASI <<<\n\n" << RESET;
            cout << "  --------------------------------------------------------------------------------\n";

            bool adaData = false;
            for (size_t i = 0; i < daftarLaporan.size(); i++) {
                if (daftarLaporan[i].usernameWarga == usernameActive) {
                    adaData = true;
                    string warna = (daftarLaporan[i].status == "Selesai") ? GREEN : YELLOW;
                    cout << "  [" << daftarLaporan[i].jenis << "] - "
                        << warna << "[" << daftarLaporan[i].status << "] " << RESET
                        << "\n  Isi: " << daftarLaporan[i].isi << "\n";
                    cout << "  --------------------------------------------------------------------------------\n";
                }
            }
            if (!adaData) cout << YELLOW << "  Anda belum mengirimkan laporan atau aspirasi apapun.\n" << RESET;
            cout << "\n";
            system("pause");
        }
    } while (pilihan != 4);
}