#include <bits/stdc++.h>
#include "GeneratePi.cpp"
#include "SquareRoot.cpp"
using namespace std;

int main() {
    int choice;
    int numDig;
    int m;
    int pow2 = 1;

    cin >> choice >> numDig >> m;

    // make the base
    for(int i = 0;i < m;i++)
        pow2 *= 2;

    if(choice == 1) {
        Number* Pi = GeneratePi(10, numDig);
        Pi->printNumber(numDig);
        // GeneratePi(pow2, numDig);
    }
    else if(choice == 2) {
        Number* sqrt2 = SquareRoot(Number::retTwo(10), numDig);
        sqrt2->printNumber(numDig);
        // Number* sqrt2 = SquareRoot(Number::retTwo(pow2), numDig);
    }
}