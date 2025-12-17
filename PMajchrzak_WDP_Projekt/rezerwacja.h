#ifndef REZERWACJE
#define REZERWACJE

#define MIASTO 25
#define IMIE 25
#define NAZWISKO 25

#define BAZA_LOTY "loty.bin"
#define BAZA_REZERWACJE "rezerwacje.bin"

struct Lot{
    int id_lotu;
    char miasto_odlotu[MIASTO];
    char miasto_przylotu[MIASTO];
    int dostepne_miejsca;
    double cena;
};

struct Rezerwacja{
    int id_rezerwacja;
    int id_lotu;
    char imie[IMIE];
    char nazwisko[NAZWISKO];
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
