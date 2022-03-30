#ifndef DIVISION
#define DIVISION
#include <bits/stdc++.h>
#include <cmath>
#include "Number.hpp"
#include "Addition.cpp"
#include "Subtraction.cpp"
#include "Multiplication.cpp"
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

pair<Number *, Number *> Divide(Number* A, Number* B) {
    // initialise R = A
    vector<int> r_dig(A->digits.begin(), A->digits.end());
    Number* R = new Number(r_dig, A->base, 0);
    R->digits.push_back(0);

    // A->printNumber();
    // B->printNumber();
    // R->printNumber();
    // cout << endl;

    // sizes of different numbers
    int k = A->digits.size();   // A, R
    int l = B->digits.size();   // B
    int m = k - l + 1;          // Q
    int base = A->base;
    int carry = 0;

    // initialise Q
    vector<int> q_dig(m, 0);
    Number* Q = new Number(q_dig, A->base, 0);
    // this step is required as vector cannot be initialised to 0
    // otherwise remove zeroes function call in contructor will remove 
    // all zeroes
    
    //Q->digits.resize(m, 0);
    // A->rev();
    // B->rev();
    // R->rev();

    for(int i = k - l; i >= 0; i--) {
        Q->digits[i] = floor((float)( (R->digits[i+l]*base + R->digits[i+l-1])/B->digits[l-1] ));
        // Q->printNumber();

        if(Q->digits[i] >= base)
            Q->digits[i] = base-1;
        
        carry = 0;

        // // -------------------------------

        // // TODO: free newly allocated objects
        // // here we have to do (r(i+l) ... r(i))(base B) = (r(i+l) ... r(i))(base B) - q(i)*b
        // vector<int> r_il_i;
        // for(int k = i;k <= i+l;k++)
        //     r_il_i.push_back(R->digits[k]);
        // Number* R_IL_I = new Number(r_il_i, base, 0);
        // // cout << "R_IL_I: ";
        // // R_IL_I->printNumber();
        // vector<int> q_i{Q->digits[i]};
        // Number* Q_I = new Number(q_i, base, 0);
        // Number* Q_I_times_B = Multiply(Q_I, B);
        // Number* Sub_Res = Sub(R_IL_I, Q_I_times_B);
        // // Sub_Res->printNumber();
        
        
        // // (r(i+l) ... r(i))(base B) = (r(i+l) ... r(i))(base B) + (b(l-1) ... b(0))(base B)
        // while(Sub_Res->sign == true) {
        //     Sub_Res = Add(Sub_Res, B);
        //     // Sub_Res->printNumber();
        //     Q->digits[i] -= 1;
        // }
        
        // for(int k = i;k <= i+l;k++){
        //     // cout << "Hello\n";
        //     R->digits[k] = Sub_Res->digits[k-i];
        // }

        // free(R_IL_I);
        // free(Q_I);
        // free(Q_I_times_B);
        // free(Sub_Res);

        // // -------------------------------

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
    // A->rev();
    // B->rev();
    // R->rev();
    // Q->rev();

    
    Q->removeZeroes();
    R->removeZeroes();
    return make_pair(Q, R);
}


int main() {
    vector<int> a = {7,5,5,8,1,5};
    vector<int> b = {7,0,2,3,9};
    Number* A = new Number(a, 10, 0, 0);
    Number* B = new Number(b, 10, 0, 0);
    pair<Number*, Number*> p = Divide(A, B);
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