/* 
 * File:   Species.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:48
 */

#ifndef SPECIES_H
#define SPECIES_H

#include "ResourceType.h"
#include <vector>
#include <string>
using namespace std;

class Species {
public:
   vector<ResourceType*> rtList;
   Species();
   Species(string);
   ~Species();
   int getSensitivity();
   int compareTo(Species*);
   string getName();
   int getReliance();
   void setReliance(int);
   void addResourceType(ResourceType*);
   bool isBelow(Species*);
   string toString();
   bool isIn(vector<Species*>);
private:
   string speciesName;    
   int reliance;
   bool containsAll(vector<ResourceType*>, vector<ResourceType*>);
};
bool sortFunctionSpecies(Species *i, Species *j);
bool sortFunctionSpeciesID(Species *i, Species *j);
#endif /* SPECIES_H */

