#ifndef MODULESAVRAMENKO_H_INCLUDED
#define MODULESAVRAMENKO_H_INCLUDED

using namespace std;

double s_calculation(double x, double y, double z);
int waveGrade(double waveHeight);
double fahrenheitToCelsius(double tF);
int processBinary(unsigned int N);
bool processTask10_1(const string& inputFile, const string& outputFile, const string& authorInfo);
bool processTask10_2(const string& inputFile);
bool processTask10_3(const string& outputFile, double x, double y, double z, int b);

#endif // MODULESAVRAMENKO_H_INCLUDED
