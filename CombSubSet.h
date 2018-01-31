/* 
 * File:   CombSubSet.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 11:36
 */

#ifndef COMBSUBSET_H
#define COMBSUBSET_H

#include <vector>  //for std::vector
#include <string>  //for std::string
using namespace std;

class CombSubSet {
protected:
   //store all subsets with given cardSize and all elements bounded above by 
   // maxNumber (not included) and below by zero (included)
   vector<vector<int>> subSets;

public:
   CombSubSet(int, int);
   ~CombSubSet();
   vector<vector<int>> getSubSets();
   string toString();
private:
   int maxNumber;
   int cardSize;
   void initialize();
   
};

#endif /* COMBSUBSET_H */

