#ifndef SUBTRACTION
#define SUBTRACTION
#include "Number.hpp"
// void Adjust(Number * A, Number * B)
// {
//     if(A->exponent > B->exponent)
//     {
//         int diff = A->exponent - B->exponent;
//         A->exponent = B->exponent;
//         vector<int> vec = {1};
//         Number adjustfactor(vec,A->base,diff,0);
//         Multiply(A,&adjustfactor);
//     }
//     else if(A->exponent < B->exponent)
//     {
//         int diff = B->exponent - A->exponent;
//         B->exponent = A->exponent;
//         vector<int> vec = {1};
//         Number adjustfactor(vec,B->base,diff,0);
//         Multiply(B,&adjustfactor);
//     }
// }
int Order(Number *A, Number *B)
{
    if (A->digits.size() < B->digits.size())
    { // B is the larger Number.
        vector<int> temp;
        temp = A->digits;
        A->digits = B->digits;
        B->digits = temp;
        return 1; // Swapping has been done.
    }
    else if (A->digits.size() == B->digits.size())
    {
        for (int i = 0; i < A->digits.size(); i++)
        {
            if (A->digits[i] > B->digits[i])
            {
                // This means that A is indeed larger than B

                return -1; // no swap is necessary
            }
            else
            {
                // If this part is reached then B is larger than A and we need to swap
                vector<int> temp;
                temp = A->digits;
                A->digits = B->digits;
                B->digits = temp;
                return 1; // Swapping has been done.
            }
        }
    }
    return -1; // no swapping needs to be done.
}
Number *Sub(Number *A, Number *B)
{
    // Adjust(A,B);
    // FOR Bk and Al length vectors
    int swapflag = Order(A, B);
    int sign = 0;
    if (swapflag == 1)
    {
        sign = 1; // negative
        
    }
    vector<int> c;
    int k = B->digits.size();
    int l = A->digits.size();
    int b = A->base;
    int carry = 0;
    int Ci = 0;
    int minLen = min(l, k);
    int maxLen = max(l, k);
    for (int i = 0; i < minLen; i++)
    {
        if ((A->digits[l - i - 1] - B->digits[k - i - 1] + carry) >= 0)
        {
            Ci = (A->digits[l - i - 1] - B->digits[k - i - 1] + carry) % b;
            carry = 0;
            c.push_back(Ci);
        }
        else
        {
            Ci = ((A->base + (A->digits[l - i - 1])) - B->digits[k - i - 1] + carry) % b;
            carry = -1;
            c.push_back(Ci);
        }
    }
    for (int i = minLen; i < maxLen; i++)
    { // l > k in this case always since A always has the larger value
        if (A->digits[i] == 0 && carry == -1)
        {
            Ci = ((A->base + (A->digits[l - i - 1])) + carry) % b;
            carry = -1;
            c.push_back(Ci);
        }
        else
        {
            Ci = (A->digits[l - i - 1] + carry) % b;
            carry = 0;
            c.push_back(Ci);
        }
    }
    vector<int> res;
    for (int i = c.size() - 1; i > -1; i--)
    {
        res.push_back(c[i]);
    }

    Number *ans = new Number(res, A->base, 0, sign);

    return ans;
}

int main()
{
    vector<int> a = {2,0,1};
    vector<int> b = {5,0,5};
    Number A(a, 10, 0, 0);
    Number B(b, 10, 0, 0);
    Number *ans = Sub(&A, &B);
    for (int i = 0; i < ans->digits.size(); i++)
    {
        cout << ans->digits[i];
    }
    cout << endl;
    cout << ans->sign << endl;
}
// Rough : -
//  123  B 3 3-i-1 = 2 1
//  093  A 2 2-i-1 = 1 0
//    0
//   1   carry = 1
//  2

#endif