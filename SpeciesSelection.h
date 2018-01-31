/* 
 * File:   SpeciesSelection.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:53
 */

#ifndef SPECIESSELECTION_H
#define SPECIESSELECTION_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SpecRTGraph;

class SpeciesSelection {
public:
   SpeciesSelection();
   ~SpeciesSelection();
   void main(vector<string>);
   void processLine(string, SpecRTGraph*, int);
private:
   vector<int> stringToVector(string);
   string intToString(int);
   void readFile(string, SpecRTGraph*, int);
};

istream& getlineSafe(istream& is, string& t);
#endif /* SPECIESSELECTION_H */

