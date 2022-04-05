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

int ConvertToSci(Number* A, Number *B)
{
    //A > B
    if(A->exponent > B->exponent)
    {
        return A->exponent;
    }
    else if(A->exponent == B->exponent)
    {
        int count = 0;
        for(int i =0;i<A->digits.size();i++)
        {
            if(A->digits[i] == B->digits[i])
            count++;
        }
        return A->exponent-count;
    }
    return 0;
}

void padding(Number * A, Number * B)
{
    //A>B
    int pad = (A->exponent - B->exponent) - (A->digits.size() -1) + (B->digits.size() -1);
    A->exponent = B->exponent;
    if(pad > 0)
    {
        //We need to pad the first number A by pad
        for(int i =0;i<pad;i++)
        {
            A->digits.push_back(0);
        }
    }
    else
    {
        for(int i =0;i<pad;i++)
        {
            B->digits.push_back(0);
        }
    }

}
int Order(Number *A, Number *B)
{
    reverse(A->digits.begin(),A->digits.end());
    reverse(B->digits.begin(),B->digits.end());

    if (A->exponent < B->exponent)
    { // B is the larger Number.
        vector<int> temp;
        swap(A->exponent,B->exponent);
        temp = A->digits;
        A->digits = B->digits;
        B->digits = temp;
        return 1; // Swapping has been done.
    }
    else if (A->exponent == B->exponent)
    {
        for (int i = 0; i < A->digits.size(); i++)
        {
            if(A->digits[i] > B->digits[i])
            {
                return -1;
            }
            if (A->digits[i] < B->digits[i])
            {
                // If this part is reached then B is larger than A and we need to swap
                vector<int> temp;
                swap(A->exponent,B->exponent);
                temp = A->digits;
                A->digits = B->digits;
                B->digits = temp;
                return 1; // Swapping has been done.
            }
        }
    }
    return -1; // no swapping needs to be done.
}
Number *Sub(Number A, Number B)
{
    // Adjust(A,B);
    // FOR Bk and Al length vectors
    A.printNumber();
    B.printNumber();
    // A.printNumber();
    // B.printNumber();
    // A.printNumber();
    // B.printNumber();
    int sa = A.sign;
    int sb = B.sign;
    int swapflag = Order(&A, &B);
    int exp = ConvertToSci(&A,&B);
    padding(&A,&B);
    
    int sign = 0;
    A.printNumber();
    B.printNumber();
    if (swapflag == 1)
    {
        sign = 1; // negative       
    }
    if(sa == 1 && sb == 0)
    {
        if(sign ==1) sign = 0;
        else sign =1;
    }
    vector<int> c;
    int l = A.digits.size();
    int k = B.digits.size();
    int b = A.base;
    int carry = 0;
    int Ci = 0;
    int minLen = min(l, k);
    int maxLen = max(l, k);
    for (int i = 0; i < minLen; i++)
    {
        if ((A.digits[l - i - 1] - B.digits[k - i - 1] + carry) >= 0)
        {
            Ci = (A.digits[l - i - 1] - B.digits[k - i - 1] + carry) % b;
            carry = 0;
            c.push_back(Ci);
            // cout<<Ci<<endl;
        }
        else
        {
            Ci = ((A.base + (A.digits[l - i - 1])) - B.digits[k - i - 1] + carry) % b;
            carry = -1;
            c.push_back(Ci);
            // cout<<Ci<<endl;
        }
    }
    for (int i = minLen; i < maxLen; i++)
    { // l > k in this case always since A always has the larger value
        if (A.digits[l-i-1] == 0 && carry == -1)
        {
            Ci = ((A.base + (A.digits[l - i - 1])) + carry) % b;
            carry = -1;
            c.push_back(Ci);
        }
        else
        {
            Ci = (A.digits[l - i - 1] + carry) % b;
            carry = 0;
            c.push_back(Ci);
        }
    }
    vector<int> res;
    for (int i = c.size() - 1; i > -1; i--)
    {
        res.push_back(c[i]);
    }
    
    reverse(res.begin(),res.end());
    reverse(A.digits.begin(),A.digits.end());
    reverse(B.digits.begin(),B.digits.end());
    Number *ans = new Number(res, A.base, 0, sign);
    ans->removeZeroes();
    ans->exponent = exp;
    return ans;
}

// int main()
// {
//     vector<int> a = {0,5,3};
//     vector<int> b = {0,2,0,0,5};
//     Number A(a, 10, 3, 0);
//     Number B(b, 10, 2, 0);
//     Number *ans = Sub(A, B);
    
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