//#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
#include <getopt.h>
#include <locale.h>
#include <string.h>

#include "mrowka.h"




/*
void zmiana_pola(int* y, int* x, int size_r, int size_c, char siatka[size_r][size_c], int* ptr)
{
    if(siatka[*y][*x]=='.')
    {
        siatka[*y][*x]='X';
        switch(*ptr)
        {
            case 0: *ptr = 1; *x=*x+1; break;
            case 1: *ptr = 2; *y=*y+1; break;
            case 2: *ptr = 3; *x=*x-1; break;
            case 3: *ptr = 0; *y=*y-1; break;
        }
    }
    else
    if(siatka[*y][*x]=='X')
    {
        siatka[*y][*x]='.';
        switch(*ptr)
        {
            case 0: *ptr = 3; *x=*x-1; break;
            case 1: *ptr = 0; *y=*y-1; break;
            case 2: *ptr = 1; *x=*x+1; break;
            case 3: *ptr = 2; *y=*y+1; break;
        }
    }
}
void wypisz_siatke(int size_r, int size_c, char siatka[size_r][size_c])
{
    for(int i=0; i<size_r; i++)
    {
        for(int j=0; j<size_c; j++)
        {
            printf("%c", siatka[i][j]);
        }
        printf("\n");
    }
}
*/
void wypisz_wywolanie_programu(char * argv_0) {
    printf("%s -m l_wierszy -n l_kolumn -i l_iteracji -name przedrostek -input wejście -g zapełnienie -x kolumna -y wiersz -z kierunek -mrowki l_mrowek -h --help\n\
Wszystkie argumenty są opcjonalne:\n\
m       - liczba wierszy planszy. Domyślnie wynosi %i.\n\
n       - liczba kolumn planszy. Domyślnie wynosi %i.\n\
i       - liczba iteracji mrówki. Domyślnie wynosi %i.\n\
name    - przedrostek plików wynikowych. Jeśli przedrostek nie zostanie podany, domyślnie program będzie wypisywał na standardowe wyjście.\n\
input   - nazwa pliku wejściowego zawierającego siatkę. Plik powininen być w takim samym formacie, w jakim jest wypisywany przez program (z ramką, mrówki są na siatce. Domyślnie program nie wczytuje z pliku.\n\
g       - liczba naturalna oznaczająca zapełnienie planszy losowo wygenerowanymi \"czarnymi\" polami, wg zapełnienia podanego w procentach, domyślnie %i. Wypełnienie wygenerowanej planszy może trochę odbiegać od podanego wypełnienia.\n\
x       - numer początkowej kolumna pierwszej mrówki Langtona (numerowany od 1, ignorowany jeśli podano plik wejściowy). Domyślnie to m/2 zaokrąglone w dół.\n\
y       - numer początkowego wiersza pierwszej mrówki Langtona (numerowany od 1, ignorowany jeśli podano plik wejściowy). Domyślnie to n/2 zaokrąglone w dół.\n\
z       - początkowy kierunek pierwszej mrówki Langtona (0 - góra, 1 - prawo, 2 - dół, 3 - lewo, domyślnie %i)\n\
mrowki  - liczba mrówek Langtona na planszy, domyślnie %i. Jeśli liczba ta jest większa niż 1, współrzędne początkowe i kierunki pozostałych mrówek będą wylosowane. Liczba ta jest ignorowana, jeśli podano plik wejściowy.\n\
h, help - wypisuje pomoc i wywołanie programu.\n\
Przykład:\n\
%s -m 100 -n 100 -i 1111 -name ant -g 25 -x 34 -y 77 -z 2 -mrowki 3\n", argv_0, arg_m_default, arg_n_default, arg_i_default, arg_g_default, arg_z_default, arg_mrowki_default, argv_0);
}
void wypisz_pomoc_programu(char * argv_0) {
    printf("Program obliczający kolejne etapy mrówki Langtona i zapisujący je do plików lub na standardowe wyjście.\n");
    /// printf("Program umożliwia symulowanie wielu mrówek Langtona.\n"); Jeszcze nie umożliwia
    wypisz_wywolanie_programu(argv_0);
}
static int help_flag = 0;
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "C.UTF-8");
    srand(time(NULL));
    FILE * input_file;
    int arg_m = arg_m_default;
    int arg_n = arg_n_default;
    int arg_i = arg_i_default;
    char * arg_name = "";
    char * arg_input = "";
    double arg_g = arg_g_default;
    int arg_x = arg_m/2;
    int arg_y = arg_n/2;
    int arg_z = arg_z_default;
    int arg_mrowki = arg_mrowki_default;
    int czy_blad = 0;char komunikat_blad[300];
    static struct option long_options[] =
    {
        {"m",      required_argument, 0, 'm'},
        {"n",      required_argument, 0, 'n'},
        {"i",      required_argument, 0, 'i'},
        {"name",   required_argument, 0, 'N'},
        {"input",  required_argument, 0, 'I'},
        {"g",      required_argument, 0, 'g'},
        {"x",      required_argument, 0, 'x'},
        {"y",      required_argument, 0, 'y'},
        {"z",      required_argument, 0, 'z'},
        {"mrowki", required_argument, 0, 'M'},
        {"h",      no_argument, &help_flag, 1},
        {"help",   no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };
    int getopt_res,option_index = 0;
    while ((getopt_res = getopt_long_only (argc, argv, "m:n:i:N:I:g:x:y:z:M:", long_options, &option_index)) != -1)
    {
      switch (getopt_res)
      {
        case 0:
            if (long_options[option_index].flag != 0) break;
            printf ("option %s", long_options[option_index].name);
            if (optarg) printf (" with arg %s", optarg);
            printf ("\n");
            break;
        case 'm':
            arg_m = atoi(optarg);
            if ((arg_m < arg_m_min || arg_m > arg_m_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -m powinien być liczbą naturalną z przedziału <%i,%i>\n", arg_m_min, arg_m_max);
            }
            break;
        case 'n':
            arg_n = atoi(optarg);
            if ((arg_n < arg_n_min || arg_n > arg_n_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -n powinien być liczbą naturalną z przedziału <%i,%i>\n", arg_n_min, arg_n_max);
            }
            break;
        case 'i':
            arg_i = atoi(optarg);
            if ((arg_i < arg_i_min || arg_n > arg_i_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -i powinien być liczbą naturalną z przedziału <%i,%i>\n", arg_i_min, arg_i_max);
            }
            break;
        case 'N':
            arg_name = optarg;
            if (strlen(arg_name) > arg_name_max_len) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -N jest za długi, powinien być nie dłuższy niż %i",arg_name_max_len);
            }
            break;
        case 'I':
            arg_input = optarg;
            input_file = fopen(arg_input, "r");
            if (input_file == NULL) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Nie znaleziono pliku określonego przez argument -I: %s\n", arg_input);
            }
            break;
        case 'g':
            arg_g = atof(optarg);
            if ((arg_g < arg_g_min || arg_g > arg_g_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -g powinien być liczbą rzeczywistą z przedziału <%i,%i>\n", arg_g_min, arg_g_max);
            }
            break;
        case 'x':
            arg_x = atoi(optarg);
            break;
        case 'y':
            arg_y = atoi(optarg);
            break;
        case 'z':
            arg_z = atoi(optarg);
            if ((arg_z < arg_g_min || arg_z > arg_z_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -z powinien być liczbą naturalną z przedziału <%i,%i>\n", arg_z_min, arg_z_max);
            }
            break;
        case 'M':
            arg_mrowki = atoi(optarg);
            if ((arg_mrowki < arg_mrowki_min || arg_mrowki > arg_mrowki_max) && !czy_blad) {
                czy_blad = 1;
                sprintf(komunikat_blad,"Argument -mrowki powinien być liczbą naturalną z przedziału <%i,%i>\n", arg_mrowki_min, arg_mrowki_max);
            }
            break;
        case '?':
            break;
        default:
            abort ();
        }
    }
    if (help_flag) {
        wypisz_pomoc_programu(argv[0]);
        return 0;
    }
    if ((arg_x < 1 || arg_x > arg_n) && !czy_blad) {
        czy_blad = 1;
        sprintf(komunikat_blad,"Argument -x powinien być wewnątrz siatki, tzn. w przedziale <%i,%i>\n", 1, arg_n);
    }
    if ((arg_y < 1 || arg_y > arg_m) && !czy_blad) {
        czy_blad = 1;
        sprintf(komunikat_blad,"Argument -y powinien być wewnątrz siatki, tzn. w przedziale <%i,%i>\n", 1, arg_m);
    }
    if (czy_blad) {
        printf("%s", komunikat_blad);
        wypisz_wywolanie_programu(argv[0]);
        return 0;
    }
    /// Indeksowanie od 1 -> Indeksowanie od 0
    arg_x--;
    arg_y--;
    if (inicjacja_siatki(arg_n, arg_m, arg_g) != 0) {
        printf("Wystąpił błąd przy inicjacji siatki.\n");
        return 1;
    }
    if (dodaj_mrowke(arg_x, arg_y, arg_z) != 0) {
        printf("Wystąpił błąd przy dodawaniu mrówki.\n");
        return 2;
    }
    int k;
    for (k = 1; k < arg_mrowki;) {
        int rand_x,rand_y,rand_z;
        rand_x = (rand()/(double)RAND_MAX)*arg_n;
        if (rand_x == arg_n) rand_x--;
        rand_y = (rand()/(double)RAND_MAX)*arg_m;
        if (rand_y == arg_m) rand_y--;
        rand_z = (rand()/(double)RAND_MAX)*4;
        if (rand_z == 4) rand_z--;
        if (dodaj_mrowke(rand_x, rand_y, rand_z) == 0) k++;
    }
    FILE *files[arg_i_max];
    for (k = 0; k <= arg_i; k++) {
        if (strlen(arg_name) == 0) {
            printf("%i:\n", k);
            wypisz_siatke(stdout);
        } else {
            char filename[200];
            sprintf(filename, "%s_%d.txt", arg_name, k);
            files[k] = fopen(filename, "w");
            wypisz_siatke(files[k]);
            fclose(files[k]);
        }
        //mrowka_ruch(mrowki); /// mrowki == mrowki+0 == &(mrowki[0])
        mrowki_ruch();
    }
    return 0;
}
