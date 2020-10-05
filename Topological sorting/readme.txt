Piotr Przemielewski
12.05.2020

Omówienie programu:
Korzystając ze wcześniejszych implementacji grafu, stosu oraz sposobów przechodzenia grafu DFS & BFS przygotowałem implementację sortowania topologicznego.

Do stworzenia programu wykorzystałem algorytm przechodzenia grafu DFS, który przekształciłem. Algorytm w obecnej postaci działa w ten sposób, iż dla danego wierzchołka uruchamiane jest rekurencyjne przechodzenie jego sąsiadów, a gdy wszyscy sąsiedzi zostaną „sprawdzeni” wierzchołek jest dodawany na stos. Po zastosowania owego algorytmu dla wszystkich wierzchołków uzyskamy stos, którego kolejno zdejmowane elementy, będą prezentowały posortowany topologicznie zbiór. Uzasadnieniem stojącym za tym, iż dany algorytm działa jest to, iż wierzchołek znajdujący się „najgłębiej”, tzn. do którego można dojść z wielu wierzchołków, będzie znajdował się na końcu / na ostatnich pozycjach posortowanego zbioru. 

Omówienie dodanych metod:

void GraphList::DFS()

W tej metodzie ustawiamy wszystkie wierzchołki na nieodwiedzone i rozpoczynamy rekurencyjne przechodzenie grafu w pętli.

void GraphList::DFSRecursion(int k)

W wewnętrznej metodzie rekurencyjnej sprawdzamy, czy zadany wierzchołek został już wcześniej odwiedzony, jeżeli nie, rozpoczynamy właściwą część algorytmu. Oznaczamy wierzchołek jako odwiedzony i rozpoczynamy rekurencyjne przechodzenie przez wszystkich jego sąsiadów, o ile nie zostali wcześniej odwiedzeni. Po sprawdzeniu wszystkich sąsiadów dodajemy wierzchołek k na stos.

void GraphList::printTopology()

W metodzie wypisujemy na ekran zdjęty ze stosu wierzchołek, a następnie go usuwamy. Procedurę powtarzamy do momentu aż stos zostanie pusty.

