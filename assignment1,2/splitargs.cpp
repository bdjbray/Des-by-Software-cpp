// Copyright 2019 Dingjun Bian braybian@bu.edu
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
int main(int argc, char** argv)
{
    for(int i=1;i < 5;i++)
    {
       cout<<*(argv+i)<<endl;
    }
    
    for(int i=5;i<(argc);i++){
        cerr<<*(argv+i)<<endl;
     }
    return 0;
}