//
// Created by Caglar Sinayuc on 11/02/16.
//

#ifndef VOROCPP_CSCALCULATION_H
#define VOROCPP_CSCALCULATION_H

#include <iostream>
#include "voro++.hh"
using namespace voro;

class Calculation {
    public:
        int numberOfParticles;
        double *pressure;
        double *rightHandSide;
        double **coefficient;
        double *positionX;
        double *positionY;
        double *positionZ;
        double *cellVolume;
        void buildModel();
        void simRun(container& aCon);
        void calculate();
        double distance(double x1, double y1, double z1, double x2, double y2, double z2);

};


#endif //VOROCPP_CSCALCULATION_H
