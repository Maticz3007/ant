#ifndef MROWKA_H_IS_INCLUDED
#define MROWKA_H_IS_INCLUDED

#include <stdio.h>
#include <wchar.h>

/// Ograniczenia programu i biblioteki, domyślne wartości argumentów programu
#define arg_m_default 10
#define arg_m_min 2
#define arg_m_max 100 /// Maksymalna liczba wierszy siatki

#define arg_n_default 10
#define arg_n_min 2
#define arg_n_max 100 /// Maksymalna liczba kolumn siatki

#define arg_i_default 10
#define arg_i_min 0
#define arg_i_max 50000 /// Maksymalna liczba iteracji

#define arg_name_max_len 30

#define arg_g_default 0
#define arg_g_min 0
#define arg_g_max 100

#define arg_z_default 0
#define arg_z_min 0
#define arg_z_max 3

#define arg_mrowki_default 1
#define arg_mrowki_min 0
#define arg_mrowki_max 100 /// Maksymalna liczba mrówek

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
    unsigned int v[arg_m_max][arg_n_max];
    /// Tablica dwuwymiarowa przechowująca pozycje mrówek
    /// Na każdym polu może być co najwyżej 1 mrówka, ale w przypadku kolizji mogą przez chwilę być nawet 4
    /// m[wiersz][kolumna][i] - indeks mrówki w wektorze mrowki znajdującej się na polu siatki w wierszu wiersz, kolumnie kolumna,
    /// gdzie 0 <= i <= lm[wiersz][kolumna]
    unsigned int m[arg_m_max][arg_n_max][4];
    unsigned int lm[arg_m_max][arg_n_max];
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
extern mrowka mrowki[arg_mrowki_max];
/// Liczba mrowek
extern unsigned int liczba_mrowek;

/// Zainicjuj siatkę białymi polami
/// Zwraca 1, jeśli podana liczba wierszy lub kolumn jest nieprawidłowa lub 0 w przeciwnym wypadku
int inicjacja_siatki(int wiersze, int kolumny, int rand_perc, char * arg_input);

/// Dodaje mrówkę do wektora mrowki
/// Zwraca 0 jeśli się udało, 1 jeśli argumenty są nieprawidłowe lub 2 jeśli jest za dużo mrówek, aby dodać nową
int dodaj_mrowke(int x, int y, int kierunek);

/// Pojedynczy ruch Mrówki Langtona
/// Mrówka odwraca kolor pola na którym jest, przesuwa się do przodu i skręca w zależności od koloru pola
void mrowka_ruch(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, przesuwa mrówkę do przodu o 1 pole
/// Jeśli mrówka wyjdzie poza siatkę, to wraca na początek wiersza / kolumny
void mrowka_do_przodu(mrowka * m);
/// Funkcja pomocnicza do mrowki_ruch
/// Przesuwa mrówkę do tyłu o 1 pole
/// UWAGA: działa inaczej niż obrócenie mrówki, ruch do przodu i obrócenie mrówki!
void mrowka_do_tylu(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, odwraca kolor pola na którym jest mrówka
void mrowka_odwroc_pole(mrowka * m);
/// Funkcja pomocnicza do mrowka_ruch, skręca mrówkę w zależności od koloru pola
void mrowka_skret(mrowka * m);
/// Funkcja pomocnicza do mrowki_ruch, odwraca kierunek, w którym zwrócona jest mrówka
void mrowka_odwroc_kierunek(mrowka * m);

/// Ruch wszystkich mrówek na siatce jednocześnie
void mrowki_ruch();

/// Wypisywanie siatki i mrówek
void wypisz_siatke(FILE * gdzie);

#endif //MROWKA_H_IS_INCLUDED