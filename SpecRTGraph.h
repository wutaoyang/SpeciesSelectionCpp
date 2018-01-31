/* 
 * File:   SpecRTGraph.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:52
 */


#ifndef SPECRTGRAPH_H
#define SPECRTGRAPH_H

#include <vector>
#include <string>
using namespace std;

class Species;
class ResourceType;
class SpecSetFamily;
class MinSpecSetFamily;
class SpecTree;
class SpecTreeNode;

class SpecRTGraph {
protected:
   vector<Species*> specNode;
   vector<ResourceType*> rtNode;
public:
   SpecRTGraph();
   ~SpecRTGraph();
   void addSpecNode(Species*);
   int numSpecies();
   int numResourceTypes();
   void addRTNode(ResourceType*);
   bool containsSpecies(Species*);
   bool containsResourceType(ResourceType*);
   bool noIsolatedResourceType();
   ResourceType* getResourceTypeByID(int);
   void addEdge(Species*, ResourceType*);
   SpecSetFamily* getDomSpecSets(int, int, MinSpecSetFamily*);
   SpecSetFamily* getDomSpecSets(int, int);
   MinSpecSetFamily* getMinDomSpecSets();
   SpecTree* getMinSpecTree();
   SpecTree* getMinimalConstSpecTreeRootedAt(Species*);
   vector<ResourceType*> getEssentialResourceTypes();
   vector<Species*> getOneMinimalConstituteSpecies();
   string toString();
private:
   bool isDominated(vector<Species*>, vector<ResourceType*>);
   SpecTreeNode* getFirstNonCompleteLeaf(SpecTree*, vector<ResourceType*>);
   ResourceType* getFirstNonDominatedRT(vector<Species*>, vector<ResourceType*>);
   ResourceType* getFirstEssentialResourceType();
   void removeDomination(vector<ResourceType*>, Species*);
   void removeAll(vector<ResourceType*>&, const vector<ResourceType*>&);
};

#endif /* SPECRTGRAPH_H */

