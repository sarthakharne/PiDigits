#ifndef NUMBER
#define NUMBER

#include <bits/stdc++.h>
using namespace std;

class Number {
    public:
        vector<int> digits;
        unsigned int base;
        int exponent;
        bool sign;

        Number(vector<int> &dig, int b, int expo, bool sig = false);
        Number(Number *n);

        // removes zeroes from the Left and adjusts the exponent
        void removeZeroes();

        // add exponent
        Number* addExponent(int e);

        // print to see the number
        void printNumber();
};

#endif // NUMBER