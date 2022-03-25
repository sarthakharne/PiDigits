#include "Number.hpp"

Number::Number(vector<int> &dig, int b, int expo, bool sig)  {
    digits = dig;
    base = b;
    exponent = expo;
    sign = sig;
}

Number::Number(Number* n) {
    this->digits = n->digits;
    this->base = n->base;
    this->exponent = n->exponent;
    this->sign = n->sign;
}

void Number::removeZeroes() {
    int i = this->digits.size() - 1;

    while(i >= 0) {
        // remove digit if zero
        if(this->digits[i] == 0)
            this->digits.pop_back();
        else
            break;
    }

    this->exponent = this->digits.size();
}

Number* Number::addExponent(int e) {
    this->exponent += e;
    return this;
}