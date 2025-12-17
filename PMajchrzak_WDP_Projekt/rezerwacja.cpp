#include "rezerwacja.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

int ostatniaRezerwacjaID()
{
    FILE *plik = fopen(BAZA_REZERWACJE, "rb");
    if(plik == nullptr){
        return 0;
    }
    Rezerwacja rezerwacja;
    int id_szukane = 0;
    fseek(plik, 0, SEEK_END);
    long rozmiar = ftell(plik);
    
    if(rozmiar >= sizeof(Rezerwacja))
    {
        fseek(plik, - (long)sizeof(Rezerwacja), SEEK_END);
        if(fread(&rezerwacja, sizeof(Rezerwacja),1,plik) == 1)
        {
            id_szukane = rezerwacja.id_lotu;
        }
    }
    fclose(plik);
    return id_szukane;
}

long miejsceLotuWPliku(int id)
{
    FILE *plik = fopen(BAZA_LOTY, "rb");
    if(plik == nullptr)return -1;
    Lot lot;
    long rekord = 0;
    while(fread(&lot, sizeof(Lot), 1, plik) == 1){
        if(lot.id_lotu == id)
        {
            fclose(plik);
            return rekord;
        }
    }
    fclose(plik);
    return -1;
}

void stworzBazeDanych()
{
    FILE *loty = fopen(BAZA_LOTY, "ab");
    FILE *rezerwacje = fopen(BAZA_REZERWACJE, "ab");
    
    if(rezerwacje == nullptr || loty == nullptr)
    {
        printf("Blad: \n Nie udalo sie otworzyc/utworzyc pliku.");
        if(rezerwacje) fclose(rezerwacje);
        if(loty) fclose(loty);
        return;
    }
    else{
        printf("Bazy danych zostaly wczystane/zaladowane.");
    }
    fclose(rezerwacje);
    fclose(loty);
    
}

void wyswietlLoty()
{
    FILE * plik = fopen(BAZA_LOTY, "rb");
    if(plik == nullptr){
        printf("Blad bazy danych.");
        return;
    }
    
    fseek(plik, 0, SEEK_END);
    if(ftell(plik) == 0)
    {
        printf("Brak dostepnych lotow.");
        fclose(plik);
        return;
    }
    fseek(plik, 0, SEEK_SET);
    printf("\n LOTY \n");
    printf("| ID  | Odlot | Przylot | Miejsca | Cena |\n");
    
    Lot lot;
    while (fread(&lot,sizeof(Lot), 1, plik) == 1) {
        printf("| %d | %s | %s | %d | %.2f PLN |\n",
               lot.id_lotu,
               lot.miasto_odlotu,
               lot.miasto_przylotu,
               lot.dostepne_miejsca,
               lot.cena);
        printf("----------------------------------------\n");
    }
    fclose(plik);
}

void dodajLot(int id_lotu, const char* odlot, const char*przylot, int miejsca, double cena){
    
    if(miejsca <= 0 || cena <= 0.0 || id_lotu <= 0)
    {
        printf("Jedna z ponizszych danych nie jest dodatnia: ID lotu, cena, ilosc dostepnych miejsc.");
        return;
    }
    if(miejsceLotuWPliku(id_lotu) != -1)
    {
        printf("Istnieje juz lot o takim numerze!");
        return;
    }
    
    FILE *plik = fopen(BAZA_LOTY, "ab");
    Lot nowy;
    nowy.id_lotu = id_lotu;
    nowy.cena = cena;
    nowy.dostepne_miejsca = miejsca;
    strncpy(nowy.miasto_odlotu, odlot, MIASTO-1);
    nowy.miasto_odlotu[MIASTO-1] = '\0';
    strncpy(nowy.miasto_przylotu, przylot, MIASTO-1);
    nowy.miasto_przylotu[MIASTO-1] = '\0';
    fwrite(&nowy,sizeof(Lot) ,1 ,plik );
    printf("Nowy lot o numerze %d zostal dodany.",id_lotu);
    fclose(plik);
}



int znajdzLot(int id, Lot *lot){
    long rekord = miejsceLotuWPliku(id);
    if(rekord == -1) return 0;
    
    FILE *plik = fopen(BAZA_LOTY, "rb");
    if(plik == nullptr) return 0;
    
    fseek(plik, rekord, SEEK_SET);
    fread(lot, sizeof(Lot), 1,plik);
    
    fclose(plik);
    return 0;
}

