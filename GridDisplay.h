#ifndef GRID_DISPLAY
#define GRID_DISPLAY
#include<string>
#include<vector>
class triple{
public:
	double a,b,c;
};

extern std::string gridDisplay(const std::vector<triple>& arrs , const int inputi, const int inputj, std::string title);

#endif
