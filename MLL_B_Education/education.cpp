#include "education.h"

void createPegawai(listPegawai &L) {
    firstPegawai(L) = nil;
}

void createPendidikan(listPendidikan &L) {
    firstPendidikan(L) = nil;
}

void createRelasi(listRelasi &L) {
    firstRelasi(L) = nil;
}

adr_pegawai alokasiPegawai(pegawai P) {
    adr_pegawai ap = new elm_pegawai;
    infoPegawai(ap) = P;
    nextPegawai(ap) = nil;
    return ap;
}

adr_pendidikan alokasiPendidikan(pendidikan P) {
    adr_pendidikan ad = new elm_pendidikan;
    infoPendidikan(ad) = P;
    nextPendidikan(ad) = nil;
    return ad;
}

adr_relasi alokasiRelasi(adr_pegawai P, adr_pendidikan D) {
    adr_relasi ar = new elm_relasi;
    nextPegawai(ar) = P;
    nextPendidikan(ar) = D;
    nextRelasi(ar) = nil;
    prevRelasi(ar) = nil;
    return ar;
}

void addPegawai(listPegawai &L, adr_pegawai P) {
    if (firstPegawai(L) == nil) {
        firstPegawai(L) = P;
        nextPegawai(P) = P;
    } else {
        adr_pegawai Q = firstPegawai(L);

        nextPegawai(P) = firstPegawai(L);
        while (nextPegawai(Q) != firstPegawai(L)) {
            Q = nextPegawai(Q);
        }

        nextPegawai(Q) = P;
        firstPegawai(L) = P;
    }
}

void addPendidikan(listPendidikan &L, adr_pendidikan D) {
    if (firstPendidikan(L) == nil) {
        firstPendidikan(L) = D;
    } else {
        nextPendidikan(D) = firstPendidikan(L);
        firstPendidikan(L) = D;
    }
}

void addRelasi(listRelasi &L, adr_relasi R) {
    if (firstRelasi(L) == nil) {
        firstRelasi(L) = R;
        nextRelasi(R) = R;
        prevRelasi(R) = R;
    } else {
        prevRelasi(R) = prevRelasi(firstRelasi(L));
        nextRelasi(prevRelasi(firstRelasi(L))) = R;
        nextRelasi(R) = firstRelasi(L);
        prevRelasi(firstRelasi(L)) = R;
        firstRelasi(L) = R;
    }
}

adr_pegawai findPegawai(listPegawai P, string name) {
    adr_pegawai Q = firstPegawai(P);
    while (nextPegawai(Q) != firstPegawai(P)) {
        if (infoPegawai(Q).nama == name) {
            return Q;
        }
        Q = nextPegawai(Q);
    }

    if (nextPegawai(Q) == firstPegawai(P)) {
        if (infoPegawai(Q).nama == name) {
            return Q;
        }
    }

    return nil;
}

void makeRelasi(listRelasi &L, adr_pegawai P, adr_pendidikan D) {
    // Check if the relasi already exists in the list
    bool found = false;
    adr_relasi current = firstRelasi(L);
    if (current != nil) {
        do {
            if (nextPegawai(current) == P && nextPendidikan(current) == D) {
                found = true;
            }
            current = nextRelasi(current);
        } while (current != firstRelasi(L) && !found);
    } else {
        adr_relasi R = alokasiRelasi(P, D);
        firstRelasi(L) == nil;
        addRelasi(L, R);
        cout << "Relasi berhasil ditambahkan" << endl;
        found = true;
    }
    // If the relasi does not already exist, add it to the list
    if (!found) {
        adr_relasi R = alokasiRelasi(P, D);
        if (firstRelasi(L) == nil) {
            addRelasi(L, R);
            cout << "Relasi berhasil ditambahkan" << endl;
        } else {
            adr_relasi Q = firstRelasi(L);
            while (nextRelasi(Q) != firstRelasi(L)) {
                Q = nextRelasi(Q);
            }
            nextRelasi(Q) = R;
            prevRelasi(R) = Q;
            nextRelasi(R) = firstRelasi(L);
            prevRelasi(firstRelasi(L)) = R;
            cout << "Relasi berhasil ditambahkan" << endl;
        }
    } else {
        cout << "Relasi sudah ada" << endl;
    }
}


