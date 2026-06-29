#include "infodesa.h"
#include "style.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    // DATABASE UTAMA
    vector<Users> daftarUser;
    vector<Surat> daftarSurat;
    vector<Laporan> daftarLaporan;
    vector<Penduduk> daftarPenduduk;
    vector<Berita> daftarBerita;
    vector<Darurat> daftarDarurat;

    int pilihMenu, pilihLayanan;

    // Default Akun untuk Testing
    //Users adminPDDefault = { "adminpd", "adminpd", "123", PerangkatDesa, true };
    //Users adminWDefault = { "adminwarga", "adminw", "123", Warga, true };
    //daftarUser.push_back(adminWDefault);
    //daftarUser.push_back(adminPDDefault);

    // Default Berita
   

    DataDummy(daftarPenduduk, daftarUser, daftarBerita);

    while (true) {
        bool successLogin = true;
        bool Exit = true;
        Role RoleLogin = GagalLogin;
        string namaLogin = "";
        string usernameLogin = "";

        //LANDING PAGE
        do {
            system("cls");
            cout << CYAN << BOLD;
            cout << "\n  ======================================================\n";
            cout << "  ||                                                  ||\n";
            cout << "  ||         S E L A M A T   D A T A N G   D I        ||\n";
            cout << "  ||                I N F O D E S A                   ||\n";
            cout << "  ||          Sistem Informasi Desa Digital           ||\n";
            cout << "  ||                                                  ||\n";
            cout << "  ======================================================\n" << RESET;

            cout << "\n  " << BOLD << "[ P O R T A L   U T A M A ]\n\n" << RESET;
            cout << GREEN << "  1. " << RESET << "Login ke Sistem\n";
            cout << CYAN << "  2. " << RESET << "Registrasi Akun Baru\n";
            cout << RED << "  3. " << RESET << "Keluar Aplikasi\n\n";
            cout << "  " << BOLD << "Pilih Menu (1-3) : " << RESET;

            cin >> pilihMenu;

            //untuk tidak error saat salah input
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(10000, '\n'); 

                system("cls");
                cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
                system("pause");
                continue;     
            }

            switch (pilihMenu) {
            case 1: {
                system("cls");
                RoleLogin = loginUser(daftarUser, namaLogin, usernameLogin);
                if (RoleLogin != GagalLogin) successLogin = false; 
                break;
            }
            case 2:
                system("cls");
                registrasiUser(daftarUser, daftarPenduduk);
                system("pause"); 
                break;
            case 3:
                system("cls");
                cout << GREEN << BOLD << "\n  Terima kasih telah menggunakan INFODESA. Sampai jumpa!\n\n" << RESET;
                return 0;
            default:
                system("cls");
                cout << RED << BOLD << "\n  [ERROR] Pilihan tidak valid! Silakan masukkan angka 1, 2, atau 3.\n\n" << RESET;
                system("pause");
            }
        } while (successLogin);

   
        //MENU UTAMA
        do {
            system("cls");
            if (RoleLogin == PerangkatDesa) {
                screenPD(namaLogin);
                cin >> pilihLayanan;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    system("cls");
                    cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
                    system("pause");
                    continue;
                }

                switch (pilihLayanan) {
                case 1: menuSuratPD(daftarSurat); break;
                case 2: menuKependudukanPD(daftarPenduduk); break;
                case 3: menuPengaduanPD(daftarLaporan); break;
                case 4: menuKabarDesa(daftarBerita, RoleLogin); break;
                case 5: menuManajemenAkun(daftarUser, daftarPenduduk, usernameLogin);; break;
                case 6: menuPanicButton(daftarDarurat, RoleLogin, usernameLogin); break;
                case 7: Exit = false; break; 
                case 8: return 0;            
                default:
                    cout << RED << "\n  [ERROR] Pilihan tidak valid!\n" << RESET;
                    system("pause");
                    break;
                }
            }
            else if (RoleLogin == Warga) {
                screenWarga(namaLogin);
                cin >> pilihLayanan;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    system("cls");
                    cout << RED << BOLD << "\n  [ERROR] Input tidak valid! Harap masukkan ANGKA.\n\n" << RESET;
                    system("pause");
                    continue;
                }

                switch (pilihLayanan) {
                case 1: menuSuratWarga(daftarSurat, usernameLogin, namaLogin); break;
                case 2: menuPengaduanWarga(daftarLaporan, usernameLogin); break;
                case 3: menuKabarDesa(daftarBerita, RoleLogin); break;
                case 4: menuPanicButton(daftarDarurat, RoleLogin, usernameLogin); break;
                case 5: Exit = false; break; 
                case 6: return 0;          
                default:
                    cout << RED << "\n  [ERROR] Pilihan tidak valid!\n" << RESET;
                    system("pause");
                    break;
                }
            }
        } while (Exit);

      
        system("cls");
    }
    return 0;
}