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

void stworzBazeDanych();

void wyswietlLoty();

void znajdzLot();

void rezerwacjaBiletu();

void dodajLot();

void usunLot();

void edytujLot();

void listaPasazerow();

#endif
