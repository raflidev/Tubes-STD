#include "tusegs.h"

void createList_mk(List_MK &list_MK) {
    list_MK.first = NULL;
    list_MK.last = NULL;
}

void createList_mhs(List_Mhs &list_MHS) {
    list_MHS.first = NULL;
}

adr_MK createElementMK(infotype_mk dataBaru) {
    adr_MK P;
    P = new elm_MK;
    P->info = dataBaru;
    P->next = NULL;
    P->firstrel = NULL;
    return P;
}

adr_Mhs createElement_mhs(infotype_mhs dataBaru) {
    adr_Mhs Q;
    Q = new elm_Mhs;
    Q->info = dataBaru;
    Q->next = NULL;
    return Q;
}

void insertLast_MK(List_MK &list_MK,adr_MK P){
    adr_MK Q;
    if (list_MK.first == NULL) {
        list_MK.first = P;
        P->next = list_MK.first;
    } else {
        Q = list_MK.first;
        while (Q->next!= list_MK.first) {
            Q = Q->next;
        }
        Q->next = P;
        P->next = list_MK.first;
    }
}

void printList(List_MK L){
    adr_MK P;
    P = L.first;
    if (P != NULL) {
        while (P->next != L.first){
            cout<<"MK : "<<P->info.nama_mk<<endl;
            cout<<"Jumlah : "<<P->info.jumlah<<endl;
            cout<<"Maks: " <<P->info.kuota_maks<<endl;
            P = P->next;
        }
        cout<<"MK : "<<P->info.nama_mk<<endl;
        cout<<"Jumlah : "<<P->info.jumlah<<endl;
        cout<<"Maks: " <<P->info.kuota_maks<<endl;
    }
}

void deleteFirst(List_MK &L,adr_MK P) { // menghapus list pertama
    adr_MK Q;
    P = L.first;
    if (L.first->next == L.first) {
        L.first = NULL;
        P->next = NULL;
    } else {
        L.first = L.first->next;
        Q = L.first;
        P->next = NULL;
        while(Q->next != P) {
            Q = Q->next;
        }
        Q->next = L.first;
    }
}

void deleteLast(List_MK &L,adr_MK P) { // menghapus list terakhir
    adr_MK Q;
    Q = L.first;
    while (Q->next->next != L.first) {
        Q = Q->next;
    }
    P = Q->next;
    P->next = NULL;
    Q->next = L.first;
}

void deleteAfter(adr_MK prec, adr_MK &P){ // menghapus list yang ditunjuk
    P = prec->next;
    prec->next = P->next;
    P->next = NULL;
}

void deleteMK(List_MK &L,adr_MK P){ // menghapus elemen yang ditunjuk
    adr_MK Q;
    if (P  == L.first) {
        deleteFirst(L,P);
    } else if (P == L.last) {
        deleteLast(L,P);
    } else {
        Q = L.first;
        while (P != Q->next) {
            Q = Q->next;
        }
        deleteAfter(Q,P);
    }
}

adr_MK search_mk(List_MK L,string nama_mk) {
    adr_MK P = L.first;
    while (P->next != L.first) {
        if (P->info.nama_mk == nama_mk) {
            return P;
        }
        P = P->next;
    }
    if (P->info.nama_mk == nama_mk) {
        return P;
    }
    return NULL;
}

void insertLast_Mhs(List_Mhs &L, adr_Mhs P) {
    adr_Mhs temp;
    if (L.first == NULL) {
        L.first = P;
    } else {
        temp = L.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = P; // memasukkan elemen dari belakang list
        P = NULL;
    }
}

void insertFirst_Mhs(List_Mhs &L,adr_Mhs P) {
    if (L.first== NULL){
        L.first = P;
    } else {
        P->next = L.first;
        L.first= P;
    }
}

void deleteFirst_mhs(List_Mhs &L,adr_Mhs P) {
    P = L.first;
    if (L.first->next == NULL) {
        L.first = NULL;
    } else {
        L.first = L.first->next;
    }
    P->next = NULL;
}

