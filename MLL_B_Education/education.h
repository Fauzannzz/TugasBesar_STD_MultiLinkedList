#ifndef EDUCATION_H_INCLUDED
#define EDUCATION_H_INCLUDED

#include <iostream>
using namespace std;

#define nil NULL
#define firstPendidikan(L) ((L).firstPendidikan)
#define firstPegawai(L) ((L).firstPegawai)
#define firstRelasi(L) ((L).firstRelasi)
#define infoPendidikan(P) (P)->infoPendidikan
#define nextPendidikan(P) (P)->nextPendidikan
#define infoPegawai(P) (P)->infoPegawai
#define nextPegawai(P) (P)->nextPegawai
#define nextRelasi(P) (P)->nextRelasi
#define prevRelasi(P) (P)->prevRelasi

//List Pendidikan
typedef struct elm_pendidikan *adr_pendidikan;
struct pendidikan {
    string institusi;
    string tahunLulus;
};

struct elm_pendidikan {
    pendidikan infoPendidikan;
    adr_pendidikan nextPendidikan;
};

struct listPendidikan {
    adr_pendidikan firstPendidikan;
};

//List Pegawai
typedef struct elm_pegawai *adr_pegawai;
struct pegawai {
    string nama;
    int NIP;
};

struct elm_pegawai {
    pegawai infoPegawai;
    adr_pegawai nextPegawai;
};

struct listPegawai {
    adr_pegawai firstPegawai;
};

//List Relasi
typedef struct elm_relasi *adr_relasi;
struct elm_relasi {
    adr_pegawai nextPegawai;
    adr_pendidikan nextPendidikan;
    adr_relasi nextRelasi;
    adr_relasi prevRelasi;
};

struct listRelasi {
    adr_relasi firstRelasi;
};

void createPegawai(listPegawai &L);
void createPendidikan(listPendidikan &L);
void createRelasi(listRelasi &L);

adr_pegawai alokasiPegawai(pegawai P);
adr_pendidikan alokasiPendidikan(pendidikan P);
adr_relasi alokasiRelasi(adr_pegawai P, adr_pendidikan D);

void addPegawai(listPegawai &L, adr_pegawai P);
void addPendidikan(listPendidikan &L, adr_pendidikan D);
void addRelasi(listRelasi &L, adr_relasi R);

adr_pegawai findPegawai(listPegawai P, string name);
listPegawai findPegawai_dataPendidikan(listRelasi L, string institusi);
adr_pendidikan findPendidikan(listPendidikan D, string institusi);
void makeRelasi(listRelasi &L, adr_pegawai P, adr_pendidikan D);

void deletePendidikan(listRelasi &L, listPendidikan &D, string institusi);
void deletePegawai(listRelasi &L, listPegawai &P, string nama);
void deletePegawai_by_pendidikan(listRelasi &L, listPendidikan &D, listPegawai &P, string institusi);

void show_Pegawai_dan_Pendidikan(listRelasi L);

int jumlah_pendidikan_pegawai(listRelasi L, adr_pegawai AP);
void show_Pegawai_Pendidikan_Terbanyak(listPegawai P, listRelasi L);

int jumlah_relasi_pendidikan(listRelasi L, adr_pendidikan AD);
void show_Pendidikan_Terbanyak(listPendidikan D, listRelasi L);

void show_pendidikan(listPendidikan L);
void show_pegawai(listPegawai L);

#endif // EDUCATION_H_INCLUDED