listPegawai findPegawai_dataPendidikan(listRelasi L, string institusi) {
    listPegawai foundPegawai;
    createPegawai(foundPegawai);

  // Check for an empty list of relationships or an empty search criterion
    if (firstRelasi(L) == nil) {
        return foundPegawai;
    }

  // Iterate over the relationships in the list
    adr_relasi R = firstRelasi(L);
    do {
    // Check whether the educational institution in the relationship matches the search criterion
        if (infoPendidikan(nextPendidikan(R)).institusi == institusi) {
      // If it does, create a new employee node and add it to the list of found employees
            adr_pegawai Q = alokasiPegawai(infoPegawai(nextPegawai(R)));
            addPegawai(foundPegawai, Q);
        }
        R = nextRelasi(R);
    } while (R != firstRelasi(L));

  // Return the list of found employees
    return foundPegawai;
}

adr_pendidikan findPendidikan(listPendidikan D, string institusi) {
    adr_pendidikan Q = firstPendidikan(D);
    while (Q != nil) {
        if (infoPendidikan(Q).institusi == institusi) {
            return Q;
        }
        Q = nextPendidikan(Q);
    }
    return nil;
}

void deletePendidikan(listRelasi &L, listPendidikan &D, string institusi) {
    adr_pendidikan AD = findPendidikan(D, institusi);
    if (AD != nil && firstRelasi(L) != nil) {
        // Find and delete any relasi nodes that reference the pendidikan node
        adr_relasi current = firstRelasi(L);
        adr_relasi next = nextRelasi(current);

        while (next != firstRelasi(L)) {
            if (nextPendidikan(current) == AD) {
                if (current == firstRelasi(L)) {
                    // Unlink the relasi node from the list
                    nextRelasi(prevRelasi(current)) = next;
                    prevRelasi(next) = prevRelasi(current);
                    // Delete the relasi node
                    prevRelasi(current) = nil;
                    nextRelasi(current) = nil;
                    firstRelasi(L) = next;
                    delete current;
                    // Start again from the beginning of the list
                    current = firstRelasi(L);
                    next = nextRelasi(current);
                } else {
                    // Unlink the relasi node from the list
                    nextRelasi(prevRelasi(current)) = next;
                    prevRelasi(next) = prevRelasi(current);
                    // Delete the relasi node
                    prevRelasi(current) = nil;
                    nextRelasi(current) = nil;
                    delete current;
                    // Start again from the beginning of the list
                    current = firstRelasi(L);
                    next = nextRelasi(current);
                }
            } else {
                // Move to the next relasi node
                current = next;
                next = nextRelasi(current);
            }
        }
        if (nextRelasi(current) == firstRelasi(L) && nextPendidikan(current) == AD) {
            // Unlink the relasi node from the list
            nextRelasi(prevRelasi(current)) = nextRelasi(current);
            prevRelasi(nextRelasi(current)) = prevRelasi(current);
            // Delete the relasi node
            prevRelasi(current) = nil;
            nextRelasi(current) = nil;
            delete current;
        }

        // Delete the pendidikan node from the pendidikan list
        if (firstPendidikan(D) == AD) {
            if (nextPendidikan(AD) == nil) {
                firstPendidikan(D) = nil;
                delete AD;
            } else {
                adr_pendidikan P = firstPendidikan(D);
                firstPendidikan(D) = nextPendidikan(P);
                nextPendidikan(P) = nil;
                delete P;
            }
        } else if (nextPendidikan(AD) == nil) {
            adr_pendidikan Q = firstPendidikan(D);
            while (nextPendidikan(Q) != AD) {
            Q = nextPendidikan(Q);
            }
            nextPendidikan(Q) = nil;
            delete AD;
        } else {
            adr_pendidikan Q = firstPendidikan(D);
            while (nextPendidikan(Q) != AD) {
            Q = nextPendidikan(Q);
            }
            nextPendidikan(Q) = nextPendidikan(AD);
            nextPendidikan(AD) = nil;
            delete AD;
        }
    } else {
        cout << "Riwayat Pendidikan tidak ditemukan" << endl;
    }
}

