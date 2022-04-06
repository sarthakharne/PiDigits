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
    if(n->digits.size() - 1 < ind) {
        // dig = {0}
        vector<int> dig(1, 0);

        lowSplit = new Number(n);
        lowSplit->removeZeroes();
        highSplit = new Number(dig, n->base, 0);
        highSplit->removeZeroes();
    }
    else {
        vector<int> digLow;
        vector<int> digHigh;
        for(int i = 0;i < n->digits.size();i++) {
            if(i < ind)
                digLow.push_back(n->digits[i]);
            else
                digHigh.push_back(n->digits[i]);
        }

        lowSplit = new Number(digLow, n->base, 0);
        lowSplit->removeZeroes();
        highSplit = new Number(digHigh, n->base, 0);
        highSplit->removeZeroes();
    }

    return make_pair(lowSplit, highSplit);
}

Number* NormalMult(Number* n1, Number* n2) {
    // size of the digit taken into consideration
    int size1 = n1->digits.size();
    int size2 = n2->digits.size();
    vector<int> c(size1 + size2, 0);

    for(int i = 0;i < size1;i++) {
        int carry = 0;

        for(int j = 0;j < size2;j++) {
            int temp = n1->digits[i]*n2->digits[j] + c[i + j] + carry;
            carry = temp/n1->base;
            c[i + j] = temp%n1->base;
            if(j == size2 - 1) {
                c[i + j + 1] = carry;
            }
        }
    }

    int base = n1->base;
    int exp = 0;    // will be normalised afterwards

    Number* res = new Number(c, base, exp);
    res->removeZeroes();

    // adjusting exponents
    // digits after decimal for the result
    // with exponent = n1.exp + n2.exp
    int res_exp = n1->exponent + n2->exponent;
    // if there are digits before decimal then we need to adjust exponent
    // we know that there are (n1.size - 1) + (n2.size - 1) digits
    // after the decimal, so digits before dec = res.size - ((n1.size - 1) + (n2.size - 1))
    int digitsBeforeDecimal = res->digits.size() - (n1->digits.size() - 1) - (n2->digits.size() - 1);
    // we need to discard all digits other than 1
    int extraDig = digitsBeforeDecimal - 1;
    // we need to add this to the exponent to get scientific val
    res_exp += extraDig;
    res->exponent = res_exp;
    
    res->sign = n1->sign ^ n2->sign;

    return res;
}

Number* Karatsuba(Number* n1, Number* n2) {
    // size of the digit taken into consideration
    int size1 = n1->digits.size();
    int size2 = n2->digits.size();

    // base case, when only 1 digit is received
    if(size1 == 1 || size2 == 1) {
        return NormalMult(n1, n2);
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

    Number *lowSpl1 = new Number(n1Split.first);
    Number *highSpl1 = new Number(n1Split.second);
    Number *lowSpl2 = new Number(n2Split.first);
    Number *highSpl2 = new Number(n2Split.second);
    lowSpl1->removeZeroes();
    highSpl1->removeZeroes();
    lowSpl2->removeZeroes();
    highSpl2->removeZeroes();

    // free memory
    free(n1Split.first);
    free(n1Split.second);
    free(n2Split.first);
    free(n2Split.second);

    // each operation of Karatsuba written separately
    Number* higherMult = Karatsuba(highSpl1, highSpl2);
    Number* lowerMult = Karatsuba(lowSpl1, lowSpl2);
    Number* Sum1 = Add(lowSpl1, highSpl1);
    Number* Sum2 = Add(lowSpl2, highSpl2);
    Number* Prod1 = Karatsuba(Sum1, Sum2);
    Number* Diff1 = Sub(Prod1, higherMult);
    Number* Diff2 = Sub(Diff1, lowerMult);
    Number* highMultPlusLowerMult = Diff2;

    higherMult->addExponent(2*greaterSizBy2);
    highMultPlusLowerMult->addExponent(greaterSizBy2);
    Number* Sum3 = Add(higherMult, highMultPlusLowerMult);
    Number* Sum4 = Add(Sum3, lowerMult);
    Number* FinalProd = new Number(Sum4);
    FinalProd->removeZeroes();
    FinalProd->sign = n1->sign ^ n2->sign;

    // free objects which aren't required
    free(lowSpl1);
    free(highSpl1);
    free(lowSpl2);
    free(highSpl2);
    free(higherMult);
    free(lowerMult);
    free(Sum1);
    free(Sum2);
    free(Prod1);
    free(Diff1);
    free(Diff2);
    free(Sum3);
    free(Sum4);

    return FinalProd;
}

Number* Multiply(Number* n1, Number* n2) {
    Number* Res = new Number(Karatsuba(n1, n2));
    Res->sign = n1->sign ^ n2->sign;
    Res->removeZeroes();

    // adjusting exponents
    // digits after decimal for the result
    // with exponent = n1.exp + n2.exp
    int res_exp = n1->exponent + n2->exponent;
    // if there are digits before decimal then we need to adjust exponent
    // we know that there are (n1.size - 1) + (n2.size - 1) digits
    // after the decimal, so digits before dec = res.size - ((n1.size - 1) + (n2.size - 1))
    int digitsBeforeDecimal = Res->digits.size() - (n1->digits.size() - 1) - (n2->digits.size() - 1);
    // we need to discard all digits other than 1
    int extraDig = digitsBeforeDecimal - 1;
    // we need to add this to the exponent to get scientific val
    res_exp += extraDig;
    Res->exponent = res_exp;

    return Res;
}

// int main() {
//     // TODO: Correct the code for this input
//     vector<int> a = {0,5};
//     vector<int> b = {2};
//     Number* A = new Number(a, 10, 1, 0);
//     Number* B = new Number(b, 10, -10, 0);
//     Number* ans = Multiply(A, B);
//     // Number* ans = NormalMult(A, B);

//     cout << "\nAnswer: \n";
//     ans->printNumber();
// }

#endif // MULTIPLICATION