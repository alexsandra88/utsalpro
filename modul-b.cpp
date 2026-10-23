
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Parent Class
class PesertaKuliah {
protected:
    string nim, nama;
    double tugas, kuis, uts, uas, kehadiran;
    double nilaiAkhir;
    char nilaiHuruf;
    bool lulus;

public:
    PesertaKuliah(string n, string nm, double t, double k,
                  double u, double a, double h)
        : nim(n), nama(nm), tugas(t), kuis(k),
          uts(u), uas(a), kehadiran(h),
          nilaiAkhir(0), nilaiHuruf('E'), lulus(false) {}

    virtual ~PesertaKuliah() {}

    string getNIM() const { return nim; }
    string getNama() const { return nama; }
    double getNilaiAkhir() const { return nilaiAkhir; }
    char getNilaiHuruf() const { return nilaiHuruf; }
    bool getLulus() const { return lulus; }

    virtual bool memenuhiKehadiran() const = 0;
    virtual string getJenis() const = 0;

    void hitungNilai() {
        // Bobot contoh: tugas 20%, kuis 20%,
        // UTS 30%, UAS 30%
        nilaiAkhir = tugas * 0.20 + kuis * 0.20
                   + uts * 0.30 + uas * 0.30;

        if (nilaiAkhir >= 85) nilaiHuruf = 'A';
        else if (nilaiAkhir >= 75) nilaiHuruf = 'B';
        else if (nilaiAkhir >= 65) nilaiHuruf = 'C';
        else if (nilaiAkhir >= 50) nilaiHuruf = 'D';
        else nilaiHuruf = 'E';

        lulus = nilaiAkhir >= 60 && memenuhiKehadiran();
    }

    void ubahNilai(double t, double k, double u, double a) {
        tugas = t;
        kuis = k;
        uts = u;
        uas = a;
        hitungNilai();
    }

    virtual void tampilkan() const {
        cout << left << setw(13) << nim
             << setw(20) << nama
             << setw(12) << getJenis()
             << setw(10) << fixed << setprecision(2)
             << nilaiAkhir
             << setw(8) << nilaiHuruf
             << (lulus ? "Lulus" : "Tidak lulus")
             << '\n';
    }
};

// Child Class
class MahasiswaReguler : public PesertaKuliah {
public:
    using PesertaKuliah::PesertaKuliah;

    bool memenuhiKehadiran() const override {
        return kehadiran >= 75;
    }

    string getJenis() const override {
        return "Reguler";
    }
};

// Child Class
class MahasiswaDispensasi : public PesertaKuliah {
public:
    using PesertaKuliah::PesertaKuliah;

    bool memenuhiKehadiran() const override {
        // Kehadiran khusus mengikuti ketentuan dosen.
        // Pada contoh ini, syarat kehadiran reguler
        // tidak diterapkan untuk mahasiswa dispensasi.
        return true;
    }

    string getJenis() const override {
        return "Dispensasi";
    }
};

// Class Pengelola
class NilaiManager {
private:
    vector<PesertaKuliah*> mahasiswa;

    PesertaKuliah* cari(string nim) {
        for (auto m : mahasiswa) {
            if (m->getNIM() == nim)
                return m;
        }
        return nullptr;
    }

