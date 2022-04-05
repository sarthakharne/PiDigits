#ifndef ADDITION
#define ADDITION
#include "Number.hpp"
#include "Subtraction.cpp"
#include <algorithm>
using namespace std;

Number* Add(Number* A, Number* B) {
    // if any one of the number is negative, call sub
    // adjust exponents
    // add the numbers
    // restore exponents
    // return

    Number* A_Copy = new Number(A);
    Number* B_Copy = new Number(B);
    Number* Ans;

    if((A_Copy->sign ^ B_Copy->sign) == true) {
        if(B->sign == true)
            Ans = Sub(A, B);
        else if(A->sign == true)
            Ans = Sub(B, A);
    }
    else {
        // adjust exponents
        int restoringExp = 0;
        // 0 if A_Copy has smaller exp, 1 if B_Copy has smaller exp
        int biggerExpNo = 0;
        
        if(A_Copy->exponent >= B_Copy->exponent) {
            Number::padNumbers(A_Copy, B_Copy);
            biggerExpNo = 0;
        }
        else {
            Number::padNumbers(B_Copy, A_Copy);
            biggerExpNo = 1;
        }

        int k = A_Copy->digits.size();
        int l = B_Copy->digits.size();
        int base = A_Copy->base;
        int carry = 0;
        vector<int> c_dig(k+1, 0);

        // addition (both will have the same size)
        for(int i = 0;i < k;i++) {
            int temp = A_Copy->digits[i] + B_Copy->digits[i] + carry;
            carry = Number::QuoRem(temp, base).first;
            c_dig[i] = Number::QuoRem(temp, base).second;
        }
        c_dig[k] = carry;


        int c_exp;
        if(carry == 0) {
            c_dig.pop_back();
            // the number with bigger exponent is untouched, so its exponent is assigned
            // as length of answer is length of numbers
            c_exp = (biggerExpNo == 0 ? A_Copy->exponent : B_Copy->exponent);
        }
        else {
            // if carry is not 0, then length of answer is bigger than the numbers,
            // so the intact exponent (exponent of bigger number) + 1 is assigned
            c_exp = (biggerExpNo == 0 ? A_Copy->exponent+1 : B_Copy->exponent+1);
        }
        free(A_Copy);
        free(B_Copy);

        bool c_sign = A_Copy->sign & B_Copy->sign;

        Ans = new Number(c_dig, base, c_exp, c_sign);

    }
    return Ans;

}

// int main()
// {
//     vector<int> a = {0,0,0,0,0,0,0,0,0,0,5};
//     vector<int> b = {1};
//     Number A(a,10,0,0);
//     Number B(b,10,0,0);
//     Number *ans = Add(&A,&B);
//     // for(int i =0;i<ans->digits.size();i++)
//     // {
//     //     cout<<ans->digits[i];
//     // }
//     ans->printNumber();
//     cout<<endl;
// }
// Rough : -
//  123  B 3 3-i-1 = 2 1
//  093  A 2 2-i-1 = 1 0
//    6
//   1   carry = 1
//  2

#endif