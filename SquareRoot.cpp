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
    vector<int> thresh_dig(1, 5);
    Number* Thresh = new Number(thresh_dig, num->base, -1*(precision + 1));
    Thresh->removeZeroes(true);
    // Threshold of the form 0.000000005 or 5*e-9

    while(1) {
        pair<Number*, Number*> div1 = Divide(num, Ans, precision);
        Number* sum = Add(Ans, div1.first);
        pair<Number*, Number*> div2 = Divide(sum, Two, precision);
        Number* newAns = new Number(div2.first);
        // loop breaks when difference between two successive answers is less than threshold
        if(Number::compare(Sub(Ans, newAns), Thresh) < 0)
            break;

        
        // free the previous Ans and make a new one
        free(Ans);
        Ans = new Number(newAns);

        // free the objects
        free(newAns);
        free(div1.first);
        free(div1.second);
        free(sum);
        free(div2.first);
        free(div2.second);
    }

    // free all objects which are no longer required
    free(Two);
    free(Thresh);

    return Ans;
}

int main() {
    vector<int> a = {4};
    Number* A = new Number(a, 10, 0);

    Number* Ans = SquareRoot(A, 10);
    cout << "Square Root: ";
    Ans->printNumber();
}

#endif // SQUAREROOT