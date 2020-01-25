

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

//#include "timer.h"

using std::vector;
using std::string;
using std::cout;
using std::sort;
vector<string> v1;
vector<string> v2;
class Arrangements
{
public:
    string seated = "";
    string thestring = "";

    Arrangements();
    explicit Arrangements(string thenames);
    vector<string> panel_shuffles(int n);
    vector<string> dinner_shuffles(int n);
    int decToBin(int dec);
    void swap(char &a, char &b);
    double panel_count(int n);
    double dinner_count(int n);
};

Arrangements::Arrangements()
{
 
}

Arrangements::Arrangements(string thenames)
{
  seated = "";
  thestring = thenames;
}

int Arrangements::decToBin(int dec){
  int result = 0, temp = dec, j = 1;
  while(temp){
    result = result + j * (temp % 2);
    temp = temp / 2;
    j = j * 10;
  }
  return result;
}

void Arrangements::swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

 vector<string> Arrangements::panel_shuffles(int n){
  if (n > thestring.length()) throw n;
  string currentstring=thestring.substr(0,n);
  vector<string> seats,shuff,panel;
  string x;
  n=n-1;
  for(int i=0;i<pow(2,n);i++)
{
  x=std::to_string(decToBin(i));
  while (x.length()<n)
    {x=x.insert(0,"0");}
  seats.push_back(x);
}

int state,last_state;
string X;
for(int i=0;i<seats.size();i++)
{
  X= seats.at(i);
  for(int j=1;j<n;j++)
  {
    state=X.at(j)-'0';
    if(state==1)
    { last_state=X.at(j-1)-'0';
      if(last_state==1) j=n;
    }
    if(j==n-1) shuff.push_back(X);
  }
}
for(auto& a:shuff)
{
  for(int m=0; m<a.length() ;m++)
  {  if(a.at(m)=='1') {swap(currentstring.at(m),currentstring.at(m+1));}  }
  panel.push_back(currentstring);
  currentstring=thestring.substr(0,n+1);
}
  return panel;
 }

 vector<string> Arrangements::dinner_shuffles(int n)
 {
   if (n > thestring.length()) throw n;
   string currentstring=thestring.substr(0,n);
   vector<string> seats,shuff,panel;
   string x;

    for(int i=0;i<pow(2,n);i++)
  { x=std::to_string(decToBin(i));
    while (x.length()<n)
    {x=x.insert(0,"0");}
    seats.push_back(x); }
  
  int state,last_state;
  string X,one_zero;

  for(int i=0;i<n;i++)
  {if(i==n-1) one_zero.push_back('0');
   else one_zero.push_back('1'); }

  for(int i=0;i<seats.size();i++)
  { X= seats.at(i);
    for(int j=1;j<n;j++)
    { state=X.at(j)-'0';
      if(state==1)
     { last_state=X.at(j-1)-'0';
       if(last_state==1) j=n;
      }

      if(j==n-1)
      { state=X.at(j)-'0'; last_state=X.at(0)-'0';
        if(state==1 && last_state==1) j=n;}

    if(j==n)
    { if(X==one_zero) shuff.push_back(X); }

    if(j==n-1) shuff.push_back(X);
  }
}

for(auto& a:shuff)
{
  for(int m=0; m<a.length() ;m++)
  {  if(m<=a.length()-2){ if(a.at(m)=='1') {swap(currentstring.at(m),currentstring.at(m+1));}  }
     if(m==a.length()-1){ if(a.at(m)=='1') {swap(currentstring.at(m),currentstring.at(0));}   }
   }

  panel.push_back(currentstring);
  currentstring=thestring.substr(0,n);
}
char t,t1;
int item=n-1;  
for(item; item>=0 ; item--)
{
  if(item==n-1) {t=currentstring.at(item);currentstring.at(item)=currentstring.at(item-1);}
  if(item>0 && item<n-1) currentstring.at(item)=currentstring.at(item-1);
  if(item==0) currentstring.at(0)=t;
}

panel.push_back(currentstring);
return panel;
 }



double  Arrangements::panel_count(int n){
  double c1=1.0,c2=2.0;
  double tot=2.0;
  if(n==1)return c1;
  if(n==2)return c2;
  for(int i=3;i<=n;i++){
    tot=c2; 
    c2=c1+tot;
    c1=tot;
  }
  return c2;
}

double  Arrangements::dinner_count(int n){

  double t1=1,t2=2,t3=6,t4=9,tot;
  if(n==1)return t1;
  if(n==2)return t2;
  if(n==3)return t3;
  if(n==4)return t4;

  for(int i=5;i<=n;i++)
  {
    tot=t4; 
    t4=t3+tot-2;
    t3=tot;
  }
  return t4;
}


int main()
{
  Arrangements s1("1234567");
  std::vector<string> v;
  std::vector<string> v2;
  std::vector<string> v3;
  v=s1.panel_shuffles(6);
  v2=s1.panel_shuffles(5);
  v3=s1.panel_shuffles(4);
  cout<<"the result of panel_shuffles(6 person):";  //test the output of panel_shuffles
  for (int i = 0; i < v.size(); ++i)
  {
    cout<<v[i]<<" ";
  }
  cout<<"\n";
  cout<<"the result of panel_shuffles2(5 person):";  //test the output of panel_shuffles
  for (int i = 0; i < v2.size(); ++i)
  {
    cout<<v2[i]<<" ";
  }
  cout<<"\n";
  cout<<"the result of panel_shuffles3(4 person):";  //test the output of panel_shuffles
  for (int i = 0; i < v3.size(); ++i)
  {
    cout<<v3[i]<<" ";
  }
  cout<<"\n";

  std::vector<string> v1;
  v1=s1.dinner_shuffles(6);
  cout<<"the result of dinner_shuffles:";  //test the output of dinner_shuffles
  for (int i = 0; i < v1.size(); ++i)
  {
    cout<<v1[i]<<" ";
  }
  cout<<"\n";


  double pcout;
  cout<<"the result of the panel_count:"; //test the output of panel_count
  pcout=s1.panel_count(6);
  cout<<pcout<<"\n";

  double pcout1;
  cout<<"the result of the dinner_count:"; //test the output of dinner_count
  pcout1=s1.dinner_count(6);
  cout<<pcout1<<"\n";
  return 0;
}





