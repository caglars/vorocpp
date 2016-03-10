#include <iostream>
#include "voro++.hh"
#include "CSCalculation.h"
#include "CSData.h"

using namespace voro;
using namespace std;

int main() {
    // insert code here...
    std::cout << "Hello, World!\n";

    CSDataReader myReader;
    myReader.readDataFor("PARTICLES");

    Calculation myCalculator;
    myCalculator.calculate();
    // insert code here...
    std::cout << "Hello, World Again!\n";


    return 0;

}