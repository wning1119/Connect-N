// main.cpp


#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

void dochoosemoveTests()
{
    BadPlayer bp("Homer");
    HumanPlayer hp("Marge");
    Game g(4, 3, 3, &bp, &hp);
    g.play();
}

int main()
{
    dochoosemoveTests();
    cout << "Passed all tests" << endl;
}