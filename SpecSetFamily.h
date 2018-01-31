/* 
 * File:   SpecSetFamily.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:53
 */

#ifndef SPECSETFAMILY_H
#define SPECSETFAMILY_H

//#include "SpecSet.h"
#include <vector>
#include <string>
using namespace std;

class SpecSet;

class SpecSetFamily {
protected:
   vector<SpecSet*> ssf;
public:
   SpecSetFamily();
   ~SpecSetFamily();
   int getNumSetsLimit();
   void setNumSetsLimit(int);
   SpecSet* getMaxSpecSetBySensitivity();
   int size();
   SpecSet* get(int);
   void sortBySensitivity();
   void addSpecSet(SpecSetFamily*);
   bool addSpecSet(SpecSet*);
   string toString();
private:
   void sortSsf();
   int numSetsLimit;
   
};

//bool sortFunctionSpecSet(SpecSet*, SpecSet*);

#endif /* SPECSETFAMILY_H */

