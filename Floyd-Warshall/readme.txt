Piotr Przemielewski
23.05.2020



Opis programu:
Korzystając ze wcześniejszej implementacji grafu opartej o listy sąsiedztwa dokonuję zmian w metodzie:
void GraphList::addEdge(int v, int w, int m)

tak aby wraz z kierunkiem krawędzi podawana była jego waga, która następnie zostaje wpisana do tablicy utworzonej w konstruktorze grafu, gdzie domyślnie wszystkie wartości, prócz przekątnej (distance[i][i] == 0), mają wartość INT_MAX. Tak więcej na pozycji distance[v][w] zostaje umieszczona waga m.
Całość działania algorytmu odbywa się w metodzie:

void GraphList::Floyd()

Początkowo zostaje stworzona dwuwymiarowa tablica intermediary[][], która w przyszłości będzie mogła posłużyć nam do odczytania trasy dzielącej każdą parę wierzchołków. Inicjalizujemy ją wartością -1. 
Właściwą część algorytmu stanowi potrójna pętla w której sprawdzamy odległości znajdujące się w tablicy distance[][].

for(int i = 0; i < V; i++)
    for(int v = 0; v < V; v++)
        for(int w = 0; w < V; w++)
 
Aby sprawdzanie wierzchołków miało jakikolwiek sens początkowo zostaje sprawdzony warunek czy odległości, które będziemy porównywać, nie wynoszą INT_MAX.

if(distance[v][i] != INT_MAX && distance[i][w] != INT_MAX)

Porównanie odległości działa na zasadzie szukania pośrednich wierzchołków dzielących pewne dwa wierzchołki v oraz w i sprawdzaniu, czy przejście przez dany wierzchołek pośredni nie sprawi, że trasę od v do w będzie można „przebyć prędzej”. W przypadku gdy dany warunek jest prawdziwi odległości w tablicy dinstance[][] zostają zmienione, a wierzchołek pośredni zapisujemy do tablicy intermediary[][] na pozycji [v][w].

Końcową część algorytmu stanowi wypisane odległości dzielących wszystkie pary wierzchołków. W celu odczytania danej odległości należy przyjąć, iż wierzchołek w kolumnie najbardziej na prawo jest wierzchołkiem źródłowym, a poszczególne wierzchołki w wierszu na samej górze stanowią punkt docelowy. Na potrzebę estetyki wartości INT_MAX zostały zastąpione napisanem „INF”, mówiącym nam, iż dane połączenie pomiędzy wierzchołkami nie istnieje. 


 
