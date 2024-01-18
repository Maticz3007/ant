#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include "mrowka.h"

struct siatka_t siatka;
mrowka mrowki[arg_mrowki_max];
unsigned int liczba_mrowek;

/// Zainicjuj siatkę białymi polami
/// Zwraca 1, jeśli podana liczba wierszy lub kolumn jest nieprawidłowa lub 0 w przeciwnym wypadku
int inicjacja_siatki(int kolumny, int wiersze, double rand_perc, char * arg_input) {
    setlocale(LC_ALL, "");
    int i=-1, j=0;
    siatka.wiersze = wiersze;
    siatka.kolumny = kolumny;
    if (arg_input==NULL) {
        if (wiersze <= 0 || kolumny <= 0) return 1;
        liczba_mrowek = 0;
        for (i = 0; i < wiersze; i++)
            for (j = 0; j < kolumny; j++) {
                if (1 + rand() % 100 > rand_perc)
                    siatka.v[i][j] = siatka_biale;
                else
                    siatka.v[i][j] = siatka_czarne;
            }
    }
    else
    {
        wchar_t temp;
        FILE * fptr = fopen(arg_input, "r");
        liczba_mrowek = 0;
        while ((temp = fgetwc(fptr)) != WEOF) {
            switch (temp) {
                case 0x2588: // Unicode dla '█'
                    siatka.v[i][j] = siatka_czarne;
                    break;
                case ' ':
                    siatka.v[i][j] = siatka_biale;
                    break;
                case 0x25B2: // Unicode dla '▲'
                    siatka.v[i][j] = siatka_czarne;
                    dodaj_mrowke(j, i, 0);
                    break;
                case 0x25B6: // Unicode dla '▶'
                    siatka.v[i][j] = siatka_czarne;
                    dodaj_mrowke(j, i, 1);
                    break;
                case 0x25BC: // Unicode dla '▼'
                    siatka.v[i][j] = siatka_czarne;
                    dodaj_mrowke(j, i, 2);
                    break;
                case 0x25C0: // Unicode dla '◀'
                    siatka.v[i][j] = siatka_czarne;
                    dodaj_mrowke(j, i, 3);
                    break;
                case 0x25B3: // Unicode dla '△'
                    siatka.v[i][j] = siatka_biale;
                    dodaj_mrowke(j, i, 0);
                    break;
                case 0x25B7: // Unicode dla '▷'
                    siatka.v[i][j] = siatka_biale;
                    dodaj_mrowke(j, i, 1);
                    break;
                case 0x25BD: // Unicode dla '▽'
                    siatka.v[i][j] = siatka_biale;
                    dodaj_mrowke(j, i, 2);
                    break;
                case 0x25C1: // Unicode dla '◁'
                    siatka.v[i][j] = siatka_biale;
                    dodaj_mrowke(j, i, 3);
                    break;}
            j++;
            if(temp=='\n')
            {
                j=-1;
                i++;
            }
            if(i==kolumny) break; ///zapobieganie mazaniu po pamięci
        }


    }
    return 0;
}

/// Dodaje mrówkę do wektora mrowki
/// Zwraca 0 jeśli się udało,
///        1 jeśli argumenty są nieprawidłowe,
///        2 jeśli jest za dużo mrówek, aby dodać nową lub
///        3 jeśli na danym polu już jest mrówka
int dodaj_mrowke(int x, int y, int kierunek) {
    if (x < 0 || x >= siatka.kolumny || y < 0 || y >= siatka.wiersze || kierunek < 0 || kierunek > 3) return 1;
    if (liczba_mrowek >= arg_mrowki_max) return 2;
    if (siatka.lm[y][x] != 0) return 3;
    mrowki[liczba_mrowek].x = x;
    mrowki[liczba_mrowek].y = y;
    mrowki[liczba_mrowek].kierunek = kierunek;
    siatka.m[y][x][siatka.lm[y][x]++] = liczba_mrowek;
    liczba_mrowek++;
    return 0;
}

