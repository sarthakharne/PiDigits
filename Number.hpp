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
        void removeZeroes(bool maintain_exp=false, int exp=INT_MAX);

        // add exponent
        Number* addExponent(int e);

        // print to see the number
        void printNumber();

        // reverse digits
        void rev();

        // compare a number with current number
        static int compare(Number* n1, Number* n2, bool considerSign = false);

        // two
        static Number* retTwo(int b, int expo = 0, bool sig = false);

        // pad numbers to normalise exponents
        // diffexp - (n1 - 1) + (n2 - 1)
};

#endif // NUMBER