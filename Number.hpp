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

        Number(vector<int> &dig, int b, int expo, bool sig = 0);
};

#endif // NUMBER