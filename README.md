## Parametry wywołania (Wszystkie są opcjonalne):




-i (liczba całkowita): liczba kroków/iteracji wykonywanych przez mrówkę. Zakres: <1, 50000>, domyślnie 10.

-m (liczba całkowita) oraz -n (liczba całkowita): liczba wierszy/kolumn planszy. Zakres: <2, 100>, domyślnie 10.

-name (wyraz): Przedrostek plików wynikowych. Jeśli przedrostek nie zostanie podany, domyślnie program będzie wypisywał na standardowe wyjście.

-input (ścieżka do pliku): plik wejściowy z planszą i pozycją mrówki(lub mrówek), który powinien być w formacie prawidłowej planszy. Domyślnie program nie wczytuje z pliku.

-z <0/1/2/3>: Początkowy stan mrówki *przed rozpoczęciem pierwszego kroku*. 0 - w górę 1 - w prawo 2 - w dół 3 - w lewo, domyślnie 0.

-y (liczba całkowita) oraz -x (liczba całkowita): Rząd i kolumna określająca położenie startowe mrówki, domyślnie floor(n/2)ty rząd/kolumna od lewej/góry.

-g (liczba całkowita): Procent zapełnienia początkowej planszy czarnymi polami. Zakres: <0, 100>, domyślnie 0.

-h lub -help: Pomoc i wywołanie programu.

Jeśli obecny jest plik wejściowy, argumenty -g, -x, -y, -z, -m, -n są ignorowane.
