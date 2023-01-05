#include "education.h"

using namespace std;

// k. Program utama dari aplikasi Education
int main()
{
    listPegawai Lp;
    listPendidikan Ld;
    listRelasi Lr;
    createPegawai(Lp);
    createPendidikan(Ld);
    createRelasi(Lr);

    //a. Menambahkan data riwayat pendidikan
    pendidikan p1;
    p1.institusi = "Universitas_Indonesia";
    p1.tahunLulus = "2020";
    adr_pendidikan d1 = alokasiPendidikan(p1);
    addPendidikan(Ld, d1);

    pendidikan p2;
    p2.institusi = "Universitas_Gadjah_Mada";
    p2.tahunLulus = "2018";
    adr_pendidikan d2 = alokasiPendidikan(p2);
    addPendidikan(Ld, d2);

    pendidikan p3;
    p3.institusi = "Universitas_Airlangga";
    p3.tahunLulus = "2015";
    adr_pendidikan d3 = alokasiPendidikan(p3);
    addPendidikan(Ld, d3);

    pendidikan p4;
    p4.institusi = "Universitas_Brawijaya";
    p4.tahunLulus = "2021";
    adr_pendidikan d4 = alokasiPendidikan(p4);
    addPendidikan(Ld, d4);

    pendidikan p5;
    p5.institusi = "Universitas_Hasanuddin";
    p5.tahunLulus = "2021";
    adr_pendidikan d5 = alokasiPendidikan(p5);
    addPendidikan(Ld, d5);

    // b. Menambahkan data pegawai
    pegawai pe1;
    pe1.nama = "Salwa_Yolanda";
    pe1.NIP = 102910;
    adr_pegawai e1 = alokasiPegawai(pe1);
    addPegawai(Lp, e1);

    pegawai pe2;
    pe2.nama = "Makara_Prasetyo";
    pe2.NIP = 102992;
    adr_pegawai e2 = alokasiPegawai(pe2);
    addPegawai(Lp, e2);

    pegawai pe3;
    pe3.nama = "Bakiadi_Manullang";
    pe3.NIP = 102127;
    adr_pegawai e3 = alokasiPegawai(pe3);
    addPegawai(Lp, e3);

    pegawai pe4;
    pe4.nama = "Titin_Halimah";
    pe4.NIP = 102000;
    adr_pegawai e4 = alokasiPegawai(pe4);
    addPegawai(Lp, e4);

    cout << "====================================== DATA PEGAWAI ======================================" << endl;
    show_pegawai(Lp);
    cout << "===================================== DATA PENDIDIKAN =====================================" << endl;
    show_pendidikan(Ld);

    // c. Mencari data pegawai tertentu
    cout << "===============================================================================" << endl;
    cout << "c. Mencari data pegawai tertentu" << endl << endl;
    string nama;
    cout << "Masukkan nama pegawai yang ingin dicari: ";
    cin >> nama;
    cout << endl;
    adr_pegawai PE = findPegawai(Lp, nama);
    if (PE == nil) {
        cout << "Pegawai dengan nama " << nama << " tidak ditemukan" << endl;
    } else {
        cout << "Nama: " << infoPegawai(PE).nama << " - NIP: " << infoPegawai(PE).NIP << endl;
    }

    // d. Menambahkan relasi data riwayat pendidikan dengan pegawai yang mengikutinya dan sebaliknya
    cout << "===============================================================================" << endl;
    makeRelasi(Lr, e1, d1);
    makeRelasi(Lr, e2, d1);
    makeRelasi(Lr, e2, d1);
    makeRelasi(Lr, e2, d2);
    makeRelasi(Lr, e2, d4);
    makeRelasi(Lr, e3, d4);
    makeRelasi(Lr, e4, d3);
    makeRelasi(Lr, e4, d5);

    // e. Mencari data pegawai yang memiliki riwayat pendidikan tertentu
    cout << endl << "===============================================================================" << endl;
    cout << "e. Mencari data pegawai yang memiliki riwayat pendidikan tertentu " << endl << endl;
    string institusi;
    cout << "Masukkan pendidikan untuk mencari pegawai: ";
    cin >> institusi;
    cout << endl;
    listPegawai foundPegawai = findPegawai_dataPendidikan(Lr, institusi);

    adr_pegawai p = firstPegawai(foundPegawai);
    if (p == nil) {
        cout << "Pegawai tidak ditemukan" << endl;
    } else {
        do {
            cout << "Nama: " << infoPegawai(p).nama << " - NIP: " << infoPegawai(p).NIP << endl;
            p = nextPegawai(p);
        } while (p != firstPegawai(foundPegawai));
    }

    // f. Menghapus data riwayat pendidikan beserta relasinya
    cout << "===============================================================================" << endl;
    cout << "f. Menghapus data riwayat pendidikan beserta relasinya" << endl << endl;
    string R;
    cout << "Masukkan pendidikan yang akan dihapus: ";
    cin >> R;
    cout << endl;
    deletePendidikan(Lr, Ld, R);

    // g. Menghapus data pegawai yang memiliki riwayat pendidikan tertentu
    cout << "===============================================================================" << endl;
    cout << "g. Menghapus data pegawai yang memiliki riwayat pendidikan tertentu" << endl << endl;
    string Q;
    cout << "Masukkan pendidikan untuk menghapus pegawai: ";
    cin >> Q;
    cout << endl;
    deletePegawai_by_pendidikan(Lr, Ld, Lp, Q);

    // h. Menampilkan seluruh data seluruh pegawai beserta riwayat pendidikannya
    cout << endl << "===============================================================================" << endl;
    cout << "h. Menampilkan seluruh data seluruh pegawai beserta riwayat pendidikannya" << endl;
    cout << endl;
    show_Pegawai_dan_Pendidikan(Lr);

    // i. Menampilkan data pegawai yang memiliki riwayat pendidikan terbanyak
    cout << endl << "===============================================================================" << endl;
    cout << "i. Menampilkan data pegawai yang memiliki riwayat pendidikan terbanyak" << endl;
    cout << endl;
    show_Pegawai_Pendidikan_Terbanyak(Lp, Lr);

    // j. Menampilkan data pendidikan yang paling banyak diikuti oleh pegawai
    cout << endl << "===============================================================================" << endl;
    cout << "j. Menampilkan data pendidikan yang paling banyak diikuti oleh pegawai" << endl;
    cout << endl;
    show_Pendidikan_Terbanyak(Ld, Lr);

    return 0;
}
