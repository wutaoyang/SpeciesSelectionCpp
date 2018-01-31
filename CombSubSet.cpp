/* 
 * File:   CombSubSet.cpp
 * Author: mre16utu
 * 
 * Created on 15 January 2018, 11:36
 */

#include "CombSubSet.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;


/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

int maxNumber;
int cardSize;
vector<vector<int>> subSets;

CombSubSet::CombSubSet(int cardSize, int maxNumber) {
   //to throw exceptions
   if (cardSize > maxNumber) {
      cout << "Something about the permutation is wrong";
   }
   this->cardSize = cardSize;
   this->maxNumber = maxNumber;
   initialize();
}

CombSubSet::~CombSubSet() {
}

vector<vector<int>> CombSubSet::getSubSets() {
   return subSets;
}

void CombSubSet::initialize() {

   //case 1
   if (cardSize == maxNumber) {
      vector<int> tmpSet;
      for (int i = 0; i < maxNumber; i++) {
         tmpSet.push_back(i);
      }
      subSets.push_back(tmpSet);
      return;
   }

   //case 2
   if (cardSize == 1) {
      for (int i = 0; i < maxNumber; i++) {
         vector<int> tmpSet;
         tmpSet.push_back(i);
         subSets.push_back(tmpSet);
      }
      return;
   }

   //the case for 1<cardSize<maxNumber 
   for (int i = cardSize; i <= maxNumber; i++) {
//      CombSubSet tmpSetFamily = new CombSubSet(cardSize - 1, i - 1);
      CombSubSet tmpSetFamily(cardSize - 1, i - 1);
      
      vector<vector<int>> tmpSets = tmpSetFamily.getSubSets();
      for (vector<int> intList : tmpSets) {
         intList.push_back(i - 1);
         subSets.push_back(intList);
      }
   }
}

string CombSubSet::toString(){
   string str = "[";

   for (vector<int> subSet : subSets)
   {
      if (!subSet.empty())
      {
         str.append("[");
         ostringstream oss;
         copy(subSet.begin(), subSet.end()-1, ostream_iterator<int>(oss, ", "));
         oss << subSet.back();

         str.append(oss.str() + "], ");
      }
   }
   if(subSets.size() > 1 && str.length() > 2){
      str = str.substr(0, str.length()-2);// trim last ', ' from string
   }
   str.append("]");
   return str;
}