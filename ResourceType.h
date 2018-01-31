/* 
 * File:   ResourceType.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:52
 */



#ifndef RESOURCETYPE_H
#define RESOURCETYPE_H

//#include "Species.h"
#include <vector>
#include <string>

using namespace std;

class Species;

class ResourceType {
protected:
   int id;
   
public:
   vector<Species *> specList;
   ResourceType();
   ResourceType(int);
   ~ResourceType();
   bool noSpecies();
   void setID(int);
   int getID();
   int numSpecies();
   void addSpecies(Species*);
   bool adjacentTo(Species*);
   Species* getFirstSpecies();
   int compareTo(ResourceType*);
   bool isCoveredBy(ResourceType*);
   string toString();
   bool isIn(vector<ResourceType*> a);
private:
   bool containsAll(vector<Species*> a, vector<Species*> b);
};

bool sortFunctionRT(ResourceType *i, ResourceType *j);
#endif /* RESOURCETYPE_H */

