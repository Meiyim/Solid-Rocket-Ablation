#ifndef COMMON_PARA
#define COMMON_PARA
#include "cstddef"
//grid size
const size_t IX=100;
const size_t IY=5;
const double LENGTH=0.5;
const double HEIGHT=0.1;
const double DUARATION=120.0;
const size_t N_STEP=1;
//physical parameters
const double ROU_BASE=1.0;
const double ROU_CARBON=0.5;
const double LUMDA_BASE_N=1.0;
const double LUMDA_BASE_P=1.0;
const double LUMDA_CARBON_P=0.5;
const double LUMDA_CARBON_N=0.5;
//chemical parameters
const double DELTA_H_THERMOLYSIS=0.0;
const double DELTA_H_CARBONIZE=0.0;
const double DELTA_ROU_THERMOLYSIS= ROU_BASE-ROU_CARBON;
#endif
