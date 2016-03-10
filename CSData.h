//
// Created by Caglar Sinayuc on 10/03/16.
//

#ifndef VOROCPP_CSDATA_H
#define VOROCPP_CSDATA_H

#include <iostream>
#include "voro++.hh"
using namespace voro;
using namespace std;

class CSDataReader {
    string myDataFile;
    double **particleList;
public:
    CSDataReader();
    double ** readParticles();
    int readDataFor(const std::string& theString);
    void test();


};



#endif //VOROCPP_CSDATA_H
