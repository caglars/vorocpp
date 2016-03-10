//
// Created by Caglar Sinayuc on 10/03/16.
//

#include "CSData.h"
#include <fstream>

using namespace std;


double *CSDataReader::readParticles() {
    double *particleList;
    return nullptr;
}

int CSDataReader::readDataFor(const string& theString) {
    string lookup = theString;
    ifstream myFile("dataFile.dat"); //put your program together with this file in the same folder.
    string line="";

    cout << "In readDataFor " << endl;


    //myFile.open("dataFileTest.txt");

    if(myFile.is_open()){
        //myFile.open("dataFileTest.txt");

        cout << "In is_open" << endl;

        // num = line number where the input string is found
        unsigned int num = 0;
        while(getline(myFile, line)) { // I changed this, see below
            num++;
            cout << line << endl;
            if (theString.compare(line) == 0) {
                cout << "compare ile bulduk " << num << endl;
                return num;
            }

        }

    }

    return 0;
}


