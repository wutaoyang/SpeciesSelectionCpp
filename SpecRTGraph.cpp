/*
 * Species Selection
 * 
 * A bipartite graph representing the incidence structure between species 
 * and resource types (RTs)
 * Contains most of the important methods of the project
 */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include "SpecRTGraph.h"
#include "SpecTree.h"
#include "SpecSet.h"
#include "SpecTreeNode.h"
#include "Species.h"
#include "ResourceType.h"
#include "MinSpecSetFamily.h"
using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//The bipartite graph is represented by two 'adjacent' lists
//Here each species is associated with a list of resource types (RT), and
//each RT is associated with a list of species.

//vector<Species*> specNode;
//vector<ResourceType*> rtNode;

SpecRTGraph::SpecRTGraph() {
}

SpecRTGraph::~SpecRTGraph() {
}

void SpecRTGraph::addSpecNode(Species* inSpecies) {
   if (inSpecies->isIn(specNode) == false) {
      specNode.push_back(inSpecies);
   }
}

int SpecRTGraph::numSpecies() {
   return specNode.size();
}

int SpecRTGraph::numResourceTypes() {
   return rtNode.size();
}

void SpecRTGraph::addRTNode(ResourceType* newRT) {
   if (newRT->isIn(rtNode) == false) {
      rtNode.push_back(newRT);
   }
}

bool SpecRTGraph::containsSpecies(Species* spec) {
   return spec->isIn(specNode);
}

bool SpecRTGraph::containsResourceType(ResourceType* rt) {
   return rt->isIn(rtNode);
}

bool SpecRTGraph::noIsolatedResourceType() {
   for (ResourceType *rt : rtNode) {
      if (rt->numSpecies() == 0) {
         cout << "There is an isolated resource type.";
         return false;
      }
   }
   return true;
}

ResourceType* SpecRTGraph::getResourceTypeByID(int rtValue) {
   for (ResourceType *tmpRT : rtNode) {
      if (tmpRT->getID() == rtValue) {
         return tmpRT;
      }
   }
   return nullptr;
}

void SpecRTGraph::addEdge(Species* specEnd, ResourceType* rtEnd) {
   addSpecNode(specEnd);
   addRTNode(rtEnd);

   specEnd->addResourceType(rtEnd);
   rtEnd->addSpecies(specEnd);
}

SpecSetFamily* SpecRTGraph::getDomSpecSets(int setSize, int targetNum, MinSpecSetFamily* mssf) {
   mssf->sortBySensitivity();
   sort(rtNode.begin(), rtNode.end(), sortFunctionRT);

   SpecSetFamily *result = new SpecSetFamily();
   result->setNumSetsLimit(targetNum);

   int maxRTex = mssf->size();
   for (int i = 0; i < maxRTex; i++) {
      SpecSet *tmpSet = mssf->get(i);
      if (tmpSet->size() <= setSize) {
         SpecSetFamily *tmpFamily = tmpSet->extendToFamily(specNode, setSize, targetNum);
         result->addSpecSet(tmpFamily);
      }
   }
   return result;
}

//bool sortFunctionRT(ResourceType* i, ResourceType* j) { 
//   return i->compareTo(j) >= 0; 
//}

/**
 *
 * @param setSize The number of species in the species set
 * @param targetNum The number of species sets to be computed
 * @return A collection of species sets
 */
SpecSetFamily* SpecRTGraph::getDomSpecSets(int setSize, int targetNum) {
   MinSpecSetFamily *mssf = this->getMinDomSpecSets();
   return getDomSpecSets(setSize, targetNum, mssf);
}

/**
 * @return The collection of 'irreducible' dominated sets
 */
MinSpecSetFamily* SpecRTGraph::getMinDomSpecSets() {
   MinSpecSetFamily *result = new MinSpecSetFamily();

   ResourceType *minRT = this->getFirstEssentialResourceType();

   if (minRT == nullptr || minRT->noSpecies()) {
      cout << "There is something wrong with the minimal rticator, such as adjacent to no species.";
   }

   for (Species *spec : minRT->specList) {
      SpecTree *minTree = this->getMinimalConstSpecTreeRootedAt(spec);

      vector<SpecTreeNode*> leafList = minTree->getLeaves();

      for (SpecTreeNode *leaf : leafList) {
         vector<Species*> sp;
         sp = leaf->getAncestors();
         SpecSet *tmpSet = new SpecSet(sp);
         result->addSpecSet(tmpSet);
      }
   }
   return result;
}

SpecTree* SpecRTGraph::getMinSpecTree() {
   vector<ResourceType*> essRT = this->getEssentialResourceTypes();
   Species *root = essRT[0]->getFirstSpecies();
   return this->getMinimalConstSpecTreeRootedAt(root);
}

bool SpecRTGraph::isDominated(vector<Species*> specList, vector<ResourceType*> rtList) {
   return (getFirstNonDominatedRT(specList, rtList) == nullptr) ? true : false;
}

/**
 *
 * @param rootSpec A species
 * @return A minimal constitute species tree with root specified by rootSpec;
 * null if rootSpec is not a species
 */
