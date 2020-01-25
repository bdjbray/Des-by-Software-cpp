#include <string>
#include <iostream>
#include <vector>
using std::string;
using namespace std;
bool is_happy(int x){
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


int main(){
bool answ=is_happy(20);
std::cout<<answ<<'\n';
}