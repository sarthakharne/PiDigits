#ifndef DIVISION
#define DIVISION
#include <bits/stdc++.h>
#include <cmath>
#include "Number.hpp"
// #include "Multiplication.cpp"
using namespace std;

// THE FOLLOWING ALGORITHM HAS BEEN TAKEN FROM SCHOUP

// #define QuoRem(temp, base) make_pair(temp/base, temp%base)

pair<int, int> QuoRem(int temp, int base) {
    int quo, rem;

    if(temp >= 0) {
        quo = temp/base;
        rem = temp%base;
    }

    else {
        // if the number is negative
        // // if mod == 0 quo = -temp/base
        // // else if mod != 0 quo = -(temp/base + 1)
        if(temp%base == 0) {
            quo = temp/base;
            rem = 0;
        }
        else {
            quo = temp/base - 1;
            rem = base + temp%base; // + because temp%base is negativez
        }
    }
    
    return make_pair(quo, rem);
}

// a = (a(k-1) ,,,, a(0))(base B), k >= 1
// b = (b(l-1) .... b(0))(base B), l >= 1, b(l-1) != 0
// compute q and r such that a = bq + r, 0 <= r < b
// if k < l, q = 0, r = a
// q will have at most m := k − l + 1 base-B digits
// q = (q(m-1) .... q(0))(base B)
// r = (r(k-1) .... r(0))(base B)

pair<Number *, Number *> Divide(Number* A, Number* B, int precision=0) {
    // add zeroes in the beginning of A then remove at last to get precision
    // create copy of A and then change the exponent
    // TODO: remove exponents = precision to get accurate answer
    // zero vector with size = precision
    vector<int> zeroes(precision, 0);
    // add the zero vector to A
    Number* A_Copy = new Number(A);
    A_Copy->addExponent(precision);
    
    // initialise R = A_Copy
    vector<int> r_dig(A_Copy->digits.begin(), A_Copy->digits.end());
    Number* R = new Number(r_dig, A_Copy->base, 0);
    R->digits.push_back(0);

    // A->printNumber();
    // A_Copy->printNumber();
    // B->printNumber();
    // R->printNumber();
    // cout << endl;

    // sizes of different numbers
    int k = A_Copy->digits.size();   // A_Copy, R
    int l = B->digits.size();   // B
    int m = k - l + 1;          // Q
    int base = A_Copy->base;
    int carry = 0;

    // initialise Q
    vector<int> q_dig(m, 0);
    Number* Q = new Number(q_dig, A_Copy->base, A_Copy->exponent - B->exponent);
    Q->printNumber();
    // this step is required as vector cannot be initialised to 0
    // otherwise remove zeroes function call in contructor will remove 
    // all zeroes
    
    for(int i = k - l; i >= 0; i--) {
        if(i > Q->digits.size())
            Q->digits.resize(i+1);  // resize q if enough space not allocated
        Q->digits[i] = floor((float)( (R->digits[i+l]*base + R->digits[i+l-1])/B->digits[l-1] ));
        // Q->printNumber();

        if(Q->digits[i] >= base)
            Q->digits[i] = base-1;
        
        carry = 0;


        for(int j = 0;j <= l-1;j++) {
            int temp = R->digits[i+j] - Q->digits[i]*B->digits[j] + carry;
            carry = QuoRem(temp, base).first;
            R->digits[i + j] = QuoRem(temp, base).second;
        }

        R->digits[i+l] += carry;

        while(R->digits[i+l] < 0) {
            carry = 0;
            for(int j = 0;j <= l-1;j++) {
                int temp = R->digits[i+j] + B->digits[j] + carry;
                carry = QuoRem(temp, base).first;
                R->digits[i+j] = QuoRem(temp, base).second;
            }

            R->digits[i+l] += carry;
            Q->digits[i] -= 1;
        }

    }
    if(Q->digits.size() == 0)   Q->digits.push_back(0);
    
    Q->removeZeroes(true);
    // remove exponent = precision
    Q->addExponent(-1*precision);

    R->removeZeroes(true);
    R->addExponent(A->exponent - B->exponent);
    free(A_Copy);
    return make_pair(Q, R);
}


int main() {
    vector<int> a = {4};
    vector<int> b = {1};
    Number* A = new Number(a, 10, 0, 0);
    Number* B = new Number(b, 10, 0, 0);
    pair<Number*, Number*> p = Divide(A, B, 5);
    Number* Quotient = p.first;
    Number* Remainder = p.second;
    // Number* ans = NormalMult(A, B);

    cout << "\nQuotient: \n";
    Quotient->printNumber();
    cout << "\nRemainder: \n";
    Remainder->printNumber();
    // cout << QuoRem(-13, 7).first << " " << QuoRem(-13, 7).second << endl;
}

#endif