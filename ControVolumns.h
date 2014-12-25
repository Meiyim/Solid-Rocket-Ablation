#ifndef CONTRO_VOLUMN
#define CONTRO_VOLUMN
#include<string>
#include<iostream>
#include"CommonParameters.h"
using namespace std;

class cv {
public:
	cv(const double& xx, const double& yy, const double& rr,
	   const double& V, const double& LP, const double& LN,
	   const double& T):x(xx),y(yy),rou(rr),Vol(V),lumdaP(LP),lumdaN(LN),
	   Temp(T),Source(0.0) {}
	virtual string what(){ return "base volumn" ;}
	virtual cv* reaction(const double& dt) {return this; }

	virtual double getdepth(){ return 0.0; }
	virtual void heatBlockSource(const double& gradient, const double& mGas) {}
	void addS(const double& a) { Source+=a;}
	void decrR(const double& a) { rou-=a; }
	void addTemp(const double& t) { Temp+=t; }

	double getTemp() { return Temp; }
	double getV() { return Vol;}
	double getX() { return x; }
	double getY() { return y; }
	double getAN(const double& gridLength) { return 0.0; }
	double getAW(const double& gridLength) { return 0.0; }
	double getAS(const double& gridLength) { return 0.0; }
	double getAE(const double& gridLength) { return 0.0; }
	double getS() { 
		Source+=0.0;//由cv的热容量决定源的增量
		double temp= Source;
		Source=0.0; //get后立即清空source
		return temp;
		}
	virtual ~cv() {}
protected:
private:
	double Source;
	double rou;
	double Vol;
	double x,y;
	double lumdaP,lumdaN;
	double Temp;
};
class boundV{
public:
	boundV( cv* ori , const double& a, const double& b , const double& c , const double& d):
				  attach(ori), ch2o(a), cco2(b), pressure(c) ,heat(d){}
				  void applyBound(){ 
					  //计算边界热源
					  attach->addS(0.0);
				  }
private:
		cv* attach;
		double ch2o;
		double cco2;
		double pressure;
		double heat;
};
class emptyCV: public cv{
public:
	emptyCV(const cv&ori, const double& rr): cv(ori),remainReaction(rr) {}
	virtual string what(){ return "Empty Volumn" ;}
	virtual cv* reaction(const double& dt) { cout<<"unique call"<<endl;}
	virtual void heatBlockSource(const double& gradient, const double& mGas) {}
private:
	double remainReaction;
};
class carbonizeCV_Bound: public cv {
public:
	virtual string what(){ return "Carbonize Bound Volumn" ;}
	carbonizeCV_Bound(const cv& ori, const double& rr):
	  cv(ori),reactionDepth(rr), reactionRate(rr), setTime(0), ch2o(0.0), cco2(0.0), pe(0.0) {
		addS(reactionRate*DELTA_H_CARBONIZE);
		decrR(reactionRate*getV());
	  }
	virtual cv* reaction(const double& dt) { 
		reactionRate=carbonize(getTemp(), ch2o, cco2, pe,dt);
		reactionDepth+=reactionRate;
		decrR(reactionRate/getV());
		addS(DELTA_H_CARBONIZE*reactionRate);
		setTime=0;
		ch2o=0.0;
		cco2=0.0;
		pe=0.0;
	}
	void setPara(const double& ch, const double& cc, const double& p){
		++setTime;	
		ch2o=(ch2o*(setTime-1)+ch)/setTime;
		cco2=(cco2*(setTime-1)+cc)/setTime;
		pe=(pe*(setTime-1)+p)/setTime;
	}
	virtual void heatBlockSource(const double& gradient, const double& mGas) {
		addS( gradient*mGas );
	}
private:
	int setTime;
	double	 ch2o;
	double cco2;
	double pe; 
	double reactionDepth;
	double reactionRate;
	double carbonize(const double& T, const double& ch, const double& cc, const double& p, const double& t ){
		return 0.1; //here goes the formula
	}
							
};
class carbonizeCV: public cv {
public:
	virtual string what(){ return "Carbonize Volumn" ;}
	carbonizeCV ( const cv& ori ):
				cv(ori)  {}
	virtual cv* reaction(const double& dt) { return this;}

	cv* upgrade(const double& rr){
		carbonizeCV_Bound* temp=new carbonizeCV_Bound(*this, rr);
		delete this;
		return temp;
	}
	virtual void heatBlockSource(const double& gradient, const double& mGas) {
			addS(gradient*mGas);
	}
private:
};

class thermolysisCV: public cv {
public:
	double getdepth(){ return reactionDepth; }
	virtual string what(){ return "thermolysis volumn" ;}
	thermolysisCV(const cv& ori,const double& rr):
			  cv(ori),  reactionDepth(rr), reactionRate(rr) { 
					decrR(reactionRate/getV()); 
			  }
	virtual cv* reaction(const double& dt) { 
		reactionRate=thermolysis(reactionDepth,getTemp(),dt);
		reactionDepth+=reactionRate;
		decrR(reactionRate/getV()); //密度改变
		addS(DELTA_H_THERMOLYSIS*reactionRate);//源改变
		if(reactionDepth>=DELTA_ROU_THERMOLYSIS*getV()){
			cv*temp= new carbonizeCV(*this);
			delete this;
			return temp;
		}else{
			return this;
		}
	}
	virtual void heatBlockSource(const double& gradient, const double& mGas) {
		addS(gradient*mGas);
	}
private:
	double reactionDepth;
	double reactionRate;
	double thermolysis(const double& m,const double& T, const double&t){
		return 0.1;//here goes the formula
	}
};



extern thermolysisCV* upgrade(cv*, const double&);
typedef cv* handle;

#endif

