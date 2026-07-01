#ifndef INFODESA_H
#define INFODESA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


// ENUM & STRUCT
enum Role {
    PerangkatDesa = 1,
    Warga = 2,
    GagalLogin = 0
};

struct Users {
    string name;
    string username;
    string passwd;
    Role level;
    bool isApproved;
};

struct Surat {
    int id;
    string usernameWarga;
    string jenisSurat;
    string keterangan;
    string lampiran;
    string status;
    string tanggal; 
    string tanggalProses;
};

struct Laporan {
    int id;
    string usernameWarga;
    string jenis;
    string isi;
    string lokasi;
    string foto;
    string status;
    string tanggapan;
    string tanggal;
    string tanggalProses;
};

struct Penduduk {
    string NIK;
    string nama;
    string alamat;
    string birth;
    string agama;
    string pendidikan;
    string pekerjaan;
};

struct Berita {
    int id;
    string judul;
    string isi;
    string tanggal;
    string lokasi;
};

struct Darurat {
    int id;
    string pelapor;
    string kondisi;
    string status;
};



// PROTOTIPE FUNGSI
void registrasiUser(vector<Users>& daftarUser, const vector<Penduduk>& daftarPenduduk);
Role loginUser(const vector<Users>& daftarUser, string& namaLogin, string& usernameLogin);
void screenWarga(string nama);
void screenPD(string nama);
void menuSuratWarga(vector<Surat>& daftarSurat, string usernameActive, string namaActive);
void menuSuratPD(vector<Surat>& daftarSurat);
void menuPengaduanWarga(vector<Laporan>& daftarLaporan, string usernameActive);
void menuPengaduanPD(vector<Laporan>& daftarLaporan);
void menuKependudukanPD(vector<Penduduk>& daftarPenduduk);
void menuKabarDesa(vector<Berita>& daftarBerita, Role roleActive);
void menuPanicButton(vector<Darurat>& daftarDarurat, Role roleActive, string usernameActive);
void insertionSortPenduduk(vector<Penduduk>& arr);
int binarySearchPenduduk(const vector<Penduduk>& arr, string targetNIK);
void menuKonfirmasiAdminBaru(vector<Users>& daftarUser);
void DataDummy(vector<Penduduk>& daftarPenduduk, vector<Users>& daftarUser, vector<Berita>& daftarBerita);
void menuManajemenAkun(vector<Users>& daftarUser, const vector<Penduduk>& daftarPenduduk, string usernameActive);
void tampilkanPreviewSurat(string namaFileWeb);




//khusus antrean warga
const int MAX_QUEUE = 10;

struct Antrean {
    string noTiket;
    string namaWarga;
    string keperluan;
    string waktuDaftar;
};

struct QueueOnline {
    int depan;
    int belakang;
    Antrean data[MAX_QUEUE];
};

void inisialisasi(QueueOnline& q);
bool isEmpty(QueueOnline& q);
bool isFull(QueueOnline& q);
void ambilAntreanOnline(QueueOnline& q);



#endif // INFODESA_H