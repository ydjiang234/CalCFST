#ifndef _CALCFST
#define _CALCFST
#include <iostream>
#include "HarmonySearch.h"

class CalCFST : public HarmonySearch
{
public:
    CalCFST(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange);
    CalCFST();
    ~CalCFST();

    double objFun(Eigen::ArrayXd vector);
};

#endif
