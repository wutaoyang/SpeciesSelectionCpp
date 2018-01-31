/* 
 * File:   CombSize.h
 * Author: mre16utu
 *
 * Created on 15 January 2018, 10:39
 */

#ifndef COMBSIZE_H
#define COMBSIZE_H

class CombSize 
{
protected:
   int numSubSets;  
   int setSize;
public:
   CombSize(int, int);
   ~CombSize();
   int getSize();
private:
   int binCoeff(int, int);
};

#endif /* COMBSIZE_H */

