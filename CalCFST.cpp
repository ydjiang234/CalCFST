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
    Dfactor2 = vector(3);
    Rfactor2 = vector(4);

    CFSTana cfst = CFSTana(E, f1, f2, b1, b2, revRatio,
                           Dfactor1, Efactor1, Rfactor1,
                           Dfactor2, Efactor2, Rfactor2);

    cfst.analysisFull(this->targetXY.xdata);

    XYcyclic curXY = XYcyclic(cfst.xout, cfst.yout);

    return curXY;
}

double CalCFST::fitness(XYcyclic curXY)
{
    double out;
    double dY, dBB, dEnergy;

    curXY.getTurning();
    curXY.getHalfCycleEnergy();

    dY = (this->targetXY.ydata - curXY.ydata).pow(2).sum() / this->targetXY.num;
    dBB = (this->targetXY.turnY - curXY.turnY).pow(2).sum() / this->targetXY.turnY.size();
    //dEnergy = (this->targetXY.halfCycleEnergy - curXY.halfCycleEnergy).pow(2).sum() / (this->targetXY.halfCycleEnergy.size() - 1);
    out = -1 * std::sqrt((dY + dBB) / 2);
    return out;
}
