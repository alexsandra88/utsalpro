/**
 * ============================================================================
 * PROYEK UJIAN TENGAH SEMESTER (UTS) - SSI1144 ALGORITMA & PENGANTAR PEMROGRAMAN
 * PROGRAM STUDI SISTEM INFORMASI - UNIVERSITAS MA CHUNG
 * ============================================================================
 * STUDI KASUS 03 : Sistem Pengolahan Nilai Mata Kuliah
 * MODUL A        : Proses Utama (Input, Perhitungan Nilai Akhir, Kategori, 
 *                  Validasi, dan Penentuan Kelulusan)
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // Deklarasi Konstanta Bobot Penilaian & Syarat Kelulusan
    const double BOBOT_TUGAS     = 0.20;
    const double BOBOT_KUIS      = 0.15;
    const double BOBOT_UTS       = 0.30;
    const double BOBOT_UAS       = 0.35;
    const double SYARAT_MIN_NA   = 60.0;
    const double SYARAT_MIN_UAS  = 50.0;
    const double SYARAT_MIN_HADIR = 75.0;

    // Deklarasi Variabel
    string namaMahasiswa;
    string nimMahasiswa;
    double nilaiTugas;
    double nilaiKuis;
    double nilaiUTS;
    double nilaiUAS;
    double persentaseKehadiran;
    
    double kontribusiTugas;
    double kontribusiKuis;
    double kontribusiUTS;
    double kontribusiUAS;
    double nilaiAkhir;
    string kategoriNilai;
    string statusKelulusan;
    string catatanKelulusan;
    
    char pilihanUlang;

    // Header Program
    cout << "========================================================\n";
    cout << "      SISTEM PENGOLAHAN NILAI MATA KULIAH - MODUL A    \n";
    cout << "             PROYEK UTS ALGORITMA (SSI1144)            \n";
    cout << "========================================================\n\n";

    // Perulangan untuk memproses lebih dari satu mahasiswa
    do {
        cout << "--------------------------------------------------------\n";
        cout << "               MASUKKAN DATA MAHASISWA                  \n";
        cout << "--------------------------------------------------------\n";

        // Input Data Identitas Mahasiswa
        cout << "Masukkan Nama Mahasiswa : ";
        getline(cin >> ws, namaMahasiswa);

        cout << "Masukkan NIM Mahasiswa  : ";
        getline(cin, nimMahasiswa);

        // Input dan Validasi Nilai Tugas (0 - 100)
        do {
            cout << "Masukkan Nilai Tugas (0 - 100) : ";
            if (!(cin >> nilaiTugas)) {
                cout << "[ERROR] Input harus berupa angka numerik!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                nilaiTugas = -1;
                continue;
            }
            if (nilaiTugas < 0 || nilaiTugas > 100) {
                cout << "[ERROR] Nilai tugas tidak valid! Harus berada dalam rentang 0 - 100.\n";
            }
        } while (nilaiTugas < 0 || nilaiTugas > 100);

        // Input dan Validasi Nilai Kuis (0 - 100)
        do {
            cout << "Masukkan Nilai Kuis (0 - 100)  : ";
            if (!(cin >> nilaiKuis)) {
                cout << "[ERROR] Input harus berupa angka numerik!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                nilaiKuis = -1;
                continue;
            }
            if (nilaiKuis < 0 || nilaiKuis > 100) {
                cout << "[ERROR] Nilai kuis tidak valid! Harus berada dalam rentang 0 - 100.\n";
            }
        } while (nilaiKuis < 0 || nilaiKuis > 100);

        // Input dan Validasi Nilai UTS (0 - 100)
        do {
            cout << "Masukkan Nilai UTS (0 - 100)   : ";
            if (!(cin >> nilaiUTS)) {
                cout << "[ERROR] Input harus berupa angka numerik!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                nilaiUTS = -1;
                continue;
            }
            if (nilaiUTS < 0 || nilaiUTS > 100) {
                cout << "[ERROR] Nilai UTS tidak valid! Harus berada dalam rentang 0 - 100.\n";
            }
        } while (nilaiUTS < 0 || nilaiUTS > 100);

        // Input dan Validasi Nilai UAS (0 - 100)
        do {
            cout << "Masukkan Nilai UAS (0 - 100)   : ";
            if (!(cin >> nilaiUAS)) {
                cout << "[ERROR] Input harus berupa angka numerik!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                nilaiUAS = -1;
                continue;
            }
            if (nilaiUAS < 0 || nilaiUAS > 100) {
                cout << "[ERROR] Nilai UAS tidak valid! Harus berada dalam rentang 0 - 100.\n";
            }
        } while (nilaiUAS < 0 || nilaiUAS > 100);

        // Input dan Validasi Kehadiran (0 - 100%)
        do {
            cout << "Masukkan Kehadiran (%) (0-100) : ";
            if (!(cin >> persentaseKehadiran)) {
                cout << "[ERROR] Input harus berupa angka numerik!\n";
                cin.clear();
                cin.ignore(1000, '\n');
                persentaseKehadiran = -1;
                continue;
            }
            if (persentaseKehadiran < 0 || persentaseKehadiran > 100) {
                cout << "[ERROR] Kehadiran tidak valid! Harus berada dalam rentang 0 - 100%.\n";
            }
        } while (persentaseKehadiran < 0 || persentaseKehadiran > 100);

        // ----------------------------------------------------
        // PROSES PERHITUNGAN NILAI AKHIR (BOBOT)
        // Tugas: 20%, Kuis: 15%, UTS: 30%, UAS: 35%
        // ----------------------------------------------------
        kontribusiTugas = nilaiTugas * BOBOT_TUGAS;
        kontribusiKuis  = nilaiKuis * BOBOT_KUIS;
        kontribusiUTS   = nilaiUTS * BOBOT_UTS;
        kontribusiUAS   = nilaiUAS * BOBOT_UAS;
        nilaiAkhir      = kontribusiTugas + kontribusiKuis + kontribusiUTS + kontribusiUAS;

        // ----------------------------------------------------
        // PENENTUAN KATEGORI NILAI
        // ----------------------------------------------------
        if (nilaiAkhir >= 85.0) {
            kategoriNilai = "A";
        } else if (nilaiAkhir >= 80.0) {
            kategoriNilai = "B+";
        } else if (nilaiAkhir >= 75.0) {
            kategoriNilai = "B";
        } else if (nilaiAkhir >= 70.0) {
            kategoriNilai = "C+";
        } else if (nilaiAkhir >= 60.0) {
            kategoriNilai = "C";
        } else if (nilaiAkhir >= 50.0) {
            kategoriNilai = "D";
        } else {
            kategoriNilai = "E";
        }

        // ----------------------------------------------------
        // EVALUASI KELULUSAN
        // Syarat:
        // 1. Nilai akhir >= SYARAT_MIN_NA (60.0)
        // 2. Nilai UAS >= SYARAT_MIN_UAS (50.0)
        // 3. Kehadiran >= SYARAT_MIN_HADIR (75.0%)
        // ----------------------------------------------------
        catatanKelulusan = "";
        if (nilaiAkhir >= SYARAT_MIN_NA && nilaiUAS >= SYARAT_MIN_UAS && persentaseKehadiran >= SYARAT_MIN_HADIR) {
            statusKelulusan = "LULUS";
            catatanKelulusan = "Memenuhi seluruh persyaratan kelulusan.";
        } else {
            statusKelulusan = "TIDAK LULUS";
            if (nilaiAkhir < SYARAT_MIN_NA) {
                catatanKelulusan += "[Nilai Akhir < 60] ";
            }
            if (nilaiUAS < SYARAT_MIN_UAS) {
                catatanKelulusan += "[Nilai UAS < 50] ";
            }
            if (persentaseKehadiran < SYARAT_MIN_HADIR) {
                catatanKelulusan += "[Kehadiran < 75%] ";
            }
        }

        // ----------------------------------------------------
        // OUTPUT RINCIAN HASIL
        // ----------------------------------------------------
        cout << "\n========================================================\n";
        cout << "             RINCIAN HASIL PENILAIAN INDIVIDUAL         \n";
        cout << "========================================================\n";
        cout << left << setw(22) << "Nama Mahasiswa" << ": " << namaMahasiswa << "\n";
        cout << left << setw(22) << "NIM"            << ": " << nimMahasiswa << "\n";
        cout << "--------------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << left << setw(15) << "Komponen" << setw(12) << "Nilai Mentah" << setw(10) << "Bobot" << "Kontribusi\n";
        cout << "--------------------------------------------------------\n";
        cout << left << setw(15) << "Tugas"    << setw(12) << nilaiTugas    << setw(10) << "20%"    << kontribusiTugas << "\n";
        cout << left << setw(15) << "Kuis"     << setw(12) << nilaiKuis     << setw(10) << "15%"    << kontribusiKuis  << "\n";
        cout << left << setw(15) << "UTS"      << setw(12) << nilaiUTS      << setw(10) << "30%"    << kontribusiUTS   << "\n";
        cout << left << setw(15) << "UAS"      << setw(12) << nilaiUAS      << setw(10) << "35%"    << kontribusiUAS   << "\n";
        cout << "--------------------------------------------------------\n";
        cout << left << setw(22) << "Kehadiran"      << ": " << persentaseKehadiran << " %\n";
        cout << left << setw(22) << "Nilai Akhir"    << ": " << nilaiAkhir << "\n";
        cout << left << setw(22) << "Kategori Nilai" << ": " << kategoriNilai << "\n";
        cout << left << setw(22) << "Status Hasil"   << ": " << statusKelulusan << "\n";
        cout << left << setw(22) << "Keterangan"     << ": " << catatanKelulusan << "\n";
        cout << "========================================================\n\n";

        // Konfirmasi pengulangan program
        do {
            cout << "Apakah Anda ingin memasukkan data mahasiswa lain? (y/t): ";
            cin >> pilihanUlang;
            if (pilihanUlang != 'y' && pilihanUlang != 'Y' && pilihanUlang != 't' && pilihanUlang != 'T') {
                cout << "[ERROR] Pilihan tidak valid! Masukkan 'y' untuk ya atau 't' untuk tidak.\n";
            }
        } while (pilihanUlang != 'y' && pilihanUlang != 'Y' && pilihanUlang != 't' && pilihanUlang != 'T');

        cout << "\n";

    } while (pilihanUlang == 'y' || pilihanUlang == 'Y');

    cout << "========================================================\n";
    cout << "    PROGRAM SELESAI. TERIMA KASIH TELAH MENGGUNAKAN.    \n";
    cout << "========================================================\n";

    return 0;
}

