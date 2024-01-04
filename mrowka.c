#include "mrowka.h"

/// Zainicjuj siatkę białymi polami
/// Zwraca 1, jeśli podana liczba wierszy lub kolumn jest nieprawidłowa lub 0 w przeciwnym wypadku
int inicjacja_siatki(int kolumny, int wiersze) {
    if (wiersze <= 0 || kolumny <= 0) return 1;
    siatka.wiersze = wiersze;
    siatka.kolumny = kolumny;
    liczba_mrowek = 0;
    int i,j;
    for (i = 0;i < wiersze;i++) {
        for (j = 0;j < kolumny;j++) {
            siatka.v[i][j] = siatka_biale;
        }
    }
    return 0;
}

/// Dodaje mrówkę do wektora mrowki
/// Zwraca 0 jeśli się udało, 1 jeśli argumenty są nieprawidłowe lub 2 jeśli jest za dużo mrówek, aby dodać nową
int dodaj_mrowke(int x, int y, int kierunek) {
    if (x < 0 || x >= siatka.kolumny || y < 0 || y >= siatka.wiersze || kierunek < 0 || kierunek > 3) return 0;
    if (liczba_mrowek >= max_mrowki) return 2;
    mrowki[liczba_mrowek].x = x;
    mrowki[liczba_mrowek].y = y;
    mrowki[liczba_mrowek].kierunek = kierunek;
    liczba_mrowek++;
    return 0;
}

/// Pojedynczy ruch Mrówki Langtona
/// Mrówka odwraca kolor pola na którym jest, przesuwa się do przodu i skręca w zależności od koloru pola
void mrowka_ruch(mrowka * m) {
    mrowka_odwroc_pole(m);
    mrowka_do_przodu(m);
    mrowka_skret(m);
}
/// Funkcja pomocnicza do mrowka_ruch, przesuwa mrówkę do przodu o 1 pole
/// Jeśli mrówka wyjdzie poza siatkę, to wraca na początek wiersza / kolumny
void mrowka_do_przodu(mrowka * m) {
    switch (m->kierunek)
    {
        case mrowka_U: m->y--; break;
        case mrowka_R: m->x++; break;
        case mrowka_D: m->y++; break;
        case mrowka_L: m->x--; break;
    }
    if (m->y < 0) m->y = siatka.wiersze-1;
    if (m->y >= siatka.wiersze) m->y = 0;
    if (m->x < 0) m->x = siatka.kolumny-1;
    if (m->x >= siatka.kolumny) m->x = 0;
}
/// Funkcja pomocnicza do mrowka_ruch, odwraca kolor pola na którym jest mrówka
void mrowka_odwroc_pole(mrowka * m) {
    if (siatka.v[m->y][m->x] == siatka_biale) siatka.v[m->y][m->x] = siatka_czarne;
    else siatka.v[m->y][m->x] = siatka_biale;
}
/// Funkcja pomocnicza do mrowka_ruch, skręca mrówkę w zależności od koloru pola
void mrowka_skret(mrowka * m) {
    if (siatka.v[m->y][m->x] == siatka_biale) {
        /// W prawo
        m->kierunek++;
        if (m->kierunek > 3) m->kierunek = 0;
    } else {
        /// W lewo
        m->kierunek--;
        if (m->kierunek < 0) m->kierunek = 3;
    }
}

/// Wypisywanie siatki
void wypisz_siatke(FILE * gdzie) {
    int i,j,k;
    int mrowka_na_polu;
    for(i = 0; i < siatka.wiersze; i++)
    {
        for(j = 0; j < siatka.kolumny; j++)
        {
            mrowka_na_polu = -1;
            for (k = 0;k < liczba_mrowek;k++) {
                if (mrowki[k].y == i && mrowki[k].x == j) {
                    mrowka_na_polu = k;
                    break;
                }
            }
            if (mrowka_na_polu == -1) {
                if (siatka.v[i][j] == siatka_biale) fprintf(gdzie,"%s",wypisz_siatka_biale);
                else fprintf(gdzie,"%s",wypisz_siatka_czarne);
            } else {
                switch (mrowki[mrowka_na_polu].kierunek) {
                    case mrowka_U:
                        if (siatka.v[i][j] == siatka_biale) fprintf(gdzie,"%s",wypisz_biale_mrowka_U);
                        else fprintf(gdzie,"%s",wypisz_czarne_mrowka_U);
                        break;
                    case mrowka_R:
                        if (siatka.v[i][j] == siatka_biale) fprintf(gdzie,"%s",wypisz_biale_mrowka_R);
                        else fprintf(gdzie,"%s",wypisz_czarne_mrowka_R);
                        break;
                    case mrowka_D:
                        if (siatka.v[i][j] == siatka_biale) fprintf(gdzie,"%s",wypisz_biale_mrowka_D);
                        else fprintf(gdzie,"%s",wypisz_czarne_mrowka_D);
                        break;
                    case mrowka_L:
                        if (siatka.v[i][j] == siatka_biale) fprintf(gdzie,"%s",wypisz_biale_mrowka_L);
                        else fprintf(gdzie,"%s",wypisz_czarne_mrowka_L);
                        break;
                }
            }
        }
        fprintf(gdzie,"\n");
    }
}