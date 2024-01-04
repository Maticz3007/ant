#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

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
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "C.UTF-8");
    /// wciąż nie wypisują się strzałki w prawo i lewo...
    int iter = 0; //i
    int size_r = 0; //m
    int size_c = 0; //n
    int ant_r = 0; //y (domyślnie size_r/2)
    int ant_c = 0; //x (domyślnie size_c/2)
    int ant_state = 0; //s, 0 = U - up, 1 = R - right, 2 = D - down, 3 = L - left
    char *name = NULL; //o, przedrostek nazw plików (domyślnie "ant")
    char *input = NULL; //w, plik wejściowy z siatką (mapą) początkową i pozycją mrówki
    /// input jeszcze nie jest zaimplementowane
    int x;
    while ((x = getopt (argc, argv, "n:m:o:i:y:x:w:s:")) != -1)
    {
        switch (x)
        {
            case 's':
                ant_state = atoi(optarg);
                break;
            case 'n':
                size_c = atoi(optarg);
                break;
            case 'm':
                size_r = atoi(optarg);
                break;
            case 'o':
                name = optarg;
                break;
            case 'w':
                input = optarg;
                break;
            case 'i':
                iter = atoi(optarg);
                break;
            case 'x':
                ant_c = atoi(optarg);
                break;
            case 'y':
                ant_r = atoi(optarg);
                break;
            case '?':
                if (optopt == 'n' || optopt == 'm' || optopt == 'o' || optopt == 'i' || optopt == 'x' || optopt == 'y')
                    fprintf (stderr, "Option -%x requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%x'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort ();
        }
    }
    for (int index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    if(ant_c==0) ant_c = size_c/2;
    if(ant_r==0) ant_r = size_r/2;
    if(name==NULL) name="ant";
    /*char siatka[size_r][size_c];
    int *r = &ant_r;
    int *c = &ant_c;
    int *p = &ant_state;
    */

    printf ("size_c = %d, size_r = %d, name = %s, iter = %d, ant_c = %d, ant_r = %d, input = %s, ant_state = %d\n",
            size_c, size_r, name, iter, ant_c, ant_r, input, ant_state);

    
    /*
    for(int i=0; i<size_r; i++)
        for(int j=0; j<size_c; j++)
            siatka[i][j] = '.';
    */
   if (inicjacja_siatki(size_c, size_r) != 0) {
        printf("Wystąpił błąd przy inicjacji siatki.\n");
        return 1;
   }
   if (dodaj_mrowke(ant_c, ant_r, ant_state) != 0) {
        printf("Wystąpił błąd przy dodawaniu mrówki.\n");
        return 2;
   }

    FILE *files[iter];
    for (int k = 0; k < iter; k++)
    {
        //char filename[200];
        //sprintf(filename, "%s_%d.txt", name, k);
        //files[k] = fopen(filename, "w");
        mrowka_ruch(mrowki); /// mrowki == mrowki+0 == &(mrowki[0])
        //wypisz_siatke(files[k]);
        //wypisz_siatke(stdout);printf("\n");
        /*
        zmiana_pola(r, c, size_r, size_c, siatka, p);
        wypisz_siatke(size_r, size_c, siatka);
        for(int i=0; i<size_r; i++)
        {
            for(int j=0; j<size_c; j++)
            {
                putc(siatka[i][j], files[k]);
            }
            fprintf(files[k], "\n");
        }
        */
        //fclose(files[k]);
    }
    wypisz_siatke(stdout);
    printf ("size_c = %d, size_r = %d, name = %s, iter = %d, ant_c = %d, ant_r = %d, input = %s, ant_state = %d\n",
            size_c, size_r, name, iter, ant_c, ant_r, input, ant_state);

    return 0;
}