void deletePegawai_by_pendidikan(listRelasi &L, listPendidikan &D, listPegawai &P, string institusi) {
    adr_pendidikan AD = findPendidikan(D, institusi);
    adr_pegawai peg;
    adr_relasi current = firstRelasi(L);

    // Delete the pegawai nodes that have a relasi with the specified pendidikan node
    while (current != nil && nextPendidikan(current) == AD) {
        peg = nextPegawai(current);
        if (peg == firstPegawai(P)) {
    // Special case: deleting the first pegawai node
            firstPegawai(P) = nextPegawai(peg);
            nextPegawai(peg) = nil;
            delete peg;
        } else if (nextPegawai(peg) == nil) {
            adr_pegawai Q = firstPegawai(P);
            while (nextPegawai(Q) != peg) {
            Q = nextPegawai(Q);
            }
            nextPegawai(Q) = nil;
            delete peg;
        } else {
            adr_pegawai Q = firstPegawai(P);
            while (nextPegawai(Q) != peg) {
            Q = nextPegawai(Q);
            }
            nextPegawai(Q) = nextPegawai(peg);
            nextPegawai(peg) = nil;
            delete peg;
        }
        current = nextRelasi(current);
    }


    if (AD != nil && firstRelasi(L) != nil) {
        // Find and delete any relasi nodes that reference the pendidikan node
        adr_relasi current = firstRelasi(L);
        adr_relasi next = nextRelasi(current);
        while (next != firstRelasi(L)) {
            if (nextPendidikan(current) == AD) {
                if (current == firstRelasi(L)) {
                    // Unlink the relasi node from the list
                    nextRelasi(prevRelasi(current)) = next;
                    prevRelasi(next) = prevRelasi(current);
                    // Delete the relasi node
                    prevRelasi(current) = nil;
                    nextRelasi(current) = nil;
                    firstRelasi(L) = next;
                    delete current;
                    // Start again from the beginning of the list
                    current = firstRelasi(L);
                    next = nextRelasi(current);
                } else {
                    // Unlink the relasi node from the list
                    nextRelasi(prevRelasi(current)) = next;
                    prevRelasi(next) = prevRelasi(current);
                    // Delete the relasi node
                    prevRelasi(current) = nil;
                    nextRelasi(current) = nil;
                    delete current;
                    // Start again from the beginning of the list
                    current = firstRelasi(L);
                    next = nextRelasi(current);

                }
            } else {
                // Move to the next relasi node
                current = next;
                next = nextRelasi(current);
            }
        }
        if (nextRelasi(current) == firstRelasi(L) && nextPendidikan(current) == AD) {
            // Unlink the relasi node from the list
            if (current == firstRelasi(L)) {
                // Special case: deleting the first node
                nextRelasi(prevRelasi(current)) = nextRelasi(current);
                prevRelasi(nextRelasi(current)) = prevRelasi(current);
                firstRelasi(L) = nextRelasi(current);
            } else {
                nextRelasi(prevRelasi(current)) = nextRelasi(current);
                prevRelasi(nextRelasi(current)) = prevRelasi(current);
            }
            // Delete the relasi node
            prevRelasi(current) = nil;
            nextRelasi(current) = nil;
            delete current;
        }
    } else {
        cout << "Tidak ada pegawai yang memiliki riwayat pendidikan tersebut" << endl;
    }
}

void show_Pegawai_dan_Pendidikan(listRelasi L) {
    if (firstRelasi(L) != nil) {
        adr_relasi current = firstRelasi(L);
        while (nextRelasi(current) != firstRelasi(L)) {
            cout << infoPegawai(nextPegawai(current)).nama << " - " << infoPegawai(nextPegawai(current)).NIP << " || ";
            cout << infoPendidikan(nextPendidikan(current)).institusi << " - " << infoPendidikan(nextPendidikan(current)).tahunLulus << endl;
            current = nextRelasi(current);
        }
        if (nextRelasi(current) == firstRelasi(L)) {
            cout << infoPegawai(nextPegawai(current)).nama << " - " << infoPegawai(nextPegawai(current)).NIP << " || ";
            cout << infoPendidikan(nextPendidikan(current)).institusi << " - " << infoPendidikan(nextPendidikan(current)).tahunLulus << endl;
        }
    } else {
        cout << "List Kosong" << endl;
    }
}

