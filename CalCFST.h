#ifndef _CALCFST
#define _CALCFST
#include <iostream>
#include <vector>
#include "HarmonySearch.h"
#include "XYcyclic.h"
#include "CFSTana.h"

class CalCFST : public HarmonySearch
{
public:
    CalCFST(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange,
                    Eigen::ArrayXd fixedVar, double interval,
                    XYcyclic targetXY);
    CalCFST();
    ~CalCFST();

    double objFun(Eigen::ArrayXd vector) override;
    
    XYcyclic targetXY;
    Eigen::ArrayXd fixedVar;
    double interval;

    XYcyclic analysis(Eigen::ArrayXd vector);
    double fitness(XYcyclic curXY);
    
    
};

#endif
