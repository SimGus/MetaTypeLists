#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, char, double>;
    using test2 = buildTList<double, char, float>;
    debug<Reverse<test>::type> d;
    
    cout << "<int, char, double> length? " << Length<test>::value << endl;
    cout << "<> empty? " << Length<buildTList<>>::value << endl;

    return EXIT_SUCCESS;
}
