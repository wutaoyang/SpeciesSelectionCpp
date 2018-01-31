/*
 * Species Selection
 * 
 * Represents the collection of 'irreducible' dominating species sets that is, 
 * those species sets covering all resources types while any proper subset does not
 */

#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "MinSpecSetFamily.h"
#include "SpecSet.h"

using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

// vector<SpecSet*> ssf;

MinSpecSetFamily::MinSpecSetFamily() {
}

MinSpecSetFamily::~MinSpecSetFamily() {
}

int MinSpecSetFamily::size() {
   return ssf.size();
}

SpecSet* MinSpecSetFamily::get(int index) {
   return ssf[index];
}

void MinSpecSetFamily::sortBySensitivity() {
   sort(ssf.begin(), ssf.end(), sortFunctionSpecSet);
}

//bool sortFunctionSpecSt(SpecSet* i, SpecSet* j) { 
//   return i->compareTo(j) >= 0; 
//}

bool MinSpecSetFamily::addSpecSet(SpecSet* inSet) {

   //check no set in the family is a subset of inSet
   for (SpecSet *spSet : ssf) {
      if (spSet->isSubSetOf(inSet))
         return false;
   }

   //remove the sets in the family that are a
   //superset of inSet
   vector<SpecSet*> tmpList;
   for (SpecSet *spSet : ssf) {
      if (spSet->isSuperSetof(inSet))
         tmpList.push_back(spSet);
   }

   removeAll(ssf, tmpList); // replaces java ssf.removeAll(tmpList)
   ssf.push_back(inSet);
   return true;
}

string MinSpecSetFamily::toString() {
   sortBySensitivity();
   string outStr = "";
   //outStr.append(ssf);
   
   // TODO - need to improve format!
   
   for (SpecSet *spSet : ssf) 
   {
        outStr.append(spSet->toString());
   }
   return outStr;
}

//https://stackoverflow.com/questions/28977799/c-equivalent-to-java-arraylist-method-removeall?rq=1
void MinSpecSetFamily::removeAll(vector<SpecSet*>& vec, const vector<SpecSet*>& toRemove) {
//void MinSpecSetFamily::removeAll(vector<SpecSet*> vec, vector<SpecSet*> toRemove) {
   set<SpecSet*> st(toRemove.begin(), toRemove.end());
   size_t newSize = 0;
   for (size_t i = 0; i < vec.size(); ++i) {
      if (0 == st.count(vec[i])) {
         vec[newSize++] = vec[i];
      }
   }
   vec.resize(newSize);
}