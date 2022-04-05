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
    if((n1->digits.size() == 1) && (n1->digits[0] == 0) && (n2->sign == false))
        return -1;

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

int Number::padNumbers(Number* A, Number* B) {
    // implicit assumption that a.exp > b.exp
    // difference in exponents
    int diffExp = A->exponent - B->exponent;

    // add zeroes to the beginning of second number
    for(int i = 0;i < diffExp;i++)
        B->digits.push_back(0);
    
    // adjust exponent for the second number by reducing exponent
    B->addExponent(-1*diffExp);

    int sizeDiff = A->digits.size() - B->digits.size();

    if(sizeDiff < 0) {
        // a has smaller size, so pad it
        for(int i = 0;i < -1*sizeDiff;i++) {
            A->digits.insert(A->digits.begin(), 0);
        }
    }
    else {
        // b has smaller size, so pad it
        for(int i = 0;i < sizeDiff;i++) {
            B->digits.insert(B->digits.begin(), 0);
        }
    }

    return diffExp;
}

pair<int, int> Number::QuoRem(int temp, int base) {
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

void Number::adjustForPrecision(int precision) {
    // goal to make digitsAfterRealDecimal = precision
    int digitsAfterRealDecimal = this->digits.size() - this->exponent - 1;
    // pad with 0 if size < exponent
    if(digitsAfterRealDecimal < 0) {
        for(int i = 0;i < -1*digitsAfterRealDecimal;i++) {
            this->digits.insert(this->digits.begin(), 0);
        }
        digitsAfterRealDecimal = 0;
    }

    // pad with 0 to make digitsAfterRealDecimal = precision
    for(int i = 0;i < precision-digitsAfterRealDecimal;i++) {
        this->digits.insert(this->digits.begin(), 0);
    }
}

// returns the power to be subtracted from the num or denom
int Number::expressWihtoutDecimal() {
    // all digits after scientific decimal are made to appear
    // so that much power is subtracted
    int res = this->digits.size() - 1;
    this->addExponent(-1*(this->digits.size() - 1));
    return res;
}

void Number::makeDigitsEqual(Number* A, Number* B) {
    int sizeDiff = A->digits.size() - B->digits.size();
    if(sizeDiff < 0) {
        for(int i = 0;i < -1*sizeDiff;i++) {
            A->digits.insert(A->digits.begin(), 0);
        }
    }
    else {
        for(int i = 0;i < sizeDiff;i++) {
            B->digits.insert(B->digits.begin(), 0);
        }
    }
}