/// Pojedynczy ruch Mrówki Langtona
/// Mrówka odwraca kolor pola na którym jest, przesuwa się do przodu i skręca w zależności od koloru pola
void mrowka_ruch(mrowka * m) {
    mrowka_skret(m);
    mrowka_odwroc_pole(m);
    mrowka_do_przodu(m);
}
int ow() {return 0;}
/// Funkcja pomocnicza do mrowka_ruch, przesuwa mrówkę do przodu o 1 pole
/// Jeśli mrówka wyjdzie poza siatkę, to wraca na początek wiersza / kolumny
void mrowka_do_przodu(mrowka * m) {
    /// Usuwamy mrówkę z odpowiedniego pola
    int i = 0,indeks_mrowki;
    while (mrowki[siatka.m[m->y][m->x][i]].kierunek != m->kierunek) {
        if (siatka.lm[m->y][m->x] <= i) {
            ow();
            printf("AUĆ TO BOLI, MRÓWKA W y=%i, x=%i\n", m->y,m->x);
            abort();
        }
        i++;
    }
    indeks_mrowki = siatka.m[m->y][m->x][i];
    siatka.lm[m->y][m->x]--;
    siatka.m[m->y][m->x][i] = siatka.m[m->y][m->x][siatka.lm[m->y][m->x]];    
    /// Do przodu
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
    /// Aktualizujemy pole, na którym jest mrówka
    siatka.m[m->y][m->x][siatka.lm[m->y][m->x]++] = indeks_mrowki;
}
/// Funkcja pomocnicza do mrowki_ruch
/// Przesuwa mrówkę do tyłu o 1 pole
/// UWAGA: działa inaczej niż obrócenie mrówki, ruch do przodu i obrócenie mrówki!
void mrowka_do_tylu(mrowka * m) {
    /// Usuwamy mrówkę z odpowiedniego pola
    int i = 0,indeks_mrowki;
    while (mrowki[siatka.m[m->y][m->x][i]].kierunek != m->kierunek) i++;
    indeks_mrowki = siatka.m[m->y][m->x][i];
    siatka.lm[m->y][m->x]--;
    siatka.m[m->y][m->x][i] = siatka.m[m->y][m->x][siatka.lm[m->y][m->x]];    
    /// Do przodu
    switch (m->kierunek)
    {
        case mrowka_U: m->y++; break;
        case mrowka_R: m->x--; break;
        case mrowka_D: m->y--; break;
        case mrowka_L: m->x++; break;
    }
    if (m->y < 0) m->y = siatka.wiersze-1;
    if (m->y >= siatka.wiersze) m->y = 0;
    if (m->x < 0) m->x = siatka.kolumny-1;
    if (m->x >= siatka.kolumny) m->x = 0;
    /// Aktualizujemy pole, na którym jest mrówka
    siatka.m[m->y][m->x][siatka.lm[m->y][m->x]++] = indeks_mrowki;
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
/// Funkcja pomocnicza do mrowki_ruch, odwraca kierunek, w którym zwrócona jest mrówka
void mrowka_odwroc_kierunek(mrowka * m) {
    m->kierunek += 2;
    if (m->kierunek > 3) m->kierunek -= 4;
}

/// Ruch wszystkich mrówek na siatce jednocześnie
/// Implementacja kolizji jest niedokończona!!
void mrowki_ruch() {
    int i;
    /// kolizje[i] -> (kolumna, wiersz), w którym zderzyły się maksymalnie 4 mrówki
    unsigned int k_kolizje[arg_mrowki_max];
    unsigned int w_kolizje[arg_mrowki_max];
    unsigned int m_kolizje = 0;
    unsigned int n_k_kolizje[arg_mrowki_max];
    unsigned int n_w_kolizje[arg_mrowki_max];
    unsigned int n_m_kolizje = 0;
    for (i = 0;i < liczba_mrowek;i++) {
        /// Wszystkie mrówki idą naprzód
        mrowka_ruch(mrowki+i);
        /// Sprawdzamy czy wystąpiły kolizje
        if (siatka.lm[mrowki[i].y][mrowki[i].x] > 1) {
            k_kolizje[m_kolizje] = mrowki[i].x;
            w_kolizje[m_kolizje] = mrowki[i].y;
            m_kolizje++;
        }
    }
    while (m_kolizje > 0) {
        for (i = 0;i < m_kolizje;i++) {
            if (siatka.lm[w_kolizje[i]][k_kolizje[i]] == 1) continue; /// "Wyminęły się"
            while (siatka.lm[w_kolizje[i]][k_kolizje[i]] != 0) {
                /// Jeśli wystąpią kolizje, cofamy mrówki, które w niej uczestniczą,
                /// a następnie odwracamy ich kierunki
                mrowka * M = mrowki+siatka.m[w_kolizje[i]][k_kolizje[i]][0];
                mrowka_do_tylu(M); /// Cofnięcie się niestety również może doprowadzić do kolizji
                if (siatka.lm[M->y][M->x] > 1) {
                    n_k_kolizje[n_m_kolizje] = M->x;
                    n_w_kolizje[n_m_kolizje] = M->y;
                    n_m_kolizje++;
                }
                mrowka_odwroc_kierunek(M);
                if (siatka.lm[w_kolizje[i]][k_kolizje[i]] < 0) {
                    printf("BOLI!\n");1/0;
                }
            }
        }
        m_kolizje = n_m_kolizje;
        for (i = 0;i < n_m_kolizje;i++) {
            k_kolizje[i] = n_k_kolizje[i];
            w_kolizje[i] = n_w_kolizje[i];
        }
        n_m_kolizje = 0;
    }
}

/// Wypisywanie siatki
void wypisz_siatke(FILE * gdzie) {
    int i,j,k;
    int mrowka_na_polu;
    /// Pierwszy wiersz ramki siatki
    fprintf(gdzie, ramka_u_l);
    for (j = 0;j < siatka.kolumny; j++) fprintf(gdzie, ramka_H);
    fprintf(gdzie, ramka_u_r);
    fprintf(gdzie, "\n");
    /// Wiersze siatki
    for(i = 0; i < siatka.wiersze; i++)
    {
        fprintf(gdzie, ramka_V); /// Ramka pionowa
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
        fprintf(gdzie, ramka_V); /// Ramka pionowa
        fprintf(gdzie,"\n");
    }
    /// Ostatni wiersz ramki siatki
    fprintf(gdzie, ramka_d_l);
    for (j = 0;j < siatka.kolumny; j++) fprintf(gdzie, ramka_H);
    fprintf(gdzie, ramka_d_r);
    fprintf(gdzie, "\n");
}