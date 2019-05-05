#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, char, double>;
    using test2 = buildTList<double, char, float>;
    debug<Find<test, float>::type> d;
    
    cout << "int in <int, char, double>? " << Elem<test, int>::value << endl;
    cout << "int in <double, char, float>? " << Elem<test2, int>::value << endl;

    return EXIT_SUCCESS;
}
