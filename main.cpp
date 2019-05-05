#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, int>;
    debug<test> d;

    return EXIT_SUCCESS;
}
