#include "rezerwacja.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

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
