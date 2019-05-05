#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, char, double>;
    /* debug<Init<test>::type> d; */
    
    cout << "<int, char, double> empty? " << IsEmpty<test>::ans << endl;
    cout << "<> empty? " << IsEmpty<buildTList<>>::ans << endl;

    return EXIT_SUCCESS;
}
