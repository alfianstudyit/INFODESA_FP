#include "infodesa.h"
#include "style.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

string inputPassword();

void registrasiUser(vector<Users>& daftarUser, const vector<Penduduk>& daftarPenduduk) {
    string inpUsername, inpPasswd, inpNama;
    int pilihanRole;
    bool inputValid = false;

    system("cls");
    cout << CYAN << BOLD;
    cout << "\n  ======================================\n";
    cout << "  ||      F O R M   D A F T A R       ||\n";
    cout << "  ======================================\n" << RESET;

    cout << "\n  " << BOLD << "Pilih Jenis Akun yang akan didaftarkan:" << RESET << "\n";
    cout << CYAN << "  1. " << RESET << "Perangkat Desa (Admin)\n";
    cout << CYAN << "  2. " << RESET << "Warga Masyarakat\n";
    cout << RED << "  3. " << RESET << "Kembali\n";

    do {
        cout << "  " << BOLD << "Pilihan (1/2)  : " << RESET;
        cin >> pilihanRole;

        if (cin.fail() || (pilihanRole != 1 && pilihanRole != 2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << RED << "  [ERROR] Pilihan tidak valid! Masukkan angka 1 atau 2.\n" << RESET;
        }
        else {
            inputValid = true;
        }
    } while (!inputValid);

    system("cls");
    cout << CYAN << BOLD;
    cout << "\n  ======================================\n";
    cout << (pilihanRole == 1 ? "  ||   R E G I S T R A S I  A D M I N ||\n" : "  ||   R E G I S T R A S I  W A R G A ||\n");
    cout << "  ======================================\n" << RESET;

    cin.ignore();

    cout << "\n  " << BOLD << "Username (Masukkan NIK Anda) : " << RESET;
    getline(cin, inpUsername);

    bool nikTerdaftarDiDesa = false;

    for (size_t i = 0; i < daftarPenduduk.size(); i++) {
        if (daftarPenduduk[i].NIK == inpUsername) {
            nikTerdaftarDiDesa = true;
            break;
        }
    }

    if (!nikTerdaftarDiDesa) {
        cout << RED << BOLD << "\n  [AKSES DITOLAK] " << RESET << "NIK Anda tidak terdaftar di database kependudukan!\n";
        cout << "  Silakan hubungi Perangkat Desa untuk pendataan warga terlebih dahulu.\n\n";
        return; 
    }

    // 2. CEK AGAR NIK TIDAK DIDAFTARKAN 2 KALI
    for (size_t i = 0; i < daftarUser.size(); i++) {
        if (daftarUser[i].username == inpUsername) {
            cout << RED << BOLD << "\n  [GAGAL] " << RESET << "Akun dengan NIK tersebut sudah pernah didaftarkan!\n\n";
            return;
        }
    }

    cout << "  " << BOLD << "Nama Lengkap                 : " << RESET;
    getline(cin, inpNama);
    cout << "  " << BOLD << "Password                     : " << RESET;
    getline(cin, inpPasswd);

    bool statusApprove = (pilihanRole == 2) ? true : false;

    daftarUser.push_back({ inpNama, inpUsername, inpPasswd, (pilihanRole == 1) ? PerangkatDesa : Warga, statusApprove });

    system("cls");
    if (pilihanRole == 1) {
        cout << YELLOW << BOLD << "\n  [PENDING] " << RESET << "Akun Perangkat Desa berhasil dibuat!\n";
        cout << "  Namun, Anda BELUM BISA LOGIN sebelum dikonfirmasi oleh Admin Pusat.\n\n";
    }
    else {
        cout << GREEN << BOLD << "\n  [SUKSES] " << RESET << "Akun Warga berhasil didaftarkan!\n";
        cout << "  Silakan login menggunakan NIK dan Password Anda.\n\n";
    }
}

//login
Role loginUser(const vector<Users>& daftarUser, string& namaLogin, string& usernameLogin) {
    string inpUsername, inpPasswd;

    system("cls");
    cout << BLUE << BOLD << "\n  ======================================\n";
    cout << "  ||       P O R T A L   L O G I N    ||\n";
    cout << "  ======================================\n" << RESET;

    cin.ignore();
    cout << "\n  " << BOLD << "Username (NIK) : " << RESET;
    getline(cin, inpUsername);
    cout << "  " << BOLD << "Password       : " << RESET;
    inpPasswd = inputPassword();

    bool usernameDitemukan = false;
    for (size_t i = 0; i < daftarUser.size(); i++) {
        if (inpUsername == daftarUser[i].username) {
            usernameDitemukan = true;
            if (inpPasswd == daftarUser[i].passwd) {

                // CEK STATUS APPROVAL
                if (!daftarUser[i].isApproved) {
                    system("cls");
                    cout << YELLOW << BOLD << "\n  [AKSES DITUNGGU] " << RESET << "Akun Anda sedang menunggu persetujuan Admin.\n";
                    cout << "  Harap hubungi kepala desa atau admin utama.\n\n";
                    system("pause");
                    return GagalLogin;
                }

                system("cls");
                namaLogin = daftarUser[i].name;
                usernameLogin = daftarUser[i].username;
                return daftarUser[i].level;
            }
            else {
                system("cls");
                cout << RED << BOLD << "\n  [AKSES DITOLAK] " << RESET << "Password yang Anda masukkan salah!\n\n";
                system("pause");
                return GagalLogin;
            }
        }
    }

    if (!usernameDitemukan) {
        system("cls");
        cout << RED << BOLD << "\n  [AKSES DITOLAK] " << RESET << "Username (NIK) tidak ditemukan!\n\n";
        system("pause");
    }
    return GagalLogin;
}

string inputPassword() {
    string passwd = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) {
            cout << endl;
            break;
        }

        else if (ch == 8) {
            if (passwd.length() > 0) {
                passwd.pop_back(); 
                cout << "\b \b";  
            }
        }
   
        else {
            passwd += ch;
            cout << (char)254;
        }
    }
    return passwd;
}