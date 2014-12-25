#include "ControVolumns.h"


thermolysisCV* upgrade( cv*p,const double& depth ){
	thermolysisCV*temp =new  thermolysisCV(*p, depth);
	delete p;
	return temp;
}
