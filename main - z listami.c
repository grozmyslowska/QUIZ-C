#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ilosc_pytan;
char pytania[50][1000];   //Przechowuje tresc pytan. Pytania są numerowane od 1 do 49.
char odp[50][5][1000];    //Przechowuje tresc odpowiedzi do danego pytania. Kazde pytanie ma 4 odpowiedzi (1-4).
int odp_poprawna[50];     //Przechowuje numer(indeks) poprawnej odpowiedzi (1,2,3 lub 4).
int odp_uzytkownika[50];  //Przechwuje wybor uzytkownika (1,2,3 lub 4).
int wynik;

int czy_pyt_bylo[50];     //Tablica pomocnicza do losowania pytania.
int czy_odp_byla[50][5];  //Tablica pomocnicza do losowania kolejnosci odpowiedzi do pytania.


//Lista jednokierunkowa przechowujaca indeksy pytan i ich odpowiedzi
//w kolejnosci, w jakiej byly wylosowane oraz wyswietlane.

typedef struct lista_pytan{
    int p,o1,o2,o3,o4;
    struct lista_pytan *nast;
};

//Poczatek listy.

 struct lista_pytan *pocz;

//Zmienne pomocnicze.

char strpom[10];
int i,p,o,o1,o2,o3,o4;


int losuj_pytanie(){

    //Funkcja losujaca.

    time_t t;
    srand((unsigned) time(&t));

    int p;

    //Losowanie odbywa sie tak dlugo, dopoki nie zostanie wybrane pytanie, ktorego jeszcze nie bylo.

    while(1){

        //Losowanie indeksu pytania z zakresu <1, ilosc_pytan>.

        p = 1 + rand() % ilosc_pytan;

        //Jezeli pytanie nie bylo wybrane juz wczesniej, jego wartosc w tablicy czy_pyt_bylo wynosi 0.

        if(czy_pyt_bylo[p] == 0){

            //Gdy wylosowano takie pytanie, ktore nie pojawilo sie wczesniej,
            //zmienia wartosci w tablicy na 1 oraz przerywa petle.

            czy_pyt_bylo[p] = 1;
            break;
        }
    }

    //Zwraca indeks wylosowanego pytania.

    return p;
}

int losuj_odpowiedz(int p){

    //Funkcja losujaca.

    time_t t;
    srand((unsigned) time(&t));

    int o;

    //Losowanie odbywa sie tak dlugo, dopoki nie zostanie wybrana odpowiedz do pytania, ktorej jeszcze nie bylo.

    while(1){

        //Losowanie z zakresu <1, 4>.

        o = 1 + rand() % 4;

        if(czy_odp_byla[p][o] == 0){

            czy_odp_byla[p][o] = 1;
            break;
        }
    }

    //Zwraca indeks wylosowanej odpowiedzi.

    return o;
}

void poprawne_wybrano(int p, int o){
    if(odp_poprawna[p] == o)
         printf("(poprawna) ");
    else if(odp_uzytkownika[p] == o)
         printf("(wybrano)  ");
    else printf("           ");
}

void dodaj_na_liste(int p, int o1, int o2, int o3, int o4){

    if( pocz == NULL ){

        pocz = malloc(sizeof(struct lista_pytan));
        pocz->p = p;
        pocz->o1 = o1;
        pocz->o2 = o2;
        pocz->o3 = o3;
        pocz->o4 = o4;
        pocz->nast = NULL;
    }

    else{

        struct lista_pytan *el = pocz;

        while( el->nast != NULL ) el = el->nast;

        el->nast = malloc(sizeof(struct lista_pytan));

        el->nast->p = p;
        el->nast->o1 = o1;
        el->nast->o2 = o2;
        el->nast->o3 = o3;
        el->nast->o4 = o4;
        el->nast->nast = NULL;
    }
}


