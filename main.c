#include <stdio.h>
#include <stdlib.h>


void field_change(int* y, int* x, int size_r, int size_c, char siatka[size_r][size_c], int* ptr)
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


int main(int argc, char *argv[])
{
    int size_r = atoi(argv[1]);
    if(size_r==0) return -1;
    int size_c = atoi(argv[2]);
    if(size_c==0) return -2;
    char siatka[size_r][size_c];
    int ant_r = atoi(argv[3]);
    int *r = &ant_r;
    int ant_c = atoi(argv[4]);
    int *c = &ant_c;
    for(int i=0; i<size_r; i++)
    {
        for(int j=0; j<size_c; j++)
        {
            siatka[i][j] = '.';
            //printf("%c", siatka[i][j]);
        }
        //printf("\n");
    }
    int ant_state = atoi(argv[5]);  //0 = U - up, 1 = R - right, 2 = D - down, 3 = L - left
    int *p = &ant_state;
    field_change(r, c, size_r, size_c, siatka, p);
    field_change(r, c, size_r, size_c, siatka, p);
    field_change(r, c, size_r, size_c, siatka, p);
    field_change(r, c, size_r, size_c, siatka, p);

    printf("%d\n", ant_state);
    for(int i=0; i<size_r; i++)
    {
        for(int j=0; j<size_c; j++)
        {
            printf("%c", siatka[i][j]);
        }
        printf("\n");
    }
    return 0;
}
