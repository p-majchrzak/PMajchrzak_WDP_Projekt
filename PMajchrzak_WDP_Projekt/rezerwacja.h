#ifndef REZERWACJE_H
#define REZERWACJE_H

#define MIASTO_MAKS 30
#define IMIE_MAKS 20
#define NAZWISKO_MAKS 30

#define BAZA_LOTY "bazadb.bin"
#define BAZA_REZERWACJE "rezerwacjedb.bin"

struct Lot{
    int id_lotu;
    char miasto_odlotu[MIASTO_MAKS];
    char miasto_przylotu[MIASTO_MAKS];
    int dostepne_miejsca;
    double cena;
};

struct Rezerwacja{
    int id_rezerwacja;
    int id_lotu;
    char imie[IMIE_MAKS];
    char nazwisko[NAZWISKO_MAKS];
};

void stworzBazeDanych(); //x

void wyswietlLoty(); //x

int znajdzLot(int id, Lot *lot); //x

void rezerwacjaBiletu(int id_lotu, const char*imie, const char* nazwisko); //x

void dodajLot(int id_lotu, const char* odlot, const char*przylot, int miejsca, double cena); //x

void usunLot(int id_lotu);// x

void edytujLot(int lot_id, int ilosc_miejsc, int cena); //x

void listaPasazerow(int id_lotu); //x

#endif
