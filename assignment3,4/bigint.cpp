//Copyright 2019 Dingjun Bian braybian@bu.edu
#include<string>
#include<vector>
using namespace std; 
  
typedef string BigInt; 
BigInt multiply_int(const BigInt &a, const BigInt &b) 
{   int len1=a.size();
    int len2=b.size();    
    vector<long int> out(len1 + len2, 0);  
    int outer = 0;  
    int inner = 0; 
    
    if (len1 == 0 || len2 == 0) 
    return "0";  
     
    for (int i=len1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int n1 = a.at(i) - '0'; 
        inner = 0;               
        for (int j=len2-1; j>=0; j--) { 
            int n2 = b.at(j) - '0'; 
            int sum = n1*n2 + out.at(outer + inner) + carry;  
            carry = sum/10; 
            out.at(outer + inner) = sum % 10;   
            inner=inner+1; 
        } 
        if (carry > 0) 
            out.at(outer + outer) += carry; 
            outer=outer+1; 
    } 
    int i = out.size() - 1; 
    while (i>=0 && out.at(i) == 0) 
      i--; 
    string s = "";  
    while (i >= 0) 
        s += std::to_string(out.at(i--));  
    return s; 
} 
  

