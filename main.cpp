#include <iostream>

#include "lib.h"

using namespace std;

int main()
{
    buildTList<int, int> test;
    test.head = 1;
    test.tail.head = 0;

    cout << "Head: " << test.head
         << "\nTail: " << test.tail.head << endl;

    printHead(test);

    return EXIT_SUCCESS;
}
