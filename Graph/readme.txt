Temat projektu: Implementacja grafów oparta na liście sąsiedztwa. Wierzchołki są liczbami int od 0
do n-1. Implementacja BFS i DFS.

Typ grafów: grafy skierowane
Język programowania: C++
Nazwa programu: project.cpp

Szczegóły programu

Nazwa klasy: Graph

Metody klasy:
• Graph(int V) – utwórz graf z V wierzchołkami
• ~Graph() – destruktor
• addEdge(int v, int w) – dodaj krawędź od wierzchołka v do wierzchołka w
• getV() – zwróć liczbę wierzchołków
• getE() – zwróć liczbę wszystkich krawędzi
• hasEdge(int v, int w) - sprawdź, czy istnieje połączenie od wierzchołka v do w, jeżeli
istnieje zwróć „1”, w przeciwnym razie „0”
• remEdge(int v, int w) - usuń krawędź od wierzchołka v do w, jeżeli krawędź została
usunięta zwróć „1”, w przeciwnym razie „0”
• clear() – usuń wszystkie połączenia między krawędziami
• isClear() – sprawdź, czy nie ma żadnych połączeń między wierzchołkami, jeżeli tak,
zwróć „1”, w przeciwnym razie „0”
• DFS(int v) – wykonaj DFS na wierzchołku v
• BFS(int s) – wykonaj BFS na wierzchołku s
• printBFS() – wyświetl wierzchołki przez które przechodził BFS w odpowiedniej
kolejności
• printDFS() – wyświetl wierzchołki przez które przechodził DFS w odpowiedniej
kolejności

Opis programu

W moim programie implementuję klasę wraz z poszczególnymi metodami, które umożliwiają
mi operowanie grafem opartym na liście sąsiedztwa. Następnie tworzę dwa oddzielne, niezależne
testy, które służą do sprawdzenia czy zaimplementowany przeze mnie program działa prawidłowo.
Funkcję test() wykonuję w funkcji main().
Piotr Przemielewski