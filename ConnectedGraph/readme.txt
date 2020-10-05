Piotr Przemielewski

26.04.2020

Opis programu:

W programie wykorzystałem wcześniejsze implementacje dla grafów skierowanych i nieskierowanych
posługując się macierzą sąsiedztwa i listą sąsiedztwa.

W tym przypadku posłużyłem się implementacjami na liście sąsiedztwa.

void GraphListNON::DFSRecursion(int v, bool visited[])
void GraphList::DFSRecursion(int v, bool visited[])

Posiadając już implementacje przechodzenia grafów DFS i BFS w miejscu dodania na kopiec zaczynam
odwoływać się do funkcji wewnętrznej, która będzie rekurencyjnie przechodziła do kolejnych
wierzchołków. Wierzchołki przez które przechodzę dodaję do listy „getDFS”.
Jako argumenty przekazujemy obecnie odwiedzany wierzchołek i tablicę bool’owską, która służy nam
do oznaczania odwiedzonych wierzchołków. Następnie w pętli sprawdzamy czy wierzchołki, do
których prowadzą krawędzie wychodzące z obecnie sprawdzanego wierzchołka zostały już
odwiedzone, jeżeli nie, ponawiamy rekurencje.

bool GraphList::isConnected()
bool GraphListNON::isConnected()

Jeżeli graf jest spójny oznacza to, że z każdego wierzchołka jesteśmy w stanie „dostać się” do każdego
innego wierzchołka. W takim wypadku wykorzystujemy fakt, że w takim wypadku nasza lista
odwiedzonych wierzchołków powinna być długości liczby wszystkich wierzchołków, wówczas graf
będzie spójny. W pętli dla każdego wierzchołka uruchamiamy algorytm przechodzenia grafu DFS i
jeżeli zdarzy się przypadek, iż któraś lista odwiedzonych wierzchołków będzie inna niż liczba
wierzchołków, zwracamy false, w przeciwnym razie graf jest spójny i zwracamy true.