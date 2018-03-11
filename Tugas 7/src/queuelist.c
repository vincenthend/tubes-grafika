// NIM		: 13515065
// Nama		: Felix Limanta
// Tanggal	: 1 November 2016
// File		: queuelist.c
// Topik	: Praktikum 10 - Stack dan Queue Representasi List Linier
// Deskripsi: Implementasi ADT Queue Representasi List Linier

#include "queuelist.h"

/* Prototype manajemen memori */
void Alokasi (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{	// ALGORITMA
	*P = (address) malloc (sizeof(infotype));
	if (*P != Nil) {
		Info(*P) = X;
		Next(*P) = Nil;
	}
}
void Dealokasi (address P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 
{	// ALGORITMA
	free(P);
}
char IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{	// ALGORITMA
	return (Head(Q) == Nil) && (Tail(Q) == Nil);
}
int NbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{	// KAMUS
	address P = Head(Q);
	int i = 1;

	// ALGORITMA
	if (IsEmpty(Q)) {
		return 0;
	} else {
		while (P != Tail(Q)) {
			P = Next(P);
			i++;
		}
		return i;
	}
}
/*** Kreator ***/
void CreateEmpty(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{	// ALGORITMA
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}
/*** Primitif Add/Delete ***/
void Add (Queue * Q, infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{  /* Kamus Lokal */
	address P;
	/* Algoritma */
	Alokasi(&P,X);
	if (P!=Nil) {
		if (IsEmpty(*Q)) {
			Head(*Q) = P; 
		} else {
			Next(Tail(*Q)) = P;
		}
		Tail(*Q) = P; 
	} /* else: alokasi gagal, Q tetap */
}
void Del(Queue * Q, infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{  /* Kamus Lokal */
	address P;
	/* Algoritma */
	*X = InfoHead(*Q);
	P = Head(*Q);
	Head(*Q) = Next(Head(*Q));
	if (Head(*Q)==Nil) {
		Tail(*Q) = Nil;
	}
	Dealokasi(P);
}