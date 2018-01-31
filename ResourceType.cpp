/*
 * Species Selection
 * 
 * Represents a column in the resource requirement matrix. Note that the use of 
 * indicator in the algorithm is different than that in the paper. That is, in 
 * the paper an indicator set refers to a set of species while here indicators mean
 */

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "ResourceType.h"
#include "Species.h"
using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//int id;
//vector<Species*> specList;

ResourceType::ResourceType() {
}

ResourceType::ResourceType(int id) {
   this->id = id;
}

ResourceType::~ResourceType() {
}

bool ResourceType::noSpecies() {
   return specList.empty();
}

void ResourceType::setID(int id) {
   this->id = id;
}

int ResourceType::getID() {
   return id;
}

int ResourceType::numSpecies() {
   return specList.size();
}

void ResourceType::addSpecies(Species* inSpec) {
   if (inSpec->isIn(specList) == false)
      specList.push_back(inSpec);
}

bool ResourceType::adjacentTo(Species* inSpec) {
   return inSpec->isIn(specList);
}

Species* ResourceType::getFirstSpecies() {
   return specList[0];
}

/**
 * @param otherRT  A second resource type  to be compared
 * @return The number of species associated with the current
 * resource type minus that of otherRT.
 */
int ResourceType::compareTo(ResourceType* otherRT) {
	int compare = numSpecies() - otherRT->numSpecies();
	if (compare != 0)
	{
		return compare;
	}
	return this->id - otherRT->id;
}

/**
 * @param otherRT A second resource type to be compared
 * @return True if the current resource type is redundant w.r.t otherRT, 
 *          that is, all species associated with otherRT are also 
 *         associated with the current one.
 */
bool ResourceType::isCoveredBy(ResourceType* otherRT) {
   return containsAll(specList, otherRT->specList);
}

string ResourceType::toString() {

   int numSpec = numSpecies();
   
   ostringstream oss;
   oss << id << ":" << numSpec;
   string specStr = oss.str();
   
   
//   specStr.append(id);
//   specStr.append(":");
//   specStr.append(numSpec);
   return specStr;
}

// returns true if one contains all elements in two
bool ResourceType::containsAll(vector<Species*> one, vector<Species*> two) {
	if (one.size() < two.size()) {
		return false;
	}
   sort(one.begin(), one.end(), sortFunctionSpeciesID);
   sort(two.begin(), two.end(), sortFunctionSpeciesID);
   return includes(one.begin(), one.end(), two.begin(), two.end(), sortFunctionSpeciesID);
}

// returns true if this ResourceType is in list
bool ResourceType::isIn(vector<ResourceType*> list) {
   return find(list.begin(), list.end(), this) != list.end();
}

bool sortFunctionRT(ResourceType* i, ResourceType* j) { 
	int compare = j->compareTo(i);
    return compare >= 0;
}