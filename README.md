## Parametry wywołania (Wszystkie są opcjonalne):




-i (liczba całkowita): liczba kroków/iteracji wykonywanych przez mrówkę. Zakres: <1, 50000>, domyślnie 10.

-m (liczba całkowita) oraz -n (liczba całkowita): liczba wierszy/kolumn planszy. Zakres: <2, 100>, domyślnie 10.

-name (wyraz): Przedrostek plików wynikowych. Jeśli przedrostek nie zostanie podany, domyślnie program będzie wypisywał na standardowe wyjście.

-input (ścieżka do pliku): plik wejściowy z planszą i pozycją mrówki(lub mrówek), który powinien być w formacie prawidłowej planszy. Domyślnie program nie wczytuje z pliku.

-z <0/1/2/3>: Początkowy stan pierwszej mrówki *przed rozpoczęciem pierwszego kroku*. 0 - w górę 1 - w prawo 2 - w dół 3 - w lewo, domyślnie 0.

-y (liczba całkowita) oraz -x (liczba całkowita): Rząd i kolumna określająca położenie startowe mrówki, domyślnie [floor(n/2)+1]-ty rząd/kolumna od lewej/góry. <TO_DO: coś się psuje i próbuje dawać mrówkę poza planszę 3x3 bez -x -y>

-g (liczba całkowita): Procent zapełnienia początkowej planszy czarnymi polami. Zakres: <0, 100>, domyślnie 0.

-mrowki (liczba rzeczywista): Liczba mrówek Langtona na planszy. Jeśli liczba ta jest większa niż 1, współrzędne początkowe i kierunki pozostałych mrówek będą wylosowane. Zakres: <0, 100>, domyślnie 1.

-h lub -help: Pomoc i wywołanie programu.

Jeśli obecny jest plik wejściowy, argumenty -g, -x, -y, -z, -m, -n oraz -mrowki są ignorowane.
