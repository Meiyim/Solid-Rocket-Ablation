#include"ControVolumns.h"
#include"CommonParameters.h" 
#include <string>
#include <vector>
using namespace std;
string gridArrange(vector< vector<handle> >& CVs) {
	std::cout<<"Now Initializing Grid"<<std::endl;
	int i,j;
	double dx[IX][IY];
	double dy[IX][IY];
	double iniT=100.0; //设置初始迭代温度值

	//cv *(*pointer)[IY-1]; 这是指向指针数组的指针
	for(i=0;i!=IX;++i)
		for(j=0;j!=IY;++j){
			dx[i][j]= LENGTH/(2.0*IX);
			dy[i][j]= HEIGHT/(2.0*IY);
		}	

	CVs.resize(IX,vector<handle>(IX,0));
	double nowx=0.0;  //对于均匀正方形网格，适用以下网格初始化方法。
	for(i=0;i!=IX;++i){
		nowx+=dx[i][0];
		double nowy=0.0;
		for(j=0;j!=IY;++j){
			double vol=(2*dx[i][j])*(2*dy[i][j]);
			nowy+=dy[i][j];
			cout<<"now processing"<<i<<"	"<<j<<endl;
			CVs[i][j]= new cv(  nowx, nowy , ROU_BASE, vol, 
											LUMDA_BASE_P, LUMDA_BASE_N, iniT);
			cout<<"debug"<<endl;
			nowy+=dx[i][j];
		}
		nowx+=dy[i][0];
	}
	return "Grid Initialization Complete";
}
