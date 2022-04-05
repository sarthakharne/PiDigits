#ifndef DIVISION
#define DIVISION
#include <bits/stdc++.h>
#include <cmath>
#include "Number.hpp"
// #include "Multiplication.cpp"
using namespace std;

// THE FOLLOWING ALGORITHM HAS BEEN TAKEN FROM SCHOUP

// #define QuoRem(temp, base) make_pair(temp/base, temp%base)

// a = (a(k-1) ,,,, a(0))(base B), k >= 1
// b = (b(l-1) .... b(0))(base B), l >= 1, b(l-1) != 0
// compute q and r such that a = bq + r, 0 <= r < b
// if k < l, q = 0, r = a
// q will have at most m := k − l + 1 base-B digits
// q = (q(m-1) .... q(0))(base B)
// r = (r(k-1) .... r(0))(base B)
pair <int, int> QuoRem(int temp, int base)
{
    if(temp > 0)
    {
        return make_pair(temp/base, temp%base);
    }
    else{
        temp = temp * -1;
        int q = temp/base ;
        int r = temp%base;
        if(r==0)
        {
            q=q*-1;
            return make_pair(q,r);
        }
        else{
            q++;
            q = q*-1;
            r = (temp*-1) - base*q;
            return make_pair(q,r);
        }
    }
}
pair<Number *, Number *> Divide(Number* A, Number* B) {
    // initialise R = A
    vector<int> r_dig(A->digits.begin(), A->digits.end());
    Number* R = new Number(r_dig, A->base, 0);
    R->digits.push_back(0);

    A->printNumber();
    B->printNumber();
    R->printNumber();
    cout << endl;

    // sizes of different numbers
    int k = A->digits.size();   // A, R
    int l = B->digits.size();   // B
    int m = k - l + 1;          // Q
    int base = A->base;
    int carry = 0;

    // initialise Q
    vector<int> q_dig(1, 0);
    Number* Q = new Number(q_dig, A->base, 0);
    // this step is required as vector cannot be initialised to 0
    // otherwise remove zeroes function call in contructor will remove 
    // all zeroes
    Q->digits.resize(m, 0);

    for(int i = k - l; i >= 0; i--) {
        Q->digits[i] = floor( (R->digits[i+l]*base + R->digits[i+l-1])/B->digits[l-1] );
        cout<<"Q["<<i<<"] :"<<Q->digits[i]<<endl;
        Q->printNumber();

        if(Q->digits[i] > base)
            Q->digits[i] = base-1;
            cout<<"Q["<<i<<"] :"<<Q->digits[i]<<endl;
        carry = 0;

        for(int j = 0;j <= l-1;j++) {
            int temp = R->digits[i+j] - Q->digits[i]*B->digits[j] + carry;
            cout<<"temp = "<<temp<<endl;
            carry = QuoRem(temp, base).first;
            cout<<"Carry Right here = "<<carry<<endl;
            R->digits[i + j] = QuoRem(temp, base).second;
        }
        R->digits[i+l] += carry;
        cout<<"ri+l "<<R->digits[i+l]<<endl;
        while(R->digits[i+l] < 0) {
            carry = 0;
            for(int j = 0;j <= l-1;j++) {
                int temp = R->digits[i+j] + B->digits[i] + carry;
                cout<<"temp = "<<temp<<endl;
                carry = QuoRem(temp, base).first;
                cout<<"Carry = "<<carry<<endl;
                R->digits[i+j] = QuoRem(temp, base).second;
                cout<<"Ri+j "<<R->digits[i+j]<<endl;
            }

            R->digits[i+l] += carry;
            Q->digits[i] -= 1;
        }

    }
    Q->removeZeroes();
    R->removeZeroes();
    return make_pair(Q, R);
}


int main() {
    vector<int> a = {9,9};
    vector<int> b = {8,1};
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
}

#endif