    double inputNilai(string keterangan) {
        double nilai;
        while (true) {
            cout << keterangan;
            if (cin >> nilai && nilai >= 0 && nilai <= 100)
                return nilai;

            cout << "Nilai harus antara 0 sampai 100!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

public:
    ~NilaiManager() {
        for (auto m : mahasiswa)
            delete m;
    }

    void tambahMahasiswa() {
        string nim, nama;
        char jenis;
        double t, k, u, a, h;

        cout << "NIM: ";
        cin >> nim;

        if (cari(nim) != nullptr) {
            cout << "NIM sudah terdaftar!\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama: ";
        getline(cin, nama);

        cout << "Jenis (R = Reguler, D = Dispensasi): ";
        cin >> jenis;

        if (jenis != 'R' && jenis != 'r' &&
            jenis != 'D' && jenis != 'd') {
            cout << "Jenis mahasiswa tidak valid!\n";
            return;
        }

        t = inputNilai("Nilai tugas: ");
        k = inputNilai("Nilai kuis: ");
        u = inputNilai("Nilai UTS: ");
        a = inputNilai("Nilai UAS: ");
        h = inputNilai("Persentase kehadiran: ");

        PesertaKuliah* m;

        if (jenis == 'R' || jenis == 'r')
            m = new MahasiswaReguler(nim, nama, t, k, u, a, h);
        else
            m = new MahasiswaDispensasi(nim, nama, t, k, u, a, h);

        m->hitungNilai();
        mahasiswa.push_back(m);

        cout << "Mahasiswa berhasil ditambahkan!\n";
    }

    void cariMahasiswa() {
        string nim;
        cout << "Masukkan NIM: ";
        cin >> nim;

        PesertaKuliah* m = cari(nim);

        if (m != nullptr)
            m->tampilkan();
        else
            cout << "Mahasiswa tidak ditemukan!\n";
    }

    void ubahNilai() {
        string nim;
        cout << "Masukkan NIM: ";
        cin >> nim;

        PesertaKuliah* m = cari(nim);

        if (m == nullptr) {
            cout << "Mahasiswa tidak ditemukan!\n";
            return;
        }

        double t = inputNilai("Nilai tugas baru: ");
        double k = inputNilai("Nilai kuis baru: ");
        double u = inputNilai("Nilai UTS baru: ");
        double a = inputNilai("Nilai UAS baru: ");

        m->ubahNilai(t, k, u, a);
        cout << "Nilai berhasil diubah dan dihitung ulang!\n";
    }

    void tampilkanSemua() {
        if (mahasiswa.empty()) {
            cout << "Belum ada data mahasiswa.\n";
            return;
        }

        cout << "\nDAFTAR NILAI MAHASISWA\n";
        cout << left << setw(13) << "NIM"
             << setw(20) << "Nama"
             << setw(12) << "Jenis"
             << setw(10) << "Nilai"
             << setw(8) << "Huruf"
             << "Status\n";

        for (auto m : mahasiswa)
            m->tampilkan();
    }

    void rekapitulasi() {
        if (mahasiswa.empty()) {
            cout << "Belum ada data mahasiswa.\n";
            return;
        }

        double total = 0;
        double tertinggi = -1, terendah = 101;
        int kategori[5] = {0, 0, 0, 0, 0};
        int lulus = 0;

        for (auto m : mahasiswa) {
            double n = m->getNilaiAkhir();
            total += n;

            if (n > tertinggi) tertinggi = n;
            if (n < terendah) terendah = n;

            char huruf = m->getNilaiHuruf();
            if (huruf == 'A') kategori[0]++;
            else if (huruf == 'B') kategori[1]++;
            else if (huruf == 'C') kategori[2]++;
            else if (huruf == 'D') kategori[3]++;
            else kategori[4]++;

            if (m->getLulus()) lulus++;
        }

        cout << "\n=== REKAPITULASI NILAI ===\n";
        cout << "Jumlah mahasiswa : " << mahasiswa.size() << '\n';
        cout << "Jumlah lulus     : " << lulus << '\n';
        cout << "Tidak lulus      : " << mahasiswa.size() - lulus << '\n';
        cout << fixed << setprecision(2);
        cout << "Rata-rata nilai  : " << total / mahasiswa.size() << '\n';
        cout << "Nilai tertinggi  : " << tertinggi << '\n';
        cout << "Nilai terendah   : " << terendah << '\n';
        cout << "Kategori A       : " << kategori[0] << '\n';
        cout << "Kategori B       : " << kategori[1] << '\n';
        cout << "Kategori C       : " << kategori[2] << '\n';
        cout << "Kategori D       : " << kategori[3] << '\n';
        cout << "Kategori E       : " << kategori[4] << '\n';
    }

    void menu() {
        int pilihan = -1;

        do {
            cout << "\n=== SISTEM PENGOLAHAN NILAI ===\n";
            cout << "1. Tambah mahasiswa\n";
            cout << "2. Cari mahasiswa berdasarkan NIM\n";
            cout << "3. Ubah nilai mahasiswa\n";
            cout << "4. Tampilkan semua mahasiswa\n";
            cout << "5. Rekapitulasi nilai\n";
            cout << "0. Keluar\n";
            cout << "Pilihan: ";

            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan pilihan berupa angka!\n";
                continue;
            }

            switch (pilihan) {
                case 1: tambahMahasiswa(); break;
                case 2: cariMahasiswa(); break;
                case 3: ubahNilai(); break;
                case 4: tampilkanSemua(); break;
                case 5: rekapitulasi(); break;
                case 0: cout << "Program selesai.\n"; break;
                default: cout << "Pilihan tidak tersedia!\n";
            }
        } while (pilihan != 0);
    }
};

int main() {
    NilaiManager manager;
    manager.menu();
    return 0;
}
