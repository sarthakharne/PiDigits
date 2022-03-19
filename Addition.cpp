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
Number  Add(Number *A, Number *B)
{
    // FOR Bk and Al length vectors
    vector<int> c;
    //Adjust(A,B);
    int k = B->digits.size();
    int l = A->digits.size();
    int b = A->base;
    
    int carry = 0;
    int Ci = 0;
    int minLen = min(l, k);
    int maxLen = max(l, k);
    for (int i = 0; i < minLen; i++)
    {
        Ci = (A->digits[l - i - 1] + B->digits[k - i - 1] + carry) % b;
        carry = (A->digits[l - i - 1] + B->digits[k - i - 1] + carry) / b;
        c.push_back(Ci);
    }
    for (int i = minLen; i < maxLen; i++)
    {
        if (l < k)
        {
            Ci = (B->digits[k - i - 1] + carry) % b;
            carry = (B->digits[k - i - 1] + carry) / b;
            c.push_back(Ci);
        }
        else
        {
            Ci = (A->digits[l - i - 1] + carry) % b;
            carry = (A->digits[l - i - 1] + carry) / b;
            c.push_back(Ci);
        }
    }
    vector<int> res;
    for(int i =c.size()-1;i >-1;i--)
    {
        res.push_back(c[i]);
    }

    Number ans(res,A->base,0,false);

    return ans;
}

int main()
{
    vector<int> a = {9,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> b = {1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
    Number A(a,10,0,0);
    Number B(b,10,0,0);
    Number ans = Add(&A,&B);
    for(int i =0;i<ans.digits.size();i++)
    {
        cout<<ans.digits[i];
    }
    cout<<endl;
}
// Rough : -
//  123  B 3 3-i-1 = 2 1
//  093  A 2 2-i-1 = 1 0
//    6
//   1   carry = 1
//  2