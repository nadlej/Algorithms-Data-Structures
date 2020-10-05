#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template< typename T > void bubblesort( T a[], int n )
{
    for( int i=0; i<n-1 ;i++)
        for(auto j= 0; j < n-1-i; j++ )
            if( a[j] > a[j+1] )
            {
                int temp = a[j+1] ;
                a[j+1] = a[j] ;
                a[j] = temp ;
            }
}

int main() {

    int v[10]={10,9,8,7,6,5,4,3,2,1};
    for(int i : v) std::cout << i << ' ' ;
    std::cout << '\n' ;
    bubblesort(v,10);
    for(int i : v) std::cout << i << ' ' ;
    std::cout << '\n' ;

}