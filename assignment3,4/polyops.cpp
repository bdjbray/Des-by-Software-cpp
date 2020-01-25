//Copyright 2019 Dingjun Bian braybian@bu.edu
//#include <iostream> 
#include <vector>
using namespace std;

typedef vector<double> Poly;
 
  Poly add_poly(const Poly &a,const Poly &b)
  {
  Poly a1=a;
  Poly b1=b;
  Poly sum;
  int len1=a1.size();
  int len2=b1.size();
  if(len1>len2){
     sum.resize(len1,0);
   for (int i = 0; i<len1; i++) 
     sum.at(i) +=a1.at(i) ;
   for (int i = 0; i<len2; i++) 
     sum.at(i) +=b1.at(i) ;
   }
  if(len1<len2){
     sum.resize(len2,0);
   for (int i = 0; i<len1; i++) 
     sum.at(i) +=a1.at(i) ;
   for (int i = 0; i<len2; i++) 
     sum.at(i) +=b1.at(i) ;
   }
   if(len1==len2){
     sum.resize(len1,0);
     for(int i=0;i<len2;i++){
       sum.at(i)=a1.at(i)+b1.at(i); 
     }
  }
  return sum; 
}


typedef vector<double> Poly;
Poly multiply_poly(const Poly &a,const Poly &b)
{ 
   Poly a1=a;
   Poly b1=b;
   int m = sizeof(a1)/sizeof(a1.at(0)); 
   int n = sizeof(b1)/sizeof(b1.at(0)); 
   Poly prod(m + n-1, 0); 
   Poly none{0};
//   Poly s;
  
   for (int i = 0; i<m+n-1; i++) 
     prod.at(i) = 0; 

   for (int i=0; i<m; i++) 
   { 
     for (int j=0; j<n; j++) 
         prod.at(i+j) += a1.at(i)*b1.at(j); 
   }   
   int i = prod.size() - 1; 
	while (i>=0 && prod.at(i) == 0) 
	i=i-1; 
        Poly s(i+1,0);
        //Poly s ; 
	if (i == -1)   //(if) the whole result is all zero
        return none; 
	int j=0;
	while (j<= i){
          s.at(j)=prod.at(j);
          j++;
               } 
              
		//s += std::to_string(prod.at(i--)); 
       
	return s; 
} 
