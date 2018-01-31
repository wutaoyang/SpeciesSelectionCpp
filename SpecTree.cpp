/*
 * Indicator Species Selection
 * 
 * The tree structure used to compute all possible 'irreducible' species sets
 * that is, those species sets covering all resource types while any proper 
 * subset does not
 */


#include <vector>
#include <string>
#include "SpecTree.h"
#include "SpecTreeNode.h"
using namespace std;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//SpecTreeNode *root;

SpecTree::SpecTree() {
   root = nullptr;
}

SpecTree::SpecTree(SpecTreeNode* root) {
   this->root = root;
}

SpecTree::~SpecTree() {
}

SpecTreeNode* SpecTree::getRoot() {
   return root;
}

int SpecTree::size() {
   return root->numNodesBelow();
}

vector<SpecTreeNode*> SpecTree::getLeaves() {
   return root->getLeavesBelow();
}

string SpecTree::toString() {
   string outStr = "Spec tree: \n";
   outStr.append(this->getRoot()->toString());
   return outStr;
}