void usunLot(int id_lotu){
    long wiersz = miejsceLotuWPliku(id_lotu);
    if(wiersz == -1 || wiersz <= 0)
    {
        printf("Podany lot nie istnieje!");
    }
    FILE *plik = fopen(BAZA_LOTY, "rb");
    FILE *plik_temp = fopen("temp_data.bin","wb");
    
    if(plik == nullptr || plik_temp == nullptr)
    {
        printf("Nie udalo sie otworzyc plikow!");
        if(plik)fclose(plik);
        if(plik_temp)fclose(plik);
        return;
    }
    
    Lot lot;
    while(fread(&lot, sizeof(Lot),1 ,plik_temp) == 1){
        if(lot.id_lotu != id_lotu) fwrite(&lot, sizeof(Lot), 1, plik_temp);
    }
    
    fclose(plik);
    fclose(plik_temp);
    
    remove(BAZA_LOTY);
    rename("temp_data.bin", BAZA_LOTY);
    
    printf("Lot numer %d zostal usuniety!",id_lotu);
}

void listaPasazerow(int id_lotu){
    if(id_lotu <= 0)
    {
        printf("Bledny numer lotu!");
        return;
    }
    
    FILE *plik = fopen(BAZA_REZERWACJE, "rb");
    if(plik == nullptr){
        printf("Blad polaczenia z baza danych!");
        return;
    }
    
    Lot lot;
    if(!znajdzLot(id_lotu, &lot))
    {
        printf("Lot o podanym numerze nie istnieje!");
        fclose(plik);
        return;
    }
    printf("Pasazerowie lotu numer %d",id_lotu);
    printf("ID Rezerwacji| Imie| Nazwisko");
    printf("----------------------------");
    Rezerwacja rezerwacja;
    int czyZnaleziono = 0;
    while(fread(&rezerwacja,sizeof(Rezerwacja),1,plik)==1)
    {
        if(rezerwacja.id_lotu == id_lotu)
        {
            printf("| %d | %s | %s |\n", rezerwacja.id_rezerwacja, rezerwacja.imie, rezerwacja.nazwisko);
            czyZnaleziono = 1;
        }
    }
    
    if(!czyZnaleziono){
        printf("Brak rezerwacji!");
    }
    fclose(plik);
}

void edytujLot(int lot_id, int ilosc_miejsc, int cena){
    long pozycja_lotu = miejsceLotuWPliku(lot_id);
    if(lot_id <= 0 || pozycja_lotu ==-1)
    {
        printf("Bledny numer lotu!");
        return;
    }
    if(ilosc_miejsc <=0 || cena <= 0)
    {
        printf("Bledna ilosc miejsc, badz cena. Obydwie wartosci musza byc dodatnie.");
        return;
    }
    FILE *plik = fopen(BAZA_LOTY, "r+b");
    if(plik == nullptr)
    {
        printf("Blad polaczenia z baza danych!");
        return;
    }
    
    Lot zamieniany;
    fseek(plik,pozycja_lotu,SEEK_SET);
    fread(&zamieniany, sizeof(Lot), 1, plik);
    
    zamieniany.dostepne_miejsca = ilosc_miejsc;
    zamieniany.cena = cena;
    
    fseek(plik, pozycja_lotu, SEEK_SET);
    fwrite(&zamieniany, sizeof(Lot), 1, plik);
    
    printf("Lot zostal zaaktualizowny!");
    
    fclose(plik);
}
void rezerwacjaBiletu(int id_lotu, const char*imie, const char* nazwisko){
    Lot zamienianyLot;
    long rekordLotu = miejsceLotuWPliku(id_lotu);
    
    if(id_lotu <= 0 || rekordLotu == -1 || !znajdzLot(id_lotu, &zamienianyLot))
    {
        printf("Nie znaleziono lotu o podanym numerze!");
        return;
    }
    
    if(zamienianyLot.dostepne_miejsca <= 0)
    {
        printf("Brak miejsc w locie numer %d",id_lotu);
        return;
    }
    
    FILE *plikLoty = fopen(BAZA_LOTY, "r+b");
    if(plikLoty == nullptr){
        printf("Blad polaczenia z baza danych!");
        return;
    }
    
    zamienianyLot.dostepne_miejsca--;
    fseek(plikLoty, rekordLotu, SEEK_SET);
    fwrite(&zamienianyLot, sizeof(Lot), 1, plikLoty);
    fclose(plikLoty);
    
    FILE *plikRezerwacja = fopen(BAZA_REZERWACJE, "ab");
    if(plikRezerwacja == nullptr){
        printf("Blad polaczenia z baza danych!");
        return;
    }
    
    Rezerwacja nowaRezerwacja;
    nowaRezerwacja.id_rezerwacja = ostatniaRezerwacjaID()+1;
    nowaRezerwacja.id_lotu = id_lotu;
    
    strncpy(nowaRezerwacja.imie, imie, IMIE);
    nowaRezerwacja.imie[IMIE-1] = '\0';
    strncpy(nowaRezerwacja.nazwisko, nazwisko, NAZWISKO);
    nowaRezerwacja.nazwisko[NAZWISKO - 1] = '\0';
    
    fwrite(&nowaRezerwacja, sizeof(Rezerwacja),1, plikRezerwacja);
    fclose(plikRezerwacja);
    
    printf("Dokonano rezerwacji.");
}