SpecTree* SpecRTGraph::getMinimalConstSpecTreeRootedAt(Species* rootSpec) {
   if (!this->containsSpecies(rootSpec)) {
      return nullptr;
   }

   vector<ResourceType*> essRT = this->getEssentialResourceTypes();
   SpecTreeNode *rootNode = new SpecTreeNode(rootSpec);
   SpecTree *returnTree = new SpecTree(rootNode);

   while (getFirstNonCompleteLeaf(returnTree, essRT) != nullptr) {
      SpecTreeNode *curNode = getFirstNonCompleteLeaf(returnTree, essRT);
      ResourceType *curRT = getFirstNonDominatedRT(curNode->getAncestors(), essRT);

      vector<Species*> specList = curRT->specList;
      for (Species *spec : specList) {
         SpecTreeNode *tmpNode = new SpecTreeNode(spec);
         curNode->addChild(tmpNode);
      }
   }
   return returnTree;
}

SpecTreeNode* SpecRTGraph::getFirstNonCompleteLeaf(SpecTree* st, vector<ResourceType*> rtList) {
   vector<SpecTreeNode*> leafList = st->getLeaves();

   for (SpecTreeNode *stn : leafList) {
      if (getFirstNonDominatedRT(stn->getAncestors(), rtList) != nullptr) {
         return stn;
      }
   }
   return nullptr;
}

/**
 *
 * @param specList A collection of species node
 * @param rtList A collection of ResourceType node
 * @return The first RT that is not adjacent to any of the species in
 * specList, null if no such RT exists
 */
ResourceType* SpecRTGraph::getFirstNonDominatedRT(vector<Species*> specList, vector<ResourceType*> rtList) {
   //  System.out.println("getFirstNonDOminatedRT");
   // System.out.println("The species set is "+specList);
   // System.out.println("The rticator set is "+rtList);

   for (ResourceType *rt : rtList) {
      bool dominated = false;
      for (Species *spec : specList) {
         if (rt->adjacentTo(spec)) {
            dominated = true;
         }
      }
      if (dominated == false) {
         // System.out.println("The return rticator is "+rt);
         return rt;
      }
   }
   return nullptr;
}

ResourceType* SpecRTGraph::getFirstEssentialResourceType() {
   vector<ResourceType*> rtList = this->getEssentialResourceTypes();
   if (rtList.empty()) {
      return nullptr;
   }
   return rtList[0];
}

/**
 *
 * @return Return a set of essential rticators, when an rticator is essential
 * if it is not covered by other rticators
 */
vector<ResourceType*> SpecRTGraph::getEssentialResourceTypes() {
   //sorting the rticator list first
   sort(rtNode.begin(), rtNode.end(), sortFunctionRT);

   vector<ResourceType*> essRT;// = new vector<ResourceType>()

   int rtSize = numResourceTypes();

   for (int i = 0; i < rtSize; i++) {
      ResourceType *curRT = rtNode[i];
      bool essFlag = true; //false rtications no essential

      for (int j = i + 1; j < rtSize; j++) {
         if (curRT->isCoveredBy(rtNode[j])) {
            essFlag = false;
            break;
         }
      } //end for

      for (ResourceType *tmpRT : essRT) {
         if (curRT->isCoveredBy(tmpRT)) {
            essFlag = false;
            break;
         }
      }

      if (essFlag == true) {
         essRT.push_back(curRT);
      }
   }
   // System.out.println(essRT);
   return essRT;
}

vector<Species*> SpecRTGraph::getOneMinimalConstituteSpecies() {
   vector<Species*> conSpecList;
   vector<ResourceType*> essRTList = getEssentialResourceTypes();

   while (essRTList.size() != 0) {
      ResourceType *tmpRT = essRTList[0]; //get the first essRTList
      Species *tmpSpec = tmpRT->getFirstSpecies();
      conSpecList.push_back(tmpSpec);
      removeDomination(essRTList, tmpSpec);
   } //while

   // System.out.println(conSpecList);
   return conSpecList;
}

/**
 * @param rtList a list of rticators
 * @param spec a species After calling the method, the rticators in the list
 * which is 'adjacent' to the species are removed
 */
void SpecRTGraph::removeDomination(vector<ResourceType*> rtList, Species* spec) {
   removeAll(rtList, spec->rtList);
}

string SpecRTGraph::toString() {
   string outStr = "Species-ResourceType graph: \n ";
   for (Species *spec : specNode) {
      for (ResourceType *rt : rtNode) {
         if (rt->adjacentTo(spec)) {
            
            ostringstream oss;
            oss << "(" << spec->getName() << "," << rt->getID() << ") ";
            outStr += oss.str();
            
//            outStr.append("(").append(spec->getName());
//            outStr.append(",").append(rt->getID()).append(") ");
         }
      }
   }
   return outStr;
}

//https://stackoverflow.com/questions/28977799/c-equivalent-to-java-arraylist-method-removeall?rq=1
void SpecRTGraph::removeAll(vector<ResourceType*>& vec, const vector<ResourceType*>& toRemove) {
   set<ResourceType*> st(toRemove.begin(), toRemove.end());
   size_t newSize = 0;
   for (size_t i = 0; i < vec.size(); ++i) {
      if (0 == st.count(vec[i])) {
         vec[newSize++] = vec[i];
      }
   }
   vec.resize(newSize);
}