Piotr Przemielewski
23.05.2020



Opis programu:

Na potrzeby zadany została zmieniona metoda:

void GraphList::addEdge(int v, int w, int m)

gdzie m oznacza tu wagę, która dzieli wierzchołek v od wierzchołka w. Wagi przechowywane są w dwuwymiarowej tablicy. W przypadku gdy połączenie między wierzchołkami nie istnieje ich odległość jest określona jako INT_MAX.
Do wcześniejszej implementacji grafu skierowanego utworzonego na listach sąsiedztwa została dodana metoda:

void GraphList::Dijkstra(int s)

która wypisuje na ekran najkrótsze trasy pomiędzy danym wierzchołkiem s, a wszystkimi pozostałymi wierzchołkami. W przypadku gdy trasa umożlwiająca dotarcie do jakiegoś wierzchołka nie istnieje zwracana jest wartość INT_MAX (zakładamy, że żadna krawędź nie posiada na tyle wysokich wag).
W zadaniu została użyta gotowa implementacja kolejki priorytetowej zwracającej priorytety rosnąco, czyli gdy użyjemy na niej metody top(), uzyskamy najmniejszy priorytet znajdujący się w kolejce. W celu szybkiego wyszukiwania wierzchołków przyporządkowanych danym priorytetem w programie tworzona jest mapa, której identyfikatorami są priorytety, a elementami wierzchołki.
Po utworzeniu pomocniczych tablic:
- known[] – mówiąca nam o tym czy dany wierzchołek został już przez nas odwiedzony
- distance[] – mówiąca nam o tym jaka odległość dzieli nas od poszczególnych wierzchołków
- predecessor[] – wskazująca nam na poprzednio odwiedzony wierzchołek przed obecnie sprawdzanym. Po wyznaczeniu całej tablicy -1 w tablicy informuje nas, iż jesteśmy w wierzchołku źródłowym. Ułatwia nam to późniejszą weryfikację trasy.
Po wstępnym zainicjalizowaniu tych tablic oznaczamy, iż dystans dzielący nas od wierzchołka źródłowego wynosi 0, dodajemy priorytet 0 do naszej kolejki priorytetowej oraz kluczowi 0 przyporządkowujemy wierzchołek źródłowy.
Następnie rozpoczyna się praca w pętli, która trwa do momentu aż kolejka nie zostanie pusta. 

Działanie pętli:
W pętli pobieramy z kolejki najniższy priorytet i sprawdzamy odpowiadający mu wierzchołek. Priorytet usuwamy z kolejki. Następnie sprawdzamy czy dany wierzchołek został już odwiedzony, jeżeli nie, działanie pętli jest kontynuowane. Oznaczamy wierzchołek jako odwiedzony i rozpoczynamy sprawdzanie sąsiadów wychodzących od pobranego wierzchołka. W przypadku gdy okaże się, iż zsumowana odległość pobranego wierzchołka od źródła i odległość pobranego wierzchołka od sprawdzanego obecnie jego sąsiada jest mniejsza niż obecnie przypisana odległość źródła od tego sąsiada, to dystans jest zamieniany.

distance[w] = d;
predecessor[w] = v;
que.push(d);
mapa.insert(std::pair<int,int>(d,w));

Przypisujemy w tablicy predecessor[] sąsiadowi wierzchołek, od którego została poprowadzona krawędź, a priorytet, czyli nową odległość od źródła, dodajemy do kolejki, a parę nowa odległość –  identyfikator sąsiada, dodajemy do mapy.
Po ukończeniu algorytmu na ekran wypisywane są poszczególne odległości źródła od wierzchołków wraz z wierzchołkami przez które algorytm przechodzi, by dany dystans osiągnąć.

 
