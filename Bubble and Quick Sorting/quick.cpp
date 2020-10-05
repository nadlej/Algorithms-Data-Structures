#include <iostream>
#include <algorithm>
#include <vector>

template< typename T > void quick(T  tab[], int left, int right)
{
    if(right <= left) return;

    int i = left - 1, j = right + 1,
            pivot = tab[(left+right)/2];

    while(1)
    {
        while(pivot>tab[++i]);
        while(pivot<tab[--j]);
        if( i <= j){
            int temp = tab[i] ;
            tab[i] = tab[j] ;
            tab[j] = temp ;
        }
        else
            break;
    }

    if(j > left)
        quick(tab, left, j);
    if(i < right)
        quick(tab, i, right);
}

int main() {

    int v[10]={10,9,8,7,6,5,4,3,2,1};
    for(int i : v) std::cout << i << ' ' ;
    std::cout << '\n' ;
    quick(v,0,10);
    for(int i : v) std::cout << i << ' ' ;
    std::cout << '\n' ;
}
