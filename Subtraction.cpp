#ifndef SUBTRACTION
#define SUBTRACTION
#include "Number.hpp"

Number* Sub(Number* A, Number* B) {
    // IMPLICIT ASSUMPTION: A>B
    // if any one of the number is negative, call sub
    // adjust exponents
    // add the numbers
    // restore exponents
    // return

    Number* A_Copy;
    Number* B_Copy;
    Number* Ans;
    bool sign_flag = false;

    // after this step, magnitude of A_Copy is bigger
    if(Number::compare(A, B) >= 0) {
        A_Copy = new Number(A);
        B_Copy = new Number(B);
        sign_flag = false;
    }
    else {
        A_Copy = new Number(B);
        B_Copy = new Number(A);
        sign_flag = true;
    }

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
    vector<int> c_dig(k, 0);

    // addition (both will have the same size)
    for(int i = 0;i < k;i++) {
        int temp = A_Copy->digits[i] - B_Copy->digits[i] + carry;
        carry = Number::QuoRem(temp, base).first;
        c_dig[i] = Number::QuoRem(temp, base).second;
    }

    if(carry==-1) {
        cout << "Error";
    }

    int c_exp = (biggerExpNo == 0 ? A_Copy->exponent : B_Copy->exponent);

    free(A_Copy);
    free(B_Copy);

    Ans = new Number(c_dig, base, c_exp, sign_flag);
    Ans->removeZeroes(true);
    return Ans;
}

// int main()
// {
//     vector<int> a = {0,2};
//     vector<int> b = {0,2};
//     Number* A = new Number(a, 10, 1, 0);
//     Number* B = new Number(b, 10, 1, 1);
//     Number *ans = Sub(A, B);
//     cout << ans->digits.size() << " " << ans->digits[0] << endl;
//     vector<int> thresh_dig(1, 5);
//     Number* Thresh = new Number(thresh_dig, 10, -10);
//     Thresh->printNumber();
//     Thresh->removeZeroes(true);
//     cout << Number::compare(ans, Thresh) << endl;
    
//     // ans->exponent = exp;
//     // padding(&A,&B);
//     ans->printNumber();
//     cout << endl;
// }
// Rough : -
//  123  B 3 3-i-1 = 2 1
//  093  A 2 2-i-1 = 1 0
//    0
//   1   carry = 1
//  2

#endif