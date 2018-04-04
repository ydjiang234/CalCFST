#include "CalCFST.h"
#include "CFSTana.h"

CalCFST::CalCFST(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange,
                    Eigen::ArrayXd fixedVar, double interval,
                    XYcyclic targetXY) : HarmonySearch(insRange, hms, hmcr, par, fwRatio, isForceRange)
{
    this->fixedVar = fixedVar;
    this->interval = interval;

    this->targetXY = targetXY;
    this->targetXY.getTurning();
    this->targetXY.getHalfCycleEnergy();
}

CalCFST::CalCFST() : HarmonySearch() {}

CalCFST::~CalCFST() {}

double CalCFST::objFun(Eigen::ArrayXd vector)
{
    double out;
    XYcyclic curXY = this->analysis(vector);
    out = this->fitness(curXY);

    return out;
}

XYcyclic CalCFST::analysis(Eigen::ArrayXd vector)
{
    double E, f1, f2, b1, b2, revRatio;
    double Dfactor1, Efactor1, Rfactor1;
    double Dfactor2, Efactor2, Rfactor2;

    Dfactor1 = 1E-6;
    Efactor1 = 1E-6;
    Rfactor1 = 1E-6;

    Dfactor2 = 1;
    Efactor2 = 1;
    Rfactor2 = 1;

    revRatio = 0.1;

    E = this->fixedVar[0];
    f1 = this->fixedVar[1];
    f2 = this->fixedVar[2];
    b1 = this->fixedVar[3];
    b2 = this->fixedVar[4];
    revRatio = this->fixedVar[5];

    Dfactor1 = vector(0);
    Efactor1 = vector(1);
    Rfactor1 = vector(2);
    Rfactor2 = vector(3);

    CFSTana cfst = CFSTana(E, f1, f2, b1, b2, revRatio,
                           Dfactor1, Efactor1, Rfactor1,
                           Dfactor2, Efactor2, Rfactor2);
    cfst.analysis(this->targetXY.turnX, this->interval);
    XYcyclic curXY = XYcyclic(cfst.xout, cfst.yout);
    return curXY;
}

double CalCFST::fitness(XYcyclic curXY)
{
    double out;
    double dY, dEnergy;
    Eigen::ArrayXd Y;

    curXY.getTurning();
    curXY.getHalfCycleEnergy();

    unsigned int turnNum = std::min(curXY.turnID.size(), this->targetXY.turnID.size());
    dY = (this->targetXY.turnY.head(turnNum) - curXY.turnY.head(turnNum)).pow(2).sum() / turnNum;
    dEnergy = (this->targetXY.halfCycleEnergy.head(turnNum-1) - curXY.halfCycleEnergy.head(turnNum-1)).pow(2).sum() / turnNum;
    out = -1 * std::sqrt(dY + dEnergy) / 2;
    return out;
}
