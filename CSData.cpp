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

    cout << "In readDataFor " << endl;


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

    return 0;
}

double **CSDataReader::readParticles() {
    string line = "";
    int num=0; // line counter
    int start = CSDataReader::readDataFor("PARTICLES");
    int end = CSDataReader::readDataFor("ENDPARTICLES");
    int numberOfParticles = end - start - 1;
    cout << "line sayısı: " << numberOfParticles << endl;
    particleList = new double *[numberOfParticles];
    for (int i = 0; i < numberOfParticles; i++) {
        particleList[i] = new double[3]; // herbir array için 3 verilik yer al
    }
    int particleCounter = 0;
    ifstream myFile(myDataFile);
    
    if(myFile.is_open()) {
        while(getline(myFile, line)) { // I changed this, see below
            cout << "----" << line << endl;
            num++;
            if (num>start && num<end) {
                cout << num << endl;
                istringstream iss(line);
                cout << line << endl;
                int n = 0;
                while (iss) {
                    string sub;
                    iss >> sub;
                    if (sub.length()>0) {
                        cout << particleCounter << " n = " << n << " and " << sub << endl;
                        particleList[particleCounter][n] = stoi(sub);
                        cout << particleList[particleCounter][n] << endl;
                        n++;
                    }
                }
                particleCounter++;

            }
            else if (num == end)
            {
                cout << "end of particles" << endl;

                for (int i = 0; i < 25; i++) {
                    for (int j = 0; j < 3; j++) {
                        cout << particleList[i][j] << endl;
                    }
                }
                return particleList;
            }
        }
    }


    return nullptr;
}

void CSDataReader::test() {
    string s("Somewhere down the road");
    istringstream iss(s);

    do
    {
        string sub;
        iss >> sub;
        cout << "Substring: " << sub << endl;

    } while (iss);
}