int main()
{

    printf("WITAJ W QUIZIE. \n\n");

    //Otwieranie pliku.

    FILE* plik;
    if((plik = fopen("input.txt","r")) == NULL){
        printf("Nie mozna otworzyc pliku.\n");
    }


    //Wczytywanie danych z pliku - pytań i odpowiedzi.

    while(!feof(plik)){

        ilosc_pytan++;
        fgets (pytania[ilosc_pytan], 10000, plik);
        fgets (odp[ilosc_pytan][1], 10000, plik);
        fgets (odp[ilosc_pytan][2], 10000, plik);
        fgets (odp[ilosc_pytan][3], 10000, plik);
        fgets (odp[ilosc_pytan][4], 10000, plik);
        fgets (strpom, 5, plik);
        odp_poprawna[ilosc_pytan] = strpom[0] - 48;
        fgets (strpom, 5, plik);
    }

    //Zamkniecie pliku.

    fclose(plik);


    //Petla w ktorej wykonuje sie glowna czesc programu - wyswietlanie pytan
    //z odpowiedziami i pobieranie wyboru uzytkownika.

    while(i++ < ilosc_pytan){

        p = losuj_pytanie();
        o1 = losuj_odpowiedz(p);
        o2 = losuj_odpowiedz(p);
        o3 = losuj_odpowiedz(p);
        o4 = losuj_odpowiedz(p);

        printf("%s",pytania[p]);
        printf("a) %s",odp[p][o1]);
        printf("b) %s",odp[p][o2]);
        printf("c) %s",odp[p][o3]);
        printf("d) %s",odp[p][o4]);

        dodaj_na_liste(p,o1,o2,o3,o4);

        printf("\n");

        //Petla w ktorej nastepuje pobranie odpowiedzi od uzytkownika.
        //Wykonuje sie tak dlugo, dopoki uzytkownik nie poda odpowiedzi w dozwolonym formacie.
        //Dozwolony format: a, b, c, d, A, B, C lub D.

        while(1){

            scanf("%c",&o);

            if(( o>96 && o<101 ) || ( o>64 && o<69 )){

                if((o == 'a') || ( o == 'A'))odp_uzytkownika[p] = o1;
                if((o == 'b') || ( o == 'B'))odp_uzytkownika[p] = o2;
                if((o == 'c') || ( o == 'C'))odp_uzytkownika[p] = o3;
                if((o == 'd') || ( o == 'D'))odp_uzytkownika[p] = o4;

                //Jezeli odpowiedz uzytkownika na dane pytanie pokrywa sie z poprawna, wynik sie inkrementuje.

                if(odp_uzytkownika[p] == odp_poprawna[p])wynik++;

                break;
            }
        }

        printf("\n");
    }


    //Wyswietlenie wyniku w procentach.

    printf("-------------------------------------------------------------------------\n\n");

    printf(" WYNIK: %d %% \n\n", wynik*100/ilosc_pytan);

    printf("-------------------------------------------------------------------------\n\n");


    //Wyswietlenie pytan, na ktore uzytkownik odpowiedzial niepoprawnie,
    //wraz z zaznaczeniem odpowiedzi wybranej oraz poprawnej.

    //Pytania i odpowiedzi wyswietlaja sie w takiej samej kolejnosci,
    //w jakiej wyswietlaly sie podczas quizu.

    struct lista_pytan *el = pocz;

    while( el != NULL ){

        p = el->p;
        o1 = el->o1;
        o2 = el->o2;
        o3 = el->o3;
        o4 = el->o4;

        if(odp_uzytkownika[p] != odp_poprawna[p]){

            printf("%s",pytania[p]);

            poprawne_wybrano(p,o1);
            printf("a) %s",odp[p][o1]);

            poprawne_wybrano(p,o2);
            printf("b) %s",odp[p][o2]);

            poprawne_wybrano(p,o3);
            printf("c) %s",odp[p][o3]);

            poprawne_wybrano(p,o4);
            printf("d) %s",odp[p][o4]);

            printf("\n");
            printf("\n");
        }

        el = el->nast;
    }

    printf("KONIEC.\n");

    return 0;
}
