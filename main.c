#include <stdio.h>
#include <stdlib.h>


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

int main(int argc, char *argv[])
{
    int size_r = atoi(argv[1]);
    if(size_r<1) return -1;
    int size_c = atoi(argv[2]);
    if(size_c<1) return -2;
    char siatka[size_r][size_c];
    int ant_r = atoi(argv[3]);
    int *r = &ant_r;
    int ant_c = atoi(argv[4]);
    int *c = &ant_c;
    int ant_state = atoi(argv[5]);  //0 = U - up, 1 = R - right, 2 = D - down, 3 = L - left
    int *p = &ant_state;

    for(int i=0; i<size_r; i++)
        for(int j=0; j<size_c; j++)
            siatka[i][j] = '.';

    for(int i=0; i<atoi(argv[6]); i++)
    {
        zmiana_pola(r, c, size_r, size_c, siatka, p);
        wypisz_siatke(size_r, size_c, siatka);
    }

    FILE *fptr;
    fptr = fopen("C:\\ant_output\\test.txt","w"); //w makefile należy dać mkdir
    if(fptr == NULL)
    {
        printf("Error!");
        return -10;
    }
    for(int i=0; i<size_r; i++)
        {
            for(int j=0; j<size_c; j++)
            {
                putc(siatka[i][j], fptr);
            }
            fprintf(fptr, "\n");
        }
    return 0;
}
