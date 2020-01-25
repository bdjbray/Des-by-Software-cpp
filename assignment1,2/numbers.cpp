//Copyright 2019 Dingjun Bian braybian@bu.edu
#include <vector>
#include <string>
using std::vector;
using std::string;

bool is_happy(int x) {
 string num;
num=std::to_string(x);
for(int j=0;j<10;j++){
int sum=0;
for(int i=0;i<num.size();i++){;
int smasum=0;
int newnum=num.at(i)-'0';
smasum=newnum*newnum;
sum=sum+smasum;
 }
 if (sum==1){
   return true;
   }
   else{
   int neww;
   neww=sum;
   num=std::to_string(neww);
   }
}
return false;
}


double product_of_positives(vector<double> v) {
double sum=1.0;
  for(int i=0;i<v.size();i++){
    if (v.at(i)>0){
    sum=sum*v.at(i);
    }
   }
  return sum;
}


int product_of_positives(vector<int> v) {
  int sum=1;
  for(int i=0;i<v.size();i++){
    if (v.at(i)>0){
    sum=sum*v.at(i);
    }
   }
  return sum;
}


vector<int> proper_divisors(int n) {
  vector<int> v;
   for(int i=1;i<n;i++){
    if (n%i==0){
    v.push_back(i);
    }
  }
  return v;
}

string add(const string& num1, const string& num2) {
  string sum;
  string num11=num1;
  string num22=num2;
  if(num11.size()>num22.size()){
   int len=num11.size()-num22.size();
   string num3(len,'0');
   num22=num3+num22;
   int ci=0;
   for(int i=num22.size()-1;i>=0;i--){
      int nn=num11.at(i)-'0'+num22.at(i)-'0'+ci;
      if(nn>9){
       ci=1;          
       sum.push_back((nn-10)+'0');
              if(i==0){
         sum.push_back('1');
            }   
      }
      else{
       ci=0;
       sum.push_back(nn+'0');
      }
    } 
  }

  else if(num11.size()<num22.size()){
   int len=num22.size()-num11.size();
   string num3(len,'0');
   num11=num3+num11;
   int ci=0;
   for(int i=num22.size()-1;i>=0;i--){
      int nn=num11.at(i)-'0'+num22.at(i)-'0'+ci;
      if(nn>9){
       ci=1;
       sum.push_back((nn-10)+'0');
            if(i==0){
         sum.push_back('1');
            }   
      }
      else{
       ci=0;
       sum.push_back(nn+'0');
      }
    } 
  }

 else if (num11.size()==num22.size()){
   int len=num11.size()-num22.size();
   int ci=0;
   for(int i=num22.size()-1;i>=0;i--){
      int nn=num11.at(i)-'0'+num22.at(i)-'0'+ci;
      if(nn>9){
       ci=1;         
       sum.push_back((nn-10)+'0');
            if(i==0){
         sum.push_back('1');
            }   
      }
      else{
      ci=0;
       sum.push_back(nn+'0');
      }
    } 
  }


int k=0,j=sum.size()-1;
while(k<j) std::swap(sum.at(k++),sum.at(j--));
return sum;
}
