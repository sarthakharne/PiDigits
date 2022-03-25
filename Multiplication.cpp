#ifndef MULTIPLICATION
#define MULTIPLICATION

#include <bits/stdc++.h>
#include "Number.hpp"
#include "Addition.cpp"
#include "Subtraction.cpp"
using namespace std;

pair<Number*, Number*> splitAt(Number *n, int ind) {
    Number* lowSplit;
    Number* highSplit;
    if(n->digits.size() - 1 <= ind) {
        vector<int> dig(1, 0);

        // TODO: free these objects
        lowSplit = new Number(n);
        highSplit = new Number(dig, n->base, 0);
    }
    else {
        vector<int> digLow;
        vector<int> digHigh;
        for(int i = 0;i < n->digits.size();i++) {
            if(i <= ind)
                digLow.push_back(n->digits[i]);
            else
                digHigh.push_back(n->digits[i]);
        }

        // TODO: free these objects
        lowSplit = new Number(digLow, n->base, 0);
        lowSplit->removeZeroes();
        highSplit = new Number(digHigh, n->base, 0);
        highSplit->removeZeroes();
    }

    return make_pair(lowSplit, highSplit);
}

Number* Karatsuba(Number* n1, Number* n2) {
    // size of the digit taken into consideration
    int size1 = n1->digits.size();
    int size2 = n2->digits.size();

    // base case, when only 1 digit is received    
    if(size1 == 1 || size2 == 1) {
        vector<int> c(size1 + size2, 0);

        // int bigSize = max(n1->digits.size(), n2->digits.size());

        for(int i = 0;i < size1;i++) {
            int carry = 0;

            for(int j = 0;j < size2;j++) {
                int temp = n1->digits[i]*n2->digits[j] + c[i + j] + carry;
                carry = temp/n1->base;
                c[i + j] = temp%n1->base;
            }
        }

        int base = n1->base;
        int exp = 0;    // will be normalised afterwards

        // TODO: free res
        Number* res = new Number(c, base, exp);
        res->removeZeroes();    // exponent set

        return res;
    }

    /*
        low1 * * * * * * * * * * | * * * * * * * * * * * high1
        low2 * * * * * * * * * * | * * * * *  high2
        
        low1 * * * * * * * * * highspl1 | lowspl1 * * * * * * * * * * high1
        low2 * * * * * * * * * highspl2 | lowspl2 * * * *  high2
    */

    // find the greater size and split both numbers accordingly
    int greaterSiz = max(size1, size2);
    int greaterSizBy2 = greaterSiz/2;

    pair<Number*, Number*> n1Split = splitAt(n1, greaterSizBy2);
    pair<Number*, Number*> n2Split = splitAt(n2, greaterSizBy2);
    
    // TODO: free memory for these objects
    Number *lowSpl1 = new Number(n1Split.first);
    Number *highSpl1 = new Number(n1Split.second);
    Number *lowSpl2 = new Number(n2Split.first);
    Number *highSpl2 = new Number(n2Split.second);

    // free memory
    free(n1Split.first);
    free(n1Split.second);
    free(n2Split.first);
    free(n2Split.second);
    
    // TODO: free memory for these objects
    Number* higherMult = Karatsuba(highSpl1, highSpl2);
    Number* lowerMult = Karatsuba(lowSpl1, lowSpl2);
    Number* highMultPlusLowerMult = Sub(Sub(Karatsuba(Add(lowSpl1, highSpl1), Add(lowSpl2, highSpl2)), higherMult), lowerMult);
    // TODO: free memory for prod
    Number* Prod = new Number(Add(Add(higherMult->addExponent(greaterSiz), highMultPlusLowerMult->addExponent(greaterSizBy2)), lowerMult));

    // free unrequired objects
    free(lowSpl1);
    free(highSpl1);
    free(lowSpl2);
    free(highSpl2);
    free(higherMult);
    free(lowerMult);
    free(highMultPlusLowerMult);

    return Prod;
}

Number* Multiply(Number* n1, Number* n2) {
    Number* Res = new Number(Karatsuba(n1, n2));
    Res->sign = n1->sign | n2->sign;
    Res->removeZeroes();

    return Res;
}

#endif // MULTIPLICATION