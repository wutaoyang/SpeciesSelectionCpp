/*
 * ResourceType Species Selection
 * 
 * Represent a species, which is comparable according to their
 * sensitivities
 */


#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Species.h"
#include "ResourceType.h"
using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

string speciesName;
int reliance;
vector<ResourceType*> rtList;

Species::Species() {
}

Species::Species(string speciesName) {
   this->speciesName = speciesName;
}

Species::~Species() {
}

int Species::getSensitivity() {
   //to check reliance and sensitivity; todo
   if (reliance < 0) {
      cout << "The species has non-positive reliance";
   }
   return reliance * rtList.size();
}

/**
 * @param otherSpec Another species
 * @return the sensitivity of the current minus that of the otherSpec.
 */
int Species::compareTo(Species* otherSpec) {
   return this->getSensitivity() - otherSpec->getSensitivity();
}

string Species::getName() {
   return speciesName;
}

int Species::getReliance() {
   return reliance;
}

void Species::setReliance(int inRel) {
   this->reliance = inRel;
}

void Species::addResourceType(ResourceType* newInd) {
   if (newInd->isIn(rtList) == false) {
      rtList.push_back(newInd);
   }
}

//return true if the rticator in this object is used by other 
bool Species::isBelow(Species* other) {
   return containsAll(other->rtList, rtList);
}

string Species::toString() {
   string specStr = ""; //"Species: ");
   specStr.append(speciesName); //.append("\n");
   return specStr;
}

// returns true if this species is in specList
bool Species::isIn(vector<Species*> specList) {
   return find(specList.begin(), specList.end(), this) != specList.end();
}

// returns true if one contains all elements in two
bool Species::containsAll(vector<ResourceType*> one, vector<ResourceType*> two) {
   sort(one.begin(), one.end(), sortFunctionRT);
   sort(two.begin(), two.end(), sortFunctionRT);
   return includes(one.begin(), one.end(), two.begin(), two.end(), sortFunctionRT);
}

bool sortFunctionSpecies(Species *i, Species *j) { 
	int compare = j->compareTo(i);
   return compare > 0;
}

bool sortFunctionSpeciesID(Species *i, Species *j) {
	int compare = (j->getName()).compare(i->getName());
	return compare > 0;
}
