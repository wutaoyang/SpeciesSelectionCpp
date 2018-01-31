/* 
 * File:   SpecTree.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 14:53
 */

#ifndef SPECTREE_H
#define SPECTREE_H

#include <vector>
#include <string>
using namespace std;

class SpecTreeNode;

class SpecTree {
public:
   SpecTree();
   SpecTree(SpecTreeNode*);
   ~SpecTree();
   SpecTreeNode* getRoot();
   int size();
   vector<SpecTreeNode*> getLeaves();
   string toString();
private:
   SpecTreeNode* root;
};

#endif /* SPECTREE_H */