void deleteLast_mhs(List_Mhs &L,adr_Mhs P) {
    adr_Mhs temp;
    temp = L.first->next;
    while (temp->next != NULL) {
        P = temp;
        temp = temp->next;
    }
    P->next = NULL; // menhapus elemen dari paling belakang list
}

void deteleAfter_mhs(adr_Mhs prec, adr_Mhs &P) {
    P = prec->next;
    prec->next = P->next;
    P->next = NULL;
}

void deleteMhs(List_Mhs &mhs,List_MK &mk,adr_Mhs P) {
    adr_MK adrMK;
    adrMK = mk.first;
    adr_Mhs Q;
    while (adrMK->next != mk.first) {
        deleteRelasi(P,adrMK);
        adrMK = adrMK->next;
    }
    deleteRelasi(P,adrMK);
    if (P == mhs.first) {
        deleteFirst_mhs(mhs,P);
    } else if (P->next == NULL) {
        deleteLast_mhs(mhs,P);
    } else {
        Q = mhs.first;
        while (P != Q->next) {
            Q = Q->next;
        }
        deteleAfter_mhs(Q,P);
    }

}

adr_Mhs search_mhs(List_Mhs L,string nama_mhs){
    adr_Mhs P = L.first;
    while (P != NULL) {
        if (P->info.nama_mhs == nama_mhs) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void testprintList(List_Mhs L){
    adr_Mhs Q;
    if (L.first == NULL) {
        cout<<"List Kosong!"<<endl;
        cout<<endl;
    } else {
        Q = L.first;
        while (Q != NULL) { // mengeluarkan info elemen dengan loop
            cout<<Q->info.nama_mhs<<endl;
            Q = Q->next;
        }
    }

}

void createrelation(adr_MK mk,adr_Mhs mhs) {
    adr_relation Rel = new elm_relation;
    Rel->next_mhs =  mhs;
    Rel->next = NULL;
    if (mk->firstrel == NULL) {
        mk->firstrel = Rel;
        mk->info.jumlah++;
    } else {
        if (mk->info.jumlah == mk->info.kuota_maks) {
            cout<<"Penuh gan"<<endl;
        } else {
            adr_relation temp;
            temp = mk->firstrel;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = Rel;
            mk->info.jumlah++;
        }
    }
}

void printFull(List_MK mk) {
    adr_MK P = mk.first;
    if (P != NULL) {
        while (P->next != mk.first) {
            adr_relation Q = P->firstrel;
            cout<<"MK : "<<P->info.nama_mk<<endl;
            cout<<"Jumlah : "<<P->info.jumlah<<endl;
            cout<<"Kuota Maks : "<<P->info.kuota_maks<<endl;
            while (Q != NULL) {
                cout<<"-->"<<Q->next_mhs->info.nama_mhs<<endl;
                Q = Q->next;
            }
            cout<<endl;
            P = P->next;
        }
        adr_relation Q = P->firstrel;
        cout<<"MK : "<<P->info.nama_mk<<endl;
        cout<<"Jumlah : "<<P->info.jumlah<<endl;
        cout<<"Kuota Maks : "<<P->info.kuota_maks<<endl;
        while (Q != NULL) {
            cout<<"-->"<<Q->next_mhs->info.nama_mhs<<endl;
            Q = Q->next;
        }
    }
}

void deleteRelasi(adr_Mhs mhs,adr_MK mk) {
    adr_relation P = mk->firstrel;
    while (P != NULL) {
        if (P->next_mhs == mhs) {
            mk->info.jumlah--;
            if (P == mk->firstrel) {
                mk->firstrel = P->next;
            } else {
                adr_relation prec;
                prec = mk->firstrel;
                while (prec->next != P) {
                    prec = prec->next;
                }
                prec->next = P->next;
            }
        }
        P = P->next;
    }
}





