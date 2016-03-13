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
public:
    string myDataFile;
    int numberOfParticles;
    CSDataReader(); // constructor
    int readParticles(double **particleList);
    int readDataFor(const std::string& theString);
    void readValues(const string& propertyString, double *valueList);


};



#endif //VOROCPP_CSDATA_H
