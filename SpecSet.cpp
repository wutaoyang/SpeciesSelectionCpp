/* 
 * File:   SpecSet.cpp
 * Author: mre16utu
 * 
 * Created on 15 January 2018, 14:24
 */


#include <unordered_set>//<ext/hash_set>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <iostream>
#include <algorithm>
#include "CombSize.h"
#include "CombSubSet.h"
#include "SpecSet.h"
#include "Species.h"
#include "SpecSetFamily.h"
using namespace std;
//using namespace __gnu_cxx;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//hash_set<Species*> spSet;

SpecSet::SpecSet() {
}

SpecSet::SpecSet(vector<Species*> specList) {
   for (Species *spec : specList) {
      addSpecies(spec);
   }
}

SpecSet::~SpecSet() {
}

bool SpecSet::contains(Species* spec) {
   return spSet.find(spec) != spSet.end();
}

void SpecSet::addSpecies(Species* spec) {
   spSet.insert(spec);
}

void SpecSet::addSpecies(unordered_set<Species*> inSpecSet) {
   for (Species *inSpec : inSpecSet) {
      spSet.insert(inSpec);
   }
}

int SpecSet::size() {
   return spSet.size();
}

bool SpecSet::isEqualTo(SpecSet* other) {
   if (size() == other->size() && containsAll(spSet, other->spSet))
      return true;
   else
      return false;
}

bool SpecSet::isSubSetOf(SpecSet* other) {
   return containsAll(other->spSet, spSet);
}

bool SpecSet::isSuperSetof(SpecSet* other) {
   return containsAll(spSet, other->spSet);
}

// returns true if one contains all elements in two
bool SpecSet::containsAll(unordered_set<Species*> one, unordered_set<Species*> two) {
   if(two.size() > one.size())
   {
      return false;
   }
   
   for(Species *species : two)
   {
      if(one.find(species) == one.end())
      {
         return false;
      }
   }
   return true;
   
//   sort(one.begin(), one.end());
//   sort(two.begin(), two.end());
//   return includes(one.begin(), one.end(), two.begin(), two.end());
}

int SpecSet::getSumSensitivity() {
   int result = 0;
   for (Species *sp : spSet) {
      result += sp->getSensitivity();
   }
   return result;
}

double SpecSet::getMeanSensitivity() {
   if (spSet.empty()) {
      return 0;
   }
   return this->getSumSensitivity()*1.0 / spSet.size();
}

int SpecSet::getMaxSensitivity() {
   if (spSet.empty()) {
      cout << "The species set contains no elements!";
   }

   int result = 0;

   for (Species *sp : spSet) {
      int sensitivity = sp->getSensitivity();
      if (result < sensitivity) {
         result = sensitivity;
      }
   }
   return result;
}

//bool sortFunctionSpecies(Species *i, Species *j) { 
//   return i->compareTo(j) >= 0; 
//}

SpecSetFamily* SpecSet::extendToFamily(vector<Species*> inSpecList, int targetSetSize, int targetFamilyNum) {

   SpecSetFamily *result = new SpecSetFamily();

   //find the elements that are not in the current set
   vector<Species*> tmpSpecList;
   for (Species *sp : inSpecList) {
      if (!contains(sp))
         tmpSpecList.push_back(sp);
   }

   sort(tmpSpecList.begin(), tmpSpecList.end(), sortFunctionSpecies);

   int extNum = targetSetSize - size();
   if (extNum == 0) {
      result->addSpecSet(this);
      return result;
   }

   //get the combinatorical size and subset indicator
   CombSize *rangSize = new CombSize(extNum, targetFamilyNum);
   int maxNum = rangSize->getSize();

   if (maxNum > tmpSpecList.size()) {
      cout << "Something is wrong about tmpSpecList";
   }

   CombSubSet *rangSets = new CombSubSet(extNum, maxNum);
   vector<vector<int>> indexSets = rangSets->getSubSets();

   for (vector<int> curList : indexSets) {
      SpecSet *tmpSet = new SpecSet();
      tmpSet->addSpecies(spSet);
      for (int index : curList) {
         Species *tmpSpecies = tmpSpecList[index];
         tmpSet->addSpecies(tmpSpecies);
      }
      result->addSpecSet(tmpSet);
   }
   return result;
}

/**
 * 
 * @param inSpecList  A set of species to be added into the current family
 * @param targetSize  The number of members in the family aimed to get
 * @return true iff the current family has been extended to the target size
 */
bool SpecSet::increaseToSize(vector<Species*> inSpecList, int targetSize) {
   if (size() > targetSize) return false;
   if (size() == targetSize) return true;

   for (Species *spec : inSpecList) {
      this->addSpecies(spec);
      if (this->size() == targetSize) {
         return true;
      }
   }
   return false;
}

int SpecSet::compareTo(SpecSet* other) {
   int curSen = this->getMaxSensitivity();
   int otherSen = other->getMaxSensitivity();
   if (curSen != otherSen)
      return curSen - otherSen;

   double curMean = this->getMeanSensitivity();
   double otherMean = other->getMeanSensitivity();

   if (curMean < otherMean) return -1;
   if (curMean == otherMean) return 0;

   return 1;
}

string SpecSet::toString() {
//   string outStr = "";
//   outStr.append("\r\n");
//   outStr.append(this->getMaxSensitivity()).append(":");
   
   ostringstream oss;
   oss << "\n" << this->getMaxSensitivity() << ":";
   string outStr = oss.str();
   

   double meanSens = this->getMeanSensitivity();
   stringstream stream;
   stream << fixed << setprecision(2) << meanSens;
   string meanSensStr = stream.str();
   outStr.append(meanSensStr).append(":");
   
   outStr.append("[");
   for (Species *species : spSet) 
   {
        outStr.append(species->toString());
		outStr.append(", ");
   }
   outStr = outStr.substr(0, outStr.size() - 2);
   outStr.append("],");
   return outStr;
}

bool sortFunctionSpecSet(SpecSet* i, SpecSet* j) { 
   return j->compareTo(i) > 0; 
}