#include "CFSTana.h"
#include <algorithm>

CFSTana::CFSTana(double E, double f1, double f2, double b1, double b2, double revRatio,
                             double Dfactor1, double Efactor1, double Rfactor1,
                             double Dfactor2, double Efactor2, double Rfactor2):
matCFSTdet(E, f1, f2, b1, b2, revRatio,
        Dfactor1, Efactor1, Rfactor1,
           Dfactor2, Efactor2, Rfactor2) {}

CFSTana::CFSTana() {}

CFSTana::~CFSTana() {}

void CFSTana::analysis(Eigen::ArrayXd loadingProtocol, double interval)
{
    this->reset();
    this->loadingProtocol = loadingProtocol;
    for (int i=0; i<this->loadingProtocol.size(); ++i) {
        this->analysisOneStep(this->loadingProtocol[i], interval);
    }
    this->convertResults();
}

void CFSTana::analysisFull(Eigen::ArrayXd loadingProtocol)
{
    this->reset();
    this->loadingProtocol = loadingProtocol;
    for (int i=0; i<loadingProtocol.size(); i++) {
        this->nextStress(loadingProtocol[i]);
        this->next();
        this->Xresults.push_back(this->strain);
        this->Yresults.push_back(this->stress);
    }
    this->convertResults();
}

void CFSTana::analysisOneStep(double target, double interval)
{
    if (this->strain <= target) {
        while (this->strain < target) {
            this->nextStress(this->strain + interval);
            this->next();
            this->Xresults.push_back(this->strain);
            this->Yresults.push_back(this->stress);
        }
    } else {
        while (this->strain > target) {
            this->nextStress(this->strain - interval);
            this->next();
            this->Xresults.push_back(this->strain);
            this->Yresults.push_back(this->stress);
        }
    }
}

void CFSTana::reset()
{
    this->Xresults.clear();
    this->Yresults.clear();
}

void CFSTana::convertResults()
{
    this->xout = Eigen::Map<Eigen::ArrayXd>(this->Xresults.data(), this->Xresults.size());
    this->yout = Eigen::Map<Eigen::ArrayXd>(this->Yresults.data(), this->Yresults.size());
}
