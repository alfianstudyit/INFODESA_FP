#include "infodesa.h"

void DataDummy(vector<Penduduk>& daftarPenduduk, vector<Users>& daftarUser, vector<Berita>& daftarBerita) {

    // 1. DUMMY AKUN DEFAULT
    daftarUser.push_back({ "ADMIN Perangkat Desa", "adminpd", "123", PerangkatDesa, true });
    daftarUser.push_back({ "Budi Santoso", "3404050101900001", "123", Warga, true });
    daftarUser.push_back({ "ADMIN Warga", "adminw", "123", Warga, true });


    // 2. DUMMY DATA KEPENDUDUKAN
    daftarPenduduk.push_back({ "3404050101900001", "Budi Santoso","26 Juni 2003","islam","Pegawai Negeri","S1", "Dusun Sidoagung RT 01/RW 02"});
    daftarPenduduk.push_back({ "3404050202950002", "Siti Aminah", "26 Juni 2003","islam","Pegawai Negeri","S1","Dusun Sidomulyo RT 03/RW 01" });
    daftarPenduduk.push_back({ "3404050303800003", "Bambang Pamungkas","26 Juni 2003","islam","Pegawai Negeri","S1", "Dusun Sidokarto RT 02/RW 04"});
    daftarPenduduk.push_back({ "3404050404990004", "Rina Wati", "26 Juni 2003","islam","Pegawai Negeri","S1","Dusun Sidoagung RT 01/RW 02"});
    daftarPenduduk.push_back({ "3404050505880005", "Agus Prasetyo","26 Juni 2003","islam","Pegawai Negeri","S1", "Dusun Sidomoyo RT 05/RW 02"});
    daftarPenduduk.push_back({ "3404050606750006", "Sri Rahayu", "26 Juni 2003","islam","Pegawai Negeri","S1","Dusun Sidoarum RT 04/RW 03"});
    daftarPenduduk.push_back({ "3404050707920007", "Eko Susanto", "26 Juni 2003","islam","Pegawai Negeri","S1","Dusun Sidomulyo RT 02/RW 01"});
    daftarPenduduk.push_back({ "3404050808850008", "Endang Lestari", "26 Juni 2003","islam","Pegawai Negeri","S1","Dusun Sidoarum RT 01/RW 05" });
    daftarPenduduk.push_back({ "3404050909980009", "Rizky Pratama","26 Juni 2003","islam","Pegawai Negeri","S1", "Dusun Sidokarto RT 03/RW 03" });
    daftarPenduduk.push_back({ "3404051010010010", "Dewi Safitri","26 Juni 2003","islam","Pegawai Negeri","S1", "Dusun Sidomoyo RT 01/RW 04" });

    // 3. DUMMY BERITA
    daftarBerita.push_back({ 1, "Jadwal Posyandu", "Posyandu diadakan besok jam 8 pagi di Balai Desa." });
    daftarBerita.push_back({ 1, "Jadwal Posyandu", "Posyandu diadakan besok jam 8 pagi di Balai Desa." });
    daftarBerita.push_back({ 2, "Gotong Royong", "Kerja bakti pembersihan selokan utama akan dilaksanakan hari Minggu." });
    daftarBerita.push_back({ 3, "Pendaftaran BLT", "Pendaftaran bantuan BLT tahap 2 dibuka mulai hari Senin depan." });
    daftarBerita.push_back({ 4, "Perbaikan Jalan", "Jalan utama desa akan ditutup sementara untuk pengaspalan." });
    daftarBerita.push_back({ 5, "Rapat HUT RI", "Rapat persiapan lomba 17 Agustus bertempat di Balai Desa malam ini." });
    daftarBerita.push_back({ 6, "Pelatihan UMKM", "Pelatihan digital marketing untuk pelaku usaha desa diadakan besok." });
    daftarBerita.push_back({ 7, "Sosialisasi Pajak", "Sosialisasi pembayaran PBB dilakukan di kantor desa pukul 09.00." });
    daftarBerita.push_back({ 8, "Lomba Kebersihan", "Lomba kebersihan antar RT akan dinilai juri bulan depan." });
    daftarBerita.push_back({ 9, "Fogging Nyamuk", "Penyemprotan fogging untuk pencegahan DBD dijadwalkan hari Rabu." });
    daftarBerita.push_back({ 10, "Update Data", "Warga dimohon melapor ke perangkat desa jika ada perubahan data kependudukan." });
}