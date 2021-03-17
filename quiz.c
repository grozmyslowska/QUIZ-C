#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int ilosc_pytan;
char pytania[50][1000];  //przechowuje pytania
char odp[50][5][1000];   //przechowuje odpowiedzi do pytañ

int odp_poprawna[50];            //przechowuje informacje, która odpowiedŸ jest pooprawna
int odp_uzytkownika[50];
int wynik;

int czy_pyt_bylo[50];
int czy_odp_byla[50][5];

int kolejnosc_pytan[50];
int kolejnosc_odpowiedzi[50][5];

char strpom[10];
int i,p,o,o1,o2,o3,o4;


int losuj_pytanie(){

    time_t t;
    srand((unsigned) time(&t));

    int p;

    while(1){

        p = 1 + rand() % ilosc_pytan;  //losowanie z zakresu <1, ilosc_pytan>

        if(czy_pyt_bylo[p] == 0){

            czy_pyt_bylo[p] = 1;
            break;
        }
    }

    return p;
}
int losuj_odpowiedz(int p){

    time_t t;
    srand((unsigned) time(&t));

    int o;

    while(1){

        o = 1 + rand() % 4;          //losowanie z zakresu <1, 4>

        if(czy_odp_byla[p][o] == 0){

            czy_odp_byla[p][o] = 1;
            break;
        }
    }
    return o;
}
void poprawne_wybrano(int p, int o){
    if(odp_poprawna[p] == o)
         printf("(poprawna) ");
    else if(odp_uzytkownika[p] == o)
         printf("(wybrano)  ");
    else printf("           ");
}


int main()
{

    printf("WITAJ W QUIZIE. \n\n");

    //otwieranie pliku

    FILE* plik;
    if((plik = fopen("input.txt","r")) == NULL){
        printf("Nie mozna otworzyc pliku.\n");
    }


    //wczytywanie danych z pliku

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

    //zamkniecie pliku

    fclose(plik);



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

        kolejnosc_pytan[i] = p;
        kolejnosc_odpowiedzi[i][1] = o1;
        kolejnosc_odpowiedzi[i][2] = o2;
        kolejnosc_odpowiedzi[i][3] = o3;
        kolejnosc_odpowiedzi[i][4] = o4;

        printf("\n");

        while(1){

            scanf("%c",&o);

            if( o>96 && o<101 ){

                if(o == 'a')odp_uzytkownika[p] = o1;
                if(o == 'b')odp_uzytkownika[p] = o2;
                if(o == 'c')odp_uzytkownika[p] = o3;
                if(o == 'd')odp_uzytkownika[p] = o4;

                if(odp_uzytkownika[p] == odp_poprawna[p])wynik++;

                break;
            }
            //else printf("Nieprawidlowa odpowiedz. Prosze podac odpowiedz ponownie.\n");
        }

        printf("\n");
    }




    //wyswietlenie wyniku w procentach

    printf("-------------------------------------------------------------------------\n\n");

    printf(" WYNIK: %d %% \n\n", wynik*100/ilosc_pytan);

    printf("-------------------------------------------------------------------------\n\n");



    i=0;

    while(i++ < ilosc_pytan){

        p = kolejnosc_pytan[i];
        o1 = kolejnosc_odpowiedzi[i][1];
        o2 = kolejnosc_odpowiedzi[i][2];
        o3 = kolejnosc_odpowiedzi[i][3];
        o4 = kolejnosc_odpowiedzi[i][4];

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
    }


    printf("KONIEC.\n");

    return 0;
}
