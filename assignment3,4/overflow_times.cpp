//Copyright 2019 Dingjun Bian braybian@bu.edu

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

int main(){
clock_t start0,end0;  //int8 
uint16_t ui1=1;
start0=clock();
   while(ui1>0){
    ui1++;
  }
end0=clock();
long double time0=(long double)(end0-start0);
long double mid0=0xffff/0xff;
//time0=time0/mid0*1000;
time0=time0/pow(2,8)*1000;
cout << "estimated int8 time (nanoseconds): "<<time0<<endl;


clock_t start1,end1;    //int16
uint16_t ui2=1;
start1=clock();
  while(ui2>0){
    ui2++;
  }
end1=clock();
long double time1=(long double)(end1-start1);
cout << "measured int16 time (microseconds): "<<time1<<endl;


clock_t start2,end2;    //int32
uint16_t ui3=1;
start2=clock();
  while(ui3>0){
    ui3++;
  }
end2=clock();
long double time2=(long double)(end2-start2);
long double mid1=0xffffffff/0xffff;
//time2=mid1*time2*0.00001;
time2=time2*pow(2,8)*0.00001;
cout << "estemated int32 time (seconds): "<<time2<<endl;


clock_t start3,end3;    //int64
uint16_t ui4=1;
start3=clock();
  while(ui4>0){
    ui4++;
  }
end3=clock();
long double time3=(long double)(end3-start3);
long double mid2=0xffffffffffffffff/0xffff;
//time3=mid2*time3*3.17098e-14;
time3=time3*pow(2,16)*3.17098e-14;
cout << "estemated int64 time (years): "<<time3<<endl;

}