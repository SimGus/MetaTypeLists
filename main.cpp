#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    using test = buildTList<int, int>;
    debug<Tail<test>::value> d;

    return EXIT_SUCCESS;
}
