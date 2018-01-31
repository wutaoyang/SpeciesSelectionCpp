/* 
 * File:   SpecSetFamily.cpp
 * Author: mre16utu
 * 
 * Created on 15 January 2018, 14:53
 */


#include <vector>
#include <string>
#include <algorithm>
#include "SpecSetFamily.h"
#include "SpecSet.h"
using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//int numSetsLimit;
//vector<SpecSet*> ssf;

SpecSetFamily::SpecSetFamily() {
   numSetsLimit = -1; //-1 denotes no limit
}

SpecSetFamily::~SpecSetFamily() {
}

int SpecSetFamily::getNumSetsLimit() {
   return numSetsLimit;
}

void SpecSetFamily::setNumSetsLimit(int numSetsLimit) {
   this->numSetsLimit = numSetsLimit;
}

SpecSet* SpecSetFamily::getMaxSpecSetBySensitivity() {
   sortSsf();
   return ssf[ssf.size() - 1];
}

int SpecSetFamily::size() {
   return ssf.size();
}

SpecSet* SpecSetFamily::get(int index) {
   return ssf[index];
}

void SpecSetFamily::sortBySensitivity() {
   sortSsf();
}

void SpecSetFamily::addSpecSet(SpecSetFamily* inSSFamily) {
   for (SpecSet *spSet : inSSFamily->ssf) {
      addSpecSet(spSet);
   }
}

bool SpecSetFamily::addSpecSet(SpecSet* inSS) {
   //check no set in the family is a subset of inSet
   for (SpecSet *spSet : ssf) {
      if (spSet->isEqualTo(inSS)) {
         return false;
      }
   }
   ssf.push_back(inSS);

   //when no limit or the limit of size has not reached
   if (numSetsLimit < 0 || ssf.size() < numSetsLimit) {
      return true;
   }

   //when the limit reached, removed the one with largest sensitivity
   sortBySensitivity();
   int lastEleIndex = ssf.size() - 1;
   if (lastEleIndex >= 0) {
      auto i = find(begin(ssf), end(ssf), ssf[lastEleIndex]);
      ssf.erase(i);
   }
   return true;
}

string SpecSetFamily::toString() {
   sortSsf();
   string outStr = "[";
   for (SpecSet *spSet : ssf) 
   {
        outStr.append(spSet->toString());
   }

   // trim off last comma if set not empty
   if (outStr.length() > 1) {
	   outStr = outStr.substr(0, outStr.size() - 1);
   }

   outStr.append("]");
   return outStr;
}

void SpecSetFamily::sortSsf() {
   sort(ssf.begin(), ssf.end(), sortFunctionSpecSet);
}

//bool sortFunctionSpecSet(SpecSet* i, SpecSet* j) { 
//   return i->compareTo(j) >= 0; 
//}