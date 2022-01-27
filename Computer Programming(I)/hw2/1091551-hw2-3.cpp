#include<iostream>
using namespace std;
#include<stdio.h>
#include<math.h>
int main(){
    int number;
    int a,b,c;
    cout << "all Armstrong numbers of three digits:" << endl;
    for(number =100;number <=999;number++){
	  a= number /100;
      b= number /10%10;
      c= number %10;
      
      if(number ==pow(a,3)+pow(b,3)+pow(c,3)){
          
		  cout<<100*a+10*b+c<<" "; 
    	}
    }


	return 0;
}

