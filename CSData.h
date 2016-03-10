//
// Created by Caglar Sinayuc on 10/03/16.
//

#ifndef VOROCPP_CSDATA_H
#define VOROCPP_CSDATA_H

#include <iostream>
#include "voro++.hh"
using namespace voro;

class CSDataReader {
public:
    double * readParticles();
    int readDataFor(const std::string& theString);


};



#endif //VOROCPP_CSDATA_H
