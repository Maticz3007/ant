#ifndef MROWKA_H_IS_INCLUDED
#define MROWKA_H_IS_INCLUDED

#include <stdio.h>
#include <wchar.h>

/// Maksymalna liczba wierszy siatki
#define max_wiersze 500
/// Maksymalna liczba kolumn siatki
#define max_kolumny 500
/// Maksymalna liczba mrówek
#define max_mrowki 100 

/// Białe pole siatki
#define siatka_biale 0
#define wypisz_siatka_biale " "
/// Czarne pole siatki
#define siatka_czarne 1
#define wypisz_siatka_czarne "█"

/// Ramka siatki
#define ramka_V "│"
#define ramka_H "─"
#define ramka_d_l "└"
#define ramka_d_r "┘"
#define ramka_u_l "┌"
#define ramka_u_r "┐"

/// Kierunki mrówki
#define mrowka_U 0 /// U - up (góra)
#define wypisz_biale_mrowka_U "△"
#define wypisz_czarne_mrowka_U "▲"
#define mrowka_R 1 /// R - right (prawo)
#define wypisz_biale_mrowka_R "▷"
#define wypisz_czarne_mrowka_R "▶"
#define mrowka_D 2 /// D - down (dół)
#define wypisz_biale_mrowka_D "▽"
#define wypisz_czarne_mrowka_D "▼"
#define mrowka_L 3 /// L - left (lewo)
#define wypisz_biale_mrowka_L "◁"
#define wypisz_czarne_mrowka_L "◀"

/// Siatka, po której poruszają się wszystkie Mrówki Langtona
struct siatka_t {
    /// Tablica dwuwymiarowa kolorów pól siatki
    /// Indeksowana od 0, v[wiersz][kolumna] - kolor pola w wierszu wiersz i kolumnie kolumna
    unsigned int v[max_wiersze][max_kolumny]; 
    unsigned int wiersze; /// Liczba wierszy siatki
    unsigned int kolumny; /// Liczba kolumn siatki
};
extern struct siatka_t siatka;

/// Pojedyncza Mrówka Langtona
typedef struct {
    int x; /// Kolumna, w której jest mrówka licząc od 0
    int y; /// Wiersz, w którym jest mrówka licząc od 0
    int kierunek; /// Kierunek mrówki - góra, prawo, dół, lewo
} mrowka;

/// Wektor wszystkich Mrówek Langtona
extern mrowka mrowki[max_mrowki];
/// Liczba mrowek
extern unsigned int liczba_mrowek;

/// Zainicjuj siatkę białymi polami
/// Zwraca 1, jeśli podana liczba wierszy lub kolumn jest nieprawidłowa lub 0 w przeciwnym wypadku
int inicjacja_siatki(int wiersze, int kolumny, double rand_perc, char * arg_input);

/// Dodaje mrówkę do wektora mrowki
/// Zwraca 0 jeśli się udało, 1 jeśli argumenty są nieprawidłowe lub 2 jeśli jest za dużo mrówek, aby dodać nową
int dodaj_mrowke(int x, int y, int kierunek);

/// Pojedynczy ruch Mrówki Langtona
/// Mrówka odwraca kolor pola na którym jest, przesuwa się do przodu i skręca w zależności od koloru pola
void mrowka_ruch(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, przesuwa mrówkę do przodu o 1 pole
/// Jeśli mrówka wyjdzie poza siatkę, to wraca na początek wiersza / kolumny
void mrowka_do_przodu(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, odwraca kolor pola na którym jest mrówka
void mrowka_odwroc_pole(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, skręca mrówkę w zależności od koloru pola
void mrowka_skret(mrowka * m);

/// Wypisywanie siatki i mrówek
void wypisz_siatke(FILE * gdzie);

#endif //MROWKA_H_IS_INCLUDED