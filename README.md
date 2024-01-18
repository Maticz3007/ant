## Parametry wywołania:


### Wymagane:


-i <liczba całkowita>: liczba kroków/iteracji wykonywanych przez mrówkę.

### Oraz jedno z:

-m <liczba całkowita> oraz -n <liczba całkowita>: ilość rzędów/kolumn planszy.

-w <ścieżka do pliku>: plik wejściowy z planszą i pozycją mrówki.


### Opcjonalne:


-s <0/1/2/3>: Początkowy stan mrówki *przed rozpoczęciem pierwszego kroku*. 0 - w górę 1 - w prawo 2 - w dół 3 - w lewo, domyślnie 0.

-y <liczba całkowita> oraz -x <liczba całkowita>: Rząd i kolumna określająca położenie startowe mrówki, domyślnie [floor(n/2)+1]-ty rząd/kolumna od lewej/góry.

-o <nazwa>: przedrostek nazwy plików, brak podania spowoduje wyprowadzenie planszy na standardowe wyjście.
