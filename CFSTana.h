#ifndef _CFSTANA_H
#define _CFSTANA_H
#include <iostream>
#include "matCFSTdet.h"
#include "Dense"

class CFSTana : public matCFSTdet
{
public:
    CFSTana(double E, double f1, double f2, double b1, double b2, double revRatio,
            double Dfactor1, double Efactor1, double Rfactor1,
            double Dfactor2=1.0, double Efactor2=1.0, double Rfactor2=1.0);
    CFSTana();
    ~CFSTana();
    void analysis(Eigen::ArrayXd loadingProtocol, double interval);

    std::vector<double> Xresults, Yresults;
    Eigen::ArrayXd loadingProtocol, xout, yout;

private:
    void analysisOneStep(double target, double interval);
    void reset();
    void convertResults();


};

#endif
