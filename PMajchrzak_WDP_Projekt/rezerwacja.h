#definie BAZA_LOTY "loty.bin"
#definie BAZA_REZERWACJE "rezerwacje.bin"

#definie MIASTO 25
#definie IMIE 25
#definie NAZWISKO 25

struct Lot{
    int id_lotu;
    char miasto_odlotu[MIASTO];
    char miasto_przylotu[MIASTO];
    int dostepne_miejsca;
    double cena;
}

struct Rezerwacja{
    int id_rezerwacja;
    int id_lotu;
    char imie[IMIE];
    char nazwisko[NAZWISKO];
}

void stworzBazeDanych();

void wyswietlLoty();

void znajdzLot();

void rezerwacjaBiletu();

void dodajLot();

void usunLot();

void edytujLot();

void listaPasazerow();
