#include "Number.hpp"

Number::Number(vector<int> &dig, int b, int expo, bool sig)  {
    digits = dig;
    base = b;
    exponent = expo;
    sign = sig;
    // this->removeZeroes();
}

Number::Number(Number* n) {
    this->digits = n->digits;
    this->base = n->base;
    this->exponent = n->exponent;
    this->sign = n->sign;
    // this->removeZeroes();
}

void Number::removeZeroes(bool maintain_exp, int exp) {
    int i = this->digits.size() - 1;
    int count = 0;

    while(i > 0) {
        // remove digit if zero
        if(this->digits[i] == 0)
            this->digits.pop_back();
        else
            break;
        i--;
        count++;
    }

    if(maintain_exp == true) {
        this->addExponent(-1*count);
    }
    else if(exp != INT_MAX) {
        this->exponent = exp;
    }
    else {
        this->exponent = this->digits.size()-1;
    }

    // if(exp == INT_MAX && maintain_exp == false) this->exponent = this->digits.size() - 1;
    // else this->exponent = exp;
}

Number* Number::addExponent(int e) {
    for(int i = 0;i < e;i++)
        this->digits.insert(this->digits.begin(), 1, 0);

    // for(int i = 0;i > e;i--) {
    //     if(this->digits[0] == 0)
    //         this->digits.erase(this->digits.begin());
    //     else
    //         break;
    // }

    this->exponent += e;

    return this;
}

void Number::printNumber() {
    cout << "Digits: " << (this->sign == 1 ? "- " : "+ ");
    for(int i = this->digits.size() - 1;i >= 0;i--) {
        cout << this->digits[i] << " ";
    }
    cout << endl;
    cout << "Exponent: " << this->exponent << endl;
}

void Number::rev() {
    reverse(this->digits.begin(), this->digits.end());
}

// will return 1 if n1 > n2, 0 if n1 == n2, -1 if n1 < n2
int Number::compare(Number* n1, Number* n2, bool considerSign) {
    // all numbers are in scientific notation, so the following method is followed
    // check signs
    // compare exponents
    // if same, compare the msb
    // if same, start comparing from msb - 1

    if(considerSign) {
        if(n1->sign ^ n2->sign != false) {
            // if signs are different, then if first number's sign is negative, return -1
            return n1->sign == true ? -1 : 1;
        }
    }
    if(n1->exponent == n2->exponent) {
        int i = n1->digits.size() - 1;
        int j = n2->digits.size() - 1;
        while(i >= 0 && j >= 0) {
            if(n1->digits[i] == n2->digits[j]){
                i--;
                j--;
            }
            else {
                return n1->digits[i] > n2->digits[j] ? 1 : -1;
            }
        }
        // if both i and j are zero, numbers are equal
        if(i == j) {
            return 0;
        }
        // else return the number with more precision
        else {
            return i > j ? 1 : -1;
        }
    }
    else {
        return n1->exponent > n2->exponent ? 1 : -1;
    }
}

Number* Number::retTwo(int b, int expo, bool sig) {
    vector<int> two(1, 2);
    // adjust for base
    while(two[two.size() - 1]/b != 0) {
        two.push_back(two[two.size()-1]/b);
        two[two.size() - 2] %= b;
    }
    Number* Two = new Number(two, b, 0);
    Two->removeZeroes();

    return Two;
}
