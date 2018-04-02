#include "CalCFST.h"

CalCFST::CalCFST(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange,
                    Eigen::ArrayXd fixedVar,
                    XYcyclic targetXY) : HarmonySearch(insRange, hms, hmcr, par, fwRatio, isForceRange)
{
    this->fixedVar = fixedVar;
    
    this->targetXY = targetXY;
    this->targetXY.getTurning();
    this->targetXY.getHalfCycleEnergy();
}

CalCFST::CalCFST() : HarmonySearch() {}

CalCFST::~CalCFST() {}

double CalCFST::objFun(Eigen::ArrayXd vector)
{
    double out;
    double E, f1, f2, b1, b2, revRatio;
    double Dfactor1, Efactor1, Rfactor1;
    double Dfactor2, Efactor2, Rfactor2;
    
    Dfactor1 = 1E-6;
    Efactor1 = 1E-6;
    Rfactor1 = 1E-6;
    
    Dfactor2 = 1E-6;
    Efactor2 = 1E-6;
    Rfactor2 = 1E-6;
    
    revRatio = 0.1;
    
    E = this->fixedVar[0];
    f1 = this->fixedVar[1];
    f2 = this->fixedVar[2];
    b1 = this->fixedVar[3];
    b2 = this->fixedVar[4];
    
    return out;
}