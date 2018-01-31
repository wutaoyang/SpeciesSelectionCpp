/* 
 * File:   MinSpecSetFamily.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 13:54
 */

#ifndef MINSPECSETFAMILY_H
#define MINSPECSETFAMILY_H

#include "SpecSet.h"
#include <vector>
#include <string>
using namespace std;

class MinSpecSetFamily {
public:
   MinSpecSetFamily();
   ~MinSpecSetFamily();
   int size();
   SpecSet* get(int);
   void sortBySensitivity();
   bool addSpecSet(SpecSet*);
   string toString();
   
private:
   vector<SpecSet*> ssf;
   void removeAll(vector<SpecSet*>&, const vector<SpecSet*>&);
};

#endif /* MINSPECSETFAMILY_H */

