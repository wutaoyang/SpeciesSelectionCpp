/*
 * Indicator Species Selection
 * 
 * The class is designed to find the smallest positive number $n$ such that the binomial 
 * coefficient ${n choose k}$ is larger than or equal to $m$.
 * Here $m$ is specified by numSubSets and $k$ by setSize
 */

#include "CombSize.h"
int numSubSets;
int setSize;

/**
 * @author taoyang wu @UEA (taoyang.wu@uea.ac.uk)
 * Converted to C++ by stephen whiddett (mre16utu@uea.ac.uk)
 */

//Constructor
CombSize::CombSize(int setSize, int numSubSets) {
   this->numSubSets = numSubSets;
   this->setSize = setSize;
}

//Destructor
CombSize::~CombSize() {
}

/**
 * @return The smallest positive number $n$ such that the binomial 
 * coefficient ${n choose k}$ is larger than or equal to $m$.
 * Here $m$ is specified by numSubSets and $k$ by setSize
 */
int CombSize::getSize() {
   int result = setSize;
   while (binCoeff(setSize, result) < numSubSets) {
      result++;
   }
   return result;
}

/*           
 * return The binomial coefficient ${n choose k}$ 
 */
int CombSize::binCoeff(int k, int n) {
   if (k == 0) return 1;
   if (2 * k > n) return binCoeff(n - k, n);

   int result = n - k + 1;

   for (int i = result + 1; i <= n; i++) {
      result *= i;
   }

   for (int j = 2; j <= k; j++) {
      result /= j;
   }

   return result;
}