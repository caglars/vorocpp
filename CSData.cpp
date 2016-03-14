//
// Created by Caglar Sinayuc on 10/03/16.
//

#include "CSData.h"
#include <fstream>
#include <sstream>

using namespace std;

CSDataReader::CSDataReader () {
    myDataFile = "myDataFile.dat";
}


int CSDataReader::readDataFor(const string& theString) {
    ifstream myFile(myDataFile); //put your program together with this file in the same folder.
    string line="";

    if(myFile.is_open()){

        // num = line number where the input string is found
        unsigned int num = 0;
        while(getline(myFile, line)) { // I changed this, see below
            num++;
            if (theString.compare(line) == 0) {
                return num;
            }
        }
    }
    else {
        cout << "Error reading the file" << endl;
    }


    return 0;
}

void CSDataReader::readParticles(double **particleList) {
    string line = "";
    int num=0; // line counter
    int start = CSDataReader::readDataFor("PARTICLES");
    int end = CSDataReader::readDataFor("ENDPARTICLES");
    //numberOfParticles = end - start - 1;

    //particleList = new double *[numberOfParticles];
    //for (int i = 0; i < numberOfParticles; i++) {
    //    particleList[i] = new double[3]; // herbir particle için 3 verilik yer al
    //}
    int particleCounter = 0;

    ifstream myFile(myDataFile);

    // Start reading x, y and z coordinates of each particle
    if(myFile.is_open()) {
        while(getline(myFile, line)) { // I changed this, see below
            num++;
            if (num>start && num<end) {
                istringstream iss(line);
                int n = 0;
                while (iss) {
                    string sub;
                    iss >> sub;
                    if (sub.length()>0) {
                        particleList[particleCounter][n] = stod(sub);
                        n++;
                    }
                }
                particleCounter++;
            }
        }
    }
    else {
        cout << "Error reading the file" << endl;
    }

    //return numberOfParticles;

}

void CSDataReader::readValues(const string& propertyString, double *valueList) {
    ifstream myFile(myDataFile); //put your program together with this file in the same folder.
    string line="";
    int start = readDataFor(propertyString);
    int end = readDataFor("END"+propertyString);
    //int range = end - start - 1;
    int numberOfTimes = 0;
    int counter = 0;

    //valueList = new double[range];

    if(myFile.is_open()){

        // num = line number where the input string is found
        unsigned int num = 0;
        while(getline(myFile, line)) {
            num++;
            if (num>start && num<end) {
                istringstream iss(line);
                int n=0;
                while (iss) {
                    string sub;
                    iss >> sub;
                    if (sub.length()>0) {
                        n=sub.find('*');

                        if (n!=string::npos) {
                            cout << "* found at: " << n << '\n';
                            numberOfTimes = stoi(sub.substr (0,n));
                            cout << numberOfTimes << endl;
                            for (int i = 0; i < numberOfTimes; ++i) {
                                cout << sub.substr(n+1) << endl;
                                valueList[counter] = stod(sub.substr(n+1));
                                counter++;
                                cout << counter << endl;
                            }
                        }
                        else {
                            cout << "no * found" << endl;
                            valueList[counter] = stod(sub);
                            counter++;
                            cout << counter << endl;
                        }
                    }
                    cout << "This is it " << sub << endl;
                }
            }
        }
    }
    else {
        cout << "Error reading the file" << endl;
    }


}



