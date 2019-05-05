#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, char, double>;
    using test2 = buildTList<double, char, float>;
    /* debug<BeforeIndex<1, test>::type> d; */
    
    cout << "int in <int, char, double>: " << ElemIndex<test, int>::value << endl;
    cout << "int in <double, char, float>: " << ElemIndex<test2, int>::value << endl;

    test l = createList(1, 'a', 0.35);

    return EXIT_SUCCESS;
}
