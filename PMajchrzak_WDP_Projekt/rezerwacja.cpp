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
