#include<iostream>
#include<vector>
#include<stdio.h>
#include<string>
#include"ControVolumns.h"
#include"CommonParameters.h" 
#include "GridDisplay.h"

extern string gridArrange(vector< vector<handle> >& CVs) ;
extern string thermalDiffusion(vector< vector<handle> >& CVs, double);
extern string  chemicalReaction( vector< vector<handle> >& CVs, double);
int main(int argc, char* argv[]) {
	int i,j;
	int t;
    
    vector<	vector<handle> > CVs;
    cout<<gridArrange(CVs)<<endl;;   //网格前处理
	
	double timeStep=DUARATION/ N_STEP;
	double nowTime=0.0;
	double Temps[1][IX][IY];
	for(t=0; t!=N_STEP; ++t){  // 时层推进循环
		cout<<"On Going nstep="<<t<<"    now time="<<nowTime<<"s"<<endl;		
		
		cout<< thermalDiffusion(CVs, timeStep)<<endl;  //Thermol Diffusion

		cout << chemicalReaction(CVs,timeStep) << endl; //Chemical Reaction

		for(i=0; i!=IX; ++i)
			for(j=0; j!=IY; ++j) {
				Temps[t][i][j]=CVs[i][j]->getTemp();
			}
		nowTime+=timeStep;
	}

	vector<triple> InStep; // 以下为后处理，画图
	for (i=0; i!=IX; ++i)
		for (j=0; j!=IY; ++j){
			triple tri;
			tri.a=  CVs[i][j]->getX();
			tri.b=  CVs[i][j]->getY();
			tri.c=  Temps[0][i][j]; 
			InStep.push_back(tri) ;  //将temps结果装进一个vectors里以便画图
		}
    cout<<gridDisplay(InStep ,IX,IY,"Temperature Distributions")<<endl; // Grid Display
	return 0;
}
