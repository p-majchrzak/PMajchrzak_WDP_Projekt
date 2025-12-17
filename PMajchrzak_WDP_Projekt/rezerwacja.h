#ifndef REZERWACJE
#define REZERWACJE

#define BAZA_LOTY "loty.bin"
#define BAZA_REZERWACJE "rezerwacje.bin"

#define MIASTO 25
#define IMIE 25
#define NAZWISKO 25

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

void rezerwacjaBiletu();

void dodajLot(int id_lotu, const char* odlot, const char*przylot, int miejsca, double cena); //x

void usunLot(int id_lotu);// x

void edytujLot();

void listaPasazerow(int id_lotu); //x

#endif
