Piotr Przemielewski
02.06.2020



Opis programu:

Program w stanie przed dodaniem metody implementującej algorytm Prima zawierał implementację grafu nieskierowanego opartego o listy sąsiedztwa, gdzie wagi poszczególnych krawędzi przechowywane są w dwuwymiarowej tablicy.

GraphListNON Prim();

Tym, co będzie wartością zwracaną przez metodę Prim() będzie nowe drzewo, minimalne drzewo rozpinające. 
Implementacja rozpoczyna się od zdefiniowania pary <int, list<int>>, która później będzie nam potrzebna przy dołączaniu elementów do kolejki priorytetowej.
typedef std::pair<int,std::list<int>> pi;

Tworzymy również wektor, który będzie przechowywał listy zawierające elementy typu int.
std::vector<std::list<int>> T;

Przystępujemy do zdefiniowana kolejki priorytetowej:
std::priority_queue<pi, std::vector<pi>, std::greater<pi> > pq;

Zapis ten oznacza, iż chcemy stworzyć kolejkę priorytetową, która będzie przechowywała pary
<int, list<int>, a jego priorytet będzie wyznaczany względem pierwszego argumentu, czyli w tym przypadku wagi. Lista, która będzie dołączana do poszczególnych wag, będzie zawierała wierzchołki, pomiędzy którymi dana waga występuje.
Definiujemy i inicjalizujemy tablice visited[ ], która przysłuży nam się przy sprawdzaniu czy dany wierzchołek został już dodany do nowo stworzonego grafu.
Następnie rozpoczyna się właściwe działanie algorytmu w pętli.
Przyjmujemy, że wierzchołek, od którego będziemy rozpoczynać budowanie naszego drzewa, posiada indeks 0 (jednocześnie może to być każdy inny wierzchołek, byleby należał do grafu). Tworzymy listę, do której przypisujemy wszystkie wierzchołki z którymi połączony jest dany wierzchołek 0. Następnie sprawdzamy czy sąsiedzi sprawdzanego przez nas wierzchołka nie zostali już odwiedzeni, jeżeli nie, to wagę oraz listę zawierającą źródłowy wierzchołek i wierzchołek docelowy, dodajemy do kolejki priorytetowej. 
Po sprawdzaniu połączeń rozpoczynamy sprawdzanie elementów w kolejce priorytetowej. W pętli pobieramy połączenie z najmniejszą wagą, zapisujemy odpowiadające temu połączeniu wierzchołki, usuwamy z kolejki i sygnalizujemy, że pętla ma się odbywać do momentu aż obecny wierzchołek docelowy był odwiedzony. Inaczej mówiąc, jeżeli okaże się, że wierzchołek docelowy nie został jeszcze odwiedzony, pobieranie elementów z kolejki ma się zakończyć.
Następnie tworzymy listę, dodajemy do niej układ elementów:
Wierzchołek źródłowy – wierzchołek docelowy – waga 
I dodajmy tak stworzą listę do wektora list, który stworzyliśmy na początku metody. 
Wierzchołek docelowy, który przerwał działanie pętli pobierania elementów z kolejki, zostaje oznaczony jako odwiedzony i od niego rozpocznie się ponownie działanie całej pętli. Działanie pętli odbędzie się tyle razy, ile jest wierzchołków.
Następne działania polegają na stworzeniu nowego grafu, zainicjalizowaniu jego połączeń posługując się wektorem list i zwróceniu tak utworzonego grafu.



  





