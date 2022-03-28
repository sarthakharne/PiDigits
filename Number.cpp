#include "Number.hpp"

Number::Number(vector<int> &dig, int b, int expo, bool sig)  {
    digits = dig;
    base = b;
    exponent = expo;
    sign = sig;
    this->removeZeroes();
}

Number::Number(Number* n) {
    this->digits = n->digits;
    this->base = n->base;
    this->exponent = n->exponent;
    this->sign = n->sign;
    this->removeZeroes();
}

void Number::removeZeroes() {
    int i = this->digits.size() - 1;

    while(i > 0) {
        // remove digit if zero
        if(this->digits[i] == 0)
            this->digits.pop_back();
        else
            break;
        i--;
    }

    this->exponent = this->digits.size() - 1;
}

Number* Number::addExponent(int e) {
    for(int i = 0;i < e;i++)
        this->digits.insert(this->digits.begin(), 1, 0);

    this->removeZeroes();
    return this;
}

void Number::printNumber() {
    cout << "Digits: ";
    for(int i = this->digits.size() - 1;i >= 0;i--) {
        cout << this->digits[i] << " ";
    }
    cout << endl;
    cout << "Exponent: " << this->exponent << endl;
}