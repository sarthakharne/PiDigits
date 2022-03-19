#include "Number.hpp"

Number::Number(vector<int> &dig, int b, int expo, bool sig)  {
    digits = dig;
    base = b;
    exponent = expo;
    sign = sig;
}