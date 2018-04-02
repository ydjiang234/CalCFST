#ifndef _CALCFST
#define _CALCFST
#include <iostream>
#include "HarmonySearch.h"
#include "XYcyclic.h"
#include "CFSTana.h"

class CalCFST : public HarmonySearch
{
public:
    CalCFST(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange,
                    Eigen::ArrayXd fixedVar,
                    XYcyclic targetXY);
    CalCFST();
    ~CalCFST();

    double objFun(Eigen::ArrayXd vector);
    
    XYcyclic targetXY;
    Eigen::ArrayXd fixedVar;
    
    
};

#endif
