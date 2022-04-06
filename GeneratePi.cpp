#ifndef GENERATEPI
#define GENERATEPI

#include <bits/stdc++.h>
#include "Number.hpp"
#include "Addition.cpp"
#include "Multiplication.cpp"
#include "Division.cpp"
#include "SquareRoot.cpp"

using namespace std;

Number* GeneratePi(int base, int precision) {
    // increase precision to get more correct digits
    precision += 5;
    
    // 1
    vector<int> one_dig(1,1);
    Number* One = new Number(one_dig, base, 0);
    
    // 2
    Number* Two = Number::retTwo(base);

    // a = sqrt(2)
    Number* A = SquareRoot(Two, precision);

    // b = 0
    vector<int> b_dig(1, 0);
    Number* B = new Number(b_dig, base, 0);

    // p = 2 + sqrt(2)
    Number* P = Add(Two, A);
    
    // A->printNumber();
    // B->printNumber();
    // P->printNumber();

    // threshold
    // initialise all 0s and then push 1
    vector<int> thresh_dig(1, 1);
    Number* Thresh = new Number(thresh_dig, base, -1*(precision + 1));
    Thresh->removeZeroes(true);
    // Threshold of the form 0.000000001 or 1*e-9

    while(1) {
        // calculation for new A
        Number* sqrtA = SquareRoot(A, precision);
        // sqrtA->printNumber();
        Number* recSqrtA = Divide(One, sqrtA, precision);
        // recSqrtA->printNumber();
        Number* sqrtASum = Add(sqrtA, recSqrtA);
        Number* newA = Divide(sqrtASum, Two, precision);
        // newA->printNumber();

        // calculation for new B
        Number* sumBplus1 = Add(One, B);
        // sumBplus1->printNumber();
        Number* sqrtAdotBplus1 = Multiply(sumBplus1, sqrtA);
        // sqrtAdotBplus1->printNumber();
        Number* aPlusB = Add(A, B);
        // aPlusB->printNumber();
        Number* newB = Divide(sqrtAdotBplus1, aPlusB, precision);
        // newB->printNumber();

        // calculation fro new P
        Number* newAPlus1 = Add(One, newA);
        Number* pDotNewB = Multiply(P, newB);
        Number* numProd = Multiply(newAPlus1, pDotNewB);
        Number* denom = Add(One, newB);
        Number* newP = Divide(numProd, denom, precision);

        Number* Diff = Sub(newP, P);
        if(Number::compare(Diff, Thresh) <= 0) {
            free(P);
            P = new Number(newP);
            break;
        }
        
        free(A);
        free(B);
        free(P);
        A = new Number(newA);
        B = new Number(newB);
        P = new Number(newP);
        // cout << "\n\nP: ";
        // P->printNumber();

        // freeing objects
        free(Diff);
        free(sqrtA);
        free(recSqrtA);
        free(sqrtASum);
        free(sumBplus1);
        free(sqrtAdotBplus1);
        free(aPlusB);
        free(newAPlus1);
        free(pDotNewB);
        free(numProd);
        free(denom);
    }

    return P;
}

// int main() {
//     int precision = 100;
//     Number* Pi = GeneratePi(10, precision + 5);
//     cout << "Final Value: ";
//     Pi->printNumber();
// }

#endif // GENERATEPI