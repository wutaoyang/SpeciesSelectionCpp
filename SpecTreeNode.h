/* 
 * File:   SpecTreeNode.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:53
 */

#ifndef SPECTREENODE_H
#define SPECTREENODE_H

#include <vector>
#include <string>
using namespace std;

class Species;

class SpecTreeNode {
protected:
   Species* spec;
   SpecTreeNode* parent;
   vector<SpecTreeNode*> chList;
public:
   SpecTreeNode();
   SpecTreeNode(Species*);
   ~SpecTreeNode();
   void setSpecies(Species*);
   Species* getSpecies();
   void setParent(SpecTreeNode*);
   SpecTreeNode* getParent();
   void addChild(SpecTreeNode*);
   void removed();
   bool hasChild(SpecTreeNode*);
   bool isLeaf();
   bool isRoot();
   int getLevel();
   vector<Species*> getAncestors();
   vector<SpecTreeNode*> getLeavesBelow();
   bool isAncestor(Species*);
   int numNodesBelow();
   string toString();
private:
   bool isIn(vector<SpecTreeNode*>);
};

#endif /* SPECTREENODE_H */

