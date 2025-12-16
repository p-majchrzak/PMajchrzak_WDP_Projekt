#include "rezerwacja.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

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
