#include<vector>
#include<iostream>
#include<string>
#include "ControVolumns.h"
using namespace std;
void func(){ 
	static bool bo= true;
	if (bo){
		bo=false;
		cout<<"it is true"<<endl;
	}else{
		cout<<"it is false now"<<endl;
	}
}
