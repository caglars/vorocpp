#include <iostream>
#include "voro++.hh"
#include "CSCalculation.h"
#include "CSData.h"

using namespace voro;
using namespace std;


int main() {
    // insert code here...
    std::cout << "Hello, World!\n";





    Calculation myCalculator;
    myCalculator.buildModel();
    myCalculator.calculate();
    // insert code here...
    std::cout << "Hello, World Again!\n";


    return 0;

}

void incompressibleFlow() {


}