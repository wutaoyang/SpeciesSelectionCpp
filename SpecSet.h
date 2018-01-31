/* 
 * File:   SpecSet.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:24
 */

#ifndef SPECSET_H
#define SPECSET_H

#include "Species.h"
#include "SpecSetFamily.h"
#include <vector>
#include <string>
#include <unordered_set>//<ext/hash_set>
using namespace std;
//using namespace __gnu_cxx;

class SpecSet {
public:
   SpecSet();
   SpecSet(vector<Species*>);
   ~SpecSet();
   bool contains(Species*);
   void addSpecies(Species*);
   void addSpecies(unordered_set<Species*>);
   int size();
   bool isEqualTo(SpecSet*);
   bool isSubSetOf(SpecSet*);
   bool isSuperSetof(SpecSet*);
   int getSumSensitivity();
   double getMeanSensitivity();
   int getMaxSensitivity();
   SpecSetFamily* extendToFamily(vector<Species*>, int, int);
   bool increaseToSize(vector<Species*>, int);
   int compareTo(SpecSet*);
   string toString();
private:
   unordered_set<Species*> spSet;
   bool containsAll(unordered_set<Species*>, unordered_set<Species*>);
   
};

bool sortFunctionSpecSet(SpecSet*, SpecSet*);

#endif /* SPECSET_H */

