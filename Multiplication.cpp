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

    // int bigSize = max(n1->digits.size(), n2->digits.size());

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
    // lowSpl1->printNumber();
    // highSpl1->printNumber();
    // lowSpl2->printNumber();
    // highSpl2->printNumber();

    // free memory
    free(n1Split.first);
    free(n1Split.second);
    free(n2Split.first);
    free(n2Split.second);

    Number* higherMult = Karatsuba(highSpl1, highSpl2);
    // cout << "highSpl1: ";
    // highSpl1->printNumber();
    // cout << "highSpl2: ";
    // highSpl2->printNumber();
    // cout << "higherMult: ";
    // higherMult->printNumber();
    Number* lowerMult = Karatsuba(lowSpl1, lowSpl2);
    // cout << "lowSpl1: ";
    // lowSpl1->printNumber();
    // cout << "lowSpl2: ";
    // lowSpl2->printNumber();
    // cout << "lowerMult: ";
    // lowerMult->printNumber();

    Number* Sum1 = Add(lowSpl1, highSpl1);
    // cout << "lowSpl1: ";
    // lowSpl1->printNumber();
    // cout << "highSpl1: ";
    // highSpl1->printNumber();
    // cout << "Sum1: ";
    // Sum1->printNumber();
    Number* Sum2 = Add(lowSpl2, highSpl2);
    // cout << "lowSpl2: ";
    // lowSpl2->printNumber();
    // cout << "highSpl2: ";
    // highSpl2->printNumber();
    // cout << "Sum2: ";
    // Sum2->printNumber();
    Number* Prod1 = Karatsuba(Sum1, Sum2);
    // cout << "Sum1: ";
    // Sum1->printNumber();
    // cout << "Sum2: ";
    // Sum2->printNumber();
    // cout << "Prod1: ";
    // Prod1->printNumber();
    Number* Diff1 = Sub(*Prod1, *higherMult);
    // cout << "Prod1: ";
    // Prod1->printNumber();
    // cout << "higherMult: ";
    // higherMult->printNumber();
    // cout << "Diff1: ";
    // Diff1->printNumber();
    Number* Diff2 = Sub(*Diff1, *lowerMult);
    // cout << "Diff1: ";
    // Diff1->printNumber();
    // cout << "lowerMult: ";
    // lowerMult->printNumber();
    // cout << "Diff2: ";
    // Diff2->printNumber();
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

    return Res;
}

int main() {
    // TODO: Correct the code for this input
    vector<int> a = {2,1,5,4,5,7,4,3};
    vector<int> b = {0,3,4,2,3,0,8,4};
    Number* A = new Number(a, 10, 0, 0);
    Number* B = new Number(b, 10, 0, 0);
    Number* ans = Multiply(A, B);
    // Number* ans = NormalMult(A, B);

//     cout << "\nAnswer: \n";
//     ans->printNumber();
// }

#endif // MULTIPLICATION