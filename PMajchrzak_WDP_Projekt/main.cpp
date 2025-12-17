#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "rezerwacja.h"

#define HASLO "admin123"

void czyscKonsole(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void czekajNaEnter(){
    int c;
    printf("\nNacisnij ENTER aby kontynuowac...");
    while((c=getchar()) != '\n' && c !=EOF);
    
    getchar();
}

void menuKlient(){
    printf("\n--- MENU KLIENTA ---\n");
    printf("1. Wyswietl dostepne loty\n");
    printf("2. Zarezerwuj bilet\n");
    printf("3. Przelacz na tryb ADMIN\n");
    printf("4. Wyjdz\n");
    printf("Wybierz opcje: ");
}

void menuAdmina() {
    printf("\n--- MENU ADMINISTRATORA ---\n");
    printf("1. Wyswietl wszystkie loty\n");
    printf("2. Dodaj nowy lot\n");
    printf("3. Usun lot\n");
    printf("4. Modyfikuj lot (miejsca/cena)\n");
    printf("5. Wyswietl pasazerow lotu\n");
    printf("6. Przelacz na tryb KLIENT\n");
    printf("7. Wyjdz z programu\n");
    printf("Wybierz opcje: ");
}

int main() {
    czyscKonsole();
    int tryb = 0;
    int wybor = 0;
    
    stworzBazeDanych();
    
    do{
        if(tryb == 0)
        {
            menuKlient();
        }
        else
        {
            menuAdmina();
        }
        
        if(scanf("%d", &wybor) != 1)
        {
            printf("Blad wczytywania. Podaj liczbe.\n");
            while(getchar() != '\n');
            continue;
        }
        
        int id, miejsca;
        double cena;
        char imie[IMIE], nazwisko[NAZWISKO];
        char odlot[MIASTO], przylot[MIASTO];
        char haslo[20];
        
        if(tryb == 0)
        {
            switch (wybor) {
                case 1: wyswietlLoty(); break;
                case 2:
                    printf("Podaj ID lotu: ");
                        if(scanf("%d",&id) != 1) break;
                    printf("Podaj Imie: ");
                        if(scanf("%s", imie) != 1) break;
                    printf("Podaj nazwisko: ");
                        if(scanf("%s",nazwisko) != 1) break;
                    rezerwacjaBiletu(id, imie, nazwisko);
                    break;
                case 3:
                    printf("Podaj haslo do konta administratora: ");
                    if(scanf("%s", haslo) != 1) break;
                    
                    if(strcmp(haslo,HASLO) == 0){
                        tryb = 1;
                        printf("Uzyskano dostep do konta administratora.");
                    }
                    else
                    {
                        printf("Odmowa dostepu, podano bledne haslo.");
                    }
                    break;
                case 4:
                    printf("Dziekujemy za korzystanie z naszych uslug!");
                    wybor = 7;
                    break;
                default:
                    printf("Wybrano niedostepna opcje. Prosze ponownie dokonac wyboru.");
                    break;
                }
            }
            else{
                switch (wybor) {
                    case 1: wyswietlLoty(); break;
                    case 2:
                        printf("Podaj nowy numer lotu: ");
                        if(scanf("%d",&id) != 1) break;
                        printf("Podaj miasto odlotu: ");
                        if(scanf("%s", odlot) != 1) break;
                        printf("Podaj miasto przylotu: ");
                        if(scanf("%s", przylot) != 1) break;
                        printf("Podaj liczbe miejsc: ");
                        if(scanf("%d", &miejsca) != 1) break;
                        printf("Podaj cene: ");
                        if(scanf("%lf", &cena) != 1) break;
                        dodajLot(id, odlot, przylot, miejsca, cena);
                        break;
                    case 3:
                        printf("Podaj numer lotu do usuniecia: ");
                        if(scanf("%d",&id) != 1) break;
                        usunLot(id);
                        break;
                    case 4:
                        printf("Podaj numer lotu do modyfikacji: ");
                        if(scanf("%d", &id) != 1)break;
                        printf("Podaj nowa liczbe miejsc: ");
                        if(scanf("%d",&miejsca) != 1) break;
                        printf("Podaj nowa cene: ");
                        if(scanf("%lf", &cena) != 1) break;
                        edytujLot(id, miejsca, cena);
                        break;
                    case 5:
                        printf("Podaj numer lotu, dla ktorego chcesz uzyskac dane pasazerow: ");
                        if(scanf("%d",&id) != 1)break;
                        listaPasazerow(id);
                        break;
                    case 6:
                        tryb = 0;
                        printf("Powrot do trybu klienta...");
                        break;
                    case 7:
                        printf("Zakonczono dzialanie programu...");
                        break;
                    default:
                        printf("Wybrano niedostepna opcje. Prosze ponownie dokonac wyboru.");
                        break;
            }
        }
        if(wybor != 4 && wybor != 7){
            czekajNaEnter();
            czyscKonsole();
        }
    }while(wybor!=7);
    
    return 0;
}
