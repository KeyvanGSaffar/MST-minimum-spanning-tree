#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include "function.hpp"
#include <cmath>
#include <string.h>   //to use memset
using namespace std;

int main(){
  const int Pth = 1;
  // const string n = "n";
  // int sq_area = 400;  // square area with this value as side length
  int n_num[] = {5,15,25,-1};//{5,15,25,35,45,65,85,105,125,145,170,190,200,-1};    // number of nodes
  double cost_vec[13];
  int alpha = 2;  // pathloss exponent
  int round = 100; // number of rounds for each number of nodes (n_num)
  algorithm_CA(Pth,alpha,round,n_num,cost_vec);
  return 0;
}




