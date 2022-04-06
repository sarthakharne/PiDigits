#ifndef SQUAREROOT
#define SQUAREROOT

#include <bits/stdc++.h>
#include "Number.hpp"
#include "Addition.cpp"
#include "Subtraction.cpp"
#include "Division.cpp"

using namespace std;

// bool check(Number* num, int precision) {
//     if(num->digits.size() >= precision+1)
//         return true;
//     else
//         return false;
// }

Number* SquareRoot(Number* num, int precision) {
    precision += 5;
    // TODO: free space
    // guess number
    vector<int> ans_dig(1, 1);  // initialise the guess with 1
    Number* Ans;
    Ans = new Number(ans_dig, num->base, 0);

    // TODO: free space
    // 2
    Number* Two = Number::retTwo(num->base);

    // threshold
    // initialise all 0s and then push 1
    vector<int> thresh_dig(1, 1);
    Number* Thresh = new Number(thresh_dig, num->base, -1*(precision + 1));
    Thresh->removeZeroes(true);
    // Threshold of the form 0.000000001 or 1*e-9

    while(1) {
        Number* div1 = Divide(num, Ans, precision);
        Number* sum = Add(Ans, div1);
        Number* div2 = Divide(sum, Two, precision);
        Number* newAns = new Number(div2);
        // loop breaks when difference between two successive answers is less than threshold
        // TODO: check compare function
        Number* Diff = Sub(Ans, newAns);
        if(Number::compare(Diff, Thresh) < 0)
            break;

        
        // free the previous Ans and make a new one
        free(Ans);
        Ans = new Number(newAns);
        Ans->removeZeroes(true);
        // Ans->printNumber();

        // free the objects
        free(Diff);
        free(newAns);
        free(div1);
        free(sum);
        free(div2);
    }

    // free all objects which are no longer required
    free(Two);
    free(Thresh);

    return Ans;
}

// int main() {
//     vector<int> a = {2};
//     Number* A = new Number(a, 10, 0);

//     Number* Ans = SquareRoot(Number::retTwo(10), 100);
//     cout << "Square Root of 2: ";
//     Ans->printNumber(95);

//     // Number* SqrtSqrtA = SquareRoot(Ans, 10);
//     // cout << "Square Root of Sqaure Root of 2: ";
//     // SqrtSqrtA->printNumber();
// }

#endif // SQUAREROOT