int jumlah_pendidikan_pegawai(listRelasi L, adr_pegawai AP) {
    int jumlah = 0;
    adr_relasi Q = firstRelasi(L);
    while (nextRelasi(Q) != firstRelasi(L)) {
        if (nextPegawai(Q) == AP) {
            jumlah++;
        }
        Q = nextRelasi(Q);
    }

    if (nextRelasi(Q) == firstRelasi(L)) {
        if (nextPegawai(Q) == AP) {
            jumlah++;
        }
    }

    return jumlah;
}

void show_Pegawai_Pendidikan_Terbanyak(listPegawai P, listRelasi L) {
    adr_pegawai AP, Q;
    AP = firstPegawai(P);
    Q = nil;
    int max = 0;
    while (nextPegawai(AP) != firstPegawai(P)) {
        int jumlah = jumlah_pendidikan_pegawai(L, AP);
        if (jumlah > max) {
            max = jumlah;
            Q = AP;
        }
        AP = nextPegawai(AP);
    }
    cout << "--- Pegawai dengan riwayat pendidikan terbanyak ---" << endl;
    if (Q == nil) {
        cout << "Pegawai tidak ditemukan" << endl;
    } else {
        cout << "Nama : " << infoPegawai(Q).nama << endl;
        cout << "NIP: " << infoPegawai(Q).NIP << endl;
        cout << "Jumlah Pendidikan: " << max << endl;
    }
}

int jumlah_relasi_pendidikan(listRelasi L, adr_pendidikan AD) {
    int jumlah = 0;
    adr_relasi Q = firstRelasi(L);
    while (nextRelasi(Q) != firstRelasi(L)) {
        if (nextPendidikan(Q) == AD) {
            jumlah++;
        }
        Q = nextRelasi(Q);
    }

    if (nextRelasi(Q) == firstRelasi(L)) {
        if (nextPendidikan(Q) == AD) {
            jumlah++;
        }
        Q = nextRelasi(Q);
    }

    return jumlah;
}

void show_Pendidikan_Terbanyak(listPendidikan D, listRelasi L) {
    adr_pendidikan AD, Q;
    AD = firstPendidikan(D);
    Q = nil;
    int max = 0;
    while (AD != nil) {
        int jumlah = jumlah_relasi_pendidikan(L, AD);
        if (jumlah > max) {
            max = jumlah;
            Q = AD;
        }
        AD = nextPendidikan(AD);
    }
    cout << "-------- Riwayat pendidikan terbanyak --------" << endl;
    if (Q == nil) {
        cout << "Pendidikan tidak ditemukan" << endl;
    } else {
        cout << "Institusi : " << infoPendidikan(Q).institusi << endl;
        cout << "Jumlah Relasi: " << max << endl;
    }
}

void show_pendidikan(listPendidikan L) {
    if (firstPendidikan(L) == nil) {
        cout << "Tidak ada data pendidikan." << endl;
        return;
    }
    adr_pendidikan current = firstPendidikan(L);
    int i = 1;
    while (current != nil) {
        cout << i << ". " << infoPendidikan(current).institusi << " (" << infoPendidikan(current).tahunLulus << ")" << endl;
        current = nextPendidikan(current);
        i++;
    }
}

void show_pegawai(listPegawai L) {
    if (firstPegawai(L) == nil) {
        cout << "Tidak ada data pegawai." << endl;
        return;
    }
    adr_pegawai current = firstPegawai(L);
    int i = 1;
    while (nextPegawai(current) != firstPegawai(L)) {
        cout << i << ". " << infoPegawai(current).nama << " (" << infoPegawai(current).NIP << ")" << endl;
        current = nextPegawai(current);
        i++;
    }
    if (nextPegawai(current) == firstPegawai(L)) {
        cout << i << ". " << infoPegawai(current).nama << " (" << infoPegawai(current).NIP << ")" << endl;
    }
}
