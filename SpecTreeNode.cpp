/*
 * Indicator Species Selection
 * 
 * Represents a node in class SpecTree
 */


#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "SpecTreeNode.h"
#include "Species.h"
using namespace std;


/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */
//Species *spec;
//SpecTreeNode *parent;
//vector<SpecTreeNode*> chList;

SpecTreeNode::SpecTreeNode() {
   spec = nullptr;
   parent = nullptr;
}

SpecTreeNode::SpecTreeNode(Species* spec) {
   this->spec = spec;
   parent = nullptr;
}

SpecTreeNode::~SpecTreeNode() {
}

void SpecTreeNode::setSpecies(Species* spec) {
   this->spec = spec;
}

Species* SpecTreeNode::getSpecies() {
   return spec;
}

void SpecTreeNode::setParent(SpecTreeNode* parent) {
   this->parent = parent;
}

SpecTreeNode* SpecTreeNode::getParent() {
   return parent;
}

// returns true if this ResourceType is in list
bool SpecTreeNode::isIn(vector<SpecTreeNode*> list) {
   return find(list.begin(), list.end(), this) != list.end();
}

void SpecTreeNode::addChild(SpecTreeNode* chSpec) {

   chSpec->setParent(this);

   if (!chSpec->isIn(chList)) {
      chList.push_back(chSpec);
   }
}

void SpecTreeNode::removed() {
   if (parent != nullptr) {
      auto i = find(begin(parent->chList), end(parent->chList), this);
      parent->chList.erase(i);
//      parent->chList.erase(this);
      parent = nullptr;
   }
   spec = nullptr;
   chList.clear();
}

bool SpecTreeNode::hasChild(SpecTreeNode* chSpec) {
   return chSpec->isIn(chList);
}

bool SpecTreeNode::isLeaf() {
   return (chList.empty()) ? true : false;
}

bool SpecTreeNode::isRoot() {
   return (parent == nullptr) ? true : false;
}

int SpecTreeNode::getLevel() {
   int level = 1;
   if (parent != nullptr) {
      level += parent->getLevel();
   }
   return level;
}

vector<Species*> SpecTreeNode::getAncestors() {
   vector<Species*> result;
   result.push_back(spec);
   if (parent != nullptr) {
      vector<Species*> ancestors = parent->getAncestors();
      result.insert(result.end(), ancestors.begin(), ancestors.end());
   }
   return result;
}

/**
 *
 * @return the collection of leave nodes below the current one
 */
vector<SpecTreeNode*> SpecTreeNode::getLeavesBelow() {
   vector<SpecTreeNode*> result;
   if (isLeaf()) {
      result.push_back(this);
   }
   for (SpecTreeNode *stn : chList) {
      vector<SpecTreeNode*> leaves = stn->getLeavesBelow();
      result.insert(result.end(), leaves.begin(), leaves.end());
   }
   return result;
}

/**
 * @param spec A species
 * @return true if the species is contained in an ancestor of the node
 * (including itself), false otherwise.
 */
bool SpecTreeNode::isAncestor(Species* spec) {
   if (getSpecies() == spec) {
      return true;
   }
   if (isRoot()) {
      return false;
   }
   return (parent->isAncestor(spec));
}

int SpecTreeNode::numNodesBelow() {
   if (this == nullptr) {
      return 0;
   }
   int result = 1;
   for (SpecTreeNode *stn : chList) {
      result += stn->numNodesBelow();
   }
   return result;
}

string SpecTreeNode::toString() {
   string outStr = "";
   if (isRoot() && isLeaf()) {
      outStr.append("(").append(spec->getName() + ")");
      return outStr;
   }

   ostringstream oss;
   oss << this->getLevel();
   string level = oss.str();
   if (isLeaf()) {
      outStr.append(spec->getName()).append("~").append(level).append(",");
   } else {
      outStr.append("(").append(spec->getName()).append(":").append(level);
      outStr.append("(");
      for (SpecTreeNode *sp : chList) {
         outStr.append(sp->toString()).append("|");
      }
      outStr.append(")");
      outStr.append(")");
   }
   return outStr;
}