#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, char, double>;
    debug<Last<test>::type> d;

    return EXIT_SUCCESS;
}
