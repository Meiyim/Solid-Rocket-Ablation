#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "GridDisplay.h"

using namespace std;
string gridDisplay(const  vector<triple>&  arrs, const  int inputi, const  int inputj,  string title) {
	cout<<"Now plotting ..."<<endl;
	static bool isFirstTime=true;
	ofstream outfile;
	if(isFirstTime=true){
		outfile.open((title+".dat").c_str(),ofstream::out);
		outfile<<"TITLE="<<title<<endl;
		outfile<<"VARIABLES= \"x\",\"y\",\""<<title<<"\""<<endl;
		isFirstTime= false;
	}else{
		outfile.open((title+".dat").c_str(),ofstream::app);
	}
	if(!outfile){
		cerr<<"error: unable to open output file:     "<<title<<endl;
		return"Grid Display failed";
	}

	outfile<<"ZONE F=POINT i="<<inputj<<" j="<<inputi<<endl;
	for (vector< triple >::const_iterator it= arrs.begin();
		it!= arrs.end(); ++it){
			outfile<<it->a<<"    "<<it->b<<"    "<<it->c<<endl;
	}
	outfile.close();
	outfile.clear();
	return"Grid Display Complete.";
